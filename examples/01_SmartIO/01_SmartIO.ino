/*
 * RobotisTools - Example 01: Smart I/O
 * * This sketch demonstrates how to use the 'Button' and 'Led' classes
 * to handle inputs and outputs without blocking the processor.
 * * Features demonstrated:
 * - Debounced button reading (isPressed)
 * - Long press detection (isHeld)
 * - Non-blocking LED blinking and toggling
 * * Author: iamfurkann
 * License: Apache-2.0
 */

#include <RobotisTools.h>

// Initialize objects with pin numbers
// BOARD_BUTTON_PIN and BOARD_LED_PIN are specific to Robotis OpenCM9.04
// If using Arduino Uno/Mega, use specific pin numbers (e.g., 2 and 13).
Button userBtn(BOARD_BUTTON_PIN);
Led statusLed(BOARD_LED_PIN);

void setup() {
  // Initialize hardware pins
  userBtn.begin();
  statusLed.begin();

  // Optional: Serial for debugging
  Serial.begin(9600);
  Serial.println("--- Example 01: Smart I/O Started ---");
  Serial.println("Press button to TOGGLE LED.");
  Serial.println("Hold button (500ms) to BLINK LED.");
}

void loop() {
  // 1. Single Click Event
  // isPressed() handles debouncing automatically.
  if (userBtn.isPressed()) {
    Serial.println("Event: Single Click -> Toggle LED");
    statusLed.toggle();
  }

  // 2. Long Press (Hold) Event
  // isHeld(duration) checks if the button is held down for 'duration' ms.
  if (userBtn.isHeld(500)) {
    // blink(interval) is non-blocking. It won't stop the code execution.
    statusLed.blink(100); 
  }
}