#include <Wire.h>
#include "BoschBMA250.h"
#include <Arduino.h>

BoschBMA250::BoschBMA250(){}

void BoschBMA250::begin(int _i2c_address, int update_time, int _range)
{
  i2c_address = _i2c_address;
  range = _range;
  Wire.begin();			  // Init I2C Transmission
  setupBandwidth(update_time);   // Setup the bandwidth
  setupRange(range);     // Setup the range measurement
}

void BoschBMA250::setupRange(int range)
{
  Wire.beginTransmission(i2c_address);
  Wire.write(BMA250_RANGE_BIT);
  Wire.write(range);
  Wire.endTransmission();
}

void BoschBMA250::setupBandwidth(int bandwidth)
{
  Wire.beginTransmission(i2c_address);
  Wire.write(BMA250_BANDWIDTH_BIT);
  Wire.write(bandwidth);
  Wire.endTransmission();
}

// Read Data Buffer
void BoschBMA250::read()
{
  uint8_t ReadBuff[8];

  // Read the 7 data bytes from the BMA250
  Wire.beginTransmission(i2c_address);
  Wire.write(0x02);
  Wire.endTransmission();
  Wire.requestFrom(i2c_address, 7);

  for(int i = 0; i < 7;i++){
    ReadBuff[i] = Wire.read();
  }

  rawX = ReadBuff[1] << 8;
  rawX = rawX | ReadBuff[0];
  rawX = rawX >> 6;

  rawY = ReadBuff[3] << 8;
  rawY = rawY | ReadBuff[2];
  rawY = rawY >> 6;

  rawZ = ReadBuff[5] << 8;
  rawZ = rawZ | ReadBuff[4];
  rawZ = rawZ >> 6;

  temperature = (ReadBuff[6] * 0.5) + 24.0;
}

// Raw Data
int BoschBMA250::getRawAccelerationX()
{
  return rawX;
}

int BoschBMA250::getRawAccelerationY()
{
  return rawY;
}

int BoschBMA250::getRawAccelerationZ()
{
  return rawZ;
}

// A/D Normalization
double BoschBMA250::normalize(int value)
{
  // Not sure where this magic formula comes from . . .
  double unit = 4.0 / 1023; // -4/+4G / 1023 (Range);
  double normalized = unit * value;
  return normalized;
}

double BoschBMA250::getAccelerationX()
{
  return normalize(rawX);
}

double BoschBMA250::getAccelerationY()
{
  return normalize(rawY);
}

double BoschBMA250::getAccelerationZ()
{
  return normalize(rawZ);
}

double BoschBMA250::getVectorMagnitude()
{
  double magnitude = sqrt(square(getAccelerationX()) + square(getAccelerationY()) + square(getAccelerationZ()));
  return magnitude;
}

// Digital Implementation of High Pass Filter (HPF)
float performHPF(float lastFilteredSample, float sample, float lastSample)
{
  float filteredSample = 0.996 * (lastFilteredSample + sample - lastSample);
  return filteredSample;
}

// Digital Implementation of Low Pass Filter (LPF)
float performLPF(float alpha, float lastFilteredSample, float sample)
{
  float filteredSample = sample * alpha + (lastFilteredSample * (1.0 - alpha));
  return filteredSample;
}
