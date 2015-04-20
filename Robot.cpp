#include "robot.h"

// The distance in cm on one encoder click
//const float ENCODER_DISTANCE = 2.35;

Robot::Robot() : 
    //brain(p23, p13, p14), 
    xbee(p13, p14,p12), 
    _x(0.0), 
    _y(0.0), 
    _th(0.0), 
    _range(0.0), 
    _encoder_left(p23,p22), 
    _lidar(p9,p10), 
    _wheels(p6,p5,p7,p8),//forward1,backward1,forward2,backward2
    _servo(p25), 
    _imu(p28, p27, 500), 
    _led1(LED1), 
    _led2(LED2), 
    _led3(LED3), 
    _led4(LED4)
{
    // Send a stop signal to the base so that it does not run the default program
    // NOTE: This can be any signal
    ///brain.stop();
}

/*
 * Alert the user that calibration is about to begin.
 */
void Robot::calibrationAlert(void)
{
    setLEDs(0, 0, 0, 0);
    wait(0.5);
    setLEDs(1, 0, 0, 0);
    wait(0.5);
    setLEDs(1, 1, 0, 0);
    wait(0.5);
    setLEDs(1, 1, 1, 0);
    wait(0.5);
    setLEDs(1, 1, 1, 1);
    wait(0.5);
    for (int i = 0; i < 8; i++) {
        setLEDs(0, 0, 0, 0);
        wait(0.1);
        setLEDs(1, 1, 1, 1);
        wait(0.1);
    }
}

/* Calibrate the robot sensors. */
void Robot::calibrate(bool calib_imu, bool calib_servo)
{
    calibrationAlert();
    //if (calib_imu) {
//        // Calibrate the robot's IMU
//        _imu.calibrate();
//    }
//    if (calib_servo) {
//        // Calibrate and initialize the servo
//        _servo.calibrate(0.001, 90.0);
//    }
    setLEDs(0, 0, 0, 0);
}

/* Returns the robot's x coordinate. */
float Robot::x(void)
{
    return _x;
}

/* Returns the robot's y coordinate. */
float Robot::y(void)
{
    return _y;
}

/* Returns the robot's heading. */
float Robot::th(void)
{
    return _imu.getTh();
}

/* Sets the robot's x coordinate. */
void Robot::setX(float new_x)
{
    _x = new_x;
}

/* Sets the robot's y coordinate. */
void Robot::setY(float new_y)
{
    _y = new_y;
}

/* Sets the robot's heading. */
void Robot::setTh(float new_th)
{
    _th = new_th;
}

/* Sets the direction of the servo. */
void Robot::setServo(float deg)
{
    _servo.position(deg);
}

/*Returns the rnage reported by the Lidar*/
/* Range of the Lidar being 6m*/
float Robot::range(void)
{
    _lidar.refreshRange();
    float total = _lidar.getRange_cm();
    return total;
}

///* Gets the white value of the left encoder. True = white; false = left. */
//bool Robot::encoderLeft(void)
//{
//    bool to_return;
//    Timer t;
//    _encoder_left.output();
//    _encoder_left = 1;
//    wait_us(100);
//    _encoder_left.input();
//    t.start();
//    while (_encoder_left = 1 && t.read_us() < 1000);
//    t.stop();
//    if (t.read_us() < 250) {
//        to_return = true;
//    }
//    else {
//        to_return = false;
//    }
//    return to_return;
//}
//
///* Gets the white value of the right encoder. True = white; false = left. */
//bool Robot::encoderRight(void)
//{
//    bool to_return;
//    Timer t;
//    _encoder_right.output();
//    _encoder_right = 1;
//    wait_us(100);
//    _encoder_right.input();
//    t.start();
//    while (_encoder_right == 1 && t.read_us() < 1000);
//    t.stop();
//    if (t.read_us() < 300) {
//        to_return = true;
//    }
//    else {
//        to_return = false;
//    }
//    return to_return;
//}

/* Moves the robot forward the specified distance. */
float Robot::forward(int dist)
{
   _wheels.forward();
   _encoder_left.forward(dist);
   _wheels.brake();
// Update the robot's x and y coordinates
    _x += cos(_th) * dist;
    _y += sin(_th) * dist;  
}

/* Moves the robot backward the specified distance. */
float Robot::backward(int dist, float speed)
{
    //return forward(dist, -speed);
}

/*Moves the robot to right with particular speed */
//void Robot::right(float speed)
//{
//    brain.right(speed);
//    wait(0.5);
//    brain.stop();
//}
//
///*Moves the robot to left with particular speed */
//void Robot::left(float speed)
//{
//    brain.left(speed);
//    wait(0.5);
//    brain.stop();
//}

/* Takes a 180-degree laser scan. */
DataSample Robot::scan(void)
{
    DataSample ds;
    ds.x = _x;
    ds.y = _y;
    // Iterate through the 160-degree range of the servo one degree at a time, 
    // taking a laser scan at each degree
    float deg = -80.0;
    // Set initial position and wait for the servo to reach that point
    _servo.write(deg);
    wait(1.0);
    // Iterate through the servo's range and take a laser scan at each point
    while (deg <= 80.0) {
        // Position the servo and wait for it to reach that position
        _servo.position(deg);
        wait_ms(50);
        // Create the data entry
        pair<float, float> entry;
        // First, record the orientation of the IR scanners relative to the robot
        entry.first = toRadians(deg);
        // Get the IR scan
        entry.second = range();
        ds.data.push_back(entry);
        // Increment the angle
        deg += 1.0;
    }
    return ds;
}

//send the Current Co ordinates over ZigBee
void Robot::sendData(void) 
{
    xbee.sendData("Move");
}

/*
 * Sets the robot's LEDs to the values given.
 */
void Robot::setLEDs(bool l1, bool l2, bool l3, bool l4)
{
    _led1 = l1;
    _led2 = l2;
    _led3 = l3;
    _led4 = l4;
}
