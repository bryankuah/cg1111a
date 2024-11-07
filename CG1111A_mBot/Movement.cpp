#include "configurations.h"
#include "Movement.h"
#include "MeMCore.h"
#include <Arduino.h>

MeDCMotor leftMotor(M1);                 // assigning leftMotor to port M1
MeDCMotor rightMotor(M2);                // assigning RightMotor to port M2

// Code for moving forward for some short interval
void moveForward() {
  leftMotor.run(-FAST_SPEED);  // Left wheel goes forward (anti-clockwise)
  rightMotor.run(FAST_SPEED);  // Right wheel goes forward (clockwise)
}
// Code for turning right 90 deg
void turnRight() {
  leftMotor.run(-FAST_SPEED);   // Left wheel goes forward (anti-clockwise)
  rightMotor.run(-FAST_SPEED);  // Right wheel goes backward (anti-clockwise)
  delay(TURN_90_DELAY);
}
// Code for turning left 90 deg
void turnLeft() {
  leftMotor.run(FAST_SPEED);   // Left wheel goes backward (clockwise)
  rightMotor.run(FAST_SPEED);  // Right wheel goes forward (clockwise)
  delay(TURN_90_DELAY);
}
// Code for u-turn
void uTurn() {
  leftMotor.run(FAST_SPEED);   // Left wheel goes backward (clockwise)
  rightMotor.run(FAST_SPEED);  // Right wheel goes backward (clockwise)
  delay(2 * TURN_90_DELAY);
}
// Code for double left turn
void doubleLeftTurn() {
  turnLeft();
  moveForward();
  delay(ONE_WALL_DELAY);
  turnLeft();
}
// Code for double right turn
void doubleRightTurn() {
  turnRight();
  moveForward();
  delay(ONE_WALL_DELAY);
  turnRight();
}

// Code for nudging slightly to the left for some short interval
void nudgeLeft() {
  leftMotor.run(-50);          // Left wheel stops
  rightMotor.run(FAST_SPEED);  // Right wheel goes forward
}

// Code for nudging slightly to the right for some short interval
void nudgeRight() {
  leftMotor.run(-FAST_SPEED);  // Left wheel goes forward
  rightMotor.run(50);          // Right wheel slows down
}

void rightWheelForwardOnly() {
  leftMotor.run(0);            // Left wheel slows down
  rightMotor.run(FAST_SPEED);  // Right wheel goes forward
}

void leftWheelForwardOnly() {
  leftMotor.run(-FAST_SPEED);  // Left wheel goes forward
  rightMotor.run(0);           // Right wheel stops
}

// Code for stopping motor
void stopMotor() {
  leftMotor.stop();
  rightMotor.stop();
}