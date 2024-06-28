#include <grpcpp/grpcpp.h>
#include <thread>
#include <map>
#include <mutex>
#include <condition_variable>
#include "../../include/server/client.h"
#include "../../include/replicator/replicator.h"

#include "../../cmake/build/logprog.grpc.pb.h"

using namespace logprog::v1;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientReaderWriter;
//using grpc::ClientReader;

 
    Replicator::Replicator(MyClient client) {
        init(client);
    }

    void Replicator::Join(std::string& name, std::string& addr)  {
        std::lock_guard<std::mutex> lock(mu);
        //init();

        if (closed) {
            return;
        }

        if (servers.find(name) != servers.end()) {
            // already replicating so skip

            return;
        }
        
        servers[name] = std::make_shared<std::condition_variable>();
   
        std::thread th(&Replicator::replicate,this,addr, servers[name]);
        th.join();
    }

    void Replicator::replicate(const std::string& addr, std::shared_ptr<std::condition_variable> leave) {
        std::cout << "Replicating..." << std::endl;
        records.clear();
        auto channel = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
        std::unique_ptr<Logging::Stub> client = Logging::NewStub(channel);

        ClientContext context;
        ConsumeRequest request;
        ConsumeResponse response;
        request.set_offset(0);

        std::shared_ptr<grpc::ClientReader<ConsumeResponse>> stream(
            client->ConsumeStream(&context, request));

   
        if (!stream) {
            //logError("failed to consume", addr);
            std::cerr << "failed to consume" << std::endl;
            return;
        }

        while (true) {
        
            if(stream->Read(&response)){
 
                records.push_back(response.record());
            } 
            else {
 
                break;
            }
                
            // records.push_back(response.record());

            // std::unique_lock<std::mutex> lock(mu);
            // If this client (We are consuming from) notifies its leave we will break or We closed ofcourse 
            // || leave->wait_for(lock, std::chrono::milliseconds(150)) == std::cv_status::timeout
            // if (closed) {
                // return;
            // }
            //}
        }
        for(auto& record : records){
            LocalClient.Produce(record.value());
        }
    }

    void Replicator::Leave( std::string& name)  {
        std::lock_guard<std::mutex> lock(mu);
        if (servers.find(name) == servers.end()) {
            return;
        }

        servers[name]->notify_all();
        servers.erase(name);
    }

    void Replicator::Close() {
        std::lock_guard<std::mutex> lock(mu);

        if (closed) {
            return;
        }

        closed = true;
        //m4 moktn3 b close as a cv hna
        close->notify_all();
    }

    MyClient Replicator::getLocalClient(){
        return LocalClient;
    }
 
    void Replicator::init(MyClient client) {
        // LocalClient = new MyClient(grpc::CreateChannel(address, grpc::InsecureChannelCredentials()));
        LocalClient = client;
        if (servers.empty()) {
            servers = std::map<std::string, std::shared_ptr<std::condition_variable>>();
        }
        if (!close) {
            close = std::make_shared<std::condition_variable>();
        }
    }

 