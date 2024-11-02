#ifndef COLOUR_SENSOR_H
#define COLOUR_SENSOR_H

#include <Arduino.h>
#include "configurations.h"
#include "utility.h"

class ColourSensor {
public:
    ColourSensor(int ina, int inb, int ldrPin, int ledPins[3]);
    void setup();
    int readLDR();
    void readColour(long *colourValue);
    int detectColour(long rgb_values[3]);
    int identifyColours(long rgb_vals[3]);
    void calibrateColourSensor();

private:
    int CS_INA;
    int CS_INB;
    int CS_LDR_PIN;
    int led_pins[3];
    long recorded_rgb_values[6][3] = { { 6391, 7171, 5341 }, { 6542, 7112, 4611 }, { 6698, 7238, 5201 }, { 6707, 6690, 4245 }, { 6700, 7539, 5650 }, { 6750, 6910, 4310 } };
    String colours[6] = { "blue", "green", "pink", "red", "white", "orange" };
};

#endif // COLOUR_SENSOR_H
