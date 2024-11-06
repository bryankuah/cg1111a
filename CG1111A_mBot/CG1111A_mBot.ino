#include "MeMCore.h"
#include "configurations.h"
#include "ColourSensor.h"
#include "utility.h"

MeUltrasonicSensor ultraSensor(PORT_1);  // assigning ultraSensor to RJ25 port 1
MeLineFollower lineFinder(PORT_2);       // assigning lineFinder to RJ25 port 2
MeDCMotor leftMotor(M1);                 // assigning leftMotor to port M1
MeDCMotor rightMotor(M2);                // assigning RightMotor to port M2
MeRGBLed led(0, 30);
MeBuzzer buzzer;

int status = false;  // global status; 0 = do nothing, 1 = mBot runs
float ultraDistance;

int led_pins[NUM_COMPONENTS] = { MUX_LED_R, MUX_LED_G, MUX_LED_B };
ColourSensor colourSensor(CS_LDR_PIN, led_pins);

// Code for playing celebratory tune
void celebrate() {
  // Simplified bass line and melody from Moonlight Sonata

  // Bass Line (arpeggio-style)
  buzzer.tone(note_C3, longDelay);  // C3
  delay(longDelay);                 // Wait for note duration
  buzzer.tone(note_G3, longDelay);  // G3
  delay(longDelay);                 // Wait for note duration
  buzzer.tone(note_C3, longDelay);  // C3
  delay(longDelay);                 // Wait for note duration
  buzzer.tone(note_G3, longDelay);  // G3
  delay(longDelay);                 // Wait for note duration
  buzzer.tone(note_C3, longDelay);  // C3
  delay(longDelay);                 // Wait for note duration

  delay(pause);  // Short pause before melody begins

  // Melody part 1
  buzzer.tone(note_Eb4, shortDelay);  // Eb4 (start of melody)
  delay(shortDelay);                  // Wait for note duration
  buzzer.tone(note_G4, shortDelay);   // G4
  delay(shortDelay);                  // Wait for note duration
  buzzer.tone(note_C4, shortDelay);   // C4
  delay(shortDelay);                  // Wait for note duration
  buzzer.tone(note_Eb4, shortDelay);  // Eb4
  delay(shortDelay);                  // Wait for note duration
  buzzer.tone(note_G4, shortDelay);   // G4
  delay(shortDelay);                  // Wait for note duration

  delay(pause);  // Pause before the next section

  // Melody part 2
  buzzer.tone(note_F4, shortDelay);  // F4
  delay(shortDelay);                 // Wait for note duration
  buzzer.tone(note_A4, shortDelay);  // A4
  delay(shortDelay);                 // Wait for note duration
  buzzer.tone(note_C4, shortDelay);  // C4
  delay(shortDelay);                 // Wait for note duration
  buzzer.tone(note_F4, shortDelay);  // F4
  delay(shortDelay);                 // Wait for note duration
  buzzer.tone(note_A4, shortDelay);  // A4
  delay(shortDelay);                 // Wait for note duration

  delay(longDelay);  // Long pause at the end

  // Repeat the song to create a loop
  delay(1000);  // Wait before repeating the piece
}
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

// Code for reading the IR
int readIR() {
  int ambientValue = analogRead(IR_READ_PIN);
  setMuxOut(MUX_LED_B);  // Turn off IR Emitter
  delay(50);
  int shineValue = analogRead(IR_READ_PIN);
  setMuxOut(MUX_IR);
  // Serial.print(ambientValue);
  // Serial.print(" ");
  // Serial.print(shineValue);
  // Serial.print(" ");
  // Serial.println(shineValue - ambientValue);
  return -(shineValue - ambientValue);
}

// Code for stopping motor
void stopMotor() {
  leftMotor.stop();
  rightMotor.stop();
}

void setupIRSensor() {
  pinMode(IR_READ_PIN, INPUT);
}

float readUltraDistance() {
  return ultraSensor.distanceCm() - 4;
}

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
  } else if (col == CS_WHITE) {
    led.setColor(255, 255, 255);
    led.show();
    stopMotor();
    celebrate();
  } else if (col == CS_ORANGE) {
    led.setColor(255, 165, 0);
    led.show();
    uTurn();
  }
  led.setColor(0, 0, 0);
  led.show();
}

void setup() {
  Serial.begin(9600);  // Setup serial monitor for debugging purpose
  pinMode(A7, INPUT);  // Setup A7 as input for the push button
  led.setpin(13);
  setupMultiplexer();
  setupIRSensor();
  led.setColor(255, 0, 0);
  led.show();
  buzzer.setpin(BUZZER_PIN);
  buzzer.tone(130, 500);
  // colourSensor.calibrateColourSensor();
}

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
      colourSensor.detectColour();
      int col = colourSensor.identifyColours();
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
        // stopMotor();
        Serial.println(irReading);
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
