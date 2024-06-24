 #include<iostream>
 #include <grpcpp/grpcpp.h>
 #include "../../cmake/build/logprog.grpc.pb.h"
 #include "../../include/segment/segment.h"
 #include<string>
void TestInsertAndReterive() {
    logprog::v1::Record record;
     record.set_value("mostafa");
     std::shared_ptr<Config>config = std::shared_ptr<Config>(new Config());
     config->MaxIndexBytes = 1000;
     config->MaxStoreBytes = 1000;
     logModule::Segment seg("../../logsData", 0, config);
     seg.Append(&record);
     logprog::v1::Record * rec = seg.Read(0);  //BUG  
     assert(rec != nullptr);
     assert(rec->value() == "mostafa");
     delete rec;
     seg.Remove();
}
void BulkTestInsertAndReterive() {
     std::shared_ptr<Config>config = std::shared_ptr<Config>(new Config());
     config->MaxIndexBytes = 1024;
     config->MaxStoreBytes = 1024;
     logModule::Segment seg("../../logsData", 1,  config);
     for (int i = 1; i < 600; i++) {
     logprog::v1::Record record;
     std::string input = "mostafa" + std::to_string(i);
     record.set_value(input);
     seg.Append(&record);
     }
    for (int i = 1; i < 600; i++) {
     std::cout << "At i = " << i << std::endl;
     logprog::v1::Record * rec = seg.Read(i);  
     std::string input = "mostafa" + std::to_string(i); 
     assert(rec != nullptr);
     assert(rec->value() == input);
     delete rec;
    }
    seg.Remove();
}





int main() {
<<<<<<< HEAD
    
    TestInsertAndReterive();
    BulkTestInsertAndReterive();
    google::protobuf::ShutdownProtobufLibrary();
=======
    BulkTestInsertAndReterive();
>>>>>>> origin/WaelBranch
}
