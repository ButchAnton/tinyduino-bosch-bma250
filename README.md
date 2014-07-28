Bosch BMA250 class for TinyDuino
========

You can use this class to communicate TinyDuino with Bosch BMA250 Accelerometer via I2C.

##Main features
* Easy access to all accelerations (X, Y and X);
* Ready to use magnitude acceleration (R); 

##Easy to install
1. Clone/download this repository;
2. Include BoschBMA250.cpp and BoschBMA250.h files in your project;
3. `#import "BoschBMA250.h"`;

##Simple usage
Just implement the code like this:
```C++
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

```

Done! =)

##About

The TinyCircuits TinyDuino is an Arduino compatible board in an ultra compact package. 

Learn more about the TinyDuino:

https://tiny-circuits.com
