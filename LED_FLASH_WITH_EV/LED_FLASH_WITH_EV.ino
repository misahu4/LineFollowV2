#include <EVShieldAGS.h>

EVShield          evshield(0x34,0x36);

void
setup()
{
    evshield.init( SH_HardwareI2C );
}

void
loop()
{
    evshield.bank_a.ledSetRGB(0,100,100);
    delay (500);
    evshield.bank_b.ledSetRGB(0,10,100);
    delay (500);
    evshield.bank_a.ledSetRGB(100,0,0);
    delay (500);
    evshield.bank_b.ledSetRGB(0,70,50);
    delay (500);
}

