 #include <grpcpp/grpcpp.h>
#include <string>
#include "../../cmake/build/logprog.grpc.pb.h"
#include "../../include/log/log.h"
#include<iostream>
using grpc::ServerBuilder; 
using namespace logprog::v1;
using namespace logModule;
using grpc::Server;
using grpc::Channel;
using grpc::ServerContext;
using grpc::Status;
using grpc::ServerReaderWriter;
// Server Implementation
 uint64_t x = 0;
class LogImplementation final : public Logging::Service {
  public:
  LogImplementation(Log *CommitLog) : commitLog_(CommitLog) {};

  Status Produce(ServerContext* context, const ProduceRequest* request,
                     ProduceResponse* reply) override {
    // Obtains the original string from the request
    Record  rec = request->record();
<<<<<<< HEAD
    // commitLog_->Append(&rec);
    Record * recADD = &rec;
     commitLog_->Append(recADD);
    std::cout << recADD->value() << std::endl;
=======
    uint64_t *offset = new uint64_t();
>>>>>>> origin/WaelBranch

    bool ok = commitLog_->Append(&rec, offset);
    std::cout << rec.value() << std::endl;
    if (ok == false){
      return Status::CANCELLED;
    }
    reply->set_offset(*offset);

    delete offset;
    return Status::OK;
  }

  Status ProduceStream(
        ServerContext* context,
        ServerReaderWriter<ProduceResponse, ProduceRequest>* stream
    ) override {
        ProduceRequest req;
        ProduceResponse res;

        while (stream->Read(&req)) {
            Status status = Produce(context, &req, &res);

            if (!status.ok()) {
                return status;
            }

            if (!stream->Write(res)) {
                return Status::CANCELLED;
            }
        }

        return Status::OK;
    }
Log * commitLog_;
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  Config b;
<<<<<<< HEAD
  b.InitialOffset = 0;
=======
>>>>>>> origin/WaelBranch
  Log lg("../../logsData", b);
  lg.SetUp();
  LogImplementation service(&lg);
 
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which
  // communication with client takes place
  builder.RegisterService(&service);
  // Assembling the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on port: " << server_address << std::endl;

  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();
  return 0;
}
