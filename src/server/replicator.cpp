#include <grpcpp/grpcpp.h>
#include <thread>
#include <map>
#include <mutex>
#include <condition_variable>
#include "../../include/server/client.h"
#include "../../cmake/build/logprog.grpc.pb.h"

using namespace logprog::v1;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientReaderWriter;
//using grpc::ClientReader;

class Replicator {
public:

    std::vector<Record> records;

    Replicator(std::string address) {
        init(address);
    }

    void Join(const std::string& name, const std::string& addr) {
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
        std::cout<<"HERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRE"<< std::endl;
        std::thread(&Replicator::replicate,this,addr, servers[name]).detach();
    }

    void replicate(const std::string& addr, std::shared_ptr<std::condition_variable> leave) {
        auto channel = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
        std::unique_ptr<Logging::Stub> client = Logging::NewStub(channel);

        ClientContext context;
        ConsumeRequest request;
        ConsumeResponse response;
        request.set_offset(0);

        std::shared_ptr<grpc::ClientReader<ConsumeResponse>> stream(
            client->ConsumeStream(&context, request));

        std::cout<<"REPLI_____________HERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRE"<< std::endl;
        if (!stream) {
            //logError("failed to consume", addr);
            std::cerr << "failed to consume" << std::endl;
            return;
        }

        while (true) {
        
            if(stream->Read(&response)){
                std::cout << "Response is " << response.record().value() << std::endl;
            } else {
                std::cout << "No response" << std::endl;
                break;
            }
                
            records.push_back(response.record());

            std::unique_lock<std::mutex> lock(mu);
            // If this client (We are consuming from) notifies its leave we will break or We closed ofcourse 
            if (closed || leave->wait_for(lock, std::chrono::milliseconds(150)) == std::cv_status::timeout) {
                return;
            }
            //}
        }
        for(auto& record : records){
            LocalClient->Produce(record.value());
        }
    }

    void Leave(const std::string& name) {
        std::lock_guard<std::mutex> lock(mu);
        if (servers.find(name) == servers.end()) {
            return;
        }

        servers[name]->notify_all();
        servers.erase(name);
    }

    void Close() {
        std::lock_guard<std::mutex> lock(mu);

        if (closed) {
            return;
        }

        closed = true;
        //m4 moktn3 b close as a cv hna
        close->notify_all();
    }

    MyClient* getLocalClient(){
        return LocalClient;
    }
private:
    void init(std::string address) {
        LocalClient = new MyClient(grpc::CreateChannel(address, grpc::InsecureChannelCredentials()));

        if (servers.empty()) {
            servers = std::map<std::string, std::shared_ptr<std::condition_variable>>();
        }
        if (!close) {
            close = std::make_shared<std::condition_variable>();
        }
    }

    MyClient* LocalClient;
    std::mutex mu;
    std::map<std::string, std::shared_ptr<std::condition_variable>> servers;
    bool closed = false;
    std::shared_ptr<std::condition_variable> close;
    // void logError(const std::string& msg, const std::string& addr) {
    //     logger->Error(msg, {{"addr", addr}});
    // }
};
