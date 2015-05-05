/* ESE 519 : Final Project TURF
Library for the brain of the bot, calls all the remaining functions and libraries
Author :Siddharth Saxena, University of Pennsylvania*/


#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include "Encoder.h"
#include "Servo.h"
#include "imu.h"
#include "LidarLite.h"
#include "XBee.h"
#include "BotMotor.h"
#include "Motor.h"
#include "rtos.h"
#include "string"
// Data sample object for holding IR/servo scans
struct DataSample
{
    float x, y, th;
    vector<pair<float, float> > data;
};

class Robot
{
public:
    Robot(void);
    void calibrate(bool, bool);
    float x(void);
    float y(void);
    float th(void);
    void setX(float);
    void setY(float);
    void setTh(float);
    void setServo(float);
    float range(void);
    bool encoderLeft(void);
    bool encoderRight(void);
    void forward(int,float);
    void brake();
    void backward(int, float);
    void right(float);
    void left(float);
    float turn(float, float);
    string servo_scan();
    DataSample scan(void);
    void sendData(void);
    void TurnAround();
    void setLEDs(bool, bool, bool, bool);
    // Xbee for communication
    XBee xbee;
    float _x, _y, _th, _range;
    
private:
    void calibrationAlert(void);
    
    Encoder _encoder_left;
    Servo _servo;
    IMU _imu;
    LidarLite _lidar;
    BotMotor _botmotor; 
    DigitalOut _led1, _led2, _led3, _led4;
};

#endif
