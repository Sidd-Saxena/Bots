/* ESE 519 Project : TURF
Author : Siddharth Saxena, University of Pennsylvania*/

#ifndef ENCODER_H
#define ENCODER_H
 

#include "mbed.h"

class Encoder {
public:
    Encoder(PinName pina, PinName pinb);
    void forward(int);
    void startEncoding();
    float read();
private:  
    DigitalIn _pina;
    DigitalIn _pinb; 
    int encoderCount;
};
 
#endif
