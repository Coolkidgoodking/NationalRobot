#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     gyroSensor,     sensorEV3_Gyro, modeEV3Gyro_RateAndAngle)
#pragma config(Sensor, S3,     colorSensor,    sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          FL,            tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          FR,            tmotorEV3_Medium, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          BR,            tmotorEV3_Medium, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorD,          BL,            tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*------------------------------------------------------------------------------------------------
This program will move your robot forward for 2 seconds. At the end of the program, all motors
will shut down automatically and turn off.

ROBOT CONFIGURATION: LEGO EV3 REM Bot
MOTORS & SENSORS:
[I/O Port]          [Name]              [Type]                			[Location]
MotorC        			leftMotor           LEGO EV3 Motor		      Left side motor
MotorB       				rightMotor          LEGO EV3 Motor		      Right side motor (reversed)
------------------------------------------------------------------------------------------------*/

task main()
{
//Foward
motor[FL] = 50;
motor[FR] = 50;
motor[BR] = -50;
motor[BL] = -50;
//Back
motor[FL] = -50;
motor[FR] = -50;
motor[BR] = 50;
motor[BL] = 50;
//Left
motor[FL] = 50;
motor[FR] = -50;
motor[BR] = -50;
motor[BL] = 50;
//Right
motor[FL] = -50;
motor[FR] = 50;
motor[BR] = 50;
motor[BL] = -50;
}
