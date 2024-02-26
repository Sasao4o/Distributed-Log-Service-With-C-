#include <cstdint>
#ifndef ConfigModule
#define ConfigMoudle
struct Config {
    uint64_t  MaxStoreBytes;  
	uint64_t 	MaxIndexBytes; 
	uint64_t	InitialOffset;  

};
#endif