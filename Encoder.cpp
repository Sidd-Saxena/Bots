#include "Encoder.h"
 
Encoder::Encoder(PinName eouta, PinName eoutb) : _eouta(eouta),_eoutb(eoutb){
//    _eouta = 0;
//    _eoutb = 0;
}
 
void Encoder::forward(int lidarReading) {
    encoderCount = (int)((float)lidarReading*0.3789+0.5);
    printf("Count = %d\n\r",encoderCount);
    startEncoding();
    return;
}

void Encoder::startEncoding(){
    Serial pc(USBTX, USBRX); //Initalise PC serial comms
    int currenta = 0, currentb = 0;
    while(encoderCount>0)
    {
           currenta = _eouta;
           currentb = _eoutb;
           pc.printf("%d , %d \n\r",currenta,currentb);
            if(currenta == 1 && currentb == 1)
            {
                encoderCount--;
                pc.printf("Count in encoding = %d\n\r",encoderCount);
                fflush(stdout);
            }
            pc.printf("Count in encoding = %d\n\r",encoderCount);
    }
    pc.printf("Stopping bot");
    return;
}

int Encoder::read(){
    return(_eouta && _eoutb);   
}


