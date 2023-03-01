#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <optional>
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
    //std::scope_lock s_lock{_mutex} - ��������� ��������� mutex ������ � ��� ������������������ � ������� �� �������� � {} fhuevtyns 
    //void successMessage() {
    //    std::lock_guard<std::mutex> lock(_mutex);
    //    std::cout << "success Message" << std::endl;
    //}

    void someFunc() {
        std::lock_guard<std::mutex> lock(_mutex);//��������� ����������� ��������, ���� �� �������� ��� ���� ��������� �� ����� ���������� � �������������� ������. 
       //� ���������� ���������� � ���������� ���������� ����� �������� 1 ����� �� ������������ ���������� �������
        std::cout << "some text" << std::endl;
        std::lock_guard<std::mutex> lock2(_secondMutex);
        // deadlock
    }
    void log1(const std::string& message) {
        std::lock_guard<std::recursive_mutex> lock(_rMutex);
        std::cout << "[" << _counter << "]" << message << "\n";
        successMessage();
    }
    void successMessage() {
        std::lock_guard<std::recursive_mutex> lock(_rMutex);
        std::cout << "message" << std::endl;
    }
   std::optional<std::string> returnIfInit() {
        bool isFound = false;
        if (isFound) {
            return std::string("success");
        }
        return std::nullopt;
    }
private:
    std::mutex _mutex;
    std::mutex _secondMutex;
    int _counter = 0;
    std::recursive_mutex _rMutex; //��������� ���� ����������� ������ ������ ����� ���
};

int main()//��� ��� ���������� � ����� ��� Mainthread, ������ ��� ������ ������ ��� ������ ���������
{
    //Logger logger;
    //logger.log("Hello");
    //logger.log("Info message");

    //std::thread t1 = std::thread([&logger]() {//������ ������� ������ [] ������ logger
    //    std::string threadName = "t1";
    //    for (size_t i = 0; i < 100; i++) {
    //        logger.log(threadName + " doing "
    //            + std::to_string(i) + " iteration of work\n");
    //        logger.someFunc();
    //    }
    //    });

    //std::thread t2 = std::thread([&logger]() {
    //    std::string threadName = "t2";
    //    for (size_t i = 0; i < 100; i++) {
    //        logger.log(threadName + " doing "
    //            + std::to_string(i) + " iteration of work\n");
    //        logger.someFunc();
    //    }
    //    });

    //t1.join(); t2.join();//����  ���� ����� t1 ���������������� ����� ������� ��� . ����� �� �� ����� �� ������ �������

    //optional
    std::string s; // ����� ����������� �� ��������� �� ����� ����� ��������
    //int x; �� ����� �������� ��� ����������
    bool isInit = false;// ������� ����
    std::optional<int> val = std::nullopt;//����������� ������������ �� ������������������ ����������..���������� � ��������� ������� ��� ��� ������
    val = 5;
    if (val.has_value()) {
        std::cout << "val has value " << val.value() << std::endl;
    }
    else {
        std::cout << "no" << std::endl;
    }
  //  std::cout << val.value() << std::endl; - error
}