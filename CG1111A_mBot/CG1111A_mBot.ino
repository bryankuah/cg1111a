#include "configurations.h"
#include "ColourSensor.h"
#include "utility.h"
#include "MeMCore.h"

// Initialize sensors and motors
MeUltrasonicSensor ultraSensor(PORT_1);  // assigning ultraSensor to RJ25 port 1
MeLineFollower lineFinder(PORT_2);       // assigning lineFinder to RJ25 port 2
MeDCMotor leftMotor(M1);                 // assigning leftMotor to port M1
MeDCMotor rightMotor(M2);                // assigning RightMotor to port M2
MeRGBLed led(0, 30);
MeBuzzer buzzer;

int status = false;  // global status; 0 = do nothing, 1 = mBot runs
float ultraDistance;

#ifdef PID
// PID constants
float Kp = 0.3;
float Kd = 0.02;
float previous_error = 0;
float setpoint = 7.0;  // Desired distance
#endif

int led_pins[NUM_COMPONENTS] = { MUX_LED_R, MUX_LED_G, MUX_LED_B };
ColourSensor colourSensor(CS_LDR_PIN, led_pins);

// Function to play celebratory tune
void celebrate() {
  // Simplified bass line and melody from Moonlight Sonata
  // Bass Line (arpeggio-style)
  buzzer.tone(NOTE_C3, LONG_DELAY);  // C3
  delay(LONG_DELAY);                 // Wait for note duration
  buzzer.tone(NOTE_G3, LONG_DELAY);  // G3
  delay(LONG_DELAY);                 // Wait for note duration
  buzzer.tone(NOTE_C3, LONG_DELAY);  // C3
  delay(LONG_DELAY);                 // Wait for note duration
  buzzer.tone(NOTE_G3, LONG_DELAY);  // G3
  delay(LONG_DELAY);                 // Wait for note duration
  buzzer.tone(NOTE_C3, LONG_DELAY);  // C3
  delay(LONG_DELAY);                 // Wait for note duration

  delay(PAUSE);  // Short pause before melody begins

  // Melody part 1
  buzzer.tone(NOTE_EB4, SHORT_DELAY);  // Eb4 (start of melody)
  delay(SHORT_DELAY);                  // Wait for note duration
  buzzer.tone(NOTE_G4, SHORT_DELAY);   // G4
  delay(SHORT_DELAY);                  // Wait for note duration
  buzzer.tone(NOTE_C4, SHORT_DELAY);   // C4
  delay(SHORT_DELAY);                  // Wait for note duration
  buzzer.tone(NOTE_EB4, SHORT_DELAY);  // Eb4
  delay(SHORT_DELAY);                  // Wait for note duration
  buzzer.tone(NOTE_G4, SHORT_DELAY);   // G4
  delay(SHORT_DELAY);                  // Wait for note duration

  delay(PAUSE);  // Pause before the next section

  // Melody part 2
  buzzer.tone(NOTE_F4, SHORT_DELAY);  // F4
  delay(SHORT_DELAY);                 // Wait for note duration
  buzzer.tone(NOTE_A4, SHORT_DELAY);  // A4
  delay(SHORT_DELAY);                 // Wait for note duration
  buzzer.tone(NOTE_C4, SHORT_DELAY);  // C4
  delay(SHORT_DELAY);                 // Wait for note duration
  buzzer.tone(NOTE_F4, SHORT_DELAY);  // F4
  delay(SHORT_DELAY);                 // Wait for note duration
  buzzer.tone(NOTE_A4, SHORT_DELAY);  // A4
  delay(SHORT_DELAY);                 // Wait for note duration

    delay(PAUSE);  // Pause before the next section

  // Repeat the song to create a loop
  delay(1000);  // Wait before repeating the piece
}

// Function to read the IR sensor
int readIR() {
  int ambientValue;
  int shineValue;
  setMuxOut(MUX_LED_B);  // Turn off IR Emitter
  delay(10);
  ambientValue = analogRead(IR_READ_PIN);
  setMuxOut(MUX_IR);
  delay(10);
  shineValue = analogRead(IR_READ_PIN);
  return -(shineValue - ambientValue);
}

