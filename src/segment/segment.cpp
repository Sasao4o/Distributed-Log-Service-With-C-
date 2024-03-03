 
#include "../../include/segment/segment.h"
  
 
using namespace logModule;
Segment::Segment(std::string segmentDirectoryName, uint64_t baseOffset, Config *config) : segmentDirectoryName(segmentDirectoryName), baseOffset(baseOffset), config_(config) {
std::string storeFileName = segmentDirectoryName + "/"  + std::to_string(baseOffset) + ".store";
std::string indexFileName = segmentDirectoryName + "/"  + std::to_string(baseOffset) + ".index";
 store = new Store(storeFileName);
 index = new Index(indexFileName);
uint32_t offset;
uint64_t pos;
index->Read(-1, &offset, &pos);
if (offset == -1 && pos == -1) {
     nextOffset = baseOffset;
} else {
    //Note offset is relative to baseoffset
    //so offset will be 32 bytes but baseOffset wil be 64 byte
    nextOffset = baseOffset + offset + 1;
}

}
bool Segment::Append(logprog::v1::Record *record) {
    record->set_offset(nextOffset);
    std::string serialized_record;
    if (!record->SerializeToString(&serialized_record)) {
        std::cerr << "Failed to serialize Record." << std::endl;
        return false;
    }
    std::cout << "Serialized Record is " << serialized_record.c_str() << std::endl;
    uint64_t insertedPos;
    bool insertInStore =   store->Append(serialized_record.c_str(), &insertedPos);
    bool insertInIndex = index->Write(uint32_t(nextOffset - baseOffset), insertedPos);
    if (insertInStore && insertInIndex) {
        nextOffset++;
        return true;
    } else {
         std::cerr << "Failed to Append Record." << std::endl;
         return false;
    }
     
}  
    logprog::v1::Record * Segment::Read(uint64_t offset) {
    //Offset is absolute offset  
    uint32_t out;
    uint64_t pos;
    std::cout << "In Index Reading from offset " << int64_t(offset - baseOffset) << std::endl;
    index->Read(int64_t(offset - baseOffset), &out, &pos);
        std::cout << "Position in Store File is " << pos << std::endl;
    if ((out == -1 && pos == -1)) {
        std::cout << "Can't Read Index File from Segment" << std::endl;
        return nullptr;
    }
  
     char ** data;
     data = new char*;
     size_t  returnedDataSize;
     store->Read(pos, data, &returnedDataSize);
    
    logprog::v1::Record* deserializedRecord = new logprog::v1::Record();
    if (! deserializedRecord->ParseFromString(std::string(*data,returnedDataSize))) {
        std::cerr << "Failed to parse serialized data into Record." << std::endl;
        delete [] data;
        return nullptr;
    }
    
    delete [] data;
    return deserializedRecord;
}

void Segment::Remove() {
        store->Remove();
        index->Remove();
    
}

void Segment::Close() {
         store->Close();
         index->Close();
}
bool Segment::IsMaxed() {
    return store->GetSize() >= config_->MaxStoreBytes || index->GetSize() >= config_->MaxIndexBytes;
}

uint64_t Segment::nearestMultiple(uint64_t j, uint64_t k) {
    if (j >= 0) {
        return (j / k) * k;
    }
    return ((j - k + 1) / k) * k;
}

uint64_t Segment::getBaseOffset() {return baseOffset;}

uint64_t Segment::getNextOffset() {return nextOffset;}

Segment::~Segment() {
    delete store;
    delete index;
}