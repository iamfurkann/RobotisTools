  RobotisTools Framework
RobotisTools is a professional, modular, and event-driven C++ framework designed for embedded robotics. It transforms standard linear Arduino code into a robust Mini-OS architecture.

Originally optimized for Robotis OpenCM9.04, this library is fully cross-platform and compatible with any Arduino-based hardware (AVR, ESP32, STM32, Teensy).

The Problem: Standard Arduino code often becomes "spaghetti code" when managing multiple sensors, motors, and serial commands simultaneously using delay().

The Solution: RobotisTools provides a Cooperative Task Scheduler, a Safe Command Line Interface, and Non-blocking Hardware Drivers to handle complex robotic tasks effortlessly.

  System Architecture
The library is organized into three logical layers:

Layer	Modules	Description
1. CORE	RobotisApp, TaskManager, Logger, SerialCommander	The brain of the system. Manages tasks, logs, and CLI commands.
2. HARDWARE	Button, Led, SmartAnalog, AsyncSonar, BatteryMonitor	Intelligent drivers for physical components. Handles debounce, hysteresis, and async triggers.
3. UTILITIES	FastPID, DiffDrive, SignalFilter, ConfigStore, SimpleTimer	Pure mathematical and helper classes for control theory, filtering, and data storage.
🚀 Quick Start
Here is a complete example showing how to set up a multitasking robot system.

C++
#include <RobotisTools.h>

// 1. Initialize the Kernel (App)
RobotisApp app(115200); // Set baud rate

// 2. Define Hardware
Led statusLed(BOARD_LED_PIN);
Button userBtn(BOARD_BUTTON_PIN);

// 3. Define Logic
void blinkTask() {
    statusLed.toggle();
}

void reportTask() {
    // Uses the internal Logger module
    app.log("System Uptime (sec)", millis() / 1000);
}

void cmdStop() {
    app.log(">> Emergency Stop Command Received!");
    statusLed.turnOff();
}

void setup() {
    // Start System & Hardware
    app.begin();
    statusLed.begin();
    userBtn.begin();

    // Schedule Tasks (No delay!)
    app.addTask(blinkTask, 500);   // Blink every 500ms
    app.addTask(reportTask, 2000); // Report every 2 seconds

    // Register Serial Command
    app.addCommand("stop", cmdStop);
}

void loop() {
    // [CRITICAL] The System Heartbeat
    app.update();
    
    // Manual Override
    if (userBtn.isPressed()) {
        app.log("Manual Button Override!");
    }
}
  Core Concepts
The app.update() Heartbeat

Unlike standard Arduino sketches, RobotisTools relies on a Cooperative Scheduler.

You must call app.update() inside loop().

This function acts as the "Operating System." It checks if any task needs to run, processes incoming Serial commands, and manages internal timers.

Do not use delay() inside your tasks, as it will pause the entire system "heartbeat."

The RobotisApp Kernel

Instead of managing the TaskManager, Logger, and SerialCommander separately, the RobotisApp class acts as a Facade. You control the entire system through the app object.

📚 Module Reference
🔌 Hardware Drivers

Button: Handles debouncing (noise filtering) and detects Long Press / Hold events.

SmartAnalog: Implements Schmitt Trigger (Hysteresis) logic to prevent sensor flickering at threshold levels. Auto-detects 10-bit vs 12-bit ADC.

BatteryMonitor: Reads battery voltage via a divider, applies a noise filter, and calculates remaining percentage (0-100%).

AsyncSonar: A non-blocking driver for HC-SR04 ultrasonic sensors. Uses a state machine for triggering.

Led: Asynchronous control (Toggle, Blink) without blocking execution.

🛠️ Utilities & Math

FastPID: A high-performance PID controller with Integral Windup Guard and Derivative on Measurement to prevent kicks.

DiffDrive: Computes kinematics for tank-drive/differential robots. Converts Joystick (X, Y) to Left/Right motor speeds with Deadband support.

SignalFilter: Implements a Moving Average Filter to smooth out noisy sensor data.

ConfigStore: A C++ Template class to save/load complex data structures (Structs) to EEPROM effortlessly.

  System Core

SerialCommander: Parses text commands from Serial Monitor (e.g., "start", "set_pid"). Uses fixed buffers to prevent Heap Fragmentation (No String usage).

Logger: Provides leveled logging (INFO, WARN, ERROR, DEBUG) to keep the Serial output clean.

  Installation
Download the repository as a .ZIP file.

Open Arduino IDE.

Navigate to Sketch -> Include Library -> Add .ZIP Library...

Select the downloaded file.

Restart Arduino IDE.

  License
This project is open-source and licensed under the Apache License 2.0. You are free to use, modify, and distribute this software for private or commercial purposes.

See the LICENSE file for details.

Maintained by: Furkan

Built for serious robotics development.