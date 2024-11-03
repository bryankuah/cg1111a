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

void ColourSensor::detectColour() {
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
}


int ColourSensor::identifyColours() {
    int best_match = -1;
    long min_distance = 9999999;

    for (int colour_idx = 0; colour_idx < 6; colour_idx++) {
        long distance = calculateDistance(colour_idx);
        if (distance < min_distance) {
            min_distance = distance;
            best_match = colour_idx;
        }
    }

    return (min_distance <= CS_THRESHOLD) ? best_match : -1;
}

long ColourSensor::calculateDistance(int colour_idx) {
    long sum = 0;
    for (int j = 0; j < 3; j++) {
        int diff = rgb_vals[j] - recorded_rgb_values[colour_idx][j];
        sum += diff * diff;
    }
    return sum;
}

void ColourSensor::calibrateColourSensor() {
    for (int i = 0; i < 6; i++) {
        Serial.println("Place the sensor on " + colours[i] + " colour");
        delay(5000);
        detectColour();
        Serial.print("RGB values: ");
        for (int j = 0; j < 3; j++) {
            Serial.print(rgb_values[j]);
            Serial.print(" ");
        }
        Serial.println();
    }
}
