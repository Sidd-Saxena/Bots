
#ifndef MBED_BOTMOTOR_H
#define MBED_BOTMOTOR_H

#include "mbed.h"
#include "Motor.h"

class BotMotor {
public:
    BotMotor(PinName lmouta, PinName lmoutb, PinName lmoute, PinName rmouta, PinName rmoutb,PinName rmoute);
    void moveForward(float BotSpeed);
    void moveBackward(float BotSpeed);
    void turnRight(float BotSpeed);
    void turnLeft(float BotSpeed);
    void stopBot();
private:
    Motor left;
    Motor right;
};

#endif
