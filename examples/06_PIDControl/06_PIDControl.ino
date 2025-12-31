/*
 * RobotisTools - Example 06: PID Control
 *
 * Demonstrates the FastPID controller and AsyncSonar.
 * This example simulates a "Distance Keeper" robot that tries
 * to maintain exactly 20cm distance from an object.
 *
 * Author: Furkan
 * License: Apache 2.0
 */

#include <RobotisTools.h>

RobotisApp app;

// 1. Hardware
// Trig: Pin 2, Echo: Pin 3
AsyncSonar sonar(2, 3); 

// 2. Controller
// Kp=5.0, Ki=0.1, Kd=2.0, Loop Time=50ms
FastPID distancePID(5.0, 0.1, 2.0, 50);

void pidTask() {
  // 1. Update Sensor (Non-blocking trigger)
  sonar.update();
  float currentDist = sonar.getDistance();

  // 2. Compute PID
  // Target: 20.0 cm
  // Input: Current Distance
  float output = distancePID.compute(20.0, currentDist);

  // 3. Apply Output to Motors
  // If output is positive -> Move Forward
  // If output is negative -> Move Backward
  
  // Debugging (Plot this in Serial Plotter)
  // Serial.print(20.0); // Target
  // Serial.print(",");
  // Serial.println(currentDist); // Actual
}

void setup() {
  app.begin();
  
  sonar.begin();
  
  // Configure PID Output Limits (Motor Speed: -255 to 255)
  distancePID.setOutputLimits(-255, 255);
  
  // Run PID calculation every 50ms
  app.addTask(pidTask, 50);
}

void loop() {
  app.update();
}