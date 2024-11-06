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
    void _readColour(double *colourValue);
    double _calculateDistance(int colour_idx);
    int _readLDR();
    double _rgb_vals[NUM_COMPONENTS];
    double _recorded_rgb_values[NUM_COLOURS][NUM_COMPONENTS] = {
                            {0.37, 0.35, 0.29},
                            {0.39, 0.36, 0.26},
                            {0.38, 0.35, 0.27},
                            {0.43, 0.35, 0.22},
                            {0.36, 0.36, 0.29},
                            {0.42, 0.36, 0.22}};

    String _colours[NUM_COLOURS] = { "blue", "green", "pink", "red", "white", "orange" };
};

#endif // COLOUR_SENSOR_H

