#ifndef COLOUR_SENSOR_H
#define COLOUR_SENSOR_H

#include <Arduino.h>
#include "configurations.h"
#include "mux.h"

#define NUM_COMPONENTS 3
#define NUM_COLOURS 6

class ColourSensor {
public:
  ColourSensor(int ldrPin, int ledPins[NUM_COMPONENTS]);
  void detectColour();
  int identifyColours();
  void calibrateColourSensor();

private:
  int _ina;
  int _inb;
  int _ldrPin;
  double _ambient_light = 0;
  int _led_pins[NUM_COMPONENTS];
  void _readColour(double *colourValue);
  double _calculateDistance(int colour_idx);
  double _rgb_vals[NUM_COMPONENTS];
  String _colours[NUM_COLOURS] = { "blue", "green", "pink", "red", "white", "orange" };
    double _recorded_rgb_values[NUM_COLOURS][NUM_COMPONENTS] = {
          {0.177570, 0.373832, 0.448598}, // Blue
          {0.236220, 0.454068, 0.309711}, // Green
          {0.394725, 0.312548, 0.292728}, // Pink
          {0.596026, 0.215845, 0.188129}, // Red
          {0.344700, 0.344329, 0.310971}, // White
          {0.546645, 0.267983, 0.185372}  // Orange
      };
};

#endif  // COLOUR_SENSOR_H
