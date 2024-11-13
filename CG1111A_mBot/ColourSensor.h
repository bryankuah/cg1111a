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
    void getWhite();
    void calibrateColourSensor();

private:
    int _ina; int _inb; int _ldrPin;
    double _ambient_light = 0;
    int _led_pins[NUM_COMPONENTS];
    void _readColour(double *colourValue);
    double _calculateDistance(int colour_idx);
    double _rgb_vals[NUM_COMPONENTS];
    double _multiplier[3] = {2.41, 3.24, 3.61};
        String _colours[NUM_COLOURS] = {"blue", "green", "pink", "red", "white", "orange"};
    double _recorded_rgb_values[NUM_COLOURS][NUM_COMPONENTS] = {
            {0.203490, 0.371844, 0.424666}, // Blue
            {0.266424, 0.414654, 0.318922}, // Green
            {0.379544, 0.301241, 0.319215}, // Pink
            {0.545672, 0.229151, 0.225177}, // Red
            {0.326557, 0.336127, 0.337316}, // White
            {0.508530, 0.276555, 0.214914}  // Orange
        };
};

        //3.5cm

#endif // COLOUR_SENSOR_H

