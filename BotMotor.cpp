/* ESE 519 Project : TURF
Author : Siddharth Saxena, University of Pennsylvania
This function is controlling the motors using digital out pins to H- Bridge and Pwm to control the speed of the bot
It moved the bot forward, backward, left right and turn around */
#include "BotMotor.h"

BotMotor::BotMotor(PinName lmouta, PinName lmoutb, PinName lmoute, PinName rmouta, PinName rmoutb,PinName rmoute):left(lmouta, lmoutb, lmoute),right(rmouta, rmoutb, rmoute){
}

void BotMotor::moveForward(float BotSpeed = 0.1) {
    left.forward(BotSpeed);
    right.forward(BotSpeed);
    return;
}

void BotMotor::moveBackward(float BotSpeed = 0.1) {
    left.backward(BotSpeed);
    right.backward(BotSpeed);
    return;
}

void BotMotor::turnRight(float BotSpeed = 0.1) {
    left.forward(BotSpeed);
    right.backward(BotSpeed);
    return;
}

void BotMotor::turnLeft(float BotSpeed = 0.1) {
    right.forward(BotSpeed);
    left.backward(BotSpeed);
    return;
}

void BotMotor::stopBot(){
    left.stop();
    right.stop();
    return;
}
