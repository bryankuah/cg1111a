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
    double _multiplier[3] = {1, 1, 1};
    String _colours[NUM_COLOURS] = {"blue", "green", "pink", "red", "white", "orange"};
        double _recorded_rgb_values[NUM_COLOURS][NUM_COMPONENTS] = {
            {0.144832, 0.357040, 0.498128}, // Blue
            {0.220149, 0.496269, 0.283582}, // Green
            {0.422764, 0.286585, 0.290650}, // Pink
            {0.732206, 0.140944, 0.126850}, // Red
            {0.331691, 0.341544, 0.326765}, // White
            {0.646144, 0.226760, 0.127095}  // Orange
        };
};

        //3.5cm

#endif // COLOUR_SENSOR_H

