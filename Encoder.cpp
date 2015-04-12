#include "Encoder.h"
 
Encoder::Encoder(PinName pin) : _pin(pin) {
//    _pin = 1;
}
 
void Encoder::forward(int lidarReading, float botSpeed) {
    m3pi m3pi;
    encoderCount = (int)((float)lidarReading*0.43);
    m3pi.forward(botSpeed);
    printf("Count = %d\n\r",encoderCount);
    startEncoding();
    return;
}

void Encoder::startEncoding(){
    Serial pc(USBTX, USBRX); //Initalise PC serial comms
    m3pi m3pi;
    float current = 0, previous = 0;
    while(encoderCount>0){
           current = _pin.read();
            if((current - previous > 0.30) || (current - previous < -0.30))
                encoderCount--;
                printf("Count in encoding = %d\n\r",encoderCount);
                fflush(stdout);
            previous = current;

    }
    m3pi.stop();
    pc.printf("Stopping bot");
    return;
}


float Encoder::read(){
    return(_pin.read());   
}


