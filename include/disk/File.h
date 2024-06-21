#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include<mutex>
namespace logModule {

class File {
public:
    File(std::string fileName);
    ~File() = default;

    void WriteFile(uint64_t offset, const char* data, int size);
    void ReadFile(uint64_t offset, char* data, int size);
    void Close();
    int GetFileSize(const std::string& file_name);

private:
    std::string fileName;
    std::fstream fileIo;
    std::mutex db_io_latch_;
};

}

#endif // FILE_H
