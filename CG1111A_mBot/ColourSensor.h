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
                            {0.357690, 0.345871, 0.296439},
                            {0.371094, 0.359107, 0.269799},
                            {0.368199, 0.348862, 0.282939},
                            {0.416583, 0.336377, 0.247040},
                            {0.349495, 0.357862, 0.292643},
                            {0.406310, 0.349920, 0.243770}};

        String _colours[NUM_COLOURS] = {"blue", "green", "pink", "red", "white", "orange"};
};

#endif // COLOUR_SENSOR_H

