#include "utility.h"

void setupMultiplexer()
{
    pinMode(MUX_INA, OUTPUT);
    pinMode(MUX_INB, OUTPUT);
    digitalWrite(MUX_INA, LOW);
    digitalWrite(MUX_INB, LOW);
}

void setMuxOut(int pin_number)
{
    if (pin_number == 0)
    {
        digitalWrite(MUX_INA, LOW);
        digitalWrite(MUX_INB, LOW);
    }
    else if (pin_number == 1)
    {
        digitalWrite(MUX_INA, HIGH);
        digitalWrite(MUX_INB, LOW);
    }
    else if (pin_number == 2)
    {
        digitalWrite(MUX_INA, LOW);
        digitalWrite(MUX_INB, HIGH);
    }
    else if (pin_number == 3)
    {
        digitalWrite(MUX_INA, HIGH);
        digitalWrite(MUX_INB, HIGH);
    }
}
