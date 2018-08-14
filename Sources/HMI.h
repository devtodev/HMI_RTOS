/*
 * HMI.h
 *
 *  Created on: Dec 23, 2017
 *      Author: karl
 */

#ifndef SOURCES_HMI_H_
#define SOURCES_HMI_H_

#define LED_OFF   1
#define LED_ON    0

#define OFF		  0
#define RED		  1
#define GREEN	  2
#define BLUE	  3
#define TURQUOISE 4 //Blue and green
#define YELLOW    5 //green and red
#define VIOLET	  6 //red and blue
#define WHITE	  7 //red, blue and green

void setLed(char color);


#endif /* SOURCES_HMI_H_ */
