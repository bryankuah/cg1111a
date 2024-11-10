#include "utility.h"

// Function to setup the multiplexer
void setupMultiplexer()
{
    pinMode(MUX_INA, OUTPUT);
    pinMode(MUX_INB, OUTPUT);
    
    for(int i = 0; i < MUX_OUTPUT_COUNT; i++) {
        setMuxOut(i);
        delay(MUX_SETUP_DELAY);
    }
}

// Function to set the multiplexer output based on the pin number
void setMuxOut(int pin_number)
{
    switch(pin_number) {
        case 0:
            digitalWrite(MUX_INA, LOW);
            digitalWrite(MUX_INB, LOW);
            break;
        case 1:
            digitalWrite(MUX_INA, HIGH);
            digitalWrite(MUX_INB, LOW);
            break;
        case 2:
            digitalWrite(MUX_INA, LOW);
            digitalWrite(MUX_INB, HIGH);
            break;
        case 3:
            digitalWrite(MUX_INA, HIGH);
            digitalWrite(MUX_INB, HIGH);
            break;
    }
}
