#include "MeMCore.h"
#include "configurations.h"

MeLineFollower lineFinder(PORT_2);  // assigning lineFinder to RJ25 port 2
MeDCMotor leftMotor(M1);            // assigning leftMotor to port M1
MeDCMotor rightMotor(M2);           // assigning RightMotor to port M2
int status = 0;                     // global status; 0 = do nothing, 1 = mBot runs

long rgb_values[3] = {0, 0, 0};
int led_pins[3] = {CS_LED_R, CS_LED_G, CS_LED_B};

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
void uTurn() {
  leftMotor.run(150);   // Left wheel goes backward (clockwise)
  rightMotor.run(150);  // Right wheel goes backward (clockwise)
  delay(TURN_180_DELAY);
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
  leftMotor.run(0);                   // Left wheel stops
  rightMotor.run(150);  // Right wheel goes forward
}
// Code for nudging slightly to the right for some short interval
void nudgeRight() {
  leftMotor.run(-150);                // Left wheel go forward
  rightMotor.run(0);                  // Right wheel stops
}
// Code for turning on the IR emitter only
void shineIR() {}

int readLDR() {
  return analogRead(CS_LDR_PIN);
}
// Code for stopping motor
void stopMotor() {
  leftMotor.stop();
  rightMotor.stop();
}

void setupColourSensor()
{
  pinMode(CS_INA, OUTPUT);
  pinMode(CS_INB, OUTPUT);
  pinMode(CS_LDR_PIN, INPUT);
  digitalWrite(CS_INA, LOW);
  digitalWrite(CS_INB, LOW);
}

void readColour(long *colourValue)
{
  *colourValue = 0;

  for (int i = CS_SAMPLES; i > 0; i--)
  {
    // need to check if it will overflow (tho hopefully not)
    *colourValue += (analogRead(CS_LDR_PIN));
  }
}

// for HD74LS139 (two to four multiplexer)
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

int detectColour(int led_pins[3], long rgb_values[3])
{
  for (int i = 0; i < 3; i++)
  {
    enablePin(led_pins[i]);
    delay(CS_DELAY_BEFORE_READING);
    readColour(rgb_values + i);
  }
  enablePin(CS_LED_OFF);
}

void setup() {
  pinMode(A7, INPUT);   // Setup A7 as input for the push button
  Serial.begin(9600);   // Setup serial monitor for debugging purpose
  setupColourSensor();  // Setup colour sensor
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
      moveForward();
    } else if (sensorState == L_B_R_W) {  // situation 2
      nudgeLeft();
    } else if (sensorState == L_W_R_B) {  // situation 3
      nudgeRight();
    } else if (sensorState == L_B_R_B) {  // situation 4
      stopMotor();
      // will be stored in the array rgb_values
      detectColour(led_pins, rgb_values);
      // we will just print them out for debugging
      for (int i = 0; i < 3; i++)
      {
        Serial.print(rgb_values[i]);
        Serial.print("  ");
      }
      Serial.println();
      // decide next move
    }
    delay(20);  // decision making interval (in milliseconds)
  }
}
