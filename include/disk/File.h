#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <sys/stat.h>

namespace logModule {

class File {
public:
    File(std::string fileName);
    ~File() = default;

    bool WriteFile(uint64_t offset, const char* data, int size);
    bool ReadFile(uint64_t offset, char* data, int size);
    void Close();
    int GetFileSize(const std::string& file_name);

private:
    std::string fileName;
    std::fstream fileIo;
};

}

#endif // FILE_H
