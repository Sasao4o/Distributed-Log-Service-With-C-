#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

class BufferedWriter {
public:
    BufferedWriter(std::ostream& stream, size_t bufferSize = 4096) : stream(stream), buffer(bufferSize), index(0) {}

    ~BufferedWriter() {
        Flush();
    }

    void Write(const char* data, size_t size) {
        for (size_t i = 0; i < size; ++i) {
            buffer[index++] = data[i];

            if (index == buffer.size()) {
                Flush();
            }
        }
    }

    void Flush() {
        if (index > 0) {
            stream.write(buffer.data(), index);
            index = 0;
        }
    }

private:
    std::ostream& stream;
    std::vector<char> buffer;
    size_t index;
};

int main() {
    std::ofstream file("example.txt");
    BufferedWriter writer(file);

    const char* data = "Hello, Buffered Writer!";
    size_t size = 24;

    writer.Write(data, size);
    writer.Flush(); 

    return 0;
}
