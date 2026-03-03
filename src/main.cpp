#include <Arduino.h>
#include "DevIsoInput.h"
#include "DevRelay.h"
#include "DevSwitch.h"

// Pin definitions (from HardwareESP32Config.md)
const uint8_t PIN_SW1 = 34; // SW1 = Enter/Select (Active Low)
const uint8_t PIN_SW2 = 35; // SW2 = Down (Active Low)
const uint8_t PIN_SW3 = 32; // SW3 = Up (Active Low)

// Instantiate switches (Active Low)
DevSwitch sw1(PIN_SW1, false);
DevSwitch sw2(PIN_SW2, false);
DevSwitch sw3(PIN_SW3, false);

// Callback handlers
void onSw1Click() {
  Serial.println("SW1: Enter/Select");
}

void onSw2Click() {
  Serial.println("SW2: Down");
}

void onSw3Click() {
  Serial.println("SW3: Up");
}

void setup() {
  Serial.begin(115200);
  delay(10);

  // Initialize switches
  sw1.begin();
  sw2.begin();
  sw3.begin();

  // Register click callbacks
  sw1.onClick(onSw1Click);
  sw2.onClick(onSw2Click);
  sw3.onClick(onSw3Click);
}

void loop() {
  // Poll switches (debounce and edge detection handled by class)
  sw1.update();
  sw2.update();
  sw3.update();

  delay(10);
}

