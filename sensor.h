#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(BNO055_ID, BNO055_ADDRESS_B);

imu::Vector<3> gyro() {
  return bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
}

imu::Vector<3> accel() {
  return bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
}

imu::Vector<3> magneto() {
  return bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
}

imu::Vector<3> linAcc() {
  return bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
}

imu::Vector<3> gravity() {
  return bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
}

/**
 * x in [0;360]
 * y in [-180;180]
 * z in [-180;180]
 * 
 * x = yaw
 * y = rot
 * z = pitch
 */
imu::Vector<3> euler() {
  return bno.getVector(Adafruit_BNO055::VECTOR_EULER);
}

