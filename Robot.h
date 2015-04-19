#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include "Encoder.h"
#include "Servo.h"
#include "imu.h"
#include "LidarLite.h"
#include "XBee.h"

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
    float forward(int);
    float backward(int, float);
    void right(float);
    void left(float);
    float turn(float, float);
    DataSample scan(void);
    void sendData(void);
    void setLEDs(bool, bool, bool, bool);
    // Xbee for communication
    XBee xbee;
    
private:
    void calibrationAlert(void);
    float _x, _y, _th, _range;
    Encoder _encoder_left, _encoder_right;
    Servo _servo;
    IMU _imu;
    LidarLite _lidar;
    Motor _motor;
    DigitalOut _led1, _led2, _led3, _led4;
};

#endif
