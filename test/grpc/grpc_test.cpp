#include <iostream>
#include <string>
#include "../../cmake/build/logprog.grpc.pb.h"
#include "../../include/log/log.h"
#include "../../include/server/server.h"
#include "../../include/server/client.h"
#include<iostream>
#include <thread>

//alias run="make -j 4 && ./grpc_test"  (Use This if u debugging fast compilation and execution)
using namespace logprog::v1;
using namespace logModule;
void RunServer(BussinessServer * bs, std::string server_address) {
  std::shared_ptr<Config>b = std::shared_ptr<Config>(new Config());
  Log lg("../../logsData", b);
  lg.SetUp();
  LogImplementation service(&lg);
  BussinessServer s(&service);
  *bs = std::move(s);
  bs->RunServer(server_address);
  
  //note that there is unique_ptr so the class is not copiable!!!
  //https://stackoverflow.com/questions/29124592/copy-constructor-to-transfer-ownership-of-a-unique-ptr
 
}

MyClient ClientConnection(std::string target_address) {
   // std::string target_address("0.0.0.0:50051");
  // Instantiates the client
  MyClient client(
      // Channel from which RPCs are made - endpoint is the target_address
      grpc::CreateChannel(target_address,
                          // Indicate when channel is not authenticated
                          grpc::InsecureChannelCredentials()));

  return client;
 
}
 void TestProduceAndConsume() {
  BussinessServer * bs = new BussinessServer();
  std::string addr = "0.0.0.0:50051";
  std::thread serverOneThread(RunServer, bs, addr);
   std::this_thread::sleep_for(std::chrono::milliseconds(500));
 
  MyClient b = ClientConnection(addr);
  b.Produce("mostafa");
  ConsumeResponse response = b.Consume(0);
  std::cout << response.record().value() << std::endl;
  assert(response.record().value() == "mostafa");
  //delete b;
  bs->ShutServer();
  serverOneThread.join();
  
 }
int main() {
 TestProduceAndConsume();
//  MyClient b = ClientConnection();
//  std::cout << b.Consume(0).record().value();
 
 }