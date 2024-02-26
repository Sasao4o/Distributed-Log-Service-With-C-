#include<iostream>
using namespace std;

 #include "./api/v1/log.pb.h"
#include "./include/segment/segment.h"
 #include "./include/disk/File.h"
 using namespace log;
int main() {
     // log::v1::Record record;
     // record.set_value("mostafa");
     // record.set_offset(0);
     // Config b;
     // b.MaxIndexBytes = 10000;
     // b.MaxStoreBytes = 10000;
     // log::Segment a("./logsData", 0, &b);
     // a.Append(&record);
//      std::string name = "Mostafa";
// std::cout << name.c_str();
// std::cout << name.c_str();
char *x = "Mos\0Tafa";
  File f("5ra");
f.WriteFile(0, x, 9);
char *y = new char[10];
f.ReadFile(0,y,9);
 
 for (int i = 0; i < 10; i++) {
     cout << *y;
     y++;
 }
// std::cout << std::string(x.c_str());
}
 