#ifndef __SERIAL_GPIO_H__
#define __SERIAL_GPIO_H__

#define TX  0
#define RX  1

typedef byte unsigned char;

/**
  * SerialGPIO:
  * Arduino helper class for using free GPIO pins as UART.
  */
class SerialGPIO {
    unsigned int    baudrate;
    byte            pins[2];

public:
    /*
     * Constructor: SerialGPIO
     * Parameters:
     * tx: 8bit value for tx GPIO.
     * rx: 8bit value for rx GPIO.
     * baudRate: baurdate used for communication.
     */
    SerialGPIO(byte tx, byte rx, unsigned int baudrate);

    /*
     * Write a single byte.
     */
    int write(byte value);

    /*
     * Read a single byte.
     */
    int read(byte *value);
};

#endif