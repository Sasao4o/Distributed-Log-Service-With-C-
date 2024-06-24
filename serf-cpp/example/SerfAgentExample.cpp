#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <arpa/inet.h>
#include <cstdlib>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include "serf-cpp/ISerfListener.h"
#include "serf-cpp/SerfClient.h"
#include "serf-cpp/SerfMsgStructs.h"
#include "serf-cpp/SerfAgent.h"
#include "serf-cpp/Config.h"
//#include "serf-cpp/Config.h"

using namespace SerfCpp; 
class Handler {
   public:
   virtual void Join(std::string name, std::string address) = 0;
   virtual void Leave(std::string name) = 0;
};

class EventListener : public ISerfEventListener {
public:
    EventListener() = delete;
    explicit EventListener(SerfClient &client, Handler * handler) : m_client(client) , handler(handler) {}

    ~EventListener() override = default;

    EventListener(const EventListener &) = delete;
    EventListener(const EventListener &&) = delete;
    void operator=(const EventListener &) = delete;
    void operator=(const EventListener &&) = delete;

    void onUserEventRecord(SerfCpp::ResponseHeader &hdr, SerfCpp::UserEventRecord &record) override;

    void onMemberEventRecord(SerfCpp::ResponseHeader &hdr, SerfCpp::MemberEventRecord &record) override;

    void onMemberJoin(SerfCpp::ResponseHeader &hdr, SerfCpp::MemberEventRecord &record) override;

    void onMemberLeave(SerfCpp::ResponseHeader &hdr, SerfCpp::MemberEventRecord &record) override;

    void onQueryEventRecord(SerfCpp::ResponseHeader &hdr, SerfCpp::QueryRecord &record) override;

private:
    SerfClient & m_client;
    Handler *handler;
};

void EventListener::onUserEventRecord(SerfCpp::ResponseHeader &hdr, SerfCpp::UserEventRecord &record) {
    std::cout << "\n==> Received UserEvent Hdr: " << hdr << record;
}

void EventListener::onMemberEventRecord(SerfCpp::ResponseHeader &hdr, SerfCpp::MemberEventRecord &record) {
    std::cout << "\n==> Received MemberEvent Hdr: " << hdr << record;
}

void EventListener::onMemberJoin(SerfCpp::ResponseHeader &hdr, SerfCpp::MemberEventRecord &record){
    std::cout << "\n==> Received join event Hdr: " << hdr << record;
    for (auto &member : record.Members) {
            handler->Join(member.Name, std::string(member.Addr.begin(), member.Addr.end()));
    }
    // handler->Join("mostafa", "ahmed");
    std::cout << "Join From The Program " << std::endl;
}

void EventListener::onMemberLeave(SerfCpp::ResponseHeader &hdr, SerfCpp::MemberEventRecord &record){
    std::cout << "\n==> Received leave event Hdr: " << hdr << record;
       for (auto &member : record.Members) {
         handler->Join(member.Name, std::string(member.Addr.begin(), member.Addr.end()));
    }
    std::cout << "Leave From The Program" << std::endl;
}

void EventListener::onQueryEventRecord(SerfCpp::ResponseHeader &hdr, SerfCpp::QueryRecord &record) {
    std::cout << "\n==> Received QueryEvent Hdr: " << hdr << record;

    // Auto respond to "testQuery"
    if (record.Name == "testQuery") {
        SerfPayload payload;
        payload.push_back('T');
        payload.push_back('E');
        payload.push_back('S');
        payload.push_back('T');

        SerfClient::SerfResponse resp = m_client.Respond(record.ID, payload);
        std::cout << "\n==> Auto response: " << resp << "\n";
    }
}


 
class ConcreteHandler : public Handler {
private:
 

public:
    void Join(const std::string name, const std::string address) override {
        std::cout << "From The Concrete Handler ;) " << std::endl;
    }

    void Leave(const std::string name) override {
            std::cout << "From The Concrete Handler ;) " << std::endl;        
    }
};


class MemberShip {
    public:
    MemberShip() = delete;
    MemberShip(Config instanceConfig, Handler* handler) {
    std::cout << "Constructing..";
    this->instanceConfig = instanceConfig;
    this->handler = handler;
    agent.Create(instanceConfig);
    if (agent.getClient() != nullptr) {
        std::cout << "ERROR M4 HNA";
    }
    listener = std::make_shared<EventListener>(*(agent.getClient()), handler);
    uint64_t seq = 0ULL;
    SerfClient::SerfResponse r1 = agent.Stream("*", listener.get(), seq);
    std::cout << r1 << std::endl;
    std::vector<std::string>currentStartJoinAddresses;
    for (int i = 0; i < instanceConfig.getPorts().size(); i++) {
        if (instanceConfig.getIPAddresses()[i] == this->instanceConfig.getIPAddress() && instanceConfig.getPorts()[i] == this->instanceConfig.getRpcPort()) {
            continue;
        }
        currentStartJoinAddresses.push_back(instanceConfig.getIPAddresses()[i] + ":" + instanceConfig.getPorts()[i]);
        std::cout << currentStartJoinAddresses[i] << std::endl;
    }
    int count = 0;
 
     SerfClient::SerfResponse r =  agent.Join(currentStartJoinAddresses,false,count);
     std::cout<< "Count is " << count  << " WHILE MY PORT IS " << this->instanceConfig.getPort() <<std::endl;
 }; 

 void Leave() {
      this->agent.Leave();
}
void wait() {
    this->agent.wait();
}
SerfAgent agent;
Config instanceConfig;
Handler * handler;
std::shared_ptr<EventListener> listener;
};

int main(){
    // std::cout << "Hello";
    std::vector<std::string>addresses{"127.0.0.1", "127.0.0.1"};
    std::vector<std::string>ports{"5000", "5001"};
    Config config("zna","127.0.0.1","5000","127.0.0.1","7373", addresses, ports);
    Config config2("zna2","127.0.0.1","5001","127.0.0.1","7374", addresses, ports);
    // SerfAgent agent;
    // SerfAgent a;
    // agent.Create(config);  
    // a.Create(config2);
     ConcreteHandler * concHandler = new ConcreteHandler();
    // EventListener eventListener(*(agent.getClient()), concHandler);
    // uint64_t seq = 0ULL;
    // SerfClient::SerfResponse r1 = agent.Stream("*", &eventListener, seq);
    // std::cout<<r1<<std::endl;
    // std::vector<std::string> addr = {"127.0.0.1:5001"};
    // int count = 0;
    // SerfClient::SerfResponse r = agent.Join(addr, false, count);
    // std::cout<<r<<std::endl;
    // MembersResponse members;
    // SerfClient::SerfResponse resp = agent.Members(members);
    // std::cout << "Members response:" << resp << "\n" << members << "\n";
    // std::cout<<"Done...."<<std::endl;
    
    // SerfClient::SerfResponse rr = a.Leave();
    //  rr = agent.Leave();
    // std::cout<<rr<<std::endl;
    // // SerfClient::SerfResponse resp = agent.m_client.Leave();
    
    // agent.Leave();
    // if (resp != SerfClient::SUCCESS) {
    //     std::cout << "FAIIIIIIIIILLLLL" << "\n";
    // }


// New Changes
    MemberShip member(config, concHandler);
    MemberShip member2(config2, concHandler);
 
 
    member.wait();
    member2.wait();
    return 0;
}