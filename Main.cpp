#include <iostream>
#include <thread>
#include <mutex>
#include <string>
// Mutex, deadlock, recursive_mutex

class Logger {
public:
    // race condition 
    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(_mutex);
        std::cout << "[" << _counter << "]" << message << "\n";
        _counter++;
        std::lock_guard<std::mutex> lock2(_secondMutex);
    }

    //void successMessage() {
    //    std::lock_guard<std::mutex> lock(_mutex);
    //    std::cout << "success Message" << std::endl;
    //}

    void someFunc() {
        std::lock_guard<std::mutex> lock(_mutex);
        std::cout << "some text" << std::endl;
        std::lock_guard<std::mutex> lock2(_secondMutex);
        // deadlock
    }

private:
    std::mutex _mutex;
    std::mutex _secondMutex;
    int _counter = 0;
};

int main()
{
    Logger logger;
    logger.log("Hello");
    logger.log("Info message");

    std::thread t1 = std::thread([&logger]() {
        std::string threadName = "t1";
        for (size_t i = 0; i < 100; i++) {
            logger.log(threadName + " doing "
                + std::to_string(i) + " iteration of work\n");
            logger.someFunc();
        }
        });

    std::thread t2 = std::thread([&logger]() {
        std::string threadName = "t2";
        for (size_t i = 0; i < 100; i++) {
            logger.log(threadName + " doing "
                + std::to_string(i) + " iteration of work\n");
            logger.someFunc();
        }
        });

    t1.join(); t2.join();
}