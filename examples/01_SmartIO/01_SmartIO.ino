/*
 * RobotisTools - Example 01: Smart I/O
 *
 * Demonstrates the non-blocking capabilities of Button and Led classes.
 * - Debounced button reading (No more flickering).
 * - Long Press detection.
 * - Asynchronous LED blinking.
 *
 * Hardware Required:
 * - 1x Push Button (Connected to BOARD_BUTTON_PIN)
 * - 1x LED (Connected to BOARD_LED_PIN)
 *
 * Author: Furkan
 * License: Apache 2.0
 */

#include <RobotisTools.h>

// Define Hardware Objects
// Note: BOARD_BUTTON_PIN is specific to OpenCM. Change to pin number for Arduino.
Button userBtn(BOARD_BUTTON_PIN);
Led statusLed(BOARD_LED_PIN);

void setup() {
  // Initialize Serial for debug
  Serial.begin(9600);
  while (!Serial); // Wait for USB connection

  // Initialize Hardware
  userBtn.begin();
  statusLed.begin();

  Serial.println("--- Example 01 Started ---");
  Serial.println("[1] Press button to TOGGLE LED.");
  Serial.println("[2] Hold button (500ms) to BLINK LED.");
}

void loop() {
  // 1. Check for Single Click
  // isPressed() handles debouncing automatically.
  if (userBtn.isPressed()) 
  {
    Serial.println(">> Event: Button Clicked -> Toggling LED");
    statusLed.toggle();
  }

  // 2. Check for Long Press (Hold)
  // isHeld(duration) checks if button is held down for X ms.
  if (userBtn.isHeld(500)) 
  {
    // blink(interval) sets the LED to blink mode asynchronously.
    // It does NOT block the loop.
    statusLed.blink(100); 
  }
}