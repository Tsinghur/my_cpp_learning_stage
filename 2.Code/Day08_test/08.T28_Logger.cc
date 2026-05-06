#include <string.h>
#include <iostream>

using namespace std;

class Logger {
public:
    static Logger* getInstance() {
        if (m_instance == nullptr) {
            m_instance = new Logger();
        }
        
        return m_instance;
    }
    static void destroyInstance() {
        if (m_instance != nullptr) {
            delete m_instance;
            m_instance = nullptr;
        }
    }
    void log(const char* str) {
        cout << str << endl;
    }
private:
    static Logger* m_instance;
    Logger() {}
    ~Logger() {}
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};
Logger* Logger::m_instance = nullptr;

int main() {
    cout << Logger::getInstance() << endl;
    cout << Logger::getInstance() << endl;
    Logger* logger = Logger::getInstance();
    cout << logger << endl;
    logger->log("test1");
    logger->log("test2");
    logger->log("test3");

    return 0;
}
