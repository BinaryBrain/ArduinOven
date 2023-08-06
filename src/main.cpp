#include <Arduino.h>
#include "TM1637Display.h"
#include "max6675.h"

#define LED 2
#define THERMO_OUT 19
#define THERMO_SELECT 18
#define THERMO_CLK 5
#define DISPLAY_CLK 22
#define DISPLAY_OUT 23
#define RELAY 27

void turnOn();
void turnOff();
void displayTemp(float temp);

// Tuto: https://randomnerdtutorials.com/arduino-k-type-thermocouple-max6675/

int maxTemp = 120;
int minTemp = 115;

MAX6675 thermocouple(THERMO_CLK, THERMO_SELECT, THERMO_OUT);
TM1637Display display(DISPLAY_CLK, DISPLAY_OUT);

void setup() {
  Serial.begin(115200);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  display.setBrightness(0x0f);
  Serial.println("Bonjour four!");
  delay(500);
}

void loop() {
  float temp = thermocouple.readCelsius();
  Serial.println(temp);
  displayTemp(temp);
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
}

void turnOff() {
  digitalWrite(RELAY, LOW);
  digitalWrite(LED, LOW);
}

void displayTemp(float temp) {
  int tempRounded = round(temp);
  display.showNumberDec(tempRounded, false);
}
