#include "../../include/log/log.h"

namespace fs = std::filesystem;

namespace logModule {

  Log::Log(std::string directoryPath,  std::shared_ptr<Config>config ): directoryPath(directoryPath), conf(config) {

  };

  void Log::SetUp() {
    std::string path = directoryPath;
    std::vector<uint64_t>baseOffsets;
    for (const auto & entry: fs::directory_iterator(path)) {
      std::string filename = entry.path().filename();
      size_t dotPos = filename.find_last_of('.');
      std::string newFileName;
      if (dotPos != std::string::npos) {
        newFileName = filename.substr(0, dotPos);
      }
        uint64_t num = std::stoull(newFileName);
        baseOffsets.push_back(num);
    }

    std::sort(baseOffsets.begin(), baseOffsets.end());
    for (int i = 0; i < baseOffsets.size(); i = i + 2) {
        // Segment * currentSeg = new Segment(directoryPath, baseOffsets[i], &conf);
        std::shared_ptr<Segment> currentSeg = std::make_shared<Segment>(directoryPath, baseOffsets[i], conf);

        segments.push_back(currentSeg);
        activeSegment = currentSeg;
    }

    if (segments.size() == 0) {
        // Segment * currentSeg = new Segment(directoryPath, conf.InitialOffset, &conf);
            std::shared_ptr<Segment> currentSeg = std::make_shared<Segment>(directoryPath, conf->InitialOffset, conf);
        segments.push_back(currentSeg);
        activeSegment = currentSeg;
    }
  }

  void Log::Append(logprog::v1::Record *record, uint64_t *offset) {
    std::lock_guard<std::mutex> lock(mtx);
       activeSegment->Append(record);
      *offset = activeSegment->getNextOffset() - 1;// offset is one less than the next record
      if (activeSegment->IsMaxed()) {
        uint64_t currentOffset = activeSegment->getNextOffset(); 
        activeSegment =  std::shared_ptr<Segment>(new Segment(directoryPath, currentOffset, conf));
        segments.push_back(activeSegment);
      }
    
   
  }

 logprog::v1::Record * Log::Read(uint64_t offset) {
     std::lock_guard<std::mutex> lock(mtx);
    //  Segment *currentSeg = nullptr;
    std::shared_ptr<Segment>currentSeg = nullptr;
     for (int i = 0; i < segments.size(); i++) {
       
      if (segments[i]->getBaseOffset() <= offset && offset < segments[i]->getNextOffset()) {
        currentSeg = segments[i];
      }
     }
 
  if (currentSeg == nullptr) {
    std::cout << "The Offset is Out Of Range " << offset << std::endl;
    throw std::runtime_error("The Offset is Out of Range");
    return nullptr;
  } 
    return currentSeg->Read(offset);
 }

 void Log::Close() {
  std::lock_guard<std::mutex> lock(mtx);
  for (int i = 0; i < segments.size(); i++) {
    segments[i]->Close();
  }

 }

 void Log::Remove() {
  std::lock_guard<std::mutex> lock(mtx); //The book didn't put this ?
  for (int i = 0; i < segments.size(); i++) {
    segments[i]->Remove();
  }
  std::cout << "Done Removing Segments" << std::endl;
  segments.clear();
 }
 void Log::Reset() {
  std::lock_guard<std::mutex> lock(mtx);
  this->Remove();
  this->SetUp();
 }

 uint64_t Log::LowestOffset() {
  std::lock_guard<std::mutex> lock(mtx);
  if (segments.size() == 0) {
    return 0;
  }
  return segments[0]->getBaseOffset();
 }
uint64_t Log::HighestOffset() {
    std::lock_guard<std::mutex> lock(mtx);
   if (segments.size() == 0) {
    return 0; //what error can i return here? LOOK HERE
   }
   return segments[segments.size() - 1]->getNextOffset() - 1;
 }

 bool Log::Truncate(uint64_t lowest) {
    std::lock_guard<std::mutex> lock(mtx);
  
    std::vector<std::shared_ptr<Segment>>newSegments;
    for (int i = 0; i < segments.size(); i++) {
      if (segments[i]->getNextOffset() - 1 <= lowest) {
        segments[i]->Remove();
      } else {
        newSegments.push_back(segments[i]);
      }
    }
    std::cout << "Done Truncating" << std::endl;
    this->segments = newSegments;
    return true;
 } 
   Log::~Log() {
    // for (int i = 0; i < segments.size(); i++) {
    //   delete segments[i];
    // }
  }
}