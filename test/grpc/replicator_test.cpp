#include <iostream>
#include <string>
#include "../../cmake/build/logprog.grpc.pb.h"
#include "../../include/log/log.h"
#include "../../include/server/server.h"
#include "../../include/server/client.h"
#include "../../include/replicator/replicator.h"
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

void RunServer2(BussinessServer * bs, std::string server_address) {
  std::shared_ptr<Config>b = std::shared_ptr<Config>(new Config());
  Log lg("../../logsData2", b);
  lg.SetUp();
  LogImplementation service(&lg);
  BussinessServer s(&service);
  *bs = std::move(s);
  bs->RunServer(server_address);
  
  //note that there is unique_ptr so the class is not copiable!!!
  //https://stackoverflow.com/questions/29124592/copy-constructor-to-transfer-ownership-of-a-unique-ptr
 
}

MyClient ClientConnection(std::string addr) {
  // Instantiates the client
  MyClient client(
      // Channel from which RPCs are made - endpoint is the target_address
      grpc::CreateChannel(addr,
                          // Indicate when channel is not authenticated
                          grpc::InsecureChannelCredentials()));

  return client;
 
}
 void TestProduceAndConsume() {
  BussinessServer * bs = new BussinessServer();
  std::string addr = "0.0.0.0:50051";
  std::thread serverOneThread(RunServer, bs, addr);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
 
  MyClient client1 = ClientConnection(addr);
  client1.Produce("mostafa");
  client1.Produce("Ali");
  ConsumeResponse response = client1.Consume(1);
  std::cout << response.record().value() << std::endl;
  assert(response.record().value() == "Ali");

// Second Server is up
  BussinessServer * bs2 = new BussinessServer();
  std::string addr2 = "0.0.0.0:50052";
  std::thread serverTwoThread(RunServer2, bs2, addr2);
   
   std::this_thread::sleep_for(std::chrono::milliseconds(500));
   MyClient client2 = ClientConnection(addr2);
 
  Replicator replicator(client2);
  std::string nodeName = "Node Two";
  replicator.Join(nodeName,addr);
  
  //replicator.Close();

  std::cout<<"REPLICATOR RECORDS SIZE :: "<<replicator.records.size()<<std::endl;
  //MyClient c = ClientConnection(addr2);
  // ConsumeResponse response2 = replicator.getLocalClient()->Consume(0);
  // std::cout << response2.record().value() << std::endl;
   client1.ConsumeStream(0);
   client2.ConsumeStream(0);

   assert(client1.records.size() == client2.records.size());
   for (int i = 0; i < client1.records.size(); i++) {
    assert(client1.records[i].value() == client2.records[i].value() && client1.records[i].offset() == client2.records[i].offset());
   }
  

  bs2->ShutServer();
  bs->ShutServer();
  serverOneThread.join();
  serverTwoThread.join();
  
 }
int main() {
 TestProduceAndConsume();
//  MyClient b = ClientConnection();
//  std::cout << b.Consume(0).record().value();
 
 }