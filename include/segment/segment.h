
#include "../store/store.h"
#include "../index/index.h"
 #include "../../cmake/build/logprog.pb.h"
 
#include "../../include/disk/File.h"
#ifndef SegmentModule
#define SegmentModule
#include "../../include/log/config.h"
namespace logModule {
class Segment {
 public:
 Segment(std::string segmentDirectoryName, uint64_t baseOffset, Config *);
 bool Append(logprog::v1::Record *record);
 logprog::v1::Record * Read(uint64_t offset);
 void Remove();
 bool IsMaxed();
 uint64_t nearestMultiple(uint64_t j, uint64_t k);
 uint64_t getBaseOffset();
 uint64_t getNextOffset();
 void Close();
 ~Segment();
private:
    Store * store;
    Index* index;
    uint64_t baseOffset;
    uint64_t nextOffset; 
    std::string segmentDirectoryName;
    Config *config_;
};


}
#endif