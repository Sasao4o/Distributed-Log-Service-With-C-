#include<iostream>
using namespace std;

 #include "./api/v1/log.pb.h"
#include "./include/segment/segment.h"
#include "./include/log/log.h"

 #include "./include/disk/File.h"
 using namespace logModule;
int main() {
     // log::v1::Record record;
     // record.set_value("mostafa");
     // record.set_offset(0);
    Config b;
     // b.MaxIndexBytes = 10000;
     // b.MaxStoreBytes = 10000;
     // log::Segment a("./logsData", 0, &b);
     // a.Append(&record);
//      std::string name = "Mostafa";
// std::cout << name.c_str();
// std::cout << name.c_str();

  Log lg("./logsData", b);
   lg.SetUp();
}
 