#include "../../include/store/store.h"

int main() {
    using namespace log;

    Store store("store");

    const char* data_1 = "Hello, Buffered Writer!";
    size_t size_1 = 24;
    const char* data_2 = "Hello, Buffered Writer2!";
    size_t size_2 = 25;

    store.Append(data_1);
    store.Append(data_2);

    char* data = new char[size_2];
    store.Read(31, data);

    for (size_t i = 0; i < size_2; i++) {
        std::cout << data[i];
    }

    delete[] data;

    return 0;
}
