#ifndef MYDHT22_H
#define MYDHT22_H

#include <Arduino.h>

class MyDHT22 {
  public:
    MyDHT22(uint8_t pin);
    bool readData();
    float getHumidity();
    float getTemperature();

  private:
    uint8_t _pin;
    uint8_t data[5];
};

#endif

