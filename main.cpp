#include <sstream>
#include "robot.h"

const char * dataToString(DataSample);

float dist;

/* Main program loop. */
int main()
{
    Robot r;
    //callibrate all the sensors and servos
    r.calibrate(true, true);
    
    while (true) {
       
        r.sendData();
        //dist = r.range();
        r.forward(5,0.1);
        r.sendData();
       // r.right(0.5);
        r.sendData();
        //r.forward
        //r.xbee.printf(dataToString(r.scan()));
    }
}

/* Convert a data sample into a string to send over the xbee. */
const char * dataToString(DataSample ds)
{
    std::stringstream ss;
    ss << '<';
    // Add the robot's position to the string
    ss << ds.x << " " << ds.y << " " << ds.th << '\n';
    // Iterate through each data point and add it to the string
    for (unsigned int i = 0; i < ds.data.size(); i++) {
        ss << ds.data[i].first << " " << ds.data[i].second << '\n';
    }
    ss << '>';
    return ss.str().c_str();
}
