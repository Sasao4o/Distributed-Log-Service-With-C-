
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int Write(char* mMap, uint64_t size,uint32_t off, uint64_t pos) {
        if (1024 < size + 12) {
            return -1;
        }

        memcpy(mMap + size, &off, 4);
        memcpy(mMap + size + 4, &pos, 8);

        size += 12;
        return 0;
}
int main(){
    char* mMap = new char(1024);
    uint64_t size = 0;
    int l = Write(mMap, size, 100, 1000);
    //cout << "Write result: "<< l << endl;
    // for (int i = 0; mMap[i] != '\0'; ++i) {
    //     cout << mMap[i];
    // }
    uint32_t copiedInt_1;
    uint64_t copiedInt_2;
    memcpy(&copiedInt_1, mMap, 4);
    memcpy(&copiedInt_2, mMap+4, 8);
    cout<<copiedInt_1<<copiedInt_2<<endl;
    delete [] mMap; 
    return 0;
}
