#ifndef COLOUR_SENSOR_H
#define COLOUR_SENSOR_H

#include <Arduino.h>
#include "configurations.h"
#include "utility.h"

#define NUM_COMPONENTS 3
#define NUM_COLOURS 6

class ColourSensor {
public:
    ColourSensor(int ldrPin, int ledPins[NUM_COMPONENTS]);
    void detectColour();
    int getRGBValues(long rgb_values[NUM_COMPONENTS]);
    int identifyColours();
    void calibrateColourSensor();

private:
    int _ina; int _inb; int _ldrPin;
    int _led_pins[NUM_COMPONENTS];
    void _readColour(long *colourValue);
    double _calculateDistance(int colour_idx);
    int _readLDR();
    double _rgb_vals[NUM_COMPONENTS];
    double _recorded_rgb_values[NUM_COLOURS][NUM_COMPONENTS] = {
        { 6391, 7171, 5341 },
        { 6542, 7112, 4611 },
        { 6698, 7238, 5201 },
        { 6707, 6690, 4245 },
        { 6700, 7539, 5650 },
        { 6750, 6910, 4310 }
    };
    String _colours[NUM_COLOURS] = { "blue", "green", "pink", "red", "white", "orange" };
};

#endif // COLOUR_SENSOR_H

