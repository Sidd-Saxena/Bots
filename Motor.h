#ifndef MOTOR_H
#define MOTOR_H
 
#include "mbed.h"


class Motor {
public:
    Motor::Motor(PinName pinf1, PinName pinr1,PinName pinf2, PinName pinr2)
    void forward();
    void backward();
    void right();
    void left();
    void brake();

private:  
    DigitalOut _pinf1;
    DigitalOut _pinr1;
    DigitalOut _pinf2;
    DigitalOut _pinr2;
};
 
#endif
