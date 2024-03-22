  
    #include <grpcpp/grpcpp.h>
#include <string>
 
#include "../../cmake/build/logprog.grpc.pb.h"
#include "../../include/server/client.h"
using namespace logprog::v1;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientReaderWriter;
  
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
  ConsumeResponse response2;
  // RPC is created and response is stored
  std::vector<Record*> records;


  Record  * myRecord = new Record();
  myRecord->set_value("mostafa");
  records.push_back(myRecord);
  // Record  * myRecord_2 = new Record();
  // myRecord_2->set_value("ahmed");
  // records.push_back(myRecord_2);
  

  client.ProduceStream(records);

  // Prints results
 
  //  std::cout << "Record is: " << response2.record().value() << std::endl;
  // std::cout << "Reversed string: " << response << std::endl;

 }