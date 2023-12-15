#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "../data_structures.h"

class Radio {
    public:

    DataJoystick data_joystick;

    const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

    double dataReceived[4] = {9999999.0, 9999999.0, 9999999.0, 9999999.0}; // this must match dataToSend in the TX
    double ackData[4] = {9999999.0, 9999999.0, 9999999.0, 9999999.0}; // the two values to be sent to the master
    bool newData = false;

    void updateReplyData(DataBus data_buffer);
    void getData(DataBus data_buffer);
    void showData();

    void radio_setup();
    void radio_update(DataBus data_buffer);
};