#ifndef GLOBALS_H
#define GLOBALS_H

#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <Arduino.h>

/*CONSTANTS FOR MAIN USE*/
#define IR_SENSOR A1
#define TX_INTERVAL 20
#define LED_PIN //probably wont use
#define SPREAD_FACTOR DR_SF9
#define CHANNEL 63 //using channel 63
#define DOT_ID 53 //54,55

static int prevParkState;

//#define TEST_ESP32 //Only use when i wanna test the ESP, else comment

/***********************************************************
 * Defining the board constants, set to 0 when not in use. *
 ***********************************************************/
 
// Pin mapping for the feather, our main microcontroller
const lmic_pinmap lmic_pins = {
    .nss = 8,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 4,
    .dio = {3, 6, LMIC_UNUSED_PIN},
    .rxtx_rx_active = 0,
    .rssi_cal = 8,              // LBT cal for the Adafruit Feather M0 LoRa, in dB
    .spi_freq = 8000000,
    
};

/*******************
 * OTHER CONSTANTS *
 *******************/

// LoRaWAN NwkSKey, network session key, MSB
static const u1_t PROGMEM NWKSKEY[16] = { 0x25, 0x03, 0x00, 0x65, 0x0E, 0x00, 0x8D, 0x06, 0x20, 0x08, 0x0D, 0xE0, 0x99, 0x0B, 0x40, 0x2D };

// LoRaWAN AppSKey, application session key, MSB
static const u1_t PROGMEM APPSKEY[16] = { 0xE8, 0x06, 0x50, 0xED, 0x04, 0xF0, 0xC0, 0x07, 0x10, 0x8A, 0x00, 0x40, 0x61, 0x0C, 0xB0, 0xE0 };

//Device addr, unique to each device
u4_t DEVADDR;

#endif //GLOBALS_H
