#ifndef STORE_H
#define STORE_H

#include <iostream>
#include <mutex>
#include "../disk/File.h"
#include <string>

namespace log {
    const size_t lenWidth = 8;

    class Store {
    public:
        Store(std::string filename);
        ~Store();

        bool Append(const char * data, uint64_t *returnPos);
        void Read(uint64_t position, char** data);
        void Close();
        uint64_t GetSize();
    private:
        File* file;
        std::string fileName;
        uint64_t size;
        std::mutex mutex;
    };
}

#endif // STORE_H
