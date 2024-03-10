  #include <grpcpp/grpcpp.h>
#include <string>
 
#include "../../cmake/build/logprog.grpc.pb.h"
#include "../../include/server/client.h"
using namespace logprog::v1;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientReaderWriter;
 
 
  MyClient::MyClient(std::shared_ptr<Channel> channel)
      : stub_(Logging::NewStub(channel)) {}

  // Assembles client payload, sends it to the server, and returns its response
  ProduceResponse MyClient::Produce(std::string a) {
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
      std::cout << "Produce Failed" << std::endl;
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      
    }
  }

    ConsumeResponse MyClient::Consume(uint64_t offset) {
    ConsumeRequest request;
    request.set_offset(offset);
    // Container for server response
    ConsumeResponse reply;

    // Context can be used to send meta data to server or modify RPC behaviour
    ClientContext context;

    // Actual Remote Procedure Call
    Status status = stub_->Consume(&context, request, &reply);

    // Returns results based on RPC status
    if (status.ok()) {
      return reply;
    } else {
      std::cout << "Consume Failed" << std::endl;
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      
    }
  }



   
   
  void MyClient::ProduceStream(std::vector<Record*> &records) {
        ProduceRequest request;
        ProduceResponse response;

        ClientContext context;
        std::shared_ptr<ClientReaderWriter<ProduceRequest, ProduceResponse>> stream(
        stub_->ProduceStream(&context));

        for (auto record:records){
          request.set_allocated_record(record);
          stream->Write(request);
        }
        stream->WritesDone();
        
        while (stream->Read(&response)) {
            // Process the received response
            std::cout << "Received response: " << response.offset() << std::endl;
        }
        
        Status status = stream->Finish();
        if (!status.ok()) {
            std::cerr << "RPC failed: " << status.error_message() << std::endl;
        }
        // delete myRecord;
        // delete myRecord_2;
        // return response;
  }

  void MyClient::ConsumeStream(uint64_t offset) {
     ConsumeRequest request;
    request.set_offset(offset);
    // Container for server response
    ConsumeResponse response;

    // Context can be used to send meta data to server or modify RPC behaviour
    ClientContext context;
   std::shared_ptr<grpc::ClientReader<ConsumeResponse>> stream(
            stub_->ConsumeStream(&context, request));

    // Actual Remote Procedure Call
     while(1) {
      if (stream->Read(&response)){
       std::cout << "Response is " << response.record().value() << std::endl;
     }
     }
  // Status status = stream->Finish();
  //   // Returns results based on RPC status
  //   if (status.ok()) {
  //    std::cout << "Consume Success" << std::endl;
  //    std::cout << "Response is " << response.record().value() << std::endl;
  //   } else {
  //     std::cout << "Consume Failed" << std::endl;
  //     std::cout << status.error_code() << ": " << status.error_message()
  //               << std::endl;
      
  //   }

  }
 

//   int main() {
//     std::string target_address("0.0.0.0:50051");
//   // Instantiates the client
//   MyClient client(
//       // Channel from which RPCs are made - endpoint is the target_address
//       grpc::CreateChannel(target_address,
//                           // Indicate when channel is not authenticated
//                           grpc::InsecureChannelCredentials()));

//   ProduceResponse response;
//   std::string a = "grpc is cool!";
//   ConsumeResponse response2;
//   // RPC is created and response is stored
//   std::vector<Record*> records;


//   Record  * myRecord = new Record();
//   myRecord->set_value("mostafa");
//   records.push_back(myRecord);
//   // Record  * myRecord_2 = new Record();
//   // myRecord_2->set_value("ahmed");
//   // records.push_back(myRecord_2);
  

//   client.ProduceStream(records);

//   // Prints results
 
//   //  std::cout << "Record is: " << response2.record().value() << std::endl;
//   // std::cout << "Reversed string: " << response << std::endl;

//  }