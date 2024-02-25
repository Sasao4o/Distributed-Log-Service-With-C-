 
#include "../../include/segment/segment.h"
 
 
#include "../../include/disk/File.h"
using namespace log;
Segment::Segment(std::string segmentDirectoryName, uint64_t baseOffset) : segmentDirectoryName(segmentDirectoryName), baseOffset(baseOffset) {
std::string storeFileName = segmentDirectoryName + "/"  + std::to_string(baseOffset) + ".store";
std::string indexFileName = segmentDirectoryName + "/"  + std::to_string(baseOffset) + ".index";
Store * store = new Store(storeFileName);
Index * index = new Index(indexFileName);


}