#ifndef __TEMP_CTRL_IMPL_H__
#define __TEMP_CTRL_IMPL_H__

#include <mutex>
#include <thread>

using namespace std;

//we may inherit from abstract API class here to define pure API
class TemperatureControlImpl {
public:
  static const int POLLING_INTERVAL_MS = 1000;
  static const int INITIAL_LOW_LIMIT = 10;
  static const int INITIAL_HIGH_LIMIT = 20;

  static TemperatureControlImpl& getInstance() {
    static TemperatureControlImpl instance;
    return instance;
  }

  int getLowLimit();
  int getHighLimit();

  void setLowLimit(int temperature);
  void setHighLimit(int temperature);

  // random value returned instead of real measurement here
  int getCurrentTemperature();

  void start();
  void stop();

private:
    TemperatureControlImpl() :
      m_low_limit(INITIAL_LOW_LIMIT),
      m_high_limit(INITIAL_HIGH_LIMIT),
      m_polling_interval_ms(POLLING_INTERVAL_MS),
      m_temperature(0),
      m_running(true) {}

    ~TemperatureControlImpl() {}

    typedef enum deviceState{TURN_OFF,TURN_ON} deviceState_t;

    void switchCooler(deviceState_t);
    void switchHeater(deviceState_t);

    int m_low_limit;
    int m_high_limit;
    int m_polling_interval_ms;
    int m_temperature;
    bool m_running;

    thread m_thread;
    mutex m_mutex;
};

#endif
