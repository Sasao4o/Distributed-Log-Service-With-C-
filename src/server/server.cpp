 #include <grpcpp/grpcpp.h>
#include <string>
#include "../../cmake/build/logprog.grpc.pb.h"
#include "../../include/log/log.h"
#include<iostream>
#include "../../include/server/server.h"
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
 
   
  LogImplementation::LogImplementation(Log *CommitLog) : commitLog_(CommitLog) {};

  Status LogImplementation::Produce(ServerContext* context, const ProduceRequest* request,
                     ProduceResponse* reply)  {
    // Obtains the original string from the request
    Record  rec = request->record();
    uint64_t *offset = new uint64_t();

     commitLog_->Append(&rec, offset);
 
    // if (ok == false){
    //   return Status::CANCELLED;
    // }
    reply->set_offset(*offset);

    delete offset;
    return Status::OK;
  }

  Status LogImplementation::Consume(ServerContext* context, const ConsumeRequest* request,
                     ConsumeResponse* response)  {
    // Obtains the original string from the request
    uint64_t offset = request->offset();

 
  try {
    Record * record  = commitLog_->Read(offset);
      response->set_allocated_record(record);
  } 
  catch (const std::runtime_error& e) {
 
      return Status::CANCELLED;
  }
    // if (record == nullptr) {
    //   std::cout << "Record is nullptr " << std::endl;
    //   return Status::CANCELLED;
    // }

    // response->set_allocated_record(record);

    
    return Status::OK;
  }
  
  

  
  
  Status LogImplementation::ProduceStream(
        ServerContext* context,
        ServerReaderWriter<ProduceResponse, ProduceRequest>* stream
    )  {
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


Status LogImplementation::ConsumeStream(ServerContext* context,const ConsumeRequest* req,  ServerWriter<ConsumeResponse>* writer)  {
          uint64_t offset = req->offset();
          
            while (1) {
 
            ConsumeResponse res;
             ConsumeRequest newReq;
            newReq.set_offset(offset);
            Status status = Consume(context, &newReq, &res);
            if (status.ok()) {
              std::cerr<<"WRITING RESPONSE  :: "<< res.record().value() <<std::endl;
                writer->Write(res);
                 offset++;
            } else {
              std::cerr << "Consume failed with error: " << status.error_message() << std::endl;
              break;
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

           if (context->IsCancelled()) {
              std::cout << "Context is Cancelled " << std::endl;
        
            }
   
        return grpc::Status::OK;

  }


 

 
 
BussinessServer::BussinessServer(Logging::Service *service) {
 this->service = service;
}
void BussinessServer::RunServer(std::string server_address) {
  //std::string server_address("0.0.0.0:50051");

  
 
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which
  // communication with client takes place
  builder.RegisterService(service);
  // Assembling the server
    // std::unique_ptr<Server> server(builder.BuildAndStart());
    server = std::unique_ptr<Server>(builder.BuildAndStart());
  std::cout << "Server listening on port: " << server_address << std::endl;
  running = true;
  server->Wait();
 
  running = false;


}
 
  void BussinessServer::ShutServer() {
    std::cout << "Shut Downning the Server" << std::endl;
    if (!running) {
      std::cout <<  "Server is Already Off" << std::endl;
    }
   
    if (server != nullptr) {
      server->Shutdown();
    }
    }
 Logging::Service * BussinessServer::GetService() {
  return service;
 }


 //Record is nullptr mtb3t4