#ifndef __TEMP_CTRL_IMPL_H__
#define __TEMP_CTRL_IMPL_H__

#include <mutex>
#include <thread>

using namespace std;

class TemperatureControlImpl {
public:
    static TemperatureControlImpl& getInstance() {
        static TemperatureControlImpl instance;
        return instance;
    }

    void setTemperature(int temperature);
    int getTemperature();

    void start(); 
    void stop();

private:
    TemperatureControlImpl() : m_temperature(0), m_running(true) {}
    ~TemperatureControlImpl() {}

    int m_temperature;
    bool m_running;
    thread m_thread;
    mutex m_mutex;
};

#endif
