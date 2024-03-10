 #include <grpcpp/grpcpp.h>
#include <string>
#include "../../cmake/build/logprog.grpc.pb.h"
#include "../../include/log/log.h"
#include<iostream>
#include "../../include/server/server.h"
using grpc::ServerBuilder; 
using namespace logprog::v1;
using namespace logModule;
using grpc::Server;
using grpc::Channel;
using grpc::ServerContext;
using grpc::Status;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;

int main() {
  Config b;
  Log lg("../../logsData", b);
  lg.SetUp();
  LogImplementation service(&lg);
  BussinessServer s(&service);
  s.RunServer();
 

}