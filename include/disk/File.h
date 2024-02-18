#include <fstream>
#include<string>
#include<iostream>
#include <sys/stat.h>
namespace log {
class File {

    public:
    File(std::string fileName);
    void WriteFile(int offset, const char * data, int size);
    void ReadFile(int offset,  char*data, int size);
    void Close();
    int GetFileSize(const std::string &file_name);
    private:
    std::fstream fileIo;   //File streams are associated with files either on construction, or by calling member open.
    std::string fileName;


};



}