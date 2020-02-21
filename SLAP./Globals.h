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
#define DOT_ID 1 //ID of the dot, see TTN for each individual dot. DOT 2 and 3 not working???

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
static const u1_t PROGMEM NWKSKEY[16] = { 0x25, 0x30, 0x65, 0xE0, 0x8D, 0x62, 0x08, 0xDE, 0x99, 0xB4, 0x2D, 0x53, 0x13, 0x47, 0x17, 0x80 };

// LoRaWAN AppSKey, application session key, MSB
static const u1_t PROGMEM APPSKEY[16] = { 0xE8, 0x65, 0xED, 0x4F, 0xC0, 0x71, 0x8A, 0x04, 0x61, 0xCB, 0xE0, 0x30, 0x70, 0x81, 0x49, 0x63 };

//Device addr, unique to each device
u4_t DEVADDR;

#endif //GLOBALS_H
