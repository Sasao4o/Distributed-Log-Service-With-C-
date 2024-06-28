#ifndef RunnableModule
#define RunnableModule


#include <iostream>
#include <memory>
#include<string>
#include "../membership/membership.h"
#include "../replicator/replicator.h"
#include "../handler/handler.h"
#include "../log/log.h"
#include "../server/server.h"
#include "../server/client.h"
#include "../../serf-cpp/include/serf-cpp/Config.h"
namespace BnYaman {
 
using namespace membershipModule;
using namespace logModule;
using namespace logprog::v1;

class RunnableConfig {
public:
    RunnableConfig() {};
    // Constructor with member initializer list
    RunnableConfig(
        std::string directoryPath,
        std::string serverAddress,
        std::string serfNodeName,
        std::string serfHost,
        std::string serfRpcPort,
        std::string serfBindPort,
        std::vector<std::string> serfStartIpAddresses,
        std::vector<std::string> serfStartPorts
    ) : 
        directoryPath_(directoryPath),
        serverAddress_(serverAddress),
        serfNodeName_(serfNodeName),
        serfHost_(serfHost),
        serfRpcPort_(serfRpcPort),
        serfBindPort_(serfBindPort),
        serfStartIpAddresses_(serfStartIpAddresses),
        serfStartPorts_(serfStartPorts)
    {}
    
    std::string directoryPath_;
    std::string serverAddress_;
    std::string serfNodeName_;
    std::string serfHost_;
    std::string serfRpcPort_;
    std::string serfBindPort_;
    std::vector<std::string> serfStartIpAddresses_;
    std::vector<std::string> serfStartPorts_;
};

class Runnable {
    public:
    Runnable(RunnableConfig configMe);
    MyClient ClientConnection(std::string target_address);
    void RunServer(BussinessServer * bs, std::string server_address, Log * lg);
    void Run();
    RunnableConfig configMe;
};














}

#endif