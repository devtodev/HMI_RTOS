/*
 * HMI.h
 *
 *  Created on: Dec 23, 2017
 *      Author: karl
 */

#ifndef SOURCES_HMI_H_
#define SOURCES_HMI_H_

#define LED_BLINK 2
#define LED_OFF   1
#define LED_ON    0

#define BLACK	  0
#define RED		  1
#define GREEN	  2
#define BLUE	  3
#define TURQUOISE 4 //Blue and green
#define YELLOW    5 //green and red
#define VIOLET	  6 //red and blue
#define WHITE	  7 //red, blue and green

// user modes to show
#define HMI_MSG_SIZE 5
#define HMI_LEDSOFF	0
#define HMI_ERROR	1
#define HMI_ALERT	2
#define HMI_CONNECT	3
#define HMI_WAITING	4
#define HMI_OK		5

#define HMITaskPeriod 100
#define TIMETOSHINE 20000 // mili seconds
#define TIMETOBLINK 200 // mili seconds
#define TIMETOSPECIALMODE 5000

void clearLeads();
char refreshHMIMsg(int blinkState);
char setHMIMsg(int msg, int timeToShine);  // user function to set msg
char showHMIMsg(char msg, int state); // set leds to show a msg

#endif /* SOURCES_HMI_H_ */
