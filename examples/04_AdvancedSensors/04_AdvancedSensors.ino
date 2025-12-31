/*
 * RobotisTools - Example 04: Advanced Hardware Drivers
 *
 * Demonstrates high-level hardware drivers:
 * - BatteryMonitor: Converts voltage to percentage automatically.
 * - SmartAnalog: Hysteresis (Schmitt Trigger) logic for sensors.
 *
 * Hardware:
 * - Battery Divider connected to Pin A0.
 * - LDR or Potentiometer connected to Pin A1.
 *
 * Author: Furkan
 * License: Apache 2.0
 */

#include <RobotisTools.h>

RobotisApp app;

// 1. Battery Monitor
// Pin: A0, Divider Ratio: 3.0, Ref Voltage: 3.3V
BatteryMonitor battery(A0, 3.0, 3.3);

// 2. Smart Analog Sensor (e.g. LDR for Night Light)
// Pin: A1, Filter Size: 10
SmartAnalog lightSensor(A1, 10);

void taskBatteryCheck() {
  // Read Voltage and Percentage
  float volts = battery.getVoltage();
  int percent = battery.getPercentage();
  
  app.log("Battery Voltage", (int)(volts * 100)); // x100 to print decimals as int
  app.log("Battery Percent", percent);

  if (battery.isLow()) 
    app.getLogger().warn("CRITICAL BATTERY LEVEL!");
}

void setup() {
  app.begin();

  // Initialize Battery (Min: 11.1V, Max: 12.6V for 3S LiPo)
  battery.begin(11.1, 12.6);

  // Initialize Light Sensor
  lightSensor.begin();
  // Set Threshold: 2000 (OpenCM is 12-bit, so 0-4095 range)
  // Hysteresis: 100 (Buffer zone)
  // Invert: True (Active when DARK / Low value)
  lightSensor.setThreshold(2000, 100);
  lightSensor.setInvert(true);

  // Check battery every 3 seconds
  app.addTask(taskBatteryCheck, 3000);
}

void loop() {
  app.update();

  // SmartAnalog handles hysteresis automatically.
  // No flickering when value is near 2000.
  if (lightSensor.isActive()) 
  {
    // Turn on night lights...
    // app.log("Night Mode ON");
  }
}