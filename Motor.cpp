#include "Encoder.h"
 
Motor::Motor(PinName pinf1, PinName pinr1,PinName pinf2, PinName pinr2)  {
//    _pin = 1;
}
 
void Motor::forward()
{
   pinf1=1;
   pinr1=0;
   pinf2=0;
   pinr2=1;
}

void Motor::backward()
{
   pinf1=0;
   pinr1=1;
   pinf2=1;
   pinr2=0;
}

void Motor::brake()
{
   pinf1=0;
   pinr1=0;
   pinf2=0;
   pinr2=0;
}

void Motor::right()
{
   pinf1=1;
   pinr1=0;
   pinf2=0;
   pinr2=0;
}
void Motor::left()
{
   pinf1=0;
   pinr1=0;
   pinf2=1;
   pinr2=0;
}
