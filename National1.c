#pragma config(Sensor, S1,     DIMC,           sensorEV3_GenericI2C)
#pragma config(Sensor, S2,     ,               sensorEV3_GenericI2C)
#pragma config(Sensor, S3,     inf1d,          sensorEV3_GenericI2C)
#pragma config(Sensor, S4,     inf2d,          sensorEV3_GenericI2C)
#pragma config(Motor,  motorA,          FR,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          BR,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorC,          BL,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorD,          FL,            tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "mindsensors-ev3smux.h"
#include "hitechnic-irseeker-v2.h"

int goalcomp; //Goal Direction
int Sorbit = 80; //Orbit Speed
int Saim = 40; //Aiming Speed
int Caim = 20; //Compass Aiming Speed
int range = 6; //Radius of Accuracy (The lower the better accuarcy)
int Sshooting = 100; //Shooting Speed
int comp,inf1,inf1s,inf2,inf2s,maxcomp,mincomp,complogic;
bool Rcomp;
float mux[3];

tMSEV3 muxedSensor[3];
tEV3SensorTypeMode typeMode[3] = {colorReflectedLight, colorReflectedLight, colorReflectedLight};

//Movement Functions
void Mstop()   {motor[FR] = 0;  			motor[BR] = 0;  				motor[BL] = 0;  				motor[FL] = 0;}
void Mforward(){motor[FR] = Sshooting;motor[BR] = Sshooting; 	motor[BL] = -Sshooting;	motor[FL] = -Sshooting;}
void Mright()  {motor[FR] = -Sorbit;	motor[BR] = Sorbit; 		motor[BL] = Sorbit; 		motor[FL] = -Sorbit;}
void Mmright() {motor[FR] = -Saim;		motor[BR] = Saim; 			motor[BL] = Saim; 			motor[FL] = -Saim;}
void Mleft()   {motor[FR] = Sorbit; 	motor[BR] = -Sorbit;		motor[BL] = -Sorbit;		motor[FL] = Sorbit;}
void Mmleft()  {motor[FR] = Saim; 		motor[BR] = -Saim;			motor[BL] = -Saim;			motor[FL] = Saim;}
void Mback()   {motor[FR] = -Sorbit;	motor[BR] = -Sorbit;		motor[BL] = Sorbit; 		motor[FL] = Sorbit;}
void Tleft()   {motor[FR] = Caim; 		motor[BR] = Caim; 			motor[BL] = Caim; 			motor[FL] = Caim;}
void Tright()  {motor[FR] = -Caim;		motor[BR] = -Caim;			motor[BL] = -Caim;			motor[FL] = -Caim;}

task main()
{ //Initialize
	eraseDisplay();
	if (!initSensor(&muxedSensor[0], msensor_S2_1, typeMode[0]))
		writeDebugStreamLine("initSensor() failed! for msensor_S2_1");

	if (!initSensor(&muxedSensor[1], msensor_S2_2, typeMode[1]))
		writeDebugStreamLine("initSensor() failed! for msensor_S2_2");

	if (!initSensor(&muxedSensor[2], msensor_S2_3, typeMode[2]))
		writeDebugStreamLine("initSensor() failed! for msensor_S2_3");
	tHTIRS2 irSeeker1;
	tHTIRS2 irSeeker2;

	initSensor(&irSeeker1, inf1d);
	initSensor(&irSeeker2, inf2d);
	comp = SensorValue[S1];
	goalcomp = comp;
	mincomp = goalcomp - range;
	maxcomp = goalcomp + range;
	if(comp <=90){
			complogic = 1;
		} else{
			complogic = 2;
		}
	while(true)
	{

		//Testing white line
		if(inf1==0&&inf2==0&&Rcomp==true){
			Mstop();
		}
		if(mux[0]>10&&mux[2]>10){
			Mback();
			sleep(2500);
		}
		else if(mux[0]>10){
			Mright();
			sleep(200);
		}
		else if(mux[1]>10){
			Mforward();
			sleep(200);
		}
		else if(mux[2]>10){
			Mleft();
			sleep(200);
		}
		//Gaining data from sensors
		readSensor(&irSeeker1);
		readSensor(&irSeeker2);
		comp = SensorValue[S1];
		inf1 = irSeeker1.acDirection;
		inf2 = irSeeker2.acDirection;
		inf1s = irSeeker1.enhStrength;
		inf2s = irSeeker2.enhStrength;
		for (int i = 0; i < 3; i++)
		{
			if (!readSensor(&muxedSensor[i]))
				writeDebugStreamLine("readSensor() failed! for %d", i);

			switch(muxedSensor[i].typeMode)
			{
			case colorReflectedLight:
				mux[i] = muxedSensor[i].light;
				break;
			}
		}
		//Displaying data
		//Orbit Logic
		if(comp>=mincomp&&comp<=maxcomp){
			Rcomp = true;
			if(inf1s<inf2s){
				if(inf2>=5&&inf2<=6)
				{
					Mleft();
				}
				else if(inf2==4)
				{
					Mright();
				}
				else{
					Mback();
				}
			}
			if(inf1s>inf2s)
			{
				if(inf1>=3&&inf1<=4)
				{
					Mmleft();
				}
				if(inf1==6||inf1==7)
				{
					Mmright();
				}
				if(inf1==5||inf1==6)
				{
					Mforward();
				}
			}
		}
		//Compass logic
		if(complogic==1){
			if((comp<mincomp)||((comp>maxcomp+84))){
				Tright();
				Rcomp = false;
			} else if((comp<maxcomp+84)&&(comp>maxcomp)){
				Tleft();
				Rcomp = false;
			}
		}
		else{
			if(((comp<mincomp-84))||(comp>maxcomp)){
				Tleft();
				Rcomp = false;
			} else if((comp>mincomp-84)&&(comp<mincomp)){
				Tright();
				Rcomp = false;
			}
		}
	}
}
