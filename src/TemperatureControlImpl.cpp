#include <iostream>
#include <cstdlib>
#include <ctime>

#include "TemperatureControlImpl.h"

using namespace std;

void TemperatureControlImpl::setLowLimit(const int temperature) {
  {
    lock_guard<mutex> lock(m_mutex);
    m_low_limit = temperature;
  }

  cout << "Low limit set to " << m_low_limit << endl;
}

void TemperatureControlImpl::setHighLimit(const int temperature) {
  {
    lock_guard<mutex> lock(m_mutex);
    m_high_limit = temperature;
  }

  cout << "High limit set to " << m_high_limit << endl;
}

int TemperatureControlImpl::getLowLimit() const {
  return m_low_limit;
}

int TemperatureControlImpl::getHighLimit() const {
  return m_high_limit;
}

void TemperatureControlImpl::switchCooler(const deviceState_t state) {
  cout << "Cooler turned " << (state==TURN_OFF?"OFF":"ON") << endl;
}

void TemperatureControlImpl::switchHeater(deviceState_t state) {
  cout << "Heater turned " << (state==TURN_OFF?"OFF":"ON") << endl;
}


int TemperatureControlImpl::getCurrentTemperature() {
  lock_guard<mutex> lock(m_mutex);

  //get some random value from -49 to 50
  auto read_result = rand() % 100 - 49;

  m_temperature = read_result;

  cout << "Current temperature is " << m_temperature << endl;

  return m_temperature;
}

void TemperatureControlImpl::run() {
  cout << "In the thread = getting temperature." << endl;
}

void TemperatureControlImpl::start() {

  m_thread = thread([this]() {
      while (m_running) {
        run();

        int temp = getCurrentTemperature();
        // todo - we may add or compute any comfort temperature range where
        // all the devices are switched OFF
        if (temp < m_low_limit) {
          switchCooler(TURN_OFF);
          switchHeater(TURN_ON);
        } else if (temp > m_high_limit) {
          switchCooler(TURN_ON);
          switchHeater(TURN_OFF);
        } else {
          cout << "Temperature within the requested comfort range :)" << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(m_polling_interval_ms));
      }
    });
}

void TemperatureControlImpl::stop() {
  m_running = false;
  m_thread.join();
}
