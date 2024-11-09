#pragma once

// Speed configurations
#define SLOW_SPEED 70
#define MID_SPEED 150
#define FAST_SPEED 200

// Delay configurations
#define TURN_90_DELAY 550
#define TURN_180_DELAY 1000
#define ONE_WALL_DELAY 850
#define SPEED_REVERSE_DELAY 400

// Line sensor states
#define L_B_R_B (0x00)  // left black, right black
#define L_B_R_W (0x01)  // left black, right white
#define L_W_R_B (0x02)  // left white, right black
#define L_W_R_W (0x03)  // left white, right white

// IR sensor configurations
#define IR_READ_COUNT 10
#define IR_READ_PIN A3
#define IR_TOO_NEAR 900  // too near when greater than this value

// Multiplexer configurations
#define MUX_INA A0
#define MUX_INB A1
#define MUX_IR 0
#define MUX_LED_R 1
#define MUX_LED_G 2
#define MUX_LED_B 3

// Colour sensor configurations
#define CS_LDR_PIN A2
#define CS_SAMPLES 50
#define CS_DELAY_BEFORE_READING 300
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

// Buzzer configurations
#define BUZZER_PIN 8

// Note frequencies (in Hz) for "Moonlight Sonata"
#define NOTE_C3 130   // C3 (bass)
#define NOTE_G3 196   // G3 (bass)
#define NOTE_EB4 311  // Eb4 (melody)
#define NOTE_G4 392   // G4 (melody)
#define NOTE_C4 261   // C4 (melody)
#define NOTE_F4 349   // F4 (melody)
#define NOTE_A4 440   // A4 (melody)

// Delay times for rhythm (in milliseconds)
#define LONG_DELAY 500  // Long note duration (half beat)
#define SHORT_DELAY 250 // Short note duration (quarter beat)
#define PAUSE 100       // Short pause between phrases
