#include <cstdint>
#ifndef ConfigModule
#define ConfigModule
struct Config {
    uint64_t  MaxStoreBytes = 1024;  
	uint64_t 	MaxIndexBytes = 1024; 
	uint64_t	InitialOffset = 0;  

};
#endif