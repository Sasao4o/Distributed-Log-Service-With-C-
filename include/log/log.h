#ifndef LogModule
#define LogModule


#include "../segment/segment.h"
 #include <string>
#include <iostream>
#include <filesystem>
 #include "../../cmake/build/logprog.pb.h"
namespace logModule {
    class Log {
        public:
        Log(std::string directoryName,Config conf);
        ~Log();
        void SetUp();
        bool Append(logprog::v1::Record *record, uint64_t *offset );
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
        Segment *activeSegment = nullptr;
        std::vector<Segment*>segments;
    };



};

#endif