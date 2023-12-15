#include <Arduino.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "../data_structures.h"

class Radio {
public:
    const byte slaveAddress[5] = {'R','x','A','A','A'};

    char txNum = '0';
    double dataToSend[4] = {9999999.0, 9999999.0, 9999999.0, 9999999.0};
    double ackData[4] = {9999999.0, 9999999.0, 9999999.0, 9999999.0}; // to hold the two values coming from the slave
    bool newData = false;

    unsigned long currentMillis;
    unsigned long prevMillis;
    unsigned long txIntervalMillis = 500; // send once per second

    void updateMessage();
    void send();
    void showData();

    void radio_setup();
    void radio_update();
};