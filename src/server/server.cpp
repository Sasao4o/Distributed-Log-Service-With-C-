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
using grpc::ServerWriter;
// Server Implementation
 uint64_t x = 0;
class LogImplementation final : public Logging::Service {
  public:
  LogImplementation(Log *CommitLog) : commitLog_(CommitLog) {};

  Status Produce(ServerContext* context, const ProduceRequest* request,
                     ProduceResponse* reply) override {
    // Obtains the original string from the request
    Record  rec = request->record();
    uint64_t *offset = new uint64_t();

    bool ok = commitLog_->Append(&rec, offset);
    std::cout << rec.value() << std::endl;
    if (ok == false){
      return Status::CANCELLED;
    }
    reply->set_offset(*offset);

    delete offset;
    return Status::OK;
  }

  Status Consume(ServerContext* context, const ConsumeRequest* request,
                     ConsumeResponse* response) override {
    // Obtains the original string from the request
    uint64_t offset = request->offset();

  std::cout << "offset is " << offset << std::endl;
    Record * record  = commitLog_->Read(offset);
    if (record == nullptr) {
      std::cout << "Record is nullptr " << std::endl;
      return Status::CANCELLED;
    }

    response->set_allocated_record(record);

    
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


Status ConsumeStream(ServerContext* context,const ConsumeRequest* req,  ServerWriter<ConsumeResponse>* writer) override {
          uint64_t offset = req->offset();
            while (1) {
             
            ConsumeResponse res;
             ConsumeRequest newReq;
            newReq.set_offset(offset);
            Status status = Consume(context, &newReq, &res);
            if (status.ok()) {
                if (!writer->Write(res)) {
                    return grpc::Status(grpc::StatusCode::INTERNAL, "Failed to write response");
                }
                 offset++;
            } else {
              continue;
            }
            // else if (status.error_code() == grpc::StatusCode::NOT_FOUND) {
            //   std::cout << "NO FOUND " << std::endl;
            //     continue;
            // } else {
            //     return status;
            // }
            if (context->IsCancelled()) {
              std::cout << "Context is Cancelled " << std::endl;
                break;
            }
        }
        return grpc::Status::OK;

  }


Log * commitLog_;
};


   
void RunServer() {
  std::string server_address("0.0.0.0:50051");
  Config b;
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
