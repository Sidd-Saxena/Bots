#include "Encoder.h"


Encoder::Encoder(PinName pina,PinName pinb):_pina(pina),_pinb(pinb)
{
    
}
 
void Encoder::forward(int lidarReading) {
    //circumference of wheel  = 13.188cm
    //one encoder count = 2.638cm
    encoderCount = (int)((float)(lidarReading/2.638)+0.5);
    printf("Count = %d\n\r",encoderCount);
    startEncoding();
    return;
}

void Encoder::startEncoding(){
    Serial pc(USBTX, USBRX); //Initalise PC serial comms
    int currenta = 0, currentb = 0;
    while(encoderCount>0){
           currenta = _pina.read();
           currentb = _pinb.read();
            if(currenta==1 && currentb==1)
            {
                 encoderCount--;
                 printf("Count in encoding = %d\n\r",encoderCount);
            } 
    }
    pc.printf("Stopping bot");
    return;
}


float Encoder::read(){
    return(_pina.read() , _pinb.read());   
 }
