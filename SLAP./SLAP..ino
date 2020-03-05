/*******************************************************************************
 * Note: LoRaWAN per sub-band duty-cycle limitation is enforced (1% in
 * g1, 0.1% in g2), but not the TTN fair usage policy (which is probably
 * violated by this sketch when left running for longer)!
 
 * Do not forget to define the radio type correctly in
 * arduino-lmic/project_config/lmic_project_config.h or from your BOARDS.txt.

 * Note that ABP is used instead of OTAA, as our gateway does not support OTAA.
 * As an estimate, can stay active for about 4 hrs/day
 *******************************************************************************/
#include "Globals.h"
#include "IMU.h" 
#include "Functions.h"
#include <Arduino.h>

// These callbacks are only used in over-the-air activation, so they are
// left empty here (we cannot leave them out completely unless
// DISABLE_JOIN is set in arduino-lmic/project_config/lmic_project_config.h,
// otherwise the linker will complain).
void os_getArtEui (u1_t* buf) { }
void os_getDevEui (u1_t* buf) { }
void os_getDevKey (u1_t* buf) { }

static uint8_t parkingState[2];
static osjob_t sendjob;

// cycle limitations.
void onEvent (ev_t ev) {
    Serial.print(os_getTime());
    Serial.print(": ");
    switch(ev) {

        case EV_TXCOMPLETE:
            Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
            if (LMIC.txrxFlags & TXRX_ACK)
              Serial.println(F("Received ack"));
            if (LMIC.dataLen) {
              Serial.println(F("Received "));
              Serial.println(LMIC.dataLen);
              Serial.println(F(" bytes of payload"));
            }

            //can set interrupt here, set to a deep sleep for TX_INTERVAL, then the TX_INTERVAL below is shorter.
            // Schedule next transmission
            os_setTimedCallback(&sendjob, os_getTime()+sec2osticks(TX_INTERVAL), do_send);
            break;
    
        default:
            //Serial.print(F("Unknown event: "));
            //Serial.println((unsigned) ev);
            break;
    }
}

void do_send(osjob_t* j){ //THIS IS WHERE I SHALL WRITE CODE TO CHECK THE STATUS OF THE SENSORS, IN THE DO_SEND FUNCTION.
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & OP_TXRXPEND) {
        Serial.println(F("OP_TXRXPEND, not sending"));
    } else {
        // Prepare upstream data transmission at the next possible time.   
        Serial.println("Starting Read");    
        uint8_t pState = magnetState();
        parkingState[0] = lowByte(pState); 
        parkingState[1] = highByte(pState);
        
        LMIC_setTxData2(1, parkingState, sizeof(parkingState)-1, 0);
        Serial.println(F("Packet queued"));
        Serial.println(parkingState[0]);
    }
    // Next TX is scheduled after TX_COMPLETE event.
}

void setup() {
    delay(5000);
    Serial.begin(115200);
    delay(100);
    Serial.println(F("Starting"));
    initIMU();

    // LMIC init
    os_init();
    // Reset the MAC state. Session and pending data transfers will be discarded.
    LMIC_reset();

    if(DOT_ID == 53){
        DEVADDR = 0x260213F1;
    }else if(DOT_ID == 54){
        DEVADDR = 0x2602121E;
    }else if(DOT_ID == 55){
        DEVADDR = 0x260214A7;
    }

    // Set static session parameters. Instead of dynamically establishing a session
    // by joining the network, precomputed session parameters are be provided.
    // On AVR, these values are stored in flash and only copied to RAM
    // once. Copy them to a temporary buffer here, LMIC_setSession will
    // copy them into a buffer of its own again.
    uint8_t appskey[sizeof(APPSKEY)];
    uint8_t nwkskey[sizeof(NWKSKEY)];
    memcpy_P(appskey, APPSKEY, sizeof(APPSKEY));
    memcpy_P(nwkskey, NWKSKEY, sizeof(NWKSKEY));
    LMIC_setSession (0x13, DEVADDR, nwkskey, appskey);

    // We'll disable all 72 channels used by TTN
    for (int c = 0; c < 72; c++){
      LMIC_disableChannel(c);
    }

    LMIC_enableChannel(CHANNEL);

    // Disable link check validation
    LMIC_setLinkCheckMode(0);

    // TTN uses SF9 for its RX2 window.
    LMIC.dn2Dr = DR_SF9; 

    LMIC_setDrTxpow(SPREAD_FACTOR,14);

    // Start job
    do_send(&sendjob);
}

void loop() {
    unsigned long now;
    now = millis();
    if ((now & 512) != 0) {
      digitalWrite(13, HIGH);
    }
    else {
      digitalWrite(13, LOW);
    }

    os_runloop_once();
}
