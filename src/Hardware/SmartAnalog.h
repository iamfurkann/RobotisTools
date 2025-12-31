/**
 * @file SmartAnalog.h
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief Intelligent Analog Sensor Driver with Hysteresis & Filtering.
 * Compatible with OpenCM9.04 (INPUT_ANALOG) and Standard Arduino (INPUT).
 * @version 1.0.0
 * @date 2025-12-31
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef SMART_ANALOG_H
#define SMART_ANALOG_H

#include <Arduino.h>
// Utilities klasöründeki filtreyi çağırıyoruz
#include "../Utils/SignalFilter.h"

/**
 * @brief Wrapper for Analog Sensors (LDR, Potentiometer, Distance).
 * Features:
 * - Automatic ADC resolution detection (10-bit vs 12-bit).
 * - Moving Average Filtering (Noise reduction).
 * - Schmitt Trigger (Hysteresis) for digital conversions.
 */
class SmartAnalog {
  private:
    int _pin;
    int _threshold;     // Target value for isActive()
    int _hysteresis;    // Dead zone buffer
    bool _state;        // Current logical state (Active/Inactive)
    bool _invert;       // Logic inversion flag
    int _adcResolution; // 1023 (AVR) or 4095 (STM32)
    SignalFilter* _filter; // Pointer to filter object

  public:
    /**
     * @brief Construct a new Smart Analog object.
     * @param pin Analog Pin (A0, A1, etc.).
     * @param filterSize Window size for noise filtering (Default: 10).
     */
    SmartAnalog(int pin, int filterSize = 10);

    /**
     * @brief Destructor to clean up dynamic memory.
     */
    ~SmartAnalog();
    
    /**
     * @brief Initializes the pin.
     * Automatically selects INPUT_ANALOG for STM32 or INPUT for Arduino.
     */
    void begin();
    
    /**
     * @brief Configures the switching logic.
     * @param threshold The trigger point.
     * @param hysteresis Buffer zone to prevent flickering (Default: 10).
     */
    void setThreshold(int threshold, int hysteresis = 10);

    /**
     * @brief Inverts logic.
     * @param invert If true: Active when value < threshold (e.g., Night Light).
     * If false: Active when value > threshold.
     */
    void setInvert(bool invert);
    
    /**
     * @brief Reads raw ADC value directly from hardware.
     */
    int readRaw();

    /**
     * @brief Reads noise-filtered value.
     */
    int readSmooth();

    /**
     * @brief Converts reading to percentage (0-100%).
     * Handles 10-bit vs 12-bit ADC automatically.
     */
    int readPercentage();
    
    /**
     * @brief Returns true if threshold is crossed (Schmitt Trigger Logic).
     * Stable output, no flickering at the edge.
     */
    bool isActive();
};

#endif