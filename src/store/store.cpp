#include "../../include/store/store.h"
 

namespace logModule {
    Store::Store(std::string filename) : fileName(filename) {
        file = std::unique_ptr<File>(new File(filename));
        int fileSize = file->GetFileSize(filename);
        if(fileSize != -1) {
            size = fileSize;
        }
        fileExist = true;
    }

    Store::~Store() {
        //This RAII CLASS WHICH WILL BE CLOSED AUTOMATICALLY IF IT AQUIRE THE RESOURCE (IF NOT THE CONSTRUCTOR WOULD HAVE FAILED)
        // if (fileExist) {
        // Close();
        // }
    }

    void Store::Append(const char * data, uint64_t *returnPos) {
        std::lock_guard<std::mutex> lock(mtx);
        uint64_t position = size;
        *returnPos = position;
        size_t dataSize = std::strlen(data);
        std::cout << "In Store Append Size is " << dataSize << std::endl;
        // throw std::runtime_error("FAYROUX"); 
        try {
        file->WriteFile(position, reinterpret_cast<const char*>(&dataSize), lenWidth);
        file->WriteFile(position + lenWidth, data, dataSize);
        size += (lenWidth + dataSize);
        } catch (std::runtime_error &e) {
            std::cout << "Throwing From Store Append" << std::endl;
            throw;
        }
    }

    void Store::Read(uint64_t position, char** data, size_t * returnedDataSize) {
       std::lock_guard<std::mutex> lock(mtx);
        size_t dataSize;
        file->ReadFile(position, reinterpret_cast<char*>(&dataSize), lenWidth);
        *returnedDataSize = dataSize;
        std::cout << "I am allocationg " << dataSize << " In Store . cpp " << std::endl;
        // *data = new char[dataSize];
        //Work alone and i will release the ownership later !! (ENFORCING RAII)
        std::unique_ptr<char[]> tempData(new char[dataSize]);
  
        file->ReadFile(position + lenWidth, tempData.get(), dataSize);
        // throw std::runtime_error("THROW FOR TEST MEMORY LEAKS"); SIMULATE READFILE THROWS
   
        *data = tempData.release();
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
