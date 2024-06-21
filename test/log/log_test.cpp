#include "../../include/log/log.h"

using namespace logModule;

void InsertOneAndReteriveOne(Log * lg) {
//This Test Just Insert 300 Records and Reterive Them    
  lg -> SetUp();
  for (int i = lg -> LowestOffset(); i < lg -> LowestOffset() + 1; i++) {
    logprog::v1::Record record;
    record.set_value("mostafa");
    //  record.set_offset(i);
    uint64_t * off = new uint64_t();
    try {
      lg -> Append( & record, off);
    } catch (...) {
      std::cout << "Catching an exception" << std::endl;
    }
    delete off;
  }

//   for (int i = lg -> LowestOffset(); i < lg -> LowestOffset() + 1; i++) {
//     std::cout << "At i = " << i << std::endl;
//     logprog::v1::Record * rec = nullptr;
//     try {
//       rec = lg -> Read(i);
//     } catch (...) {
//       std::cout << "Catching an exception " << std::endl;
//     }
//     assert(rec != nullptr);
//     assert(rec -> value() == "mostafa");
//   }
  lg -> Remove();
}
void BasicTest(Log * lg) {
  //This Test Just Insert 300 Records and Reterive Them    
  lg -> SetUp();
  for (int i = lg -> LowestOffset(); i < 300; i++) {
    logprog::v1::Record record;
    record.set_value("mostafa");
    //  record.set_offset(i);
    uint64_t * off = new uint64_t();
    try {
      lg -> Append( & record, off);
    } catch (...) {
      std::cout << "Catching an exception" << std::endl;
    }
  }

  for (int i = lg -> LowestOffset(); i < 300; i++) {
    std::cout << "At i = " << i << std::endl;
    logprog::v1::Record * rec = nullptr;
    try {
      rec = lg -> Read(i);
    } catch (...) {
      std::cout << "Catching an exception " << std::endl;
    }
    assert(rec != nullptr);
    assert(rec -> value() == "mostafa");
  }
  lg -> Remove();
}

void ReadOutOfRange(Log * lg) {
  //This Test Just Insert 300 Records and Reterive Them    
  lg -> SetUp();
  logprog::v1::Record record;
  record.set_value("mostafa");
  //  record.set_offset(i);
  uint64_t * off = new uint64_t();
  try {
    lg -> Append( & record, off);
  } catch (...) {
    std::cout << "Catching an exception" << std::endl;
  }

  {

    logprog::v1::Record * rec = nullptr;
    try {
      rec = lg -> Read(lg -> LowestOffset() + 1);
      assert(rec != nullptr); //This Ensures that we throws 
    } catch (std::runtime_error &E) {
      std::cout << "Catching an exception " << std::endl;
      std::cout << E.what() << std::endl;
      assert(strcmp(E.what(),"The Offset is Out of Range") == 0);
    }
    assert(rec == nullptr);

  }
  lg -> Remove();
}

void RemoveTest() {
  std::shared_ptr<Config>b = std::shared_ptr<Config>(new Config());
  
  b->MaxStoreBytes = 1024;
  b->MaxIndexBytes = 1024;
  b->InitialOffset = 1;
  Log lg("../../logsData", b);
  lg.SetUp();

  for (int i = b->InitialOffset; i < 2; i++) {
    logprog::v1::Record record;
    record.set_value("mostafa");
    //  record.set_offset(i);
    uint64_t * off = new uint64_t();
    lg.Append( & record, off);
  }

  for (int i = b->InitialOffset; i < 2; i++) {
    std::cout << "At i = " << i << std::endl;
    logprog::v1::Record * rec = lg.Read(i);
    assert(rec != nullptr);
    assert(rec -> value() == "mostafa");
  }
  std::cout << "Start Removing" << std::endl;
  lg.Remove();
  // assert(lg.Read(b->InitialOffset) == nullptr);
}

void TruncateTest(Log * lg) {
  BasicTest(lg);
  lg -> Truncate(110);
}

int main() {
 
  std::shared_ptr<Config>b = std::shared_ptr<Config>(new Config());
  b->MaxStoreBytes = 1024;
  b->MaxIndexBytes = 1024;
  b->InitialOffset = 1;
  Log lg("../../logsData", b);
  // InsertOneAndReteriveOne( & lg);
  // BasicTest(&lg);
  // ReadOutOfRange(&lg);
  RemoveTest();
  // TruncateTest(&lg);
      // RemoveTest();
  //     TruncateTest(&lg);
  //     lg.Remove();
}