#include "../../include/store/store.h"
#include <cassert>
#include <cstring>

 using namespace log;
void BasicTest() {
    
    Store store("store");

    const char* data_1 = "Hello, Buffered Writer!";
    size_t size_1 = 24;
    const char* data_2 = "Hello, Buffered Writer2!";
    size_t size_2 = 25;
    uint64_t returnedPos, returnedPos1;
    store.Append(data_1, &returnedPos);
    store.Append(data_2, &returnedPos1);

    char* data = new char[size_2];
    store.Read(31, &data);

    for (size_t i = 0; i < size_2; i++) {
        std::cout << data[i];
    }

    delete[] data;

}

void InsertAndReterive() {
 
    
    Store store("store");
    for (int i = 0; i < 100; i++) {
    uint64_t returnedPos;
    char *name = "Mostafa";
    store.Append(name, &returnedPos);
    }
      uint64_t pos = 0;
      for (int i = 0; i < 100; i++) {
         std::cout << "I is " << i << std::endl;
        uint32_t x;
        uint64_t y;
        char ** m = new char *;
        store.Read(pos, m);
        std::cout << *m << std::endl;
        char *answer = "Mostafa";
        assert(std::strcmp(answer, *m) == 0);
        delete [] m;
        
        pos += 15;
    }
  
//   delete *m;
   
 
}
 
int main() {
 InsertAndReterive();
 
 
}
