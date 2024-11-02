#include "MeMCore.h"
#include "configurations.h"
#include "ColourSensor.h"
#include "utility.h"

MeUltrasonicSensor ultraSensor(PORT_1);  // assigning ultraSensor to RJ25 port 1
MeLineFollower lineFinder(PORT_2);       // assigning lineFinder to RJ25 port 2
MeDCMotor leftMotor(M1);                 // assigning leftMotor to port M1
MeDCMotor rightMotor(M2);                // assigning RightMotor to port M2
int status = false;                      // global status; 0 = do nothing, 1 = mBot runs
float ultraDistance;

String colours[] = { "blue", "green", "pink", "red", "white", "orange" };
long rgb_values[3] = { 0, 0, 0 };


long recorded_rgb_values[6][3] = { { 6391, 7171, 5341 }, { 6542, 7112, 4611 }, { 6698, 7238, 5201 }, { 6707, 6690, 4245 }, { 6700, 7539, 5650 }, { 6750, 6910, 4310 } };
int num_colours = sizeof(recorded_rgb_values) / sizeof(recorded_rgb_values[0]);

int led_pins[3] = { CS_LED_R, CS_LED_G, CS_LED_B };
ColourSensor colourSensor(CS_INA, CS_INB, CS_LDR_PIN, led_pins);

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
  leftMotor.run(-50);   // Left wheel stops
  rightMotor.run(150);  // Right wheel goes forward
}

// Code for nudging slightly to the right for some short interval
void nudgeRight() {
  leftMotor.run(-150);  // Left wheel goes forward
  rightMotor.run(50);   // Right wheel slows down
}

void rightWheelForwardOnly() {
  leftMotor.run(0);     // Left wheel slows down
  rightMotor.run(150);  // Right wheel goes forward
}

void leftWheelForwardOnly() {
  leftMotor.run(-150);  // Left wheel goes forward
  rightMotor.run(0);    // Right wheel stops
}

// Code for reading the IR
int readIR() {
  int ambientValue = analogRead(IR_READ_PIN);
  enablePin(0);
  delay(50);
  int shineValue = analogRead(IR_READ_PIN);
  enablePin(3);
  // Serial.print(ambientValue);
  // Serial.print(" ");
  // Serial.print(shineValue);
  // Serial.print(" ");
  // Serial.println(shineValue - ambientValue);
  return shineValue - ambientValue;
}

// Code for stopping motor
void stopMotor() {
  leftMotor.stop();
  rightMotor.stop();
}


// Colour sensor codes

int readLDR() {
  return analogRead(CS_LDR_PIN);
}

void setupIRSensor() {
  pinMode(IR_READ_PIN, INPUT);
}

float readUltraDistance() {
  return ultraSensor.distanceCm() - 4;
}

void setup() {
  pinMode(A7, INPUT);   // Setup A7 as input for the push button
  Serial.begin(9600);   // Setup serial monitor for debugging purpose
  colourSensor.setup(); // Setup colour sensor
  setupIRSensor();
}

int colour_index = 0;
void loop() {
  if (analogRead(A7) < 100) {  // If push button is pushed, the value will be very low
    status = !status;          // Toggle status
    delay(500);                // Delay 500ms so that a button push won't be counted multiple times.
    // readColour(rgb_values);
    // colour_index = identifyColours(rgb_values);
    // if (colour_index != -1)
    // {
    //   Serial.println("Colour detected: " + String(colours[colour_index]));
    // } else {
    //   Serial.println("Colour not detected");
    // }
  }
  if (status) {                                  // run mBot only if status is 1
    int sensorState = lineFinder.readSensors();  // read the line sensor's state
    // Serial.println(sensorState);
    if (sensorState == L_B_R_B) {  // situation 4
      stopMotor();
      colourSensor.detectColour(rgb_values);
      int col = colourSensor.identifyColours(rgb_values);
      Serial.println(colours[col]);
      if (colours[col] == "pink") {
        doubleLeftTurn();
      } else if (colours[col] == "blue") {
        doubleRightTurn();
      } else if (colours[col] == "white") {
        stopMotor();
      } else if (colours[col] == "red") {
        turnLeft();
      } else if (colours[col] == "green") {
        turnRight();
      } else if (colours[col] == "orange") {
        uTurn();
      }
    } else if (sensorState == L_B_R_W) {
      rightWheelForwardOnly();
    } else if (sensorState == L_W_R_B) {
      leftWheelForwardOnly();
    } else if (sensorState == L_W_R_W) {
      ultraDistance = readUltraDistance();
      if (ultraDistance < 6) {
        nudgeRight();
      } else if (ultraDistance > 8) {
        int irReading = readIR();
        if (irReading > IR_TOO_NEAR) {
          nudgeLeft();
        } else {
          moveForward();
        }
      } else {
        moveForward();
      }
    }
  }
}
