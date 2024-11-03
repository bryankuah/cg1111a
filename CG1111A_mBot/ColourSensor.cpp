#include "ColourSensor.h"
#include "configurations.h"
ColourSensor::ColourSensor(int ldrPin, int ledPins[NUM_COMPONENTS]){
    _ldrPin = ldrPin;
    for (int i = 0; i < NUM_COMPONENTS; i++) {
        _led_pins[i] = ledPins[i];
    }
    pinMode(_ldrPin, INPUT);
}

int ColourSensor::_readLDR() {
    return analogRead(_ldrPin);
}

void ColourSensor::_readColour(long *colourValue) {
    *colourValue = 0;
    for (int i = CS_SAMPLES; i > 0; i--) {
        *colourValue += analogRead(_ldrPin);
    }
}

void ColourSensor::detectColour() {
    long ambient_light = 0;
    setMuxOut(MUX_IR); // turn off all LEDs
    delay(CS_DELAY_BEFORE_READING);
    _readColour(&ambient_light);
    long reading = 0;

    for (int i = 0; i < NUM_COMPONENTS; i++) {
        setMuxOut(_led_pins[i]);
        delay(CS_DELAY_BEFORE_READING);
        _readColour(&reading);
        reading -= ambient_light;
        _rgb_vals[i] = reading;
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

    return (min_distance <= CS_THRESHOLD) ? best_match : -1;
}

double ColourSensor::_calculateDistance(int colour_idx) {
    double sum = 0;
    for (int i = 0; i < NUM_COMPONENTS; i++) {
        sum += pow(_rgb_vals[i] - _recorded_rgb_values[colour_idx][i], 2);
    }
    return sum;
}

void ColourSensor::calibrateColourSensor() {
    for (int i = 0; i < NUM_COLOURS; i++) {
        Serial.println("Place the sensor on " + _colours[i] + " colour");
        delay(5000);
        detectColour();
        Serial.print("RGB values: ");
        for (int j = 0; j < NUM_COMPONENTS; j++) {
            Serial.print(_rgb_vals[j]);
            Serial.print(" ");
        }
        Serial.println();
    }
}
