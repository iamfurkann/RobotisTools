/*
 * RobotisTools - Example 03: Signal Filtering
 *
 * Demonstrates the Moving Average Filter and SimpleTimer.
 * Essential for noisy sensors like LDR, Distance, or Potentiometers.
 *
 * Instructions:
 * 1. Upload code.
 * 2. Open "Tools > Serial Plotter".
 * 3. Observe Blue (Raw) vs Red (Filtered) lines.
 *
 * Author: Furkan
 * License: Apache 2.0
 */

#include <RobotisTools.h>

// Create a filter with window size of 20 samples.
// Larger window = Smoother line but slower reaction.
SignalFilter myFilter(20);

// Timer to control print speed
SimpleTimer plotTimer(50); // 50ms

void setup() {
  Serial.begin(9600);
  myFilter.begin(); // Allocate memory
  
  // Legend for Serial Plotter
  Serial.println("Raw,Filtered");
}

void loop() {
  // 1. Simulate a Noisy Sensor (e.g., Sine wave + Random noise)
  float sineWave = 50.0 * sin(millis() / 1000.0) + 100.0;
  int noise = random(-20, 20);
  int rawValue = (int)sineWave + noise;

  // 2. Apply Filter
  int cleanValue = myFilter.filter(rawValue);

  // 3. Print for Serial Plotter
  if (plotTimer.isReady()) 
  {
    Serial.print(rawValue);
    Serial.print(",");
    Serial.println(cleanValue);
  }
}