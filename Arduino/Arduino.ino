/*
 * Alex Lima (alexheitorlima@gmail.com)
 * Example using BMA250 class with TinyDuino.
**/

#include <Wire.h>
#include "BoschBMA250.h"
#include <String.h>

// Create BMA250 object.
BoschBMA250 BMA250;

void setup() 
{
    // Initialize communications
    Serial.begin(115200);
    BMA250.begin();
}

// Main application loop
void loop() 
{
  // Read data from accelerometer
  BMA250.read();
  String message = "X: " + toString(BMA250.getAccelerationX(), 1) + ", " + 
                   "Y: " + toString(BMA250.getAccelerationY(), 1) + ", " +
                   "Z: " + toString(BMA250.getAccelerationZ(), 1) + ", " + 
                   "Magnitude: " + toString(BMA250.getVectorMagnitude(), 1) + "\n";
   Serial.println(message);  
   delay(100);
} 

String toString(double value, int precision)
{
    char temp[10];
    dtostrf(value, 1, precision, temp);
    String string = String(temp); 
    return string;
}
