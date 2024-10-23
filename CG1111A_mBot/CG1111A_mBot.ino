#include "MeMCore.h"

#define TURN_90_DELAY

#define L_B_R_B (0x00)
#define L_B_R_W (0x01)
#define L_W_R_B (0x02)
#define L_W_R_W (0x03)


#define LDR A0
#define LED_R 1
#define LED_G 2
#define LED_B 3


MeLineFollower lineFinder(PORT_2);  // assigning lineFinder to RJ25 port 2
MeDCMotor leftMotor(M1);            // assigning leftMotor to port M1
MeDCMotor rightMotor(M2);           // assigning RightMotor to port M2
int status = 0;                     // global status; 0 = do nothing, 1 = mBot runs

// Code for playing celebratory tune
void celebrate() {}
// Code for moving forward for some short interval
void moveForward() {
  leftMotor.run(-200);  // Left wheel goes forward (anti-clockwise)
  rightMotor.run(200);  // Right wheel goes forward (clockwise)
}
// Code for turning right 90 deg
void turnRight() {
  leftMotor.run(-150);   // Left wheel goes forward (anti-clockwise)
  rightMotor.run(-150);  // Right wheel goes backward (anti-clockwise)
  delay(TURN_90_DELAY);
}
// Code for turning left 90 deg
void turnLeft() {
  leftMotor.run(150);   // Left wheel goes backward (clockwise)
  rightMotor.run(150);  // Right wheel goes forward (clockwise)
  delay(TURN_90_DELAY);
}
// Code for u-turn
void uTurn() {}
// Code for double left turn
void doubleLeftTurn() {}
// Code for double right turn
void doubleRightTurn() {}

// Code for nudging slightly to the left for some short interval
void nudgeLeft() {}
// Code for nudging slightly to the right for some short interval
void nudgeRight() {}
// Code for turning on the IR emitter only
void shineIR() {}
int readLDR() {
  return analogRead(LDR);
}
// Code for stopping motor
void stopMotor() {
  status = 0;
}
int shineRed() {  // Code for turning on the red LED only
  digitalWrite(LED_R, HIGH);
  delay(100);
  int result = readLDR();
  digitalWrite(LED_R, LOW);
  return result;
}
int shineGreen() {  // Code for turning on the green LED only
  digitalWrite(LED_G, HIGH);
  delay(100);
  int result = readLDR();
  digitalWrite(LED_G, LOW);
  return result;
}
int shineBlue() {  // Code for turning on the blue LED only
  digitalWrite(LED_B, HIGH);
  delay(100);
  int result = readLDR();
  digitalWrite(LED_B, LOW);
  return result;
}
int detectColour() {
  int redResult = shineRed();      // Shine Red, read LDR after some delay
  int greenResult = shineGreen();  // Shine Green, read LDR after some delay
  int blueResult = shineBlue();    // Shine Blue, read LDR after some delay

  // Run algorithm for colour decoding
}
void setup() {
  pinMode(LDR, INPUT);  // Setup A0 as input for the LDR
  pinMode(A7, INPUT);   // Setup A7 as input for the push button
  Serial.begin(9600);   // Setup serial monitor for debugging purpose
}
void loop() {
  if (analogRead(A7) < 100) {  // If push button is pushed, the value will be very low
    status = 1 - status;       // Toggle status
    delay(500);                // Delay 500ms so that a button push won't be counted multiple times.
  }
  if (status == 1) {                             // run mBot only if status is 1
    int sensorState = lineFinder.readSensors();  // read the line sensor's state
    Serial.println(sensorState);
    if (sensorState == L_W_R_W) {         // situation 1
      leftMotor.run(-200);                // Left wheel goes forward (anti-clockwise)
      rightMotor.run(200);                // Right wheel goes forward (clockwise)
    } else if (sensorState == L_B_R_W) {  // situation 2
      leftMotor.run(0);                   // Left wheel stops
      rightMotor.run(150);                // Right wheel go forward
    } else if (sensorState == L_W_R_B) {  // situation 3
      leftMotor.run(-150);                // Left wheel go forward
      rightMotor.run(0);                  // Right wheel stops
    } else if (sensorState == L_B_R_B) {  // situation 4
      leftMotor.stop();
      rightMotor.stop();
      // int colour = detectColour();
      // decide next move
    }
    delay(20);  // decision making interval (in milliseconds)
  }
}
