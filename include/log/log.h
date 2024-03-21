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
        Log(std::string directoryName,std::shared_ptr<Config>conf);
        ~Log();
        void SetUp();
        void Append(logprog::v1::Record *record, uint64_t *offset );
        logprog::v1::Record * Read(uint64_t offset);
        void Close();
        void Remove();
        void Reset();
        uint64_t LowestOffset();
        uint64_t HighestOffset();
        bool Truncate(uint64_t lowest);
        private:
        std::shared_ptr<Config>conf;
        std::string directoryPath; 
        std::mutex mtx;
        // Segment *activeSegment = nullptr;
        std::shared_ptr<Segment>activeSegment = nullptr;
        std::vector<std::shared_ptr<Segment>>segments;
    };



};

#endif