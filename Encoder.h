#ifndef MBED_ENCODER_H
#define MBED_ENCODER_H
 
#include "mbed.h"

class Encoder {
public:
    Encoder(PinName pina, PinName pinb);
    void forward(int);
    void startEncoding();
    void stopBot();
    float read();
private:  
    DigitalIn _pina;
    DigitalIn _pinb
    
    int encoderCount;
};
 
#endif
