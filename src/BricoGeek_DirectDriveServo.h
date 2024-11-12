// DirectDriveServo.h

#ifndef BricoGeek_DirectDriveServo_h
#define BricoGeek_DirectDriveServo_h

#include "Arduino.h"
#include <SoftwareSerial.h>

class BricoGeek_DirectDriveServo {
public:
    BricoGeek_DirectDriveServo(uint8_t rxPin, uint8_t txPin, uint8_t id = 0x01);
    void begin(long baudRate = 115200);
    void setMode(uint8_t mode);
    void setSpeed(int16_t speed);
    void setPosition(uint16_t position);
    void brake();
    void setID(uint8_t newID);
    uint8_t getID();
    uint8_t getMode();
    int16_t getSpeed();
    uint16_t getPosition();
    uint8_t getTemperature();
    uint8_t getError();

private:
    uint8_t _id;
    SoftwareSerial _serial;
    void sendCommand(uint8_t command, int16_t data = 0);
    uint8_t calculateChecksum(uint8_t* packet, uint8_t length);
    void sendPacket(uint8_t* packet, uint8_t length);
    void readResponse(uint8_t* buffer, uint8_t length);
};

#endif
