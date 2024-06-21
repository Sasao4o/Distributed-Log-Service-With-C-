#include <cstdlib> // For system function
#include <iostream>
#include <string>
#include "serf-cpp/SerfClient.h"
#include <unistd.h> // For sleep()
#include "serf-cpp/Config.h"
#include <regex>

namespace SerfCpp
{ 

class SerfAgent {
    // This class is responsible for creation of the serf agent with the specified config & 
    // Passing the client to connect to it 
public:
//"serf agent -node=" + nodeConfig.getNodeName() + "-bind=" + nodeConfig.getIPAddress() +":"+ nodeConfig.getPort()
    void Create(Config &nodeConfig){
        Config currentConfig("dummy",m_ip,m_port);
        if(currentConfig == nodeConfig){
            throw std::runtime_error("Already created a serf agent with this config");
        }
        std::string command = "serf agent -node=" + nodeConfig.getNodeName() + "-bind=" + nodeConfig.getIPAddress() +":"+ nodeConfig.getPort() + " >> agent.log &"; 
        
        if(system(command.c_str()) == 0){

            std::cout << "Command executed successfully." << std::endl;
            initializeSerfAgent(nodeConfig.getIPAddress(), nodeConfig.getPort()); 
            //================================ Creation Phase Done, Connection Phase Start ==================================//
            std::cout<<"Trying to connect ....."<<std::endl;
            usleep(30000); //20 ms for startup of serf agent and logging in file
            SerfClient::SerfResponse resp = m_client.Connect(m_ip, static_cast<uint16_t>(std::stoi(m_port)));
            if (resp != SerfClient::SUCCESS) {
                throw std::runtime_error("Failed to connect to serf agent with the current config");
            }
            std::cout << "Connected!" <<std::endl;
        } else {
            throw std::runtime_error("Failed to create serf agent with the specified config");
        }
    }

    void Connect(){
        SerfClient::SerfResponse resp = m_client.Connect(m_ip, static_cast<uint16_t>(std::stoi(m_port)));
        if (resp != SerfClient::SUCCESS) {
            throw std::runtime_error("Failed to connect to serf agent with the current config");
        }
        //isConnected = true;
        std::cout << "Connected!" <<std::endl;
    }
            
    std::string getIp(){
        return m_ip;
    }
    uint16_t getPort() const{
        return static_cast<uint16_t>(std::stoi(m_port));
    }
    
    bool IsConnected(){
        return m_client.IsConnected();
    }

    SerfClient::SerfResponse Close(){
        return m_client.Close();
    }

    SerfClient::SerfResponse Join(const SerfStringArray &addrs, bool replay, int &nodeCount){
        return m_client.Join(addrs, replay, nodeCount);
    }

    SerfClient::SerfResponse Auth(const std::string &authKey){
        return m_client.Auth(authKey);
    }

    SerfClient::SerfResponse InstallKey(const std::string &key, KeyResponse &keys){
        return m_client.InstallKey(key, keys);
    }

    SerfClient::SerfResponse UseKey(const std::string &key){
        return m_client.UseKey(key);
    }

    SerfClient::SerfResponse RemoveKey(const std::string &key, KeyResponse &keys){
        return m_client.RemoveKey(key, keys);
    }

    SerfClient::SerfResponse ListKeys(KeyListResponse &keys){
        return m_client.ListKeys(keys);
    }

    SerfClient::SerfResponse Members(MembersResponse &members){
        return m_client.Members(members);
    }

    SerfClient::SerfResponse MembersFiltered(const SerfStringMap &tags, const std::string &status, const std::string &name,
                                 MembersResponse &members){
                                    return m_client.MembersFiltered(tags, status, name, members);
                                 }

    SerfClient::SerfResponse Event(const std::string &name, const SerfPayload &payload, bool coalesce){
        return m_client.Event(name, payload, coalesce);
    }

    SerfClient::SerfResponse ForceLeave(const std::string &nodeName){
        return m_client.ForceLeave(nodeName);
    }

    SerfClient::SerfResponse Tags(const SerfStringMap &tags, const SerfStringArray &deleteTags){
        return m_client.Tags(tags, deleteTags);
    }

    SerfClient::SerfResponse Leave(){
        return m_client.Leave();
    }

    SerfClient::SerfResponse Monitor(const std::string &level, ISerfLogListener *listener, uint64_t &seq){
        return m_client.Monitor(level, listener, seq);
    }

    SerfClient::SerfResponse Stream(const std::string &type, ISerfEventListener *listener, uint64_t &seq){
        return m_client.Stream(type, listener, seq);
    }

    SerfClient::SerfResponse Stop(const uint64_t &seq){
         return m_client.Stop(seq);
    }

    SerfClient::SerfResponse Stats(StatsResponse &stats){
        return m_client.Stats(stats);
    }

    SerfClient::SerfResponse Respond(const uint64_t &id, const SerfPayload &payload){
        return m_client.Respond(id, payload);
    }

    SerfClient::SerfResponse GetCoordinate(const std::string &node, CoordResponse &coordinate){
        return m_client.GetCoordinate(node, coordinate);
    }

   
    SerfClient::SerfResponse Query(const std::string &name, const SerfPayload &payload, ISerfQueryListener *listener,
                       // Following args are optional
                       bool requestAck = false, uint64_t timeout = SERF_CPP_DEFAULT_TIMEOUT, SerfStringArray *filterNodes = nullptr,
                       SerfStringMap *filterTags = nullptr){
                        return m_client.Query(name, payload, listener, requestAck, timeout, filterNodes, filterTags);
                       }

    void Version(uint32_t &major, uint32_t &minor, uint32_t &patch){
        m_client.Version(major, minor, patch);
    }
private:
    void initializeSerfAgent(const std::string& ip, const std::string& port){
        m_ip = ip;
        m_port = port;
    } 
    // Client for usage after intialization 
    SerfClient m_client;
//  bool isIntialized;
//  bool isConnected;
    std::string m_ip;
    std::string m_port;
};
}


