#include <Arduino.h>
#include "max6675.h"

#define LED 2
#define THERMO_OUT 19
#define THERMO_SELECT 5
#define THERMO_CLK 18
#define RELAY 10

void turnOn();
void turnOff();

// Tuto: https://randomnerdtutorials.com/arduino-k-type-thermocouple-max6675/

int maxTemp = 70;
int minTemp = 50;

MAX6675 thermocouple(THERMO_CLK, THERMO_SELECT, THERMO_OUT);

void setup() {
  Serial.begin(115200);
  // pinMode(RELAY, OUTPUT);
  // digitalWrite(RELAY, LOW);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.println("Bonjour four!");
  delay(500);
}

void loop() {
  float temp = thermocouple.readCelsius();
  Serial.println(temp);
  if (temp > maxTemp) {
    turnOff();
  } else if (temp < minTemp) {
    turnOn();
  }
  delay(500);
}

void turnOn() {
  digitalWrite(RELAY, HIGH);
  digitalWrite(LED, HIGH);
  // Serial.println("Four allumé");
}

void turnOff() {
  digitalWrite(RELAY, LOW);
  digitalWrite(LED, LOW);
  // Serial.println("Four éteint");
}
