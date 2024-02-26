#include "../../include/segment/segment.h"

void TestInsertAndReterive() {
    log::v1::Record record;
     record.set_value("mostafa");
     record.set_offset(0);
     Config config;
     config.MaxIndexBytes = 1000;
     config.MaxStoreBytes = 1000;
     log::Segment seg("./logsData", 0, &config);
     seg.Append(&record);
     log::v1::Record * rec = seg.Read(0);   
     assert(rec != nullptr);
     assert(rec->value() == "mostafa");
}


void BulkTestInsertAndReterive() {
     Config config;
     config.MaxIndexBytes = 10000;
     config.MaxStoreBytes = 10000;
     log::Segment seg("./logsData", 0, &config);
     for (int i = 0; i < 100; i++) {
     log::v1::Record record;
     record.set_value("mostafa");
    //  record.set_offset(i);
     seg.Append(&record);
     }
    
    for (int i = 0; i < 100; i++) {
        std::cout << "At i = " << i << std::endl;
     log::v1::Record * rec = seg.Read(i);   
     assert(rec != nullptr);
     assert(rec->value() == "mostafa");
    }
}




int main() {
    BulkTestInsertAndReterive();
}
