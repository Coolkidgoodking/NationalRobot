#pragma config(Sensor, S1,     DIMC,           sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "dexterind-compass.h"

task main()
{
	while(true)
	{
		SensorValue(DIMC);
	}
}