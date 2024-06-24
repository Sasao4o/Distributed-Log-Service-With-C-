#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <arpa/inet.h>
#include <cstdlib>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include "serf-cpp/SerfAgent.h"
//#include "serf-cpp/Config.h"

using namespace SerfCpp; 

int main(){
    Config config("zna","127.0.0.1","7373");
    Config config1("znas","127.0.0.1","7375");

    SerfAgent agent;
    SerfAgent agent1;
    
    agent.Create(config);  
    // SerfClient::SerfResponse resp = agent.m_client.Leave();
    // agent1.Create(config1);   
    // agent.Leave();
    // if (resp != SerfClient::SUCCESS) {
    //     std::cout << "FAIIIIIIIIILLLLL" << "\n";
    // }
    while (1) {
       
    }
    return 0;
}