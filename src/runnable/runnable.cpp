#include "../../include/runnable/runnable.h"
 
namespace BnYaman {
 Runnable::Runnable(RunnableConfig configMe) {
  this->configMe = configMe;
 }
 void Runnable::Run() {
  //Setting Up Logs
  std::shared_ptr<ConfigModule::Config>b = std::shared_ptr<ConfigModule::Config>(new ConfigModule::Config());
  b->MaxStoreBytes = 1024;
  b->MaxIndexBytes = 1024;
  b->InitialOffset = 1;
  Log *lg = new Log (configMe.directoryPath_, b);
  //Setting Up The Server
  BussinessServer * bs = new BussinessServer();
  std::thread serverOneThread(&Runnable::RunServer,this, bs, configMe.serverAddress_, lg);
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  
  
  //Setup Membership Using Replicator
  MyClient client = ClientConnection(configMe.serverAddress_);
  Replicator *replica = new Replicator(client);
  SerfCpp::Config serfAgentConfig(configMe.serfNodeName_, configMe.serfHost_, configMe.serfBindPort_, configMe.serfHost_, configMe.serfRpcPort_, configMe.serfStartIpAddresses_, configMe.serfStartPorts_);
  membershipModule::MemberShip * memberShip = new MemberShip(serfAgentConfig ,replica);
    memberShip->wait();
  serverOneThread.join();

 }
    
 void Runnable::RunServer(BussinessServer * bs, std::string server_address, Log * lg) {
    lg->SetUp();
    LogImplementation service(lg);
    BussinessServer s(&service);
    *bs = std::move(s);
     bs->RunServer(server_address);

 }

MyClient Runnable::ClientConnection(std::string target_address) {
   // std::string target_address("0.0.0.0:50051");
  // Instantiates the client
  MyClient client(
      // Channel from which RPCs are made - endpoint is the target_address
      grpc::CreateChannel(target_address,
                          // Indicate when channel is not authenticated
                          grpc::InsecureChannelCredentials()));

  return client;
 
}

//   Runnable::getSerfConfig() {
//     std::vector<std::string>addresses{"127.0.0.1", "127.0.0.1"};
//     std::vector<std::string>ports{"5000", "5001"};
//     return Config config("zna","127.0.0.1","5000","127.0.0.1","7373", addresses, ports);
// }
 
}

int main() {
   
 BnYaman::RunnableConfig config("../../logsData", "127.0.0.1:50052", "node1", "127.0.0.1", "5000", "7373", {}, {});
//  BnYaman::RunnableConfig config2("../../logsData", "127.0.0.1:50051", "node1", "127.0.0.1", "5000", "7374", {"127.0.0.1"}, {"50052"});
 BnYaman::RunnableConfig config2("../../logsData2", "127.0.0.1:50051", "node2", "127.0.0.1", "4999", "7374", {"127.0.0.1"}, {"7373"});

 BnYaman::Runnable *run = new BnYaman::Runnable(config);
 BnYaman::Runnable *run2 = new BnYaman::Runnable(config2);
 std::thread thread1(&BnYaman::Runnable::Run, run);
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
 std::thread thread2(&BnYaman::Runnable::Run, run2 );
 thread1.join();
 thread2.join();

  
}

 