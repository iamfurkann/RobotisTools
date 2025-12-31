/*
 * RobotisTools - Example 05: Full Robot Integration
 *
 * A complete template for a mobile robot.
 * - Saves settings (Max Speed) to EEPROM via ConfigStore.
 * - Calculates Tank Drive mixing via DiffDrive.
 * - Manages system via RobotisApp.
 *
 * Author: Furkan
 * License: Apache 2.0
 */

#include <RobotisTools.h>

RobotisApp app;

// --- 1. SETTINGS STORAGE ---
struct RobotConfig {
  int maxSpeed;
  float turnSensitivity;
};

// Store at EEPROM Address 0, with default values {255, 1.0}
ConfigStore<RobotConfig> config(0, {255, 1.0});

// --- 2. DRIVE SYSTEM ---
// Max PWM: 1023 (OpenCM standard)
DiffDrive driveBase(1023);

// --- TASKS ---
void driveTask() {
  // 1. Simulate Joystick Input (Replace with Real RC/Bluetooth data)
  int joyX = 0;   // No turning
  int joyY = 80;  // 80% Forward speed

  // 2. Compute Mixing
  driveBase.compute(joyX, joyY);

  // 3. Get Motor Speeds
  int leftPWM = driveBase.getLeft();
  int rightPWM = driveBase.getRight();

  // 4. Limit by Configuration
  RobotConfig settings = config.get();
  leftPWM = constrain(leftPWM, -settings.maxSpeed, settings.maxSpeed);
  rightPWM = constrain(rightPWM, -settings.maxSpeed, settings.maxSpeed);

  // 5. Apply to Motors (Pseudo-code)
  // Dxl.writeSpeed(1, leftPWM);
  // Dxl.writeSpeed(2, rightPWM);
}

// --- COMMANDS ---
// Serial Command: "speed_low" -> Sets max speed to 100 and saves it.
void cmdSetLowSpeed() {
  RobotConfig newSettings = config.get();
  newSettings.maxSpeed = 100;
  config.save(newSettings); // Writes to EEPROM
  app.log("Config Saved: Max Speed set to 100");
}

void setup() {
  app.begin();

  // Load settings from EEPROM on boot
  config.load(); 
  app.log("System Booted. Current Max Speed", config.get().maxSpeed);

  // Add tasks and commands
  app.addTask(driveTask, 50); // 20Hz Drive Loop
  app.addCommand("speed_low", cmdSetLowSpeed);
}

void loop() {
  app.update();
}