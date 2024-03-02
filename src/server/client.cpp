  #include <grpcpp/grpcpp.h>
#include <string>
 
#include "../../cmake/build/logprog.grpc.pb.h"
  
  using namespace logprog::v1;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

  class MyClient {
 public:
  MyClient(std::shared_ptr<Channel> channel)
      : stub_(Logging::NewStub(channel)) {}

  // Assembles client payload, sends it to the server, and returns its response
  ProduceResponse Produce(std::string a) {
    // Data to be sent to server
    Record  * myRecord = new Record();
    myRecord->set_value("mostafa");
    ProduceRequest request;
    request.set_allocated_record(myRecord);

    // Container for server response
    ProduceResponse reply;

    // Context can be used to send meta data to server or modify RPC behaviour
    ClientContext context;

    // Actual Remote Procedure Call
    Status status = stub_->Produce(&context, request, &reply);

    // Returns results based on RPC status
    if (status.ok()) {
      return reply;
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      
    }
  }

 private:
  std::unique_ptr<Logging::Stub> stub_;
};

  int main() {
    std::string target_address("0.0.0.0:50051");
  // Instantiates the client
  MyClient client(
      // Channel from which RPCs are made - endpoint is the target_address
      grpc::CreateChannel(target_address,
                          // Indicate when channel is not authenticated
                          grpc::InsecureChannelCredentials()));

  ProduceResponse response;
  std::string a = "grpc is cool!";

  // RPC is created and response is stored
  response = client.Produce(a);

  // Prints results
  std::cout << "Offset is: " << response.offset() << std::endl;
  // std::cout << "Reversed string: " << response << std::endl;

 }