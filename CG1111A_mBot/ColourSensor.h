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
        {0.236738, 0.391129, 0.372133}, 
        {0.259551, 0.398132, 0.342317}, 
        {0.316008, 0.357798, 0.326194}, 
        {0.357895, 0.347413, 0.294693}, 
        {0.309742, 0.357957, 0.332301}, 
        {0.349260, 0.363305, 0.287435}  
    };
};

        //3.5cm

#endif // COLOUR_SENSOR_H

