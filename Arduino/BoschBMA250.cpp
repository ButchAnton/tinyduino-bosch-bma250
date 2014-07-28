/*
 * Alex Lima (alexheitorlima@gmail.com), 2014.
 * BoschBMA250 - Library for retrieving data via I2C from the Bosh BMA250 Accelerometer. 
 * [1] Datasheet: http://ae-bst.resource.bosch.com/media/products/dokumente/bma250/bst-bma250-ds002-05.pdf
**/

#include <Wire.h>
#include "BoschBMA250.h"
#include <Arduino.h>
#include <WProgram.h>

// I2C Address
#define BMA250_I2CADDR 0x18   

// From "Table 8: Bandwidth Configuration" [1]
#define BMA250_UPDATE_TIME 0x08

// From "Table 9: Range Selection" [1]
#define BMA250_RANGE	 0x0A   

BoschBMA250::BoschBMA250(){}

void BoschBMA250::begin()
{
    Wire.begin();			  // Init I2C Transmission
    setupBandwidth(BMA250_UPDATE_TIME);   // Setup the bandwidth
    setupRange(BMA250_RANGE);		  // Setup the range measurement
}

void BoschBMA250::setupRange(int range)
{
    Wire.beginTransmission(BMA250_I2CADDR);
    Wire.write(0x0F); 
    Wire.write(range);
    Wire.endTransmission();
}

void BoschBMA250::setupBandwidth(int bandwidth)
{
    Wire.beginTransmission(BMA250_I2CADDR);
    Wire.write(0x10);
    Wire.write(bandwidth);
    Wire.endTransmission();
}

// Read Data Buffer
void BoschBMA250::read()
{
  uint8_t ReadBuff[8];
  
  // Read the 7 data bytes from the BMA250
  Wire.beginTransmission(BMA250_I2CADDR);
  Wire.write(0x02);
  Wire.endTransmission();
  Wire.requestFrom(BMA250_I2CADDR, 7);
  
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
