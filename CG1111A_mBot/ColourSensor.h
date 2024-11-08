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

    String _colours[NUM_COLOURS] = {"blue", "green", "pink", "red", "white", "orange"};
   double _recorded_rgb_values[NUM_COLOURS][NUM_COMPONENTS] = {
        {0.3405449, 0.3297276, 0.3297276},
        {0.3438472, 0.3303915, 0.3257612},
        {0.3434557, 0.3297171, 0.3268272},
        {0.3498458, 0.3232078, 0.3269464},
        {0.3408718, 0.3325139, 0.3266143},
        {0.3481116, 0.3264047, 0.3254837}};
};

        //3.5cm

#endif // COLOUR_SENSOR_H

