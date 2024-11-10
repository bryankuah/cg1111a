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
    double _rgb_vals[NUM_COMPONENTS];

    String _colours[NUM_COLOURS] = {"blue", "green", "pink", "red", "white", "orange"};
        double _recorded_rgb_values[NUM_COLOURS][NUM_COMPONENTS] = {
            {0.035536, 0.210370, 0.754094}, // Blue
            {0.053768, 0.299400, 0.646832}, // Green
            {0.151992, 0.235849, 0.612159}, // Pink
            {0.277264, 0.179708, 0.543027}, // Red
            {0.121994, 0.251456, 0.626550}, // White
            {0.263023, 0.224105, 0.512426}  // Orange
        };
};

        //3.5cm

#endif // COLOUR_SENSOR_H

