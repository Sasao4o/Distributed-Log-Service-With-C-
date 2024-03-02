#include "../../include/store/store.h"
 

namespace logModule {
    Store::Store(std::string filename) : fileName(filename) {
        file = new File(filename);
        int fileSize = file->GetFileSize(filename);
        if(fileSize != -1) {
            size = fileSize;
        }
        fileExist = true;
    }

    Store::~Store() {
        if (fileExist) {
        Close();
        }
    }

    bool Store::Append(const char * data, uint64_t *returnPos) {
        std::lock_guard<std::mutex> lock(mtx);

        uint64_t position = size;
        *returnPos = position;
        size_t dataSize = std::strlen(data);
        std::cout << "In Store Append Size is " << dataSize << std::endl;
        bool success = true;
        success &= file->WriteFile(position, reinterpret_cast<const char*>(&dataSize), lenWidth);
        success &= file->WriteFile(position + lenWidth, data, dataSize);

        size += (lenWidth + dataSize);

        return success;
    }

    void Store::Read(uint64_t position, char** data, size_t * returnedDataSize) {
        std::lock_guard<std::mutex> lock(mtx);

        size_t dataSize;
        file->ReadFile(position, reinterpret_cast<char*>(&dataSize), lenWidth);
        *returnedDataSize = dataSize;
        std::cout << "I am allocationg " << dataSize << " In Store . cpp " << std::endl;
        *data = new char[dataSize];
        file->ReadFile(position + lenWidth, *data, dataSize);
    }

    void Store::Close() {
        file->Close();
        // delete file;
    }
    uint64_t Store::GetSize() {
        return size;
    }
    void Store::Remove(){  // Don't use delete or any destructor for the same object that has been removed as u will get SEGV 
        Close();
        const char* cFileName = fileName.c_str();
        if (unlink(cFileName) == -1) {
            perror("unlink");
        }
        fileExist = false;
         
    }
}
