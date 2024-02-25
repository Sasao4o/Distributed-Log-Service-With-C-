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

        bool Append(const char * data);
        void Read(int position, char* data);
        void Close();

    private:
        File* file;
        std::string fileName;
        int size;
        std::mutex mutex;
    };
}

#endif // STORE_H
