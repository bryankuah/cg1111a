#include "MeMCore.h"
#include "configurations.h"

MeUltrasonicSensor ultraSensor(PORT_1);  // assigning ultraSensor to RJ25 port 1
MeLineFollower lineFinder(PORT_2);       // assigning lineFinder to RJ25 port 2
MeDCMotor leftMotor(M1);                 // assigning leftMotor to port M1
MeDCMotor rightMotor(M2);                // assigning RightMotor to port M2
int status = false;                      // global status; 0 = do nothing, 1 = mBot runs
float ultraDistance;

String colours[] = { "blue", "green", "pink", "red", "white", "orange" };
long rgb_values[3] = { 0, 0, 0 };

long recorded_rgb_values[6][3] = { { 5070, 5800, 6200 }, { 5300, 5770, 5130 }, { 5200, 5100, 5200 },
                                   { 5750, 3840, 3950 }, { 4800, 5200, 5300 }, { 5400, 4283, 3600 } };

int num_colours = sizeof(recorded_rgb_values) / sizeof(recorded_rgb_values[0]);
// static_assert(num_colours == 6, "Number of colours must be 6");

int led_pins[3] = { CS_LED_R, CS_LED_G, CS_LED_B };

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
  leftMotor.run(0);     // Left wheel stops
  rightMotor.run(150);  // Right wheel goes forward
}
// Code for nudging slightly to the right for some short interval
void nudgeRight() {
  leftMotor.run(-150);  // Left wheel go forward
  rightMotor.run(0);    // Right wheel stops
}
// Code for turning on the IR emitter only
void shineIR() {}

// Code for stopping motor
void stopMotor() {
  leftMotor.stop();
  rightMotor.stop();
}


// Colour sensor codes

int readLDR() {
  return analogRead(CS_LDR_PIN);
}
void setupColourSensor() {
  pinMode(CS_INA, OUTPUT);
  pinMode(CS_INB, OUTPUT);
  pinMode(CS_LDR_PIN, INPUT);
}

void readColour(long *colourValue) {
  *colourValue = 0;

  for (int i = CS_SAMPLES; i > 0; i--) {
    // need to check if it will overflow (tho hopefully not)
    *colourValue += (analogRead(CS_LDR_PIN));
  }
}

// for HD74LS139 (two to four multiplexer)
void enablePin(int pin_number) {
  if (pin_number == 0) {
    digitalWrite(CS_INA, LOW);
    digitalWrite(CS_INB, LOW);
  } else if (pin_number == 1) {
    digitalWrite(CS_INA, HIGH);
    digitalWrite(CS_INB, LOW);
  } else if (pin_number == 2) {
    digitalWrite(CS_INA, LOW);
    digitalWrite(CS_INB, HIGH);
  } else if (pin_number == 3) {
    digitalWrite(CS_INA, HIGH);
    digitalWrite(CS_INB, HIGH);
  }
}

int detectColour(int led_pins[3], long rgb_values[3]) {
  long ambient_light = 0;
  readColour(&ambient_light);
  long reading = 0;
  for (int i = 0; i < 3; i++) {
    rgb_values[i] = 0;
  }
  for (int i = 0; i < 3; i++) {
    enablePin(led_pins[i]);
    delay(CS_DELAY_BEFORE_READING);
    readColour(&reading);
    reading -= ambient_light;
    rgb_values[i] += reading;
  }
  enablePin(CS_LED_OFF);
  delay(100);
}

int identifyColours(long rgb_vals[3]) {
  int colour_idx; int j;
  for (colour_idx = 0; colour_idx < 6; colour_idx++) {
    for (j = 0; j < 3; j++) {
      Serial.print(abs(rgb_vals[j] - recorded_rgb_values[colour_idx][j]));
      Serial.print(" ");
      if (abs(rgb_vals[j] - recorded_rgb_values[colour_idx][j]) > CS_THRESHOLD) {
        Serial.println();
        break;
      }
    }
    if (j==3){
      return colour_idx;
    }
  }  return -1;
}

// will not be ran in the final code
void calibrateColourSensor() {
  long rgb_values[3];

  for (int i = 0; i < 6; i++) {
    Serial.println("Place the sensor on " + colours[i] + " colour");
    delay(5000);
    detectColour(led_pins, rgb_values);
    
    Serial.print("RGB values: ");
    for (int j = 0; j < 3; j++) {
      Serial.print(rgb_values[j]);
      Serial.print(" ");
    }
    Serial.println();
  }
}

float readUltraDistance() {
  return ultraSensor.distanceCm() - 4;
}


void setup() {

  pinMode(A7, INPUT);   // Setup A7 as input for the push button
  Serial.begin(9600);   // Setup serial monitor for debugging purpose
  setupColourSensor();  // Setup colour sensor
  while(true){
    detectColour(led_pins, rgb_values);
    int col = identifyColours(rgb_values);
    Serial.print("Colours: ");
    if(col != -1){
    Serial.print(colours[col]);}

    Serial.print(" RGB: ");
    for(int i =0;i<3;i++){
      Serial.print(rgb_values[i]);
      Serial.print(" ");
    }
      Serial.println();
  }
  // calibrateColourSensor();
  // while (true){
  // for (int i=0; i<4; i++){
  //   enablePin(i);
  //   delay(1000);
  // }
  // }
}

int colour_index = 0;
void loop() {
  if (analogRead(A7) < 100) {  // If push button is pushed, the value will be very low
    status = !status;          // Toggle status
    delay(500);                // Delay 500ms so that a button push won't be counted multiple times.
    readColour(rgb_values);
    colour_index = identifyColours(rgb_values);
    if (colour_index != -1)
    {
      Serial.println("Colour detected: " + String(colours[colour_index]));
    } else {
      Serial.println("Colour not detected");
    }
  }
  if (status) {                                  // run mBot only if status is 1
    int sensorState = lineFinder.readSensors();  // read the line sensor's state
    Serial.println(sensorState);
    if (sensorState == L_B_R_B) {  // situation 4
      stopMotor();
      // will be stored in the array rgb_values
      detectColour(led_pins, rgb_values);
      // we will just print them out for debugging
      for (int i = 0; i < 3; i++) {
        Serial.print(rgb_values[i]);
        Serial.print("  ");
      }
      Serial.println();
      // decide next move
    } else {
      ultraDistance = readUltraDistance();
      if (ultraDistance > 10 || (sensorState == L_W_R_W && ultraDistance < 7 && ultraDistance > 5)) {  // situation 1
        moveForward();
      } else if (sensorState == L_B_R_W || ultraDistance >= 7) {  // situation 2
        nudgeLeft();
      } else if (sensorState == L_W_R_B || ultraDistance <= 5) {  // situation 3
        nudgeRight();
      }
    }
  }
}
