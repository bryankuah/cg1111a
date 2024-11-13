#include "Arduino.h"
#include "ColourSensor.h"
#include "configurations.h"
ColourSensor::ColourSensor(int ldrPin, int ledPins[NUM_COMPONENTS]) {
  _ldrPin = ldrPin;
  for (int i = 0; i < NUM_COMPONENTS; i++) {
    _led_pins[i] = ledPins[i];
  }
  pinMode(_ldrPin, INPUT);
}


void ColourSensor::_readColour(double *colourValue) {
  double startValue, endValue;
  do {
    *colourValue = 0;
    startValue = analogRead(_ldrPin);
    for (int i = CS_SAMPLES; i > 0; i--) {
      *colourValue += analogRead(_ldrPin);
    }
    endValue = analogRead(_ldrPin);
  } while (abs(startValue - endValue) > 5);
}

void ColourSensor::getWhite() {
  setMuxOut(MUX_IR);  // turn off all LEDs
  delay(CS_DELAY_BEFORE_AMBIENT);
  for (int i = 0; i < NUM_COMPONENTS; i++) {
    _multiplier[i] = 1;
  }
  detectColour();

  // compute _multiplier[3] to be multiplied to r, g and b to get .3333, .3333,.3333
  for (int i = 0; i < NUM_COMPONENTS; i++) {
    Serial.println(1 / _rgb_vals[i]);
  }
}


void ColourSensor::detectColour() {
  double reading = 0;
  // setMuxOut(MUX_IR);
  for (int i = 0; i < NUM_COMPONENTS; i++) {
    setMuxOut(MUX_IR);
    delay(CS_DELAY_BEFORE_AMBIENT);
    setMuxOut(_led_pins[i]);
    delay(CS_DELAY_BEFORE_READING);
    _readColour(&reading);
    // reading -= _ambient_light;
    _rgb_vals[i] = reading * _multiplier[i];
  }

  // Normalize the values
  double sum = 0;
  for (int i = 0; i < NUM_COMPONENTS; i++) {
    sum += _rgb_vals[i];
  }
  for (int i = 0; i < NUM_COMPONENTS; i++) {
    _rgb_vals[i] /= sum;
  }
}


int ColourSensor::identifyColours() {
  int best_match = -1;
  double min_distance = 9999999;
  double distance;

  for (int colour_idx = 0; colour_idx < NUM_COLOURS; colour_idx++) {
    distance = _calculateDistance(colour_idx);
    if (distance < min_distance) {
      min_distance = distance;
      best_match = colour_idx;
    }
  }
  Serial.println(distance);
  return best_match;
}

double ColourSensor::_calculateDistance(int colour_idx) {
  double sum = 0;
  for (int i = 0; i < NUM_COMPONENTS; i++) {
    sum += pow(_rgb_vals[i] - _recorded_rgb_values[colour_idx][i], 2);
  }
  return sum;
}

void ColourSensor::calibrateColourSensor() {
  detectColour();
  for (int i = 0; i < NUM_COLOURS; i++) {
    Serial.println("Put the sensor on " + _colours[i] + " colour");
    delay(COLOUR_CALIBRATION_DELAY);
    detectColour();
    Serial.print("RGB values: ");
    for (int j = 0; j < NUM_COMPONENTS; j++) {
      Serial.print(_rgb_vals[j], 6);
      Serial.print(" ");
    }
    Serial.println();
  }
}
