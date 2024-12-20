#ifndef MUX_H
#define MUX_H

#include <Arduino.h>
#include "configurations.h"

// Function to setup the multiplexer
void setupMultiplexer();

// Function to set the multiplexer output
void setMuxOut(int pin_number);

#endif // MUX_H