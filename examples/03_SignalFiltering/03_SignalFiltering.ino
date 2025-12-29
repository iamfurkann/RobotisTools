/*
 * RobotisTools - Example 03: Signal Filtering
 * * This sketch demonstrates the 'SignalFilter' class which implements
 * a Moving Average Filter. It is useful for smoothing out noisy 
 * sensor data (e.g., LDR, Distance Sensor, Battery Voltage).
 * * Instructions:
 * 1. Upload the code.
 * 2. Open 'Tools > Serial Plotter' (baud 9600).
 * 3. Observe the Blue line (Noisy) vs Red line (Filtered).
 * * Author: iamfurkann
 * License: Apache-2.0
 */

#include <RobotisTools.h>

// Create a filter with a window size of 20 samples.
// Larger size = Smoother line but slower reaction.
// Smaller size = Faster reaction but more noise.
SignalFilter sensorFilter(20);

// Timer to control print speed (e.g., 50ms)
SimpleTimer plotTimer(50);

void setup() {
  Serial.begin(9600);
  sensorFilter.begin();
  
  Serial.println("Raw,Filtered"); // Legend for Serial Plotter
}

void loop() {
  // 1. Simulate a Noisy Sensor
  // Generate a base sine wave + random noise
  int baseSignal = 50 * sin(millis() / 1000.0) + 100; // Sine wave center at 100
  int noise = random(-20, 20); // Random noise between -20 and +20
  int rawValue = baseSignal + noise;

  // 2. Apply Filter
  int filteredValue = sensorFilter.filter(rawValue);

  // 3. Visualize using SimpleTimer
  // Using a timer prevents flooding the Serial port, unlike delay().
  if (plotTimer.isReady()) {
    Serial.print(rawValue);       // Blue Line
    Serial.print(","); 
    Serial.println(filteredValue); // Red Line (Smoothed)
  }
}