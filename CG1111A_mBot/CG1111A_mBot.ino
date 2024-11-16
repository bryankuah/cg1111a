#include "configurations.h"
#include "ColourSensor.h"
#include "utility.h"
#include "MeMCore.h"

// Initialize sensors and motors
MeUltrasonicSensor ultraSensor(ULTRA_PORT);  // assigning ultraSensor port
MeLineFollower lineFinder(LINE_PORT);        // assigning lineFinder port
MeDCMotor leftMotor(M1);                 // assigning leftMotor to port M1
MeDCMotor rightMotor(M2);                // assigning RightMotor to port M2
MeRGBLed led(0, 30);
MeBuzzer buzzer;

int status = false;  // global status; 0 = do nothing, 1 = mBot runs
float ultraDistance;

int led_pins[NUM_COMPONENTS] = { MUX_LED_R, MUX_LED_G, MUX_LED_B };
ColourSensor colourSensor(CS_LDR_PIN, led_pins);

// Function to play celebratory tune
void celebrate() {
  // Simplified melody of the first few notes of the Moonlight Sonata (1st Movement)
  int melody[] = {
    E4, E4, E4, G4, G4, G4, E4, G4, E4, C5, B4, C5, E4, E4, D5, C5
  };

  // Note durations (in milliseconds)
  int duration[] = {
    500, 500, 500, 500, 500, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 1000, 1000
  };

  // Play each note in the melody
  for (int i = 0; i < 16; i++) {
    buzzer.tone(melody[i], duration[i]);  // Play the note with the specified frequency and duration
    delay(duration[i]);                   // Wait for the note to finish
  }
  buzzer.noTone();  // Stop the buzzer after playing the melody
}

// Function to read the IR sensor
int readIR() {
  int ambientValue;
  int shineValue;
  setMuxOut(MUX_LED_R);  // Turn off IR Emitter
  delay(1);
  ambientValue = analogRead(IR_READ_PIN);
  setMuxOut(MUX_IR);
  delay(1);
  shineValue = analogRead(IR_READ_PIN);
  setMuxOut(MUX_LED_R);  // Turn off IR Emitter
  // Serial.println(-(shineValue - ambientValue));
  return -(shineValue - ambientValue);
}

// Function to move forward
void moveForward() {
  leftMotor.run(-LEFT_FAST);   // Left wheel goes forward (anti-clockwise)
  rightMotor.run(RIGHT_FAST);  // Right wheel goes forward (clockwise)
}

// Function to turn right 90 degrees
void turnRight() {
  leftMotor.run(-LEFT_FAST);    // Left wheel goes forward (anti-clockwise)
  rightMotor.run(-RIGHT_FAST);  // Right wheel goes backward (anti-clockwise)
  delay(MOVE_TURN_90_DELAY);
  stopMotor();
}

// Function to turn left 90 degrees
void turnLeft() {
  leftMotor.run(LEFT_FAST);    // Left wheel goes backward (clockwise)
  rightMotor.run(RIGHT_FAST);  // Right wheel goes forward (clockwise)
  delay(MOVE_TURN_90_DELAY);
  stopMotor();
}

// Function to perform a U-turn
void uTurn() {
  turnLeft();
  turnLeft();
}

// Function to perform a double left turn
void doubleLeftTurn() {
  turnLeft();
  moveForward();
  delay(MOVE_ONE_WALL_DELAY);
  stopMotor();
  delay(MOVE_REVERSE_DELAY);
  turnLeft();
  stopMotor();
}

// Function to perform a double right turn
void doubleRightTurn() {
  turnRight();
  moveForward();
  delay(MOVE_ONE_WALL_DELAY);
  stopMotor();
  delay(MOVE_REVERSE_DELAY);
  turnRight();
  stopMotor();
}

// Function to nudge slightly to the left
void nudgeLeft() {
  leftMotor.run(-MOVE_MID);    // Left wheel stops
  rightMotor.run(RIGHT_FAST);  // Right wheel goes forward
}

// Function to nudge slightly to the right
void nudgeRight() {
  leftMotor.run(-LEFT_FAST);  // Left wheel goes forward
  rightMotor.run(MOVE_MID);   // Right wheel slows down
}

// Function to move only the right wheel forward
void rightWheelForwardOnly() {
  leftMotor.run(0);            // Left wheel slows down
  rightMotor.run(RIGHT_FAST);  // Right wheel goes forward
}

// Function to move only the left wheel forward
void leftWheelForwardOnly() {
  leftMotor.run(-LEFT_FAST);  // Left wheel goes forward
  rightMotor.run(0);          // Right wheel stops
}

