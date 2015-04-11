#ifndef IMU_H
#define IMU_H

#include "IMUfilter.h"
#include "ADXL345.h"
#include "ITG3200.h"

class IMU
{
public:
    IMU(PinName, PinName, int);
    void calibrate(void);
    float getTh(void);
    
private:
    void sampleAcc(void);
    void sampleGyr(void);
    void filter(void);
    // IMU filter components
    ADXL345 _acc;
    ITG3200 _gyr;
    IMUfilter _imu;
    // Tickers for updating the IMU
    Ticker _acc_ticker;
    Ticker _gyr_ticker;
    Ticker _filter_ticker;
    // The readings talen when stationary won't be 0, so we average a set of readings 
    // we do get when stationary and take those away from subsequent readings to
    // ensure the gyroscope and accelerometer are offset or "biased" to 0.
    double _a_x_bias;
    double _a_y_bias;
    double _a_z_bias;
    double _w_x_bias;
    double _w_y_bias;
    double _w_z_bias;
    // Accumulators used for oversampling and then averaging.
    volatile double _a_x_accumulator;
    volatile double _a_y_accumulator;
    volatile double _a_z_accumulator;
    volatile double _w_x_accumulator;
    volatile double _w_y_accumulator;
    volatile double _w_z_accumulator;
    // Accelerometer and gyroscope readings for x, y, z axes.
    volatile double _a_x;
    volatile double _a_y;
    volatile double _a_z;
    volatile double _w_x;
    volatile double _w_y;
    volatile double _w_z;
    // Buffer for accelerometer readings.
    int _readings[3];
    // Calobration samples to take
    int _calib_samples;
    // Number of samples we're on.
    int _acc_samples;
    int _gyr_samples;
};

#endif