// Function to move forward
void moveForward() {
  leftMotor.run(-FAST_SPEED);  // Left wheel goes forward (anti-clockwise)
  rightMotor.run(FAST_SPEED);  // Right wheel goes forward (clockwise)
}

// Function to turn right 90 degrees
void turnRight() {
  leftMotor.run(-MID_SPEED);   // Left wheel goes forward (anti-clockwise)
  rightMotor.run(-MID_SPEED);  // Right wheel goes backward (anti-clockwise)
  delay(TURN_90_DELAY);
  stopMotor();
}

// Function to turn left 90 degrees
void turnLeft() {
  leftMotor.run(MID_SPEED);   // Left wheel goes backward (clockwise)
  rightMotor.run(MID_SPEED);  // Right wheel goes forward (clockwise)
  delay(TURN_90_DELAY);
  stopMotor();
}

// Function to perform a U-turn
void uTurn() {
  leftMotor.run(MID_SPEED);   // Left wheel goes backward (clockwise)
  rightMotor.run(MID_SPEED);  // Right wheel goes backward (clockwise)
  delay(TURN_180_DELAY);
  stopMotor();
}

// Function to perform a double left turn
void doubleLeftTurn() {
  turnLeft();
  moveForward();
  delay(ONE_WALL_DELAY);
  stopMotor();
  delay(SPEED_REVERSE_DELAY);
  turnLeft();
  stopMotor();
}

// Function to perform a double right turn
void doubleRightTurn() {
  turnRight();
  moveForward();
  delay(ONE_WALL_DELAY);
  stopMotor();
  delay(SPEED_REVERSE_DELAY);
  turnRight();
  stopMotor();
}

// Function to nudge slightly to the left
void nudgeLeft() {
  leftMotor.run(-SLOW_SPEED);  // Left wheel stops
  rightMotor.run(FAST_SPEED);  // Right wheel goes forward
}

// Function to nudge slightly to the right
void nudgeRight() {
  leftMotor.run(-FAST_SPEED);  // Left wheel goes forward
  rightMotor.run(SLOW_SPEED);  // Right wheel slows down
}

// Function to move only the right wheel forward
void rightWheelForwardOnly() {
  leftMotor.run(0);            // Left wheel slows down
  rightMotor.run(FAST_SPEED);  // Right wheel goes forward
}

// Function to move only the left wheel forward
void leftWheelForwardOnly() {
  leftMotor.run(-FAST_SPEED);  // Left wheel goes forward
  rightMotor.run(0);           // Right wheel stops
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
  return ultraSensor.distanceCm(20) - 4;
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

// Arduino setup function
void setup() {
  Serial.begin(9600);  // Setup serial monitor for debugging purpose
  pinMode(A7, INPUT);  // Setup A7 as input for the push button
  led.setpin(13);
  setupMultiplexer();
  setupIRSensor();
  led.setColor(255, 0, 0);
  led.show();
  // buzzer.tone(130, 500);
  // while(1){
  //   Serial.println(readIR());
  // }
  // colourSensor.calibrateColourSensor();
}

// Arduino loop function
void loop() {
  if (analogRead(A7) < 100) {  // If push button is pushed, the value will be very low
    status = !status;          // Toggle status
    if (status) {
      led.setColor(0, 0, 0);
    } else {
      led.setColor(255, 0, 0);
    }
    led.show();
    stopMotor();
    delay(500);  // Delay 500ms so that a button push won't be counted multiple times.
  }

  if (status) {                                  // run mBot only if status is 1
    int sensorState = lineFinder.readSensors();  // read the line sensor's state
    // Serial.println(sensorState);
    if (sensorState == L_B_R_B) {  // situation 4
      stopMotor();
      delay(200);
      colourSensor.detectColour();
      int col = colourSensor.identifyColours();
      if (col == CS_WHITE) {
        led.setColor(255, 255, 255);
        led.show();
        celebrate();
        status = false;
      }
      colour_move(col);
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
#ifdef PID
        float error = setpoint - ultraDistance;
        float derivative = error - previous_error;
        float output = Kp * error + Kd * derivative;

        // Adjust motor speeds based on PID output
        // leftMotor.run(output);
        // rightMotor.run(output);
#else
        moveForward();
#endif
      }
    }
  }
}
