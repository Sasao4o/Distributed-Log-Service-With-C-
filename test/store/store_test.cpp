#include "../../include/store/store.h"

#include <cassert>

#include <cstring>

#include<vector>

#include <thread>

using namespace logModule;

template < typename T >
  struct free_functor {
    void operator()(T * ptr) {
      std::cout << "Freing From FREE FUNCTOR" << std::endl;
      delete[] * ptr;
      delete ptr;
      ptr = nullptr;
    }
  };
void BasicTest() {
  //Just Insert 2 Records snad Reterive One
  Store store("../../logsData/store");
  const char * data_1 = "Hello, Buffered Writer!";
  // size_t size_1 = 24;
   const char * data_2 = "Hello, Buffered Writer2!";
 

  // size_t size_2 = 25;
  uint64_t returnedPos, returnedPos1;
  store.Append(data_1, & returnedPos);
  store.Append(data_2, & returnedPos1);
  char ** data = new char * ;
  * data = nullptr;
  size_t s;
  try {
    store.Read(returnedPos1, data, & s);
    std::cout << "Size is " << s << std::endl;
    assert(std::memcmp(data_2, *data, s) == 0);
  } catch (std::runtime_error & E) {
    std::cout << "Errrrorr" << std::endl;
    std::cout << E.what() << std::endl;
  }
  delete[] * data;
  delete data;
  store.Remove();
}

void InsertAndReterive() {
  try {
    Store store("../../logsData/store");
    for (int i = 0; i < 100; i++) {
      uint64_t returnedPos;
      char * name = "Mostafa";
      store.Append(name, & returnedPos);
    }
    uint64_t pos = 0;
    for (int i = 0; i < 100; i++) {
      char ** AX = new char * ;
      std::shared_ptr < char * > data(AX, free_functor < char * > ());
      size_t s;
      store.Read(pos, data.get(), & s);
      std::cout << * data << std::endl;
      char * answer = "Mostafa";
      assert(std::memcmp(answer, *data, s) == 0);
      pos += (s + 8); //(This 8 is the size length (SIZE|DATA) you want jump the size)
    }
    store.Remove();
  } catch (std::runtime_error & E) {
    std::cout << E.what() << std::endl;
  }

  //   delete *m;

}

void AppendToStore(Store & store, int size) {
  try {
    for (int i = 0; i < size; ++i) {
      uint64_t returnedPos;
      const char * name = "Hello Buffered Data";
      store.Append(name, & returnedPos);
    }
  } catch (std::runtime_error & e) {
    std::cout << e.what() << std::endl;
    std::cout << "FROM APPEND THROW EXCEIPTION" << std::endl;
    throw;
  }
}
void ReadFromStore(Store & store, int startIndex, int size) {
  try {
    uint64_t pos = 0;
    for (int i = startIndex; i < (startIndex + 1) * size; i++) {
      char ** AX = new char * ;
      std::shared_ptr < char * > data(AX, free_functor < char * > ());
      size_t s;
      store.Read(pos, data.get(), & s);
      std::cout << * data << std::endl;
      char * answer = "Hello Buffered Data";
      assert(std::memcmp(answer, * data, s) == 0);
      pos += (s + 8); //(This 8 is the size length (SIZE|DATA) you want jump the size)
    }
  } catch (std::runtime_error & E) {
    std::cout << "Handling ReadFrom Store" << std::endl;
    std::cout << E.what() << std::endl;
    throw;
  }
}
void ConcurrentInsertAndReterive() {
  bool exceptionThrown = false;
  Store store("../../logsData/store");
  try {
    std::vector < std::thread > threads;

    // Number of threads
    const int numThreads = 3;

    // Start threads
    for (int i = 0; i < numThreads; ++i) {
      threads.emplace_back([ & store]() {
        AppendToStore(store, 30);
      });
    }
    for (auto & thread: threads) {
      thread.join();
    }
    uint64_t pos = 0;
    for (int i = 0; i < 90; i++) {
      char ** AX = new char * ;
      std::shared_ptr < char * > data(AX, free_functor < char * > ());
      size_t s;
      store.Read(pos, data.get(), & s);
      std::cout << * data << std::endl;
      char * answer = "Hello Buffered Data";
      assert(std::memcmp(answer, * data, s) == 0);
      pos += (s + 8); //(This 8 is the size length (SIZE|DATA) you want jump the size)
    }
  } catch (std::runtime_error & E) {
    exceptionThrown = true;
    std::cout << E.what() << std::endl;
  }
  store.Remove();
  assert(exceptionThrown == false);

}

void ConcurrentInsertAndConcurrentReterive() {
  bool exceptionThrown = false;
  Store store("../../logsData/store");
  try {
    std::vector < std::thread > threads;

    // Number of threads
    const int numThreads = 10;

    // Start threads
    for (int i = 0; i < numThreads; ++i) {
      threads.emplace_back([ & store]() {
        AppendToStore(store, 400);
      });
    }
    for (auto & thread: threads) {
      thread.join();
    }

    threads.clear();
    for (int i = 0; i < numThreads; ++i) {
      threads.emplace_back([ & store, i]() {
        ReadFromStore(store, i, 400);
      });
    }
    for (auto & thread: threads) {
      thread.join();
    }
  } catch (std::runtime_error & e) {
    exceptionThrown = true;
  }
  store.Remove();
  assert(exceptionThrown == false);

}

int main() {
  // ConcurrentInsertAndConcurrentReterive();
  ConcurrentInsertAndReterive();
  // BasicTest();
  // InsertAndReterive();
}
