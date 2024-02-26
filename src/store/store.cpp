#include "../../include/store/store.h"
#include <cstring>

namespace log {
    Store::Store(std::string filename) : fileName(filename) {
        file = new File(filename);
        int fileSize = file->GetFileSize(filename);
        if(fileSize != -1) {
            size = fileSize;
        }
    }

    Store::~Store() {
        delete file;
    }

    bool Store::Append(const char * data, uint64_t *returnPos) {
        std::lock_guard<std::mutex> lock(mutex);

        uint64_t position = size;
        *returnPos = position;
        size_t dataSize = std::strlen(data);
        
        bool success = true;
        success &= file->WriteFile(position, reinterpret_cast<const char*>(&dataSize), lenWidth);
        success &= file->WriteFile(position + lenWidth, data, dataSize);

        size += lenWidth + dataSize;

        return success;
    }

    void Store::Read(uint64_t position, char** data) {
        std::lock_guard<std::mutex> lock(mutex);

        size_t dataSize;
        file->ReadFile(position, reinterpret_cast<char*>(&dataSize), lenWidth);
        std::cout << "I am allocationg " << dataSize << " In Store . cpp " << std::endl;
        *data = new char[dataSize];
        file->ReadFile(position + lenWidth, *data, dataSize);
    }

    void Store::Close() {
        file->Close();
    }
    uint64_t Store::GetSize() {
        return size;
    }
}
