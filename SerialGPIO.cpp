#include <Arduino.h>
#include "SerialGPIO.h"

SerialGPIO::SerialGPIO(byte tx, byte rx, unsigned int baudrate)
{
    pins[TX] = tx;
    pins[RX] = rx;
    this->baudrate = baudrate;

    timer = baudrate / 1000000;
    pinMode(pins[tx], OUTPUT);
    pinMode(pins[rx], INPUT);

    /* Pull TX line HIGH*/
    digitalWrite(pins[tx], HIGH);
}

int SerialGPIO::write(byte value)
{
    byte parity = 1;
    int i;

    /* Pull TX low. */
    digitalWrite(pins[TX], LOW);
    delayMicroseconds(timer);

    /* Send byte. */
    for (i = 0; i < 8; i++) {
        digitalWrite(pins[TX], (value & 1) ? HIGH : LOW);
        parity = parity ^ (value & 1);
        value >>= 1;

        delayMicroseconds(timer);
    }

    /* Send Parity Bit. */
    digitalWrite(pins[TX], parity ? HIGH : LOW);
    delayMicroseconds(timer);

    /* Send Stop Signal. */
    digitalWrite(pins[TX], HIGH);
    delayMicroseconds(timer * 2);
}

int SerialGPIO::read(byte *value)
{
    byte bitVal, parity = 1;
    int i;
    int ret = 0;

    *value = 0;

    /* Fall through if RX line is low. */
    while (true) {
        bool recieving = digitalRead(pins[RX]);

        delayMicroseconds(timer);
        if (recieving)
            break;
    }

    /* Read byte. */
    for (i = 0; i < 8; i++) {
        bitVal = digitalRead(pins[RX]) ? 1 : 0;
        *value |= bitVal << i;
        parity ^= bitVal;

        delayMicroseconds(timer);
    }

    /* Validate parity bit. */
    if (parity ^ digitalRead(pins[RX]))
        ret = -EIO;

    delayMicroseconds(timer);

    /* Check for stop bit. */
    for (i = 0; i < 2; i++) {
        if (!digitalRead(pins[RX]))
            ret = -EIO;
        delayMicroseconds(timer);
    }

    if (ret)
        *value = 0;

    return ret;
}