#include "Wheels_519.h"
 

Wheels::Wheels(PinName pinf1, PinName pinr1,PinName pinf2, PinName pinr2) :_pinf1(pinf1),_pinr1(pinr1),_pinf2(pinf2),_pinr2(pinr2){

}
 
void Wheels::forward()
{
   _pinf1=1;
   _pinr1=0;
   _pinf2=1;
   _pinr2=0;
}

void Wheels::backward()
{
   _pinf1=0;
   _pinr1=1;
   _pinf2=0;
   _pinr2=1;
}

void Wheels::brake()
{
   _pinf1=0;
   _pinr1=0;
   _pinf2=0;
   _pinr2=0;
}

void Wheels::right()
{
   _pinf1=0;
   _pinr1=1;
   _pinf2=1;
   _pinr2=0;
}
void Wheels::left()
{
   _pinf1=1;
   _pinr1=0;
   _pinf2=0;
   _pinr2=1;
}
