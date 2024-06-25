 #ifndef BussinessServerModule
 #define BussinessServerModule
#include "../../cmake/build/logprog.grpc.pb.h"
#include<memory>
#include "../log/log.h"
using namespace logprog::v1;
using namespace logModule;
 class BussinessServer {
    public:
    BussinessServer() {}
    BussinessServer(Logging::Service *service);
    //   BussinessServer(BussinessServer&& other) {

    //     server = std::move(other.server);
        
    //     std::cout << "Moving Constructor " << std::endl;
    // }
    //     BussinessServer& operator=(BussinessServer&& other) {
    //     if (this != &other) {
    //         server = std::move(other.server);
    //         service = other.service;
    //         std::cout << "Move Assignment Operator" << std::endl;
    //     }
        // return *this;
    // }


    void RunServer(std::string server_address);
    void ShutServer();
    Logging::Service * GetService();
    Logging::Service *service;
    std::unique_ptr< grpc::Server> server;
 };

 
 

class LogImplementation final : public Logging::Service {
public:
    LogImplementation(Log *CommitLog);

    grpc::Status Produce(grpc::ServerContext* context, const ProduceRequest* request, ProduceResponse* reply) override;

    grpc::Status Consume(grpc::ServerContext* context, const ConsumeRequest* request, ConsumeResponse* response) override;

    grpc::Status ProduceStream(grpc::ServerContext* context, grpc::ServerReaderWriter<ProduceResponse, ProduceRequest>* stream) override;

    grpc::Status ConsumeStream(grpc::ServerContext* context, const ConsumeRequest* req, grpc::ServerWriter<ConsumeResponse>* writer) override;

private:
    Log *commitLog_;
};

 
 #endif