// Function to stop the motors
void stopMotor() {
  leftMotor.stop();
  rightMotor.stop();
}

// Function to setup the IR sensor
void setupIRSensor() {
  pinMode(IR_READ_PIN, INPUT);
}

// Function to read the ultrasonic distance
float readUltraDistance() {
  return ultraSensor.distanceCm(20) - ULTRA_SENSOR_OFFSET;
}

// Function to handle movement based on detected colour
void colour_move(int col) {
  if (col == CS_BLUE) {
    led.setColor(0, 0, 255);
    led.show();
    doubleRightTurn();
  } else if (col == CS_GREEN) {
    led.setColor(0, 255, 0);
    led.show();
    turnRight();
  } else if (col == CS_PINK) {
    led.setColor(255, 0, 255);
    led.show();
    doubleLeftTurn();
  } else if (col == CS_RED) {
    led.setColor(255, 0, 0);
    led.show();
    turnLeft();
  } else if (col == CS_ORANGE) {
    led.setColor(255, 165, 0);
    led.show();
    uTurn();
  }
  led.setColor(0, 0, 0);
  led.show();
}

void testMovements() {
  while (true) {
    // turnRight();
    // doubleRightTurn();
    // uTurn();
    turnLeft();
    // doubleLeftTurn();
    stopMotor();
    delay(500);
  }
}

void ambulanceLight() {
  if (clrState < 20) {
    led.setColor(255, 255, 255);
    led.show();
    clrState += 1;
  } else if (clrState < 40) {
    led.setColor(255, 0, 0);
    led.show();
    clrState += 1;
  } else if (clrState < 60) {
    led.setColor(0, 0, 255);
    led.show();
    clrState += 1;
  } else {
    clrState = 0;
  }
}

// Arduino setup function
void setup() {
  //Serial.begin(9600);               // Setup serial monitor for debugging purpose
  pinMode(PUSH_BUTTON_PIN, INPUT);  // Setup push button pin as input
  setupMultiplexer();
  setupIRSensor();
  led.setpin(LED_PIN);
  led.setColor(255, 0, 0);
  led.show();
  // while (1) {
  //   int irReading = readIR();
  //   Serial.println(irReading);
  // }
  // buzzer.tone(130, 500);
  // while(1){
  //   colourSensor.detectColour();
  //   int col = colourSensor.identifyColours();
  //   colour_move(col);
  // }
  // colourSensor.getWhite();
  // colourSensor.calibrateColourSensor();
  // testMovements();
}

// Arduino loop function
void loop() {
  if (analogRead(PUSH_BUTTON_PIN) < PUSH_BUTTON_THRESHOLD) {  // If push button is pushed, the value will be very low
    status = !status;                                         // Toggle status
    if (status) {
      led.setColor(0, 0, 0);
    } else {
      led.setColor(255, 0, 0);
    }
    led.show();
    stopMotor();
    delay(BUTTON_LOOP_DELAY);  // Delay so that a button push won't be counted multiple times.
  }
  if (status) {                                  // run mBot only if status is 1
    int sensorState = lineFinder.readSensors();  // read the line sensor's state
    // Serial.println(sensorState);
    if (sensorState == LINE_BLACK_BLACK) {  // both line sensors detect black
      // begin colour challenge
      stopMotor();
      delay(LINE_SENSOR_DELAY);
      colourSensor.detectColour();
      int col = colourSensor.identifyColours();
      if (col == CS_WHITE) {
        led.setColor(255, 255, 255);
        led.show();
        celebrate();
        status = false;
      } else {
        colour_move(col);
      }
    } else if (sensorState == LINE_BLACK_WHITE) {  // only left sensor detect black
      // reposition until both sensors detect black
      rightWheelForwardOnly();
    } else if (sensorState == LINE_WHITE_BLACK) {
      // reposition until both sensors detect black
      leftWheelForwardOnly();
    } else if (sensorState == LINE_WHITE_WHITE) {  // both line sensors detect white
      // ambulanceLight();
      ultraDistance = readUltraDistance();  // distance of mBot from left wall
      // Serial.println(ultraDistance);
      if (ultraDistance < ULTRA_DISTANCE_THRESHOLD_LOW) {  // too close to left wall
        nudgeRight();
      } else if (ultraDistance > ULTRA_DISTANCE_THRESHOLD_HIGH) {  // too far from right wall
        int irReading = readIR();
        if (irReading > IR_TOO_NEAR) {  // mBot too close to right wall
          nudgeLeft();
        } else {  // there is either missing left/right wall in the grid
          moveForward();
        }
      } else {  // mBot is within the predetermined ideal distance from the left wall
        moveForward();
      }
    }
  }
}
