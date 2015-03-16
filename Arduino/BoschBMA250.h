/*
 * Alex Lima (alexheitorlima@gmail.com), 2014.
 * BoschBMA250 - Library for retrieving data via I2C from the Bosh BMA250 Accelerometer.
 * [1] Datasheet: http://ae-bst.resource.bosch.com/media/products/dokumente/bma250/bst-bma250-ds002-05.pdf
**/

#ifndef BoschBMA250_h
#define BoschBMA250_h

// I2C Address
#define BMA250_I2CADDR 0x18

// From "Table 8: Bandwidth Configuration" [1]
// #define BMA250_UPDATE_TIME 0x08
#define BMA250_BANDWIDTH_BIT       0x10
#define BMA250_UPDATE_TIME_64ms    0x08
#define BMA250_UPDATE_TIME_32ms    0x09
#define BMA250_UPDATE_TIME_16ms    0x0A
#define BMA250_UPDATE_TIME_8ms     0x0B
#define BMA250_UPDATE_TIME_4ms     0x0C
#define BMA250_UPDATE_TIME_2ms     0x0D
#define BMA250_UPDATE_TIME_1ms     0x0E
#define BMA250_UPDATE_TIME_.5ms    0x0F

// From "Table 9: Range Selection" [1]
#define BMA250_RANGE_BIT   0x0F
#define BMA250_RANGE_2G    0x03
#define BMA250_RANGE_4G    0x05
#define BMA250_RANGE_8G    0x08
#define BMA250_RANGE_16G   0x0C
// #define BMA250_RANGE   0x0A // What is this magic number?

class BoschBMA250
{
public:
  BoschBMA250();
  void begin(int _i2c_address = BMA250_I2CADDR,
             int update_time = BMA250_UPDATE_TIME_64ms,
             int _range = BMA250_RANGE_2G);
  void read();
  int getRawAccelerationX();
  int getRawAccelerationY();
  int getRawAccelerationZ();
  double getAccelerationX();
  double getAccelerationY();
  double getAccelerationZ();
  double getVectorMagnitude();
private:
  double normalize(int value);
  void init();
  void setupBandwidth(int bandwidth);
  void setupRange(int range);
  int i2c_address;
  int range;
  int rawX;
  int rawY;
  int rawZ;
  float temperature;
};

#endif
