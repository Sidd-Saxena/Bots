#include "Encoder.h"
#include "Motor.h"

Encoder::Encoder(PinName pina,PinName pinb){
//    _pin = 1;
}
 

void Encoder::forward(int lidarReading) {
    //circumference of wheel  = 13.188cm
    //one encoder count = 2.638cm
    encoderCount = (int)((float)lidarReading/2.638);
    Motor.forward();
    printf("Count = %d\n\r",encoderCount);
    startEncoding();
    return;
}

void Encoder::startEncoding(){
    Serial pc(USBTX, USBRX); //Initalise PC serial comms
    int currenta = 0, currentb = 0 ,previous = 0;
    while(encoderCount>0){
           currenta = _pina.read();
           currenta = _pinb.read();
            if(a==1 && b==1)
            {
                 encoderCount--;
                 printf("Count in encoding = %d\n\r",encoderCount);
            } 
    }
    Motor.brake();
    pc.printf("Stopping bot");
    return;
}


float Encoder::read(){
    return(_pina.read() , _pinb.read());   
}
