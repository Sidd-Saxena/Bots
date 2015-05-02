#include "robot.h"

// The distance in cm on one encoder click
//const float ENCODER_DISTANCE = 2.35;

Robot::Robot() : 
    xbee(p13, p14,p12), 
    _x(0.0), 
    _y(0.0), 
    _th(0.0), 
    _range(0.0), 
    _encoder_left(p19,p20), 
    _lidar(p9,p10), 
    _botmotor(p6,p5,p21,p7,p8,p22),
    _servo(p23), 
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
    //if (calib_imu) 
//    {
//        //Calibrate the robot's IMU
//        _imu.calibrate();
//        printf("Calibrated the imu");
//     }
//    if (calib_servo) 
//    {
//        // Calibrate and initialize the servo
//        _servo.calibrate(0.001, 90.0);
//      }
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

//Scan the area
string Robot::servo_scan()
{
    int direction,temp=0,temp_deg;
    float deg = 90;
    _servo.position(deg);
    wait(1.0);
    while (deg >= -90) 
    {
        _servo.position(deg);
        //pc.printf("Current Position: %f  \n \r" , deg);
        direction = range();
        //comparing with the previous high value
        if ( direction > temp)
        {
           temp = direction;
           temp_deg=deg;
        }
        wait_ms(50);
        deg -= 1.0;
       
    }
    _servo.position(-2);
     if ( temp_deg < 0 )
        {
            return "R";
        }
        else
        {
            return "L";
        }
}


/* Moves the robot forward the specified distance. */
void Robot::forward(int dist, float speed)
{
    
   _botmotor.moveForward(speed);
   _encoder_left.forward(dist);
   _botmotor.stopBot();
// Update the robot's x and y coordinates
    _x += cos(_th) * dist;
    _y += sin(_th) * dist; 
    
    //printf("new co ordinates: %f ,%f",_x,_y);
}

/* Moves the robot in 180 degrees */
void Robot::TurnAround()
{
    _botmotor.turnLeft(0.1);
    wait(4);
}


/* Moves the robot backward the specified distance. */
void Robot::backward(int dist, float speed)
{
    return forward(dist,speed);
}

/*Moves the robot to right with particular speed */
void Robot::right(float speed)
{
    _botmotor.turnRight(speed);
     wait(1);
    _botmotor.stopBot();
    // Update the robot's x and y coordinates
    _x += cos(_th);
    _y += sin(_th); 
}

/*Moves the robot to left with particular speed */
void Robot::left(float speed)
{
    _botmotor.turnLeft(speed);
    wait(1);
    _botmotor.stopBot();
    // Update the robot's x and y coordinates
    _x += cos(_th);
    _y += sin(_th); 
}


void Robot::brake()
{
    _botmotor.stopBot();
}

/* Takes a 180-degree laser scan. */
DataSample Robot::scan(void)
{
    DataSample ds;
    ds.x = _x;
    ds.y = _y;
    // Iterate through the 160-degree range of the servo one degree at a time, 
    // taking a laser scan at each degree
    float deg = 43;
    // Set initial position and wait for the servo to reach that point
    _servo.position(deg);
    wait(1.0);
    // Iterate through the servo's range and take a laser scan at each point
    while (deg <= -47) {
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
        deg -= 1.0;
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


