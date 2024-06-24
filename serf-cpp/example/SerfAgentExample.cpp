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
//#include "serf-cpp/Config.h"

using namespace SerfCpp; 
class EventListener : public ISerfEventListener {
public:
    EventListener() = delete;
    explicit EventListener(SerfClient &client) : m_client(client) {}

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
};

void EventListener::onUserEventRecord(SerfCpp::ResponseHeader &hdr, SerfCpp::UserEventRecord &record) {
    std::cout << "\n==> Received UserEvent Hdr: " << hdr << record;
}

void EventListener::onMemberEventRecord(SerfCpp::ResponseHeader &hdr, SerfCpp::MemberEventRecord &record) {
    std::cout << "\n==> Received MemberEvent Hdr: " << hdr << record;
}

void EventListener::onMemberJoin(SerfCpp::ResponseHeader &hdr, SerfCpp::MemberEventRecord &record){
    std::cout << "\n==> Received join event Hdr: " << hdr << record;
}

void EventListener::onMemberLeave(SerfCpp::ResponseHeader &hdr, SerfCpp::MemberEventRecord &record){
    std::cout << "\n==> Received leave event Hdr: " << hdr << record;
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

int main(){

    Config config("zna","127.0.0.1","5000","127.0.0.1","7373");
    Config config2("zna2","127.0.0.1","5001","127.0.0.1","7374");
    SerfAgent agent;
    SerfAgent a;
    agent.Create(config);  
    a.Create(config2);
    EventListener eventListener(*(agent.getClient()));
    uint64_t seq = 0ULL;
    SerfClient::SerfResponse r1 = agent.Stream("*", &eventListener, seq);
    std::cout<<r1<<std::endl;
    std::vector<std::string> addr = {"127.0.0.1:5001"};
    int count = 0;
    SerfClient::SerfResponse r = agent.Join(addr, false, count);
    std::cout<<r<<std::endl;
    // MembersResponse members;
    // SerfClient::SerfResponse resp = agent.Members(members);
    // std::cout << "Members response:" << resp << "\n" << members << "\n";
    // std::cout<<"Done...."<<std::endl;
    
    SerfClient::SerfResponse rr = a.Leave();
    rr = agent.Leave();
    std::cout<<rr<<std::endl;
    // SerfClient::SerfResponse resp = agent.m_client.Leave();
    
    //agent.Leave();
    // if (resp != SerfClient::SUCCESS) {
    //     std::cout << "FAIIIIIIIIILLLLL" << "\n";
    // }
    return 0;
}