#include "utility.h"

void enablePin(int pin_number)
{
    if (pin_number == 0)
    {
        digitalWrite(CS_INA, LOW);
        digitalWrite(CS_INB, LOW);
    }
    else if (pin_number == 1)
    {
        digitalWrite(CS_INA, HIGH);
        digitalWrite(CS_INB, LOW);
    }
    else if (pin_number == 2)
    {
        digitalWrite(CS_INA, LOW);
        digitalWrite(CS_INB, HIGH);
    }
    else if (pin_number == 3)
    {
        digitalWrite(CS_INA, HIGH);
        digitalWrite(CS_INB, HIGH);
    }
}
