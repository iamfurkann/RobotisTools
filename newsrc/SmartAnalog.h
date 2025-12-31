#ifndef SMART_ANALOG_H
#define SMART_ANALOG_H

#include <Arduino.h>
#include "SignalFilter.h"

class SmartAnalog {
    private:
        int _pin;
        int _threshold;
        int _hysteresis;
        bool _state;
        bool _invert;
        SignalFilter* _filter;

    public:
        SmartAnalog(int pin, int filterSize = 10);
        ~SmartAnalog();

        void begin();

        void setThreshold(int threshold, int hysteresis = 10);
        void setInvert(bool invert);

        int readRaw();
        int readSmooth();
        int readPercentage();

        bool isActive();
};

#endif