
#include "../segment/segment.h"
 #include <string>
#include <iostream>
#include <filesystem>
 #include "../../cmake/build/logprog.pb.h"
namespace logModule {
    class Log {
        public:
        Log(std::string directoryName,Config conf);
        void SetUp();
        void Append(logprog::v1::Record *record);
        logprog::v1::Record * Read(uint64_t offset);
        void Close();
        void Remove();
        void Reset();
        uint64_t LowestOffset();
        uint64_t HighestOffset();
        bool Truncate(uint64_t lowest);
        private:
        Config conf;
        std::string directoryPath; 
        std::mutex mtx;
        Segment *activeSegment;
        std::vector<Segment*>segments;
    };



};