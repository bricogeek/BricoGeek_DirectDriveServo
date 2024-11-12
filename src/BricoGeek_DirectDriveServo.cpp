// BricoGeek_DirectDriveServo.cpp

#include "BricoGeek_DirectDriveServo.h"

BricoGeek_DirectDriveServo::BricoGeek_DirectDriveServo(uint8_t rxPin, uint8_t txPin, uint8_t id)
    : _serial(rxPin, txPin), _id(id) {}

void BricoGeek_DirectDriveServo::begin(long baudRate) {
    _serial.begin(baudRate);
}

void BricoGeek_DirectDriveServo::setMode(uint8_t mode) {
    sendCommand(0xA0, mode);
}

void BricoGeek_DirectDriveServo::setSpeed(int16_t speed) {
    sendCommand(0x64, speed);
}

void BricoGeek_DirectDriveServo::setPosition(uint16_t position) {
    sendCommand(0x64, position);
}

void BricoGeek_DirectDriveServo::brake() {
    sendCommand(0x64, 0xFF00);
}

void BricoGeek_DirectDriveServo::setID(uint8_t newID) {
    for (int i = 0; i < 5; i++) {
        sendCommand(0x55, newID);
    }
    _id = newID;
}

uint8_t BricoGeek_DirectDriveServo::getID() {
    sendCommand(0xC8);
    uint8_t response[10];
    readResponse(response, 10);
    return response[2];
}

uint8_t BricoGeek_DirectDriveServo::getMode() {
    sendCommand(0x75);
    uint8_t response[10];
    readResponse(response, 10);
    return response[2];
}

int16_t BricoGeek_DirectDriveServo::getSpeed() {
    sendCommand(0xA2);
    uint8_t response[10];
    readResponse(response, 10);
    return (response[2] << 8) | response[3];
}

uint16_t BricoGeek_DirectDriveServo::getPosition() {
    sendCommand(0xA1);
    uint8_t response[10];
    readResponse(response, 10);
    return (response[2] << 8) | response[3];
}

uint8_t BricoGeek_DirectDriveServo::getTemperature() {
    sendCommand(0xA3);
    uint8_t response[10];
    readResponse(response, 10);
    return response[2];
}

uint8_t BricoGeek_DirectDriveServo::getError() {
    sendCommand(0xA4);
    uint8_t response[10];
    readResponse(response, 10);
    return response[2];
}

void BricoGeek_DirectDriveServo::sendCommand(uint8_t command, int16_t data) {
    uint8_t packet[10] = {0x01, command, (uint8_t)(data >> 8), (uint8_t)data, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    packet[9] = calculateChecksum(packet, 9);
    sendPacket(packet, 10);
}

uint8_t BricoGeek_DirectDriveServo::calculateChecksum(uint8_t* packet, uint8_t length) {
    uint16_t sum = 0;
    for (uint8_t i = 0; i < length; i++) {
        sum += packet[i];
    }
    return (uint8_t)(sum & 0xFF);
}

void BricoGeek_DirectDriveServo::sendPacket(uint8_t* packet, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        _serial.write(packet[i]);
    }
}

void BricoGeek_DirectDriveServo::readResponse(uint8_t* buffer, uint8_t length) {
    uint8_t index = 0;
    unsigned long startTime = millis();
    while (index < length && (millis() - startTime) < 1000) {
        if (_serial.available()) {
            buffer[index++] = _serial.read();
        }
    }
}
