/*
    Ejemplo de control de velocidad
    Oscar Gonzalez - Noviembre 2024
    BricoGeek.com

    https://tienda.bricogeek.com
*/
#include <BricoGeek_DirectDriveServo.h>

BricoGeek_DirectDriveServo motor(10, 11); // RX en pin 10, TX en pin 11

void setup() {
    motor.begin();
    motor.setMode(0x02); // Modo de control de velocidad
    motor.setSpeed(500); // Establecer velocidad a 50 rpm
}

void loop() {
    // Código principal
}
