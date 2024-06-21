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
    SerfAgent agent;
    agent.Create(config);  
    // SerfClient::SerfResponse resp = agent.m_client.Leave();
    
    agent.Leave();
    // if (resp != SerfClient::SUCCESS) {
    //     std::cout << "FAIIIIIIIIILLLLL" << "\n";
    // }
    return 0;
}