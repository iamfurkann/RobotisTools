#include "SmartAnalog.h"

SmartAnalog:SmartAnalog(int pin, int filterSize) {
    _pin = pin;
    _threshold = 512; // Default threshold
    _hysteresis = 20; // Default hysteresis
    _state = false;
    _invert = false;

    _filter = new SignalFilter(filterSize);
}

SmartAnalog::~SmartAnalog() {
    delete _filter;
}

void SmartAnalog::begin() {
    pinMode(_pin, INPUT_ANALOG);
    _filter->begin();
}

void SmartAnalog::setThreshold(int threshold, int hysteresis) {
    _threshold = threshold;
    _hysteresis = hysteresis;
}

void SmartAnalog::setInvert(bool invert) {
    _invert = invert;
}

int SmartAnalog::readRaw() {
    return analogRead(_pin);
}

int SmartAnalog::readSmooth() {
    int raw = readRaw();
    return _filter->filter(raw);
}

int SmartAnalog::readPercentage() {
    int smooth = readSmooth();
    return map(smooth, 0, 1023, 0, 100);
}

bool SmartAnalog::isActive() {
    int val = readSmooth();

    if (!_invert)
    {
        if (val > (_threshold + _hysteresis)) 
            _state = true;

        else if (val < (_threshold - _hysteresis))
            _state = false;
    }
    else
    {
        if (val < (_threshold - _hysteresis)) 
            _state = true;

        else if (val > (_threshold + _hysteresis))
            _state = false;
    }

    return _state;
}