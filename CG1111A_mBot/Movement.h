#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "MeMCore.h"
#include <Arduino.h>

void moveForward();
void turnRight();
void turnLeft();
void doubleLeftTurn();
void doubleRightTurn();
void nudgeLeft();
void nudgeRight();
void uTurn();
void rightWheelForwardOnly();
void leftWheelForwardOnly();
void stopMotor();

#endif