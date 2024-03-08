#include "../../include/log/log.h"
using namespace logModule;
void BasicTest(Log *lg) {
 
  
   lg->SetUp();
    
    for (int i = lg->LowestOffset(); i < 300; i++) {
     logprog::v1::Record record;
     record.set_value("mostafa");
    //  record.set_offset(i);
    uint64_t *off = new uint64_t();
     lg->Append(&record, off);
     }
    
    for (int i = lg->LowestOffset(); i < 300; i++) {
        std::cout << "At i = " << i << std::endl;
     logprog::v1::Record * rec = lg->Read(i);   
     assert(rec != nullptr);
     assert(rec->value() == "mostafa");
    }
}

 

void RemoveTest() {
  Config b;
  b.MaxStoreBytes = 1024;
  b.MaxIndexBytes = 1024;
  b.InitialOffset = 1;
  Log lg("../../logsData", b);
   lg.SetUp();

    for (int i = b.InitialOffset; i < 2; i++) {
     logprog::v1::Record record;
     record.set_value("mostafa");
    //  record.set_offset(i);
     uint64_t *off = new uint64_t();
     lg.Append(&record, off);
     }
    
    for (int i = b.InitialOffset; i < 2; i++) {
        std::cout << "At i = " << i << std::endl;
     logprog::v1::Record * rec = lg.Read(i);   
     assert(rec != nullptr);
     assert(rec->value() == "mostafa");
    }
    std::cout << "Start Removing" << std::endl;
    lg.Remove();
    assert(lg.Read(b.InitialOffset) == nullptr);
}


void TruncateTest(Log* lg) {
    BasicTest(lg);
     lg->Truncate(110);
}

int main() {
      Config b;
  b.MaxStoreBytes = 1024;
  b.MaxIndexBytes = 1024;
  b.InitialOffset = 1;
     Log lg("../../logsData", b);
    // BasicTest(&lg);
    // RemoveTest();
    TruncateTest(&lg);
    lg.Remove();
}   
