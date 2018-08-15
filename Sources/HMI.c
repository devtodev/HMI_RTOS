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
#include "Button.h"

int hmi_MSG_states[HMI_MSG_SIZE+1];

void setLed(char color)
{
	switch(color)
	{
		case RED:
			LED_Red_PutVal(LED_ON);
			LED_Blue_PutVal(LED_OFF);
			LED_Green_PutVal(LED_OFF);
			break;
		case GREEN:
			LED_Red_PutVal(LED_OFF);
			LED_Blue_PutVal(LED_OFF);
			LED_Green_PutVal(LED_ON);
			break;
		case BLUE:
			LED_Red_PutVal(LED_OFF);
			LED_Blue_PutVal(LED_ON);
			LED_Green_PutVal(LED_OFF);
			break;
		case TURQUOISE:
			LED_Red_PutVal(LED_OFF);
			LED_Blue_PutVal(LED_ON);
			LED_Green_PutVal(LED_ON);
			break;
		case YELLOW:
			LED_Red_PutVal(LED_ON);
			LED_Blue_PutVal(LED_OFF);
			LED_Green_PutVal(LED_ON);
			break;
		case VIOLET:
			LED_Red_PutVal(LED_ON);
			LED_Blue_PutVal(LED_ON);
			LED_Green_PutVal(LED_OFF);
			break;
		case WHITE:
			LED_Red_PutVal(LED_ON);
			LED_Blue_PutVal(LED_ON);
			LED_Green_PutVal(LED_ON);
			break;
		case BLACK:
			LED_Red_PutVal(LED_OFF);
			LED_Blue_PutVal(LED_OFF);
			LED_Green_PutVal(LED_OFF);
			break;
	}
}

// set msg into the state msg array
char setHMIMsg(int msg, int state)
{
	if (msg == HMI_LEDSOFF) {
		setLed(BLACK);
	} else {
		hmi_MSG_states[msg] = state;
	}

}

/*
 * Msgs to show in LEDs
 *
	HMI_LEDSOFF
	HMI_ERROR
	HMI_ALER
	HMI_CONNECT
	HMI_WAITING
	HMI_OK
 *  etc
 */

char showHMIMsg(char msg, int state)
{
	switch(msg)
	{
	case HMI_LEDSOFF:
		setLed(BLACK);
		break;
	case HMI_ERROR:
		if (state == LED_ON)
			setLed(RED);
		else
			setLed(BLACK);
		break;
	case HMI_ALERT:
		if (state == LED_ON)
			setLed(BLUE);
		else
			setLed(BLACK);
		break;
	case HMI_WAITING:
		if (state == LED_ON)
			setLed(GREEN);
		else
			setLed(BLACK);
		break;
	case HMI_CONNECT:
		if (state == LED_ON)
			setLed(VIOLET);
		else
			setLed(BLACK);
		break;
	case HMI_OK:
		if (state == LED_ON)
			setLed(YELLOW);
		else
			setLed(BLACK);
		break;
	default:
		 setLed(RED);
		return 1;
		break;
	}
	return 0;
}

char refreshHMIMsg(int blinkState)
{
	for (char msg = 1; msg <= HMI_MSG_SIZE; msg++)
	{
		if (hmi_MSG_states[msg] == LED_ON)
			showHMIMsg(msg, 1);
		if (hmi_MSG_states[msg] == LED_BLINK)
			showHMIMsg(msg, blinkState);
	}
}

void clearLeads()
{
	for (char msg = 1; msg <= HMI_MSG_SIZE; msg++)
	{
		hmi_MSG_states[msg] = LED_OFF;
	}
}
