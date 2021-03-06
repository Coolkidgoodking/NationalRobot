#pragma config(Sensor, S2,     RS,             sensorEV3_Touch)
#pragma config(Sensor, S3,     LS,             sensorEV3_Touch)
#pragma config(Motor,  motorA,          R,             tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          L,             tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int iRS,iLS;
task main()
{
	while (true){
		iRS = SensorValue[S2];
		iLS = SensorValue[S3];
		if(iRS==1 && iLS==1){
			motor[R] = 100;
			motor[L] = 100;
		} else if (iRS==1){
			motor[R] = 100;
			motor[L] = -100;
		} else if (iLS==1){
			motor[L] = 100;
			motor[R] = -100;
		} else{
			motor[L] = 0;
			motor[R] = 0;
		}
	}
}
