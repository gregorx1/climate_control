#include <iostream>

#include "TemperatureControlImpl.h"

//using namespace std;

void TemperatureControlImpl::setTemperature(int temperature) {
  lock_guard<mutex> lock(m_mutex);
  m_temperature = temperature;
}

int TemperatureControlImpl::getTemperature() {
  lock_guard<mutex> lock(m_mutex);
  return m_temperature;
}

void TemperatureControlImpl::start() {
  m_thread = thread([this]() {
      while (m_running) {
        // Do some climate control logic here
        // ...
        // Sleep for a short time to avoid busy waiting
        cout << "In the thread" << endl;
        
        this_thread::sleep_for(chrono::milliseconds(1000));
      }
    });
}

void TemperatureControlImpl::stop() {
  m_running = false;
  m_thread.join();
}



