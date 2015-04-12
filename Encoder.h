#ifndef MBED_ENCODER_H
#define MBED_ENCODER_H
 
#include "mbed.h"
#include "m3pi.h"

class Encoder {
public:
    Encoder(PinName pin);
    void forward(int,float);
    void startEncoding();
    void stopBot();
    float read();
private:  
    AnalogIn _pin;
    int encoderCount;
};
 
#endif
