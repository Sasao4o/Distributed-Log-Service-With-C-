#ifndef INDEX_H
#define INDEX_H

#include <iostream>
#include <cstdint>
#include "../disk/File.h"
namespace log {
    class Index {
    public:
        Index(std::string filename);
        ~Index();

        void Read(int64_t in, uint32_t *out, uint64_t *pos);
        bool Write(uint32_t off, uint64_t pos);
        off_t GetSize();
        void Remove();
        void Close();
    private:
        int fileDescriptor;
        std::string fileName;
        char* mMap;
        off_t size;

        static constexpr uint64_t offWidth = 4;
        static constexpr uint64_t posWidth = 8;
        static constexpr uint64_t entWidth = offWidth + posWidth;
        static constexpr uint64_t desiredExpansionSize = 10240;
    };
}

#endif // INDEX_H
