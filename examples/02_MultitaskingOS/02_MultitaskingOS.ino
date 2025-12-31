/*
 * RobotisTools - Example 02: Multitasking Kernel
 *
 * Demonstrates the "RobotisApp" kernel which acts as a Mini-OS.
 * - TaskManager: Run functions periodically without delay().
 * - SerialCommander: Control the board via Serial Monitor.
 * - Logger: Professional logging output.
 *
 * Commands to try in Serial Monitor:
 * - "start" : Starts the auto-counter.
 * - "stop"  : Stops the auto-counter.
 *
 * Author: Furkan
 * License: Apache 2.0
 */

#include <RobotisTools.h>

// Initialize the Kernel (App)
RobotisApp app(9600);

// Global variable
int counter = 0;
bool running = true;

// --- TASKS ---
// These functions are called automatically by the Kernel.

void taskCount() {
  if (running) 
  {
    counter++;
    // app.log is a shortcut for the Logger module
    app.log("Counter Value", counter);
  }
}

void taskHealthCheck() {
  app.log("System Heartbeat: Alive.");
}

// --- COMMANDS ---
// Functions triggered by Serial text commands.

void cmdStart() {
  running = true;
  app.log(">> Command: Counter STARTED");
}

void cmdStop() {
  running = false;
  app.log(">> Command: Counter STOPPED");
}

void setup() {
  // Start the Kernel (Starts Serial, Logger, Managers)
  app.begin();

  // Register Tasks (Function, Interval in ms)
  app.addTask(taskCount, 1000);       // Run every 1 second
  app.addTask(taskHealthCheck, 5000); // Run every 5 seconds

  // Register Commands (Name, Function)
  app.addCommand("start", cmdStart);
  app.addCommand("stop", cmdStop);
}

void loop() {
  // The magic line. Updates Scheduler and CLI.
  app.update();
}