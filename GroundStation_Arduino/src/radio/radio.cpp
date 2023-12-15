#include "radio.h"

#define CE_PIN  3
#define CSN_PIN 5

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

void Radio::send() 
{
    bool rslt;
    rslt = radio.write( &dataToSend, sizeof(dataToSend) );

    Serial.print("Data Sent ");
    Serial.print(dataToSend[0]);
    Serial.print(";");
    Serial.print(dataToSend[1]);
    Serial.print(";");
    Serial.print(dataToSend[2]);
    Serial.print(";");
    Serial.print(dataToSend[3]);
    Serial.println("");
    
    if (rslt) {
        if ( radio.isAckPayloadAvailable() ) {
            radio.read(&ackData, sizeof(ackData));
            newData = true;
        }
        else {
            Serial.println("  Acknowledge but no data ");
        }
    }
    else {
        Serial.println("  Tx failed");
    }

    prevMillis = millis();
 }

void Radio::showData() {
    if (newData == true) {
        Serial.print("Acknowledge data ");
        Serial.print(ackData[0]);
        Serial.print(";");
        Serial.print(ackData[1]);
        Serial.print(";");
        Serial.print(ackData[2]);
        Serial.print(";");
        Serial.print(ackData[3]);
        Serial.println("");
        newData = false;
    }
}

void Radio::radio_setup()
{
    radio.begin();

    radio.setDataRate( RF24_2MBPS  );
    radio.setPALevel( RF24_PA_MIN );
    radio.setChannel( 125 );

    radio.enableAckPayload();

    radio.setRetries(5,5); // delay, count
    
    // 5 gives a 1500 µsec delay which is needed for a 32 byte ackPayload
    radio.openWritingPipe(slaveAddress);
}

void Radio::radio_update()
{
    currentMillis = millis();
    if (currentMillis - prevMillis >= txIntervalMillis) {
        send();
    }
    showData();
}