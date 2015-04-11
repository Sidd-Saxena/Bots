#include "imu.h"

//Gravity at Earth's surface in m/s/s
#define g0 9.812865328
// Number of samples to average
#define SAMPLES 4
// Convert from degrees to radians
#define toRadians(x) (x * 0.01745329252)
// ITG-3200 sensitivity is 14.375 LSB/(degrees/sec)
#define GYROSCOPE_GAIN (1 / 14.375)
// Full scale resolution on the ADXL345 is 4mg/LSB
#define ACCELEROMETER_GAIN (0.004 * g0)
// Sampling gyroscope at 200Hz
#define GYRO_RATE 0.005
// Sampling accelerometer at 200Hz
#define ACC_RATE 0.005
// Updating filter at 40Hz
#define FILTER_RATE 0.1

IMU::IMU(PinName sda, PinName scl, int s) :
    _acc(sda, scl), 
    _gyr(sda, scl), 
    _imu(FILTER_RATE, 0.3), 
    _a_x_bias(0.0), 
    _a_y_bias(0.0), 
    _a_z_bias(0.0), 
    _w_x_bias(0.0), 
    _w_y_bias(0.0), 
    _w_z_bias(0.0), 
    _a_x_accumulator(0.0), 
    _a_y_accumulator(0.0), 
    _a_z_accumulator(0.0), 
    _w_x_accumulator(0.0), 
    _w_y_accumulator(0.0), 
    _w_z_accumulator(0.0), 
    _a_x(0.0), 
    _a_y(0.0), 
    _a_z(0.0), 
    _w_x(0.0), 
    _w_y(0.0), 
    _w_z(0.0), 
    _calib_samples(s), 
    _acc_samples(0), 
    _gyr_samples(0)
{
    // Low pass filter bandwidth of 42Hz
    _gyr.setLpBandwidth(LPFBW_42HZ);
    // Internal sample rate of 200Hz. (1kHz / 5)
    _gyr.setSampleRateDivider(4);
    // Go into standby mode to configure the device
    _acc.setPowerControl(0x00);
    //F ull resolution, +/-16g, 4mg/LSB
    _acc.setDataFormatControl(0x0B);
    // 200Hz data rate
    _acc.setDataRate(ADXL345_200HZ);
    // Measurement mode
    _acc.setPowerControl(0x08);
    // Wait for accelerometer to update
    wait_ms(22);
}

/*
 * Calibrates the IMU.
 */
void IMU::calibrate(void)
{
    // Take a number of readings and average them to calculate the accelerometer and gyroscope bias offset
    for (int i = 0; i < _calib_samples; i++) {
        // Get readings from the accelerometer
        _acc.getOutput(_readings);
        _a_x_accumulator += (int16_t) _readings[0];
        _a_y_accumulator += (int16_t) _readings[1];
        _a_z_accumulator += (int16_t) _readings[2];
        // Get the readings from the gyroscope
        _w_x_accumulator += _gyr.getGyroX();
        _w_y_accumulator += _gyr.getGyroY();
        _w_z_accumulator += _gyr.getGyroZ();
        wait(GYRO_RATE);
    }
    // Average the accelerometer samples
    _a_x_accumulator /= _calib_samples;
    _a_y_accumulator /= _calib_samples;
    _a_z_accumulator /= _calib_samples;
    // Average the gyroscope samples
    _w_x_accumulator /= _calib_samples;
    _w_y_accumulator /= _calib_samples;
    _w_z_accumulator /= _calib_samples;
    // Compute the accelerometer bias 
    _a_x_bias = _a_x_accumulator;
    _a_y_bias = _a_y_accumulator;
    _a_z_bias = (_a_z_accumulator - 250); // //At 4mg/LSB, 250 LSBs is 1g
    // Compute the gyroscope bias
    _w_x_bias = _w_x_accumulator;
    _w_y_bias = _w_y_accumulator;
    _w_z_bias = _w_z_accumulator;
    // Reset the accumulators
    _a_x_accumulator = 0;
    _a_y_accumulator = 0;
    _a_z_accumulator = 0;
    _w_x_accumulator = 0;
    _w_y_accumulator = 0;
    _w_z_accumulator = 0;
    //Set up timers.
    // Accelerometer data rate is 200Hz, so we'll sample at this speed
    _acc_ticker.attach(this, &IMU::sampleAcc, ACC_RATE);
    // Gyroscope data rate is 200Hz, so we'll sample at this speed
    _gyr_ticker.attach(this, &IMU::sampleGyr, GYRO_RATE);
    // Update the filter variables at the correct rate
    _filter_ticker.attach(this, &IMU::filter, FILTER_RATE);
}

/*
 * Takes a sample from the IMU accelerometer.
 */
void IMU::sampleAcc(void)
{
    // If we have taken enough samples, compute the accelerometer values; 
    // else, take another sample
    if (_acc_samples == SAMPLES) {
        //Average the samples, remove the bias, and calculate the acceleration in m/s/s
        _a_x = ((_a_x_accumulator / SAMPLES) - _a_x_bias) * ACCELEROMETER_GAIN;
        _a_y = ((_a_y_accumulator / SAMPLES) - _a_y_bias) * ACCELEROMETER_GAIN;
        _a_z = ((_a_z_accumulator / SAMPLES) - _a_z_bias) * ACCELEROMETER_GAIN;
        _a_x_accumulator = 0;
        _a_y_accumulator = 0;
        _a_z_accumulator = 0;
        _acc_samples = 0;
    }
    else {
        _acc.getOutput(_readings);
        _a_x_accumulator += (int16_t) _readings[0];
        _a_y_accumulator += (int16_t) _readings[1];
        _a_z_accumulator += (int16_t) _readings[2];
        _acc_samples++;
    }
}

/*
 * Takes a sample from the IMU gyroscope.
 */
void IMU::sampleGyr(void)
{
    // If we have taken enough samples, compute the gyroscope values; 
    // else, take another sample
    if (_gyr_samples == SAMPLES) {
        // Average the samples, remove the bias, and calculate the angular velocity in rad/s
        _w_x = toRadians(((_w_x_accumulator / SAMPLES) - _w_x_bias) * GYROSCOPE_GAIN);
        _w_y = toRadians(((_w_y_accumulator / SAMPLES) - _w_y_bias) * GYROSCOPE_GAIN);
        _w_z = toRadians(((_w_z_accumulator / SAMPLES) - _w_z_bias) * GYROSCOPE_GAIN);
        _w_x_accumulator = 0;
        _w_y_accumulator = 0;
        _w_z_accumulator = 0;
        _gyr_samples = 0;
    }
    else {
        _w_x_accumulator += _gyr.getGyroX();
        _w_y_accumulator += _gyr.getGyroY();
        _w_z_accumulator += _gyr.getGyroZ();
        _gyr_samples++;
    }
}

/*
 * Updates the IMU filter.
 */
void IMU::filter(void)
{
    //Update the filter variables
    _imu.updateFilter(_w_y, _w_x, _w_z, _a_y, _a_x, _a_z);
    //Calculate the new Euler angles
    _imu.computeEuler();
}

/*
 * Get the current angle reading from the IMU.
 */
float IMU::getTh(void)
{
    return _imu.getYaw();
}
