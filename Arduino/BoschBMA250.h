/*
 * Alex Lima (alexheitorlima@gmail.com), 2014.
 * BoschBMA250 - Library for retrieving data via I2C from the Bosh BMA250 Accelerometer. 
 * [1] Datasheet: http://ae-bst.resource.bosch.com/media/products/dokumente/bma250/bst-bma250-ds002-05.pdf
**/

#ifndef BoschBMA250_h
#define BoschBMA250_h

class BoschBMA250
{
	public:
		BoschBMA250();
		void begin();
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
                int rawX;
		int rawY;
		int rawZ;
		float temperature;
};

#endif
