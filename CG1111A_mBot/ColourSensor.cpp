#include "ColourSensor.h"
#include "configurations.h"
ColourSensor::ColourSensor(int ina, int inb, int ldrPin, int ledPins[3]){
    for (int i = 0; i < 3; i++) {
        led_pins[i] = ledPins[i];
    }
}

void ColourSensor::setup() {
    pinMode(CS_INA, OUTPUT);
    pinMode(CS_INB, OUTPUT);
    pinMode(CS_LDR_PIN, INPUT);
    digitalWrite(CS_INA, LOW);
    digitalWrite(CS_INB, LOW);
}

int ColourSensor::readLDR() {
    return analogRead(CS_LDR_PIN);
}

void ColourSensor::readColour(long *colourValue) {
    *colourValue = 0;
    for (int i = CS_SAMPLES; i > 0; i--) {
        *colourValue += analogRead(CS_LDR_PIN);
    }
}

int ColourSensor::detectColour(long rgb_values[3]) {
    long ambient_light = 0;
    readColour(&ambient_light);
    long reading = 0;
    for (int i = 0; i < 3; i++) {
        rgb_values[i] = 0;
    }
    for (int i = 0; i < 3; i++) {
        enablePin(led_pins[i]);
        delay(CS_DELAY_BEFORE_READING);
        readColour(&reading);
        reading -= ambient_light;
        rgb_values[i] += reading;
    }
    enablePin(CS_LED_OFF);
    delay(100);
    return 0;
}

int ColourSensor::identifyColours(long rgb_vals[3]) {
    int colour_idx;
    int j;
    for (colour_idx = 0; colour_idx < 6; colour_idx++) {
        for (j = 0; j < 3; j++) {
            Serial.print(abs(rgb_vals[j] - recorded_rgb_values[colour_idx][j]));
            Serial.print(" ");
            if (abs(rgb_vals[j] - recorded_rgb_values[colour_idx][j]) > CS_THRESHOLD) {
                Serial.println();
                break;
            }
        }
        if (j == 3) {
            return colour_idx;
        }
    }
    return -1;
}

void ColourSensor::calibrateColourSensor() {
    long rgb_values[3];
    for (int i = 0; i < 6; i++) {
        Serial.println("Place the sensor on " + colours[i] + " colour");
        delay(5000);
        detectColour(rgb_values);
        Serial.print("RGB values: ");
        for (int j = 0; j < 3; j++) {
            Serial.print(rgb_values[j]);
            Serial.print(" ");
        }
        Serial.println();
    }
}
