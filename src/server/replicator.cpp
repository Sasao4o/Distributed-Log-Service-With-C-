#include <grpcpp/grpcpp.h>
#include <thread>
#include <map>
#include <mutex>
#include <condition_variable>
#include "../../cmake/build/logprog.grpc.pb.h"

using namespace logprog::v1;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientReaderWriter;
//using grpc::ClientReader;

class Replicator {
public:
    std::unique_ptr<Logging::Stub> LocalClient;
    std::mutex mu;
    std::map<std::string, std::shared_ptr<std::condition_variable>> servers;
    bool closed = false;
    std::shared_ptr<std::condition_variable> close;

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

        std::thread(&Replicator::replicate, this, addr, servers[name]).detach();
    }

    void replicate(const std::string& addr, std::shared_ptr<std::condition_variable> leave) {
        auto channel = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
        std::unique_ptr<Logging::Stub> client = Logging::NewStub(channel);

        ClientContext context;
        ConsumeRequest request;
        request.set_offset(0);

        std::shared_ptr<grpc::ClientReader<ConsumeResponse>> stream(
            client->ConsumeStream(&context, request));

        if (!stream) {
            //logError("failed to consume", addr);
            std::cerr << "failed to consume" << std::endl;
            return;
        }

        //std::vector<Record> records;

        while (true) {
            

            ConsumeResponse response;
            if (!stream->Read(&response)) {
                //logError("failed to receive", addr);
                std::cerr << "failed to receive" << std::endl;
                return;
            }
            //records.push_back(response.record());

            //for (auto& record : records) {
            ProduceRequest produce_request;
            Record * rec = new Record();
            rec->set_value(response.record().value());
            rec->set_offset(response.record().offset());
            produce_request.set_allocated_record(rec);
            ClientContext produce_context;
            Status status = LocalClient->Produce(&produce_context, produce_request, nullptr);
            if (!status.ok()) {
                //logError("failed to produce", addr);
                std::cerr << "failed to produce" << std::endl;
                return;
            }

            std::unique_lock<std::mutex> lock(mu);
            // If this client (We are consuming from) notifies its leave we will break or We closed ofcourse 
            if (closed || leave->wait_for(lock, std::chrono::milliseconds(150)) == std::cv_status::timeout) {
                break;
            }
            //}
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

private:
    void init(std::string address) {

        auto channel = grpc::CreateChannel(address, grpc::InsecureChannelCredentials());
        LocalClient = Logging::NewStub(channel);

        if (servers.empty()) {
            servers = std::map<std::string, std::shared_ptr<std::condition_variable>>();
        }
        if (!close) {
            close = std::make_shared<std::condition_variable>();
        }
    }

    // void logError(const std::string& msg, const std::string& addr) {
    //     logger->Error(msg, {{"addr", addr}});
    // }
};
