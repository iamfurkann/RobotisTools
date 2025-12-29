# RobotisTools

**RobotisTools** is a high-performance, modular C++ library designed to streamline embedded systems development. It abstracts complex non-blocking logic into a clean, **Event-Driven architecture**.

Originally optimized for **Robotis OpenCM9.04** boards, this library is fully compatible with any Arduino-based hardware (**AVR, ESP32, STM32, Teensy**).

---

## Why this library?

Writing non-blocking code (avoiding `delay()`) is hard. Managing multiple tasks, parsing Serial commands, and debouncing buttons usually results in **"spaghetti code."**

**RobotisTools** solves this by providing a lightweight **"Mini-OS"** structure for your projects.

---

## Key Features

| Module | Description |
|------|------------|
| **Task Manager** | A cooperative scheduler to run functions periodically without blocking the CPU. |
| **Serial Commander** | A safe, buffer-overflow-protected CLI (Command Line Interface) for Serial control. |
| **Button Engine** | Handles debouncing, state changes, and Long Press / Hold detection natively. |
| **Async LED** | Control LEDs (Blink, Toggle) asynchronously. Fire and forget. |
| **Signal Filter** | Implements a Moving Average Filter to smooth out noisy sensor data. |
| **Simple Timer** | A clean wrapper for `millis()` to handle custom periodic events. |

---

## Installation

1. Download the latest release as a **.ZIP** file  
2. Open **Arduino IDE**  
3. Go to **Sketch → Include Library → Add .ZIP Library...**  
4. Select the downloaded file  
5. Restart Arduino IDE  

---

## Quick Start

Here is a complete example of a multi-tasking system with button control and serial commands.

```cpp
#include <RobotisTools.h>

// 1. Define Hardware
Led statusLed(BOARD_LED_PIN);
Button userBtn(BOARD_BUTTON_PIN);

// 2. Define Managers
TaskManager os;
SerialCommander cli;

// --- Tasks ---
void toggleLedTask() {
    statusLed.toggle();
}

void reportTask() {
    Serial.print("[SYSTEM] Uptime: ");
    Serial.println(millis() / 1000);
}

// --- Commands ---
void cmdStop() {
    // Logic to stop system...
    Serial.println("System Stopped via Serial.");
}

void setup() {
    statusLed.begin();
    userBtn.begin();
    cli.begin(9600);

    // Run LED toggle every 500ms
    os.addTask(toggleLedTask, 500);
    // Report status every 2 seconds
    os.addTask(reportTask, 2000);

    // Register Serial Command
    cli.addCommand("stop", cmdStop);
}

void loop() {
    // The loop remains clean!
    os.run();
    cli.check();

    // Handle physical button
    if (userBtn.isPressed()) {
        Serial.println("Button Clicked!");
    }
}
```

---

## Documentation & API

### 1. Task Manager (Cooperative Multitasking)

Replaces `delay()` based loops.

- `addTask(callback, interval)`  
  Schedules a `void function()` to run every **interval** milliseconds.

- `run()`  
  Must be called inside `loop()`. Checks and executes tasks.

---

### 2. Serial Commander (CLI)

Parses text commands from the Serial Monitor safely.  
No `String` objects used to prevent memory fragmentation.

- `addCommand("name", callback)`  
  Binds a text command to a function.

> **Note:** Commands are case-sensitive  
> (`"start"` ≠ `"START"`)

- `check()`  
  Listen for incoming data. Call this in `loop()`.

---

### 3. Button

Advanced input handling.

- `isPressed()`  
  Returns `true` on a valid click (Rising Edge + Debounce).

- `isHeld(duration)`  
  Returns `true` if the button is held down for **duration (ms)**.

---

### 4. Signal Filter

Essential for analog sensors (LDR, IR Distance, Potentiometers).

```cpp
SignalFilter filter(10); // Window size: 10 samples

// ... inside loop ...
int cleanData = filter.filter(analogRead(A0));
```

---

## Compatibility

This library is written in standard C++ and depends only on the **Arduino Core API**.

Tested on:

- Robotis OpenCM9.04 (STM32F103)
- Arduino Uno / Nano / Mega (AVR)
- STM32 Blue Pill

---

## License

This project is licensed under the **Apache License 2.0**.

You are free to use, modify, and distribute this software in **private or commercial projects**.

See the `LICENSE` file for details.

---

## Author

**Furkan**

Built for embedded systems enthusiasts.
