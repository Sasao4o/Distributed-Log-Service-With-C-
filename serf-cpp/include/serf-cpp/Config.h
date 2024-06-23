#include <iostream>
#include <string>
#include <regex>
#include <stdexcept>

class Config {
public:
    Config(const std::string& nodeName, const std::string& ipAddress, const std::string& port, const std::string& rpcAddress, const std::string& rpcPort) {
        // if (!isValidIPAddress(ipAddress) || !isValidPort(port)) {
        //     //std::cerr << "Invalid IP address or port. Configuration aborted." << std::endl;
        //     // Destroy the object by throwing an exception
        //     throw std::invalid_argument("Invalid IP address or port.");
        // }

        this->nodeName = nodeName;
        this->ipAddress = ipAddress;
        this->port = port;
        this->rpcAddress = rpcAddress;
        this->rpcPort = rpcPort;
    }

    bool isValidIPAddress(const std::string& str) {
        // Regular expression pattern for IP address
        std::regex ipPattern("^\\b(?:\\d{1,3}\\.){3}\\d{1,3}\\b$");
        return std::regex_match(str, ipPattern);
    }

    bool isValidPort(const std::string& str) {
        // Regular expression pattern for port number (1-65535)
        std::regex portPattern("^\\b(?:[1-9]\\d{0,3}|[1-5]\\d{4}|6[0-5]{2}[0-3][0-5])\\b$");
        return std::regex_match(str, portPattern);
    }

    std::string getNodeName() const {
        return nodeName;
    }

    std::string getIPAddress() const {
        return ipAddress;
    }

    std::string getPort() const {
        return port;
    }

    std::string getrpcAddress() const {
        return rpcAddress;
    }

    std::string getRpcPort() const {
        return rpcPort;
    }

    bool operator==(const Config& other) const {
        return (ipAddress == other.ipAddress && port == other.port);
    }
private:
    std::string nodeName;
    std::string ipAddress;
    std::string port;
    std::string rpcAddress;
    std::string rpcPort;
};