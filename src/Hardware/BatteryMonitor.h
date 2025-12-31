/**
 * @file BatteryMonitor.h
 * @author iamfurkann (esadfurkanduman@gmail.com)
 * @brief Battery Voltage Monitor with Noise Filtering.
 * Supports Voltage Dividers and Percentage calculation.
 * @version 1.0.0
 * @date 2025-12-30
 *
 * @copyright Copyright (c) 2025 Furkan
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H

#include <Arduino.h>
// Since this file is in Hardware/, we need to go up and into Utils/
#include "../Utils/SignalFilter.h"

/**
 * @brief Class to monitor battery status accurately.
 * Uses a Moving Average Filter to smooth out voltage spikes/drops during motor usage.
 */
class BatteryMonitor {
  private:
    int _pin;
    float _voltageDividerRatio; // Formula: (R1 + R2) / R2
    float _refVoltage;          // ADC Reference Voltage (3.3V or 5.0V)
    float _minVoltage;          // 0% level
    float _maxVoltage;          // 100% level
    int _adcResolution;         // 1023 for 10-bit, 4095 for 12-bit
    SignalFilter* _filter;      // Dynamic pointer to filter object

  public:
    /**
     * @brief Construct a new Battery Monitor object.
     * * @param pin Analog pin connected to the voltage divider.
     * @param ratio Voltage Divider Ratio. For Robotis OpenCM9.04, usually 3.0 or 4.0.
     * @param refVoltage Reference voltage of the MCU (Default 3.3V for STM32).
     */
    BatteryMonitor(int pin, float ratio = 3.0, float refVoltage = 3.3);

    /**
     * @brief Destructor to clean up filter memory.
     */
    ~BatteryMonitor();

    /**
     * @brief Initializes the monitor and sets battery limits.
     * * @param minV Voltage considered as 0% (e.g., 11.1V for 3S LiPo).
     * @param maxV Voltage considered as 100% (e.g., 12.6V for 3S LiPo).
     */
    void begin(float minV, float maxV);
    
    /**
     * @brief Reads and calculates the actual battery voltage.
     * Applies smoothing filter automatically.
     * @return float Voltage in Volts (e.g., 12.45).
     */
    float getVoltage();

    /**
     * @brief Calculates remaining battery percentage.
     * @return int Percentage (0-100).
     */
    int getPercentage();

    /**
     * @brief Checks if battery is below critical level (10%).
     * @return true If battery is critically low.
     */
    bool isLow();
};

#endif