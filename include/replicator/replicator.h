#include <grpcpp/grpcpp.h>
#include <thread>
#include <map>
#include <mutex>
#include <condition_variable>
#include "../../include/server/client.h"
#include "../../cmake/build/logprog.grpc.pb.h"
#include "../handler/handler.h"
using namespace logprog::v1;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientReaderWriter;
//using grpc::ClientReader;

class Replicator : public Handler {
public:

    std::vector<Record> records;

    Replicator(MyClient client);
    void Join(std::string& name,  std::string& addr) override;

    void replicate(const std::string& addr, std::shared_ptr<std::condition_variable> leave);
    void Leave(std::string& name) override;

    void Close();
    MyClient getLocalClient();
    private:
    void init(MyClient client);
    MyClient LocalClient;
    std::mutex mu;
    std::map<std::string, std::shared_ptr<std::condition_variable>> servers;
    bool closed = false;
    std::shared_ptr<std::condition_variable> close;
    // void logError(const std::string& msg, const std::string& addr) {
    //     logger->Error(msg, {{"addr", addr}});
    // }
};
