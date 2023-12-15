#include "radio.h"

RF24 radio_nrf24l01(9, 10);

void Radio::updateReplyData(DataBus data_buffer)
{   
    ackData[0] = data_buffer.pitch_value;
    ackData[1] = data_buffer.roll_value;

    ackData[2] = data_buffer.pressure_value;
    ackData[3] = data_buffer.altitude_value;

    radio_nrf24l01.writeAckPayload(1, &ackData, sizeof(ackData)); // load the payload for the next time
}

void Radio::getData(DataBus data_buffer) 
{
    if ( radio_nrf24l01.available() ) {
        radio_nrf24l01.read( &dataReceived, sizeof(dataReceived) );
        updateReplyData(data_buffer);
        newData = true;
    }
}

void Radio::showData() 
{
    if (newData == true) {
        
        data_joystick.axis_1_value = dataReceived[0];
        data_joystick.axis_2_value = dataReceived[1];
        data_joystick.axis_3_value = dataReceived[2];
        data_joystick.axis_4_value = dataReceived[3];

        Serial.print("Data received ");
        Serial.print(dataReceived[0]);
        Serial.print(", ");
        Serial.print(dataReceived[1]);
        Serial.print(", ");
        Serial.print(dataReceived[2]);
        Serial.print(", ");
        Serial.print(dataReceived[3]);
        Serial.println("");

        Serial.print("ackPayload sent ");
        Serial.print(ackData[0]);
        Serial.print(", ");
        Serial.print(ackData[1]);
        Serial.print(", ");
        Serial.print(ackData[2]);
        Serial.print(", ");
        Serial.print(ackData[3]);
        Serial.println("");
        newData = false;
    }
}

void Radio::radio_setup()
{
    radio_nrf24l01.begin();
    
    radio_nrf24l01.setDataRate( RF24_2MBPS );
    radio_nrf24l01.setPALevel( RF24_PA_MIN );
    radio_nrf24l01.setChannel( 125 );

    radio_nrf24l01.openReadingPipe(1, thisSlaveAddress);

    radio_nrf24l01.enableAckPayload();
    
    radio_nrf24l01.startListening();

    radio_nrf24l01.writeAckPayload(1, &ackData, sizeof(ackData)); // pre-load data
}

void Radio::radio_update(DataBus data_buffer)
{
    getData(data_buffer);
    showData();
}