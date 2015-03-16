#include <Wire.h>
#include "BoschBMA250.h"
#include <String.h>

BoschBMA250 BMA250;

void setup()
{
  Serial.begin(9600);
  BMA250.begin();
}

void loop()
{
  BMA250.read();
  String message = "Time: " + toString(millis(),1) + ", " +
                   "X: " + toString(BMA250.getAccelerationX(), 1) + ", " +
                   "Y: " + toString(BMA250.getAccelerationY(), 1) + ", " +
                   "Z: " + toString(BMA250.getAccelerationZ(), 1);
                   // "Magnitude: " + toString(BMA250.getVectorMagnitude(), 1) + "\n";
  Serial.println(message);
  delay(100);
}

String toString(double value, int precision)
{
  char temp[50];
  dtostrf(value, 1, precision, temp);
  String string = String(temp);
  return string;
}
