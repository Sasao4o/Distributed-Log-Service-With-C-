
#include "../store/store.h"
#include "../index/index.h"
#include "../../api/v1/log.pb.h"
#include "../../include/log/config.h"
#include "../../include/disk/File.h"
namespace log {
class Segment {
 public:
 Segment(std::string segmentDirectoryName, uint64_t baseOffset, Config *);
 void Append(v1::Record *record);
 v1::Record * Read(uint64_t offset);
 void Remove();
 bool IsMaxed();
 uint64_t nearestMultiple(uint64_t j, uint64_t k);
 void Close();
private:
    Store * store;
    Index* index;
    uint64_t baseOffset;
    uint64_t nextOffset;
    std::string segmentDirectoryName;
    Config *config_;
};


}