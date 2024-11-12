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
    double _multiplier[3] = {2.34, 3.22, 3.94};
        String _colours[NUM_COLOURS] = {"blue", "green", "pink", "red", "white", "orange"};
    double _recorded_rgb_values[NUM_COLOURS][NUM_COMPONENTS] = {
        {0.156016, 0.382586, 0.461398}, // Blue
        {0.224825, 0.468242, 0.306933}, // Green
        {0.387683, 0.303868, 0.308450}, // Pink
        {0.578722, 0.214699, 0.206579}, // Red
        {0.324313, 0.341865, 0.333821}, // White
        {0.545802, 0.261144, 0.193053}  // Orange
    };
};

        //3.5cm

#endif // COLOUR_SENSOR_H

