#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <sys/stat.h>

namespace log {

class File {
public:
    File(std::string fileName);
    ~File() = default;

    bool WriteFile(int offset, const char* data, int size);
    bool ReadFile(int offset, char* data, int size);
    void Close();
    int GetFileSize(const std::string& file_name);

private:
    std::string fileName;
    std::fstream fileIo;
};

}

#endif // FILE_H
