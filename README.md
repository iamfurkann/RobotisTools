## RobotisTools — Embedded Robotics Utility Library

RobotisTools is a modular, event-driven C++ utility library that turns linear Arduino sketches into a lightweight "mini-OS" for robotics projects. It provides a cooperative task scheduler, non-blocking hardware drivers, a safe serial command parser, and a set of utility classes for control and filtering.

This README is aimed at developers who want an overview of the library, its architecture, quick usage tips, and instructions for installing and running the examples.

Table of Contents
- Motivation
- Key Features
- Architecture and Core Concepts
- Quick Start (Arduino example)
- API & Module Highlights
- Examples
- Installation (Arduino IDE & PlatformIO)
- Project layout
- Contribution & Testing
- License

### Motivation

Standard Arduino sketches often grow into blocking, hard-to-maintain programs when multiple sensors, actuators, and serial commands run together. RobotisTools addresses this by providing:
- Cooperative scheduling (no blocking delays inside tasks)
- Safe, fixed-buffer serial command parsing (avoid dynamic String allocations)
- Non-blocking drivers for common sensors and actuators

The result is cleaner, deterministic behavior suitable for robots with multiple concurrent responsibilities.

### Key Features

- Cooperative Task Scheduler (TaskManager) with timed callbacks
- RobotisApp facade that aggregates core services: task scheduling, logging, serial command handling
- Non-blocking Hardware Drivers: Led, Button (debounce/long-press), SmartAnalog (hysteresis), AsyncSonar (HC-SR04), BatteryMonitor
- Utilities: FastPID (anti-windup), DiffDrive kinematics, SignalFilter (moving average), ConfigStore (EEPROM persistence), SimpleTimer
- Minimal heap usage: uses fixed-size buffers where possible to reduce heap fragmentation
- Cross-platform: AVR, ESP32, STM32, Teensy, and typical Arduino-compatible boards

### Architecture and Core Concepts

Layers:
- CORE: RobotisApp, TaskManager, Logger, SerialCommander
- HARDWARE: drivers for physical components
- UTILITIES: helper libraries and mathematical tools

Heartbeat
- The system relies on a single heartbeat call: app.update(). Call this frequently from `loop()` to keep tasks, serial parsing, and timers running.

Non-blocking design
- Avoid `delay()` inside tasks. Use the scheduler or timers for long-running workflows.

RobotisApp facade
- Use `RobotisApp` to initialize and access common subsystems (example usage below).

### Quick Start (Arduino)

This minimal sketch shows the recommended usage pattern. Replace `BOARD_LED_PIN` and `BOARD_BUTTON_PIN` with your board's definitions or pin numbers.

```cpp
#include <RobotisTools.h>

// Kernel
RobotisApp app(115200);

// Hardware instances
Led statusLed(BOARD_LED_PIN);
Button userBtn(BOARD_BUTTON_PIN);

// Tasks
void blinkTask() { statusLed.toggle(); }
void reportTask() { app.log("Uptime (s)", millis() / 1000); }

// Serial command
void cmdStop() { app.log("Emergency stop"); statusLed.turnOff(); }

void setup() {
  app.begin();
  statusLed.begin();
  userBtn.begin();

  // Add periodic tasks (non-blocking)
  app.addTask(blinkTask, 500);
  app.addTask(reportTask, 2000);

  // Register a simple serial command
  app.addCommand("stop", cmdStop);
}

void loop() {
  // Heartbeat — required
  app.update();

  // Local checks can still be performed synchronously if short
  if (userBtn.isPressed()) {
    app.log("Manual override");
  }
}
```

Notes
- Keep task callbacks short and non-blocking.
- Use `app.addTask(func, interval_ms)` for repeated tasks or `addOneShot`/timers where available.

### API & Module Highlights

Core
- RobotisApp
  - begin(), update(), addTask(...), addCommand(name, callback), log(...)
- TaskManager
  - schedule tasks and manage their timing
- Logger
  - leveled logging: INFO, WARN, ERROR, DEBUG
- SerialCommander
  - parse textual commands from Serial and invoke registered handlers using fixed buffers

Hardware drivers (examples)
- Button: start(), isPressed(), onLongPress(), debounce handling
- Led: begin(), turnOn(), turnOff(), toggle(), blink() (non-blocking)
- SmartAnalog: stable thresholding and hysteresis
- AsyncSonar: trigger/read without blocking
- BatteryMonitor: read voltage with noise filtering and percent estimation

Utilities
- FastPID: PID controller with anti-windup and derivative-on-measurement
- DiffDrive: helper to convert joystick inputs to left/right motor commands
- SignalFilter: moving average / simple filters
- ConfigStore<T>: template for EEPROM-backed persistence

For a complete API reference, see the header files in `src/` (particularly `src/Core/`, `src/Hardware/`, and `src/Utils/`). If you want, I can generate a brief function/class reference automatically from headers.

### Examples

Example sketches live in the `examples/` directory. They demonstrate common patterns and best practices:
- `01_SmartIO` — basic I/O and SmartAnalog usage
- `02_MultitaskingOS` — scheduler and task examples
- `03_SignalFiltering` — using SignalFilter and FastPID
- `04_AdvancedSensors`, `05_FullRobot`, etc.

Run an example in the Arduino IDE by opening the example `.ino` file and selecting the correct board/port.

### Installation

Arduino IDE
1. Download repository as ZIP or clone the repo.
2. In Arduino IDE: Sketch -> Include Library -> Add .ZIP Library... (choose the repo ZIP) or copy this project into your Arduino `libraries/` folder.
3. Restart the Arduino IDE, then open an example from `examples/`.

PlatformIO
1. Clone the repo into your project or add `src/` to your PlatformIO project's source path.
2. Include headers with `#include <RobotisTools.h>` and configure your `platformio.ini` with the target board.

Notes
- Some examples assume board-specific macros like `BOARD_LED_PIN`. Replace them with the appropriate pin numbers or define the macros in your build settings.

### Project layout

Top-level (source files):
- `src/RobotisTools.h` — main umbrella header
- `src/Core/` — RobotisApp, TaskManager, Logger, SerialCommander, TaskManager
- `src/Hardware/` — Led, Button, AsyncSonar, BatteryMonitor, SmartAnalog
- `src/Utils/` — FastPID, DiffDrive, SignalFilter, ConfigStore, SimpleTimer
- `examples/` — example sketches

### Contribution & Testing

Contributions are welcome. A suggested workflow:
- Fork the repo, create a feature branch, make small focused changes, open a pull request.
- Describe the change and include example usage or test sketches.

Testing
- Many changes can be verified on real hardware using the example sketches.
- For unit-like tests of pure utility code (FastPID, SignalFilter), you can create small host-side tests if ported to a desktop test harness.

If you want, I can add a basic CONTRIBUTING.md with a checklist and a simple test scaffold for utilities.

### License

This project is licensed under the Apache License 2.0 — see the bundled `LICENSE` file for details.

---
