#ifndef __SERIAL_GPIO_H__
#define __SERIAL_GPIO_H__

#define TX  0
#define RX  1

#define EIO 5

typedef unsigned char byte;

/**
  * SerialGPIO:
  * Arduino helper class for using free GPIO pins as UART.
  *
  * Limitations cannot read and write at the same time.
  */
class SerialGPIO {
    unsigned int    baudrate;
    byte            pins[2];
    byte            timer;

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