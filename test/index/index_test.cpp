<<<<<<< HEAD
#include "../../include/index/index.h"
#include <cassert>
 using namespace log;

void BasicTest() {
 
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
 
}

void InsertAndReterive() {
 
    
    Index index("index");
    for (int i = 0; i < 100; i++) {
    
    index.Write(i, 1000);
    }
      for (int i = 0; i < 100; i++) {
         std::cout << "I is " << i << std::endl;
        uint32_t x;
        uint64_t y;
        index.Read(i, &x, &y);
        assert(y == 1000);
        assert(x ==   i);

    }
  
 
}
int main() {
    InsertAndReterive();
}
=======
#include "../../include/index/index.h"
#include <cassert>
 using namespace log;

void BasicTest() {
 
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

    delete offset;
    delete position;
 
}

void InsertAndReterive() {
 
    
    Index index("index");
    for (int i = 0; i < 100; i++) {
    
    index.Write(i, 1000);
    }
      for (int i = 0; i < 100; i++) {
         std::cout << "I is " << i << std::endl;
        uint32_t x;
        uint64_t y;
        index.Read(i, &x, &y);
        assert(y == 1000);
        assert(x ==   i);

    }
  
 
}
int main() {
    InsertAndReterive();
}
>>>>>>> origin/WaelBranch
