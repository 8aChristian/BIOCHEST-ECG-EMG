#pragma once
#include <Arduino.h>

// =============================================================================
// BIOCHEST-ECG-EMG HARDWARE PINOUT DEFINITIONS
// MCU: ESP32-S3-MINI-1-N8
// =============================================================================

// SPI Interface (Isolated ADS1293 via ISO7741U)
#define PIN_SPI_SCLK    12  // U3 Pin 10 -> U2 Pin 14 -> U1 Pin 14
#define PIN_SPI_MOSI    11  // U3 Pin 9  -> U2 Pin 13 -> U1 Pin 15
#define PIN_SPI_MISO    13  // U3 Pin 11 -> U2 Pin 11 -> U1 Pin 16
#define PIN_SPI_CS      10  // U3 Pin 8  -> U2 Pin 12 -> U1 Pin 17

// I2C Interface (MAX17048 LiPo Fuel Gauge)
#define PIN_I2C_SDA     1   // U3 Pin 15 -> U11 Pin 1
#define PIN_I2C_SCL     2   // U3 Pin 16 -> U11 Pin 2
#define MAX17048_I2C_ADDR 0x36

// User Indicators
#define PIN_LED_STATUS  3   // U3 Pin 17 -> Green LED (D4) Active High
#define PIN_LED_ALERT   4   // U3 Pin 18 -> Red LED (D5) Active High

// System Controls
#define PIN_ESP_EN      0   // Reset Button (SW1) Active Low
#define PIN_ESP_IO0     0   // Boot Button (SW2) Active Low

// ADS1293 Register Map Constants
#define ADS1293_REG_REV_ID      0x40  // Revision / Chip ID Register
#define ADS1293_EXPECTED_ID     0x01  // Expected Chip ID response
