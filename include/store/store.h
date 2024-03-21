#ifndef STORE_H
#define STORE_H
#include <mutex>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include<memory>
#include "../disk/File.h"
#include <string>
#include <cstdint>
namespace logModule {
    const size_t lenWidth = 8;

    class Store {
    public:
        Store(std::string filename);
        ~Store();

        void Append(const char * data, uint64_t *returnPos);
        void Read(uint64_t position, char** data, size_t * returnedDataSize);
        void Close();
        void Remove();
        uint64_t GetSize();
    private:
        bool fileExist = false;
        // File* file;
        std::unique_ptr<File>file;
        std::string fileName;
        uint64_t size;
        std::mutex mtx;
    };
}

#endif // STORE_H
