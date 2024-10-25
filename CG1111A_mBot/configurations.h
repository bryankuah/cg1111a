#pragma once

#define TURN_90_DELAY 0
#define TURN_180_DELAY 0
#define ONE_WALL_DELAY 0

#define L_B_R_B (0x00) // left black, right black
#define L_B_R_W (0x01) // left black, right white
#define L_W_R_B (0x02) // left white, right black
#define L_W_R_W (0x03) // left white, right white

// COLOUR SENSOR
#define CS_INA A0
#define CS_INB A1

#define CS_LED_OFF 0
#define CS_LED_R 1
#define CS_LED_G 2
#define CS_LED_B 3
#define CS_LDR_PIN A2

#define CS_SAMPLES 100
#define CS_DELAY_BEFORE_READING 1000