
#include "../store/store.h"
#include "../index/index.h"

namespace log {
class Segment {
 public:
 Segment(std::string segmentDirectoryName, uint64_t baseOffset);

private:
    Store * store;
    Index* index;
    uint64_t baseOffset;
    uint64_t nextOffset;
    std::string segmentDirectoryName;
  
};


}