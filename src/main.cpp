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

// Relay pin definitions (from HardwareESP32Config.md)
const uint8_t PIN_RELAY1 = 4;  // Relay1 = Fan (Active Low)
const uint8_t PIN_RELAY2 = 16; // Relay2 = Pump (Active Low)
const uint8_t PIN_RELAY3 = 17; // Relay3 = Heater (Active Low)

// Instantiate relays (Active Low)
DevRelayWithTimer relayFan(PIN_RELAY1, true);
DevRelayWithTimer relayPump(PIN_RELAY2, true);
DevRelayWithTimer relayHeater(PIN_RELAY3, true);

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

// Relay control helpers
void toggleFan() {
  relayFan.toggle();
  Serial.printf("Fan: %s\n", relayFan.getState() ? "ON" : "OFF");
}

void togglePump() {
  relayPump.toggle();
  Serial.printf("Pump: %s\n", relayPump.getState() ? "ON" : "OFF");
}

void toggleHeater() {
  relayHeater.toggle();
  Serial.printf("Heater: %s\n", relayHeater.getState() ? "ON" : "OFF");
}

void setup() {
  Serial.begin(115200);
  delay(10);

  // Initialize switches
  sw1.begin();
  sw2.begin();
  sw3.begin();

  // Initialize relays
  relayFan.begin();
  relayPump.begin();
  relayHeater.begin();

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

  // Serial control: press keys to toggle relays
  if (Serial.available()) {
    char c = (char)Serial.read();
    switch (c) {
      case 'f': case 'F': toggleFan(); break;
      case 'p': case 'P': togglePump(); break;
      case 'h': case 'H': toggleHeater(); break;
      case '1': toggleFan(); break;
      case '2': togglePump(); break;
      case '3': toggleHeater(); break;
      default: break;
    }
  }

  delay(10);
}

