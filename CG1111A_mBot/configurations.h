#pragma once

// Speed configurations
#define MOVE_SLOW 70
#define MOVE_MID 150
#define MOVE_FAST 255
#define LEFT_FAST 255
#define RIGHT_FAST 220

// Movement delay configurations
#define MOVE_TURN_90_DELAY 320
#define MOVE_TURN_180_DELAY 1000
#define MOVE_ONE_WALL_DELAY 750
#define MOVE_REVERSE_DELAY 400

// Line sensor states
#define LINE_BLACK_BLACK (0x00)
#define LINE_BLACK_WHITE (0x01)
#define LINE_WHITE_BLACK (0x02)
#define LINE_WHITE_WHITE (0x03)

// IR sensor configurations
#define IR_READ_PIN A3
#define IR_TURN_DELTA 1.2  // too near when greater than this value
#define IR_TOO_NEAR 200

// Multiplexer configurations
#define MUX_INA A0
#define MUX_INB A1
#define MUX_IR 0
#define MUX_LED_R 1
#define MUX_LED_G 2
#define MUX_LED_B 3

// Multiplexer setup configurations
#define MUX_OUTPUT_COUNT 4
#define MUX_SETUP_DELAY 500

// Colour sensor configurations
#define CS_LDR_PIN A2
#define CS_SAMPLES 10
#define CS_DELAY_BEFORE_READING 250
#define CS_DELAY_BEFORE_AMBIENT 50
#define CS_THRESHOLD 350

// Colour definitions
#define CS_BLUE 0
#define CS_GREEN 1
#define CS_PINK 2
#define CS_RED 3
#define CS_WHITE 4
#define CS_ORANGE 5

// Ultrasonic sensor configurations
#define ULTRA_TIMEOUT 30000
#define SPEED_OF_SOUND 0.0343  // centimetre/microsecond

// Note frequencies for "Moonlight Sonata"
#define BUZZER_NOTE_C3 130
#define BUZZER_NOTE_G3 196
#define BUZZER_NOTE_EB4 311
#define BUZZER_NOTE_G4 392
#define BUZZER_NOTE_C4 261
#define BUZZER_NOTE_F4 349
#define BUZZER_NOTE_A4 440

// Delay times for rhythm
#define BUZZER_LONG_DELAY 500
#define BUZZER_SHORT_DELAY 250
#define BUZZER_PAUSE 100

// Sensor delays
#define COLOUR_CALIBRATION_DELAY 3000
#define IR_SENSOR_DELAY 1
#define LINE_SENSOR_DELAY 200

// Pin configurations
#define BUZZER_PIN 8
#define LED_PIN 13
#define PUSH_BUTTON_PIN A7

// Push button configurations
#define PUSH_BUTTON_THRESHOLD 100

// Ultrasonic sensor configurations
#define ULTRA_SENSOR_OFFSET 4
#define ULTRA_DISTANCE_THRESHOLD_LOW 6
#define ULTRA_DISTANCE_THRESHOLD_HIGH 8

// Loop delays
#define BUTTON_LOOP_DELAY 500
#define CELEBRATE_LOOP_DELAY 1000
