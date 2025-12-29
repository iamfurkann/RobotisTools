/*
 * RobotisTools - Example 02: Multitasking OS
 * * This sketch demonstrates how to build a Cooperative Multitasking system.
 * Instead of writing logic inside loop(), we define 'Tasks' and let
 * the TaskManager run them at specific intervals.
 * * It also demonstrates the 'SerialCommander' to control the device
 * via text commands sent from the Serial Monitor.
 * * Commands to try in Serial Monitor:
 * - "start" : Starts the auto-blink task
 * - "stop"  : Stops the auto-blink task
 * - "status": Prints system uptime
 * * Author: iamfurkann
 * License: Apache-2.0
 */

#include <RobotisTools.h>

// Objects
Led sysLed(BOARD_LED_PIN);
TaskManager taskManager;
SerialCommander cli;

// Global flag to control logic
bool isBlinkingActive = true;

// --- TASK FUNCTIONS ---
// These functions are called automatically by TaskManager.

void taskBlink() {
  if (isBlinkingActive) {
    sysLed.toggle();
  }
}

void taskReport() {
  Serial.print("[SYSTEM] Uptime: ");
  Serial.print(millis() / 1000);
  Serial.println(" seconds. System is healthy.");
}

// --- COMMAND CALLBACKS ---
// These functions are triggered by Serial commands.

void cmdStart() {
  isBlinkingActive = true;
  Serial.println(">> Command Executed: Blinking STARTED.");
}

void cmdStop() {
  isBlinkingActive = false;
  sysLed.turnOff(); // Ensure it's off
  Serial.println(">> Command Executed: Blinking STOPPED.");
}

void cmdStatus() {
  Serial.println(">> Command Executed: Manual Status Check Requested.");
  taskReport();
}

void setup() {
  // 1. Hardware Init
  sysLed.begin();
  cli.begin(9600);

  // 2. Register Tasks (Function, Interval in ms)
  taskManager.addTask(taskBlink, 200);   // Toggle LED every 200ms
  taskManager.addTask(taskReport, 2000); // Report status every 2 seconds

  // 3. Register Commands (Command String, Callback Function)
  // Note: Commands are case-sensitive (use lowercase).
  cli.addCommand("start", cmdStart);
  cli.addCommand("stop", cmdStop);
  cli.addCommand("status", cmdStatus);

  Serial.println("--- Example 02: Multitasking OS Ready ---");
  Serial.println("Type 'start', 'stop' or 'status' in Serial Monitor.");
}

void loop() {
  // The loop is clean! It only delegates power to managers.
  taskManager.run();
  cli.check();
}