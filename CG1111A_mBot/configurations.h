#pragma once

#define FAST_SPEED 255
#define TURN_90_DELAY 520
#define ONE_WALL_DELAY 750

#define L_B_R_B (0x00)  // left black, right black
#define L_B_R_W (0x01)  // left black, right white
#define L_W_R_B (0x02)  // left white, right black
#define L_W_R_W (0x03)  // left white, right white

// Multiplexer
#define MUX_INA A0
#define MUX_INB A1

#define MUX_IR 0
#define MUX_LED_R 1
#define MUX_LED_G 2
#define MUX_LED_B 3

// COLOUR SENSOR
#define CS_LDR_PIN A2

#define CS_SAMPLES 50
#define CS_DELAY_BEFORE_READING 250
#define CS_THRESHOLD 350

// String colours[6] = { "blue", "green", "pink", "red", "white", "orange" };
#define CS_BLUE 0
#define CS_GREEN 1
#define CS_PINK 2
#define CS_RED 3
#define CS_WHITE 4
#define CS_ORANGE 5

#define IR_READ_PIN A3
#define IR_TOO_NEAR 78  // too near when greater than this value

#define ULTRA_TIMEOUT 30000
#define SPEED_OF_SOUND 0.0343  // centimetre/microsecond

#define BUZZER_PIN 8

// Define the note frequencies (in Hz) for the first few bars of "Moonlight Sonata"
#define note_C3 130   // C3 (bass)
#define note_G3 196   // G3 (bass)
#define note_Eb4 311  // Eb4 (melody)
#define note_G4 392   // G4 (melody)
#define note_C4 261   // C4 (melody)
#define note_F4 349   // F4 (melody)
#define note_A4 440   // A4 (melody)

// Define the delay times for rhythm (in milliseconds)
#define longDelay 500  // Long note duration (half beat)
#define shortDelay 250 // Short note duration (quarter beat)
#define pause 100      // Short pause between phrases
