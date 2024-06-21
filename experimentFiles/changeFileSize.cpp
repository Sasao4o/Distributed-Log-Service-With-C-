#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>

int main() {
    const char* filename = "example.txt";
    int fileDescriptor = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fileDescriptor == -1) {
        perror("Error opening file");
        return 1;
    }

    // Stretch the file size to the desired size
    if (lseek(fileDescriptor, 1024, SEEK_SET) == -1) {
        perror("Error stretching the file");
        close(fileDescriptor);
        return 1;
    }
    
    if (write(fileDescriptor, "", 1) == -1) {
        perror("Error writing a byte to extend the file");
        close(fileDescriptor);
        return 1;
    }

    struct stat fileInfo;
    if (fstat(fileDescriptor, &fileInfo) == -1) {
        perror("Error getting file information");
        close(fileDescriptor);
        return 1;
    }
    off_t fileSize = fileInfo.st_size;
    std::cout << "Original file size: " << fileSize << std::endl;

    // Map the file into memory
    char* fileMemory = static_cast<char*>(mmap(0, fileInfo.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, 0));

    std::cout << "Original content:\n" << fileMemory << std::endl;

    if (fileMemory == MAP_FAILED) {
        perror("Error mapping file to memory");
        close(fileDescriptor);
        return 1;
    }

    // Write to the memory-mapped file
    const char* content = "Hello, Memory-Mapped World!2";
    std::strcat(fileMemory, content);

    // Synchronize changes to the file
    if (msync(fileMemory, std::strlen(fileMemory), MS_SYNC) == -1) {
        perror("Error synchronizing changes to the file");
    }

    // Unmap the memory
    if (munmap(fileMemory, fileInfo.st_size) == -1) {
        perror("Error unmapping file from memory");
        close(fileDescriptor);
        return 1;
    }

    // Truncate the file back to the size of the updated content
    if (ftruncate(fileDescriptor, 112)) {
        perror("Error truncating the file");
        close(fileDescriptor);
        return 1;
    }
    struct stat f_stat;
    int state = fstat(fileDescriptor, &f_stat);
    std::cout << "\nNew file size: " << f_stat.st_size << std::endl;
    // Close the file descriptor
    close(fileDescriptor);

    return 0;
}
