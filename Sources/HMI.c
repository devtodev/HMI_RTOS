/*
 * HMI.c
 *
 *  Created on: Dec 23, 2017
 *      Author: karl
 */

#include "HMI.h"
#include "LED_Red.h"
#include "LED_Green.h"
#include "LED_Blue.h"

char red = LED_OFF, green = LED_OFF, blue = LED_OFF;

void setLed(char color)
{
	red = LED_OFF;
	green = LED_OFF;
	blue = LED_OFF;

	switch(color)
	{
		case RED:
			red = LED_ON;
			break;
		case GREEN:
			green = LED_ON;
			break;
		case BLUE:
			blue = LED_ON;
			break;
		case TURQUOISE:
			blue = LED_ON;
			green = LED_ON;
			break;
		case YELLOW:
			red = LED_ON;
			green = LED_ON;
			break;
		case VIOLET:
			red = LED_ON;
			blue = LED_ON;
			break;
		case WHITE:
			red = LED_ON;
			blue = LED_ON;
			green = LED_ON;
			break;
	}

	LED_Red_PutVal(red);
	LED_Blue_PutVal(blue);
	LED_Green_PutVal(green);
}
