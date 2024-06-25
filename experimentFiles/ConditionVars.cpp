#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

std::queue<int> dataQueue;
std::mutex mtx;
std::condition_variable cv;
bool finished = false;

void producer() {
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //std::lock_guard<std::mutex> lock(mtx);
        dataQueue.push(i);
        std::cout << "Produced: " << i << std::endl;
        //cv.notify_one();
    }
    //finished = true;
    //cv.notify_all();
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        if(cv.wait_for(lock, std::chrono::milliseconds(150), []{ return  finished; })){
            while (!dataQueue.empty()) {
            int data = dataQueue.front();
            dataQueue.pop();
            std::cout << "Consumed: " << data << std::endl;
        }

        if (finished && dataQueue.empty()) break;
        }
        std::cout<<"didn't"<<std::endl;

        
    }
}

int main() {
    dataQueue.push(15);
dataQueue.push(29);
    std::thread prod(producer);
    std::thread prod2(producer);
    std::thread cons(consumer);

    prod.join();
    prod2.join();
    cons.join();

    return 0;
}
