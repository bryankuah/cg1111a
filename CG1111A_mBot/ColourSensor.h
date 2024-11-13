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
                {0.140260, 0.368831, 0.490909}, // Blue
                {0.218430, 0.491468, 0.290102}, // Green
                {0.408110, 0.307161, 0.284728}, // Pink
                {0.688047, 0.174927, 0.137026}, // Red
                {0.342105, 0.346260, 0.311634}, // White
                {0.614326, 0.252846, 0.132827}  // Orange
            };
};

        //3.5cm

#endif // COLOUR_SENSOR_H

