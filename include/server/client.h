#ifndef ClientModule
#define ClientModule

#include <grpcpp/grpcpp.h>
#include <string>
#include <vector>

#include "../../cmake/build/logprog.grpc.pb.h"

using namespace logprog::v1;

class MyClient {
public:
    MyClient(std::shared_ptr<grpc::Channel> channel);

    ProduceResponse Produce(std::string a);

    ConsumeResponse Consume(uint64_t offset);

    void ProduceStream(std::vector<Record*> &records);

    void ConsumeStream(uint64_t offset);

    std::vector<Record> records; // For testing

private:
    std::unique_ptr<Logging::Stub> stub_;
};

#endif  
