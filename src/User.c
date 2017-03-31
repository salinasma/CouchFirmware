// filename ******** User.c ************** 
//
// Source code file for functions to provide a user
// interface for our project
//
// Authors:          Shan and Santiago
//                   (we attribute this file to Prof Valvano)
// Date of Creation: October 30, 2016
// TA:               Dylan
// Unique number:    16620

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "User.h"
#include <math.h>
#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/adc.h>
#include <RASLib/inc/motor.h>
#include <RASLib/inc/servo.h>
#include <StellarisWare/driverlib/gpio.h>
#include "TestSampling.h"
#include "PSX.h"

#define FREESTYLE  4
#define JOSHSTYLE  6
#define SPEEDX     7
#define DIRECTIONX 11

extern uint32_t Lx, Ly, Rx, Ry,
	   X, Square, Triangle, Circle,
	   Up, Down, Right, Left,
	   L1, L2, R1, R2;
extern uint32_t BackButton, SelectButton, UpButton, DownButton;
uint32_t leftVal;
uint32_t rightVal;
tADC* leftPot;
tADC* rightPot;
tMotor* left;
tMotor* right;
float leftMotor;
float rightMotor;


void User_DriveMotors(uint32_t leftValue, uint32_t rightValue){
	if (leftValue > 127){
		leftMotor = (float)(leftValue - 127) / 128;
		SetMotor(left, leftMotor);
	}
	else if (leftValue < 127){
		leftMotor = (float)(127 - leftValue) / 127 * -1;
		SetMotor(left, leftMotor);
	}
	else if (leftValue == 127){
		SetMotor(left, 0);

	}
	if (rightValue >= 127){
		rightMotor = (float)(rightValue - 127) / 128;
		SetMotor(right, rightMotor);
	}
	else if (rightValue < 127){
		rightMotor = (float)(127 - rightValue) / 128 * -1;
		SetMotor(right, rightMotor);
	}
	else if (rightValue == 127){
		SetMotor(right, 0);
	}
}

// *****User_Begin*********
// Initializes the user interface
// Input: none
// Output: none
void User_Begin(void){
	uint32_t mode;
	mode = FREESTYLE;
	ST7735_SetCursor(0, FREESTYLE);
	ST7735_OutString("->");									// set original location of selector at free styling

	while(1){
		PSX_Poll();
		if (Up == 255 && Left == 255 && Down && 255 && Right == 255){
			PSX_Clear();
		}
	
		if(Down > 0)
			PSX_Clear();											// acknowdledge down button
			
		if(Up > 0)
			PSX_Clear();											// acknowdledge up button

		PSX_Clear();
		User_FreeStyle();
		PSX_Clear();                                                // clear all buttons
	}

}


// *****User_FreeStyle*********
// Sets the free style mode
// Input: none
// Output: none
void User_FreeStyle(void){
	while(true){

		PSX_Poll();

		leftVal = Ly;
		rightVal =  Ry;

		User_DriveMotors(Ly, Ry);
	}
	SetMotor(left, 0);
	SetMotor(right, 0);
	PSX_Clear();

}
