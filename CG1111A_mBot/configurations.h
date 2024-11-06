#pragma once

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

#define CS_SAMPLES 10
#define CS_DELAY_BEFORE_READING 1000
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