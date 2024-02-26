#include "../../include/disk/File.h"
 
namespace log {

File::File(std::string fileName) : fileName(fileName) {
    fileIo.open(fileName, std::ios::binary | std::ios::in | std::ios::out);
    if (!fileIo.is_open()) {
    fileIo.clear();
    // create a new file
    fileIo.open(fileName, std::ios::binary | std::ios::trunc | std::ios::in | std::ios::out);
    if (!fileIo.is_open()) {
        std::cout << "Cant Open DB File" << std::endl;
  ;
    }
  }
}

  bool File::WriteFile(uint64_t offset, const char * data, int size) {
        std::cout << "Writing To File" << std::endl;
        fileIo.seekp(offset);
        fileIo.write(data, size);
        if (fileIo.bad()) {
            std::cout <<  "The fileIo crashes"  << std::endl;
            return false;
        }
        fileIo.flush(); //This can protect from ungracful shut down but nullifies the buffering property of fstreams "Need to make an abstract recovery schema"
        return true;
  }



bool File::ReadFile(uint64_t offset,  char *data, int size) {
 
  if (offset > GetFileSize(fileName)) {
      std::cout << "I/O error reading past end of file" << std::endl ;
      return false;
        // throw "I/O error reading past end of file";
  } else {
    // set read cursor to offset
    fileIo.seekp(offset);
    fileIo.read(data, size);
    if (fileIo.bad()) {
    std::cout << "I/O While Reading" << std::endl;
      return false;
    }
    return true;
  }
}
void File::Close() {
    fileIo.close();
}
int File::GetFileSize(const std::string &file_name)  {
  struct stat stat_buf;
  int rc = stat(file_name.c_str(), &stat_buf);
  return rc == 0 ? static_cast<int>(stat_buf.st_size) : -1;
}
}