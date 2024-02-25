#include "../../include/index/index.h"

int main() {
    using namespace Log;

    // Test case 1: Create an Index instance and write some entries
    Index index("index");
    index.Write(100, 1000);
    index.Write(200, 2000);
    index.Write(300, 3000);

    // Test case 2: Read the entries and print them
    uint32_t* offset = new uint32_t();
    uint64_t* position = new uint64_t();

    index.Read(0, offset, position);
    std::cout << "Read entry at position " << *position << ": Offset = " << *offset << std::endl;

    // Test case 3: Attempt to read an out-of-bounds entry
    index.Read(5, offset, position);
    std::cout << "Attempted to read out-of-bounds entry. Offset = " << *offset << ", Position = " << *position << std::endl;

    delete [] offset;
    delete [] position;

    return 0;
}
