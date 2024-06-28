
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// #include <arpa/inet.h>
// #include <cstdlib>
// #include <netdb.h>
// #include <sys/socket.h>
// #include <unistd.h>
 
 
//#include "serf-cpp/Config.h"
#ifndef MemberShipModule
#define MemberShipModule
#include "../../serf-cpp/include/serf-cpp/ISerfListener.h"
#include "../../serf-cpp/include/serf-cpp/SerfClient.h"
#include "../../serf-cpp/include/serf-cpp/SerfMsgStructs.h"
#include "../../serf-cpp/include/serf-cpp/SerfAgent.h"
#include "../../serf-cpp/include/serf-cpp/Config.h"
#include "../handler/handler.h"
namespace membershipModule {

 

using namespace SerfCpp; 
 

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

// void EventListener::onUserEventRecord(SerfCpp::ResponseHeader &hdr, SerfCpp::UserEventRecord &record) {
//     std::cout << "\n==> Received UserEvent Hdr: " << hdr << record;
// }

// void EventListener::onMemberEventRecord(SerfCpp::ResponseHeader &hdr, SerfCpp::MemberEventRecord &record) {
//     std::cout << "\n==> Received MemberEvent Hdr: " << hdr << record;
// }

// void EventListener::onMemberJoin(SerfCpp::ResponseHeader &hdr, SerfCpp::MemberEventRecord &record){
//     std::cout << "\n==> Received join event Hdr: " << hdr << record;
//     for (auto &member : record.Members) {
//             std::string members = std::string(member.Addr.begin(), member.Addr.end());
//             handler->Join(member.Name, members);
//     }
//     // handler->Join("mostafa", "ahmed");
//     std::cout << "Join From The Program " << std::endl;
// }

// void EventListener::onMemberLeave(SerfCpp::ResponseHeader &hdr, SerfCpp::MemberEventRecord &record){
//     std::cout << "\n==> Received leave event Hdr: " << hdr << record;
//        for (auto &member : record.Members) {
//              std::string members = std::string(member.Addr.begin(), member.Addr.end());
//          handler->Join(member.Name, members);
//     }
//     std::cout << "Leave From The Program" << std::endl;
// }

// void EventListener::onQueryEventRecord(SerfCpp::ResponseHeader &hdr, SerfCpp::QueryRecord &record) {
//     std::cout << "\n==> Received QueryEvent Hdr: " << hdr << record;

//     // Auto respond to "testQuery"
//     if (record.Name == "testQuery") {
//         SerfPayload payload;
//         payload.push_back('T');
//         payload.push_back('E');
//         payload.push_back('S');
//         payload.push_back('T');

//         SerfClient::SerfResponse resp = m_client.Respond(record.ID, payload);
//         std::cout << "\n==> Auto response: " << resp << "\n";
//     }
// }


 
class ConcreteHandler : public Handler {
private:
 

public:
    void Join( std::string& name,  std::string& address) override {
        std::cout << "From The Concrete Handler ;) " << std::endl;
    }

    void Leave( std::string& name) override {
            std::cout << "From The Concrete Handler ;) " << std::endl;        
    }
};


class MemberShip {
    public:
    MemberShip() = delete;
    MemberShip(Config instanceConfig, Handler* handler);
    void Leave() ;
    void wait() ;
    SerfAgent agent;
    Config instanceConfig;
    Handler * handler;
    std::shared_ptr<EventListener> listener;
};










    
}

#endif