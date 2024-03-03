#include "../../include/index/index.h"
 

namespace logModule {
    Index::Index(std::string filename) : fileName(filename) {
         const char* cFileName = fileName.c_str();
        fileDescriptor = open(cFileName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

        struct stat file_stat;
        if (fstat(fileDescriptor, &file_stat) == -1) {
            perror("Error getting file information");
            close(fileDescriptor);
        
        }
        size = file_stat.st_size;
        
        if (fileDescriptor == -1) {
            perror("Error opening file");
        }

        // Stretch the file size to the desired size
        if (lseek(fileDescriptor, desiredExpansionSize, SEEK_SET) == -1) {
            perror("Error stretching the file");
            close(fileDescriptor);
        }
        // In the next line we are decieving the os into thinking that the file has been expanded by
        // writing a byte at the end of the expansion size. This will allow the OS to allocate desired space on disk for us.
        if (write(fileDescriptor, "", 1) == -1) {
            perror("Error writing a byte to extend the file");
            close(fileDescriptor);
        }
        
        mMap = static_cast<char *>(mmap(0, desiredExpansionSize, PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, 0));
        
        if (mMap == MAP_FAILED) {
            perror("Error mapping file to memory");
            close(fileDescriptor);
        }
        fileExist = true;
    }

    Index::~Index() {
        if (fileExist) {
           // std::cout<<"In Destructor Index"<<endl;
            Close();
        }
    }

    void Index::Read(int64_t in, uint32_t *out, uint64_t *pos) {
        uint64_t tmpOut;
        uint64_t tmpPos;
        uint32_t o;
        if (size == 0) {
            *out = -1;
            *pos = -1;
            return;
        }
       
        if (in == -1) {
            tmpOut = (size / entWidth) - 1;
        } else {
            tmpOut = in;
        }
        // uint64_t out64 = reinterpret_cast<uint64_t>((*out));
        // std::cout<<"fooooool"<<std::endl;
        tmpPos = tmpOut * entWidth;

        
        if (desiredExpansionSize < tmpPos + entWidth) {
            *out = 0;
            *pos = 0;
            //LOOK HERE
            return;
        }
        
        memcpy(&o, mMap + tmpPos, offWidth);
        memcpy(&tmpPos, mMap + tmpPos + offWidth, posWidth);
        
        *out = o;
        *pos = tmpPos;
    }

    bool Index::Write(uint32_t off, uint64_t pos) {
        if (desiredExpansionSize < size + entWidth) {
            std::cout << "Size is " << size << " " << entWidth << std::endl;
            std::cout << "You are writing after end of file " << std::endl;
            return 0;
        }

        memcpy(mMap + size, &off, offWidth);
        memcpy(mMap + size + offWidth, &pos, posWidth);
        // uint32_t test_off; 
        // uint64_t test_pos;
        // memcpy(&test_off, mMap + size, offWidth);
        // memcpy(&test_pos, mMap + size + offWidth, posWidth);
        // std::cout << test_off << test_pos << std::endl;
        size += entWidth;
        return 1;
    }
    off_t Index::GetSize() {
        return size;
    }

    void Index::Close() {
        //Not needed
         if (msync(mMap, desiredExpansionSize, MS_SYNC) == -1) {
            perror("Error synchronizing changes to the file");
        }

        // Don't forget to unmap the memory when you're done
        if (munmap(mMap, desiredExpansionSize) == -1) {
            perror("Error unmapping file from memory");
        }

        // truncate the file back to the updated size
        if (ftruncate(fileDescriptor, size)) {
            perror("Error truncating the file");
        }
        //delete [] mMap;
        close(fileDescriptor);
    }
 
    void Index::Remove(){ // Don't use delete or any destructor for the same object that has been removed as u will get SEGV 
        Close();
        if (unlink(fileName.c_str()) == -1) {
            perror("unlink");
        }
        std::cout << "Removed the Index " << std::endl;
        fileExist = false;
       
    }
 

}
