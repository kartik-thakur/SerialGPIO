#include <SerialGPIO.h>

SerialGPIO serialGPIO(9, 10, 9600);

void setup()
{
    unsigned char val;

    Serial.begin(9600);

    serialGPIO.write(3);
    serialGPIO.read(&val);
}

void loop()
{
}