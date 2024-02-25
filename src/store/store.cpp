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

    bool Store::Append(const char * data) {
        std::lock_guard<std::mutex> lock(mutex);

        int position = size;
        size_t dataSize = std::strlen(data);
        
        bool success = false;
        success &= file->WriteFile(position, reinterpret_cast<const char*>(&dataSize), lenWidth);
        success &= file->WriteFile(position + lenWidth, data, dataSize);

        size += lenWidth + dataSize;

        return success;
    }

    void Store::Read(int position, char* data) {
        std::lock_guard<std::mutex> lock(mutex);

        size_t dataSize;
        file->ReadFile(position, reinterpret_cast<char*>(&dataSize), lenWidth);
        file->ReadFile(position + lenWidth, data, dataSize);
    }

    void Store::Close() {
        file->Close();
    }
}
