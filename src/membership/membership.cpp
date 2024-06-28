#include "../../include/membership/membership.h"
namespace membershipModule {

void EventListener::onUserEventRecord(SerfCpp::ResponseHeader &hdr, SerfCpp::UserEventRecord &record) {
    std::cout << "\n==> Received UserEvent Hdr: " << hdr << record;
}

void EventListener::onMemberEventRecord(SerfCpp::ResponseHeader &hdr, SerfCpp::MemberEventRecord &record) {
    std::cout << "\n==> Received MemberEvent Hdr: " << hdr << record;
}

void EventListener::onMemberJoin(SerfCpp::ResponseHeader &hdr, SerfCpp::MemberEventRecord &record){
    std::cout << "\n==> Received join event Hdr: " << hdr << record;
    for (auto &member : record.Members) {
            std::string members = std::string(member.Addr.begin(), member.Addr.end());
            handler->Join(member.Name, members);
    }
    // handler->Join("mostafa", "ahmed");
    std::cout << "Join From The Program " << std::endl;
}

void EventListener::onMemberLeave(SerfCpp::ResponseHeader &hdr, SerfCpp::MemberEventRecord &record){
    std::cout << "\n==> Received leave event Hdr: " << hdr << record;
       for (auto &member : record.Members) {
             std::string members = std::string(member.Addr.begin(), member.Addr.end());
         handler->Join(member.Name, members);
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


 

    MemberShip::MemberShip(Config instanceConfig, Handler* handler) {
 
    this->instanceConfig = instanceConfig;
    this->handler = handler;
    try {
    agent.Create(instanceConfig);
    }
    catch (std::exception& e) {
        std::cout <<  "Can't Create a Serf Agent!" <<  e.what() << std::endl;
    }
    listener = std::make_shared<EventListener>(*(agent.getClient()), handler);
    uint64_t seq = 0ULL;
    SerfClient::SerfResponse r1 = agent.Stream("*", listener.get(), seq);
    
    std::vector<std::string>currentStartJoinAddresses;
    for (int i = 0; i < instanceConfig.getPorts().size(); i++) {
        if (instanceConfig.getIPAddresses()[i] == this->instanceConfig.getIPAddress() && instanceConfig.getPorts()[i] == this->instanceConfig.getRpcPort()) {
            continue;
        }
        currentStartJoinAddresses.push_back(instanceConfig.getIPAddresses()[i] + ":" + instanceConfig.getPorts()[i]);
   
    }
    int count = 0;
 
     SerfClient::SerfResponse r =  agent.Join(currentStartJoinAddresses,false,count);
     std::cout << "I Joined " <<  count << " Number of Nodes " << std::endl;
 }; 

    void MemberShip::Leave() {
      this->agent.Leave();
      }
void MemberShip::wait() {
    this->agent.wait();
}

}



    
