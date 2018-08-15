
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

/* Begin of <includes> initialization, DO NOT MODIFY LINES BELOW */

#include "TSK1.h"
#include "FRTOS1.h"
#include "frtos_tasks.h"

/* End <includes> initialization, DO NOT MODIFY LINES ABOVE */

#include "HMI.h"
#include "Button.h"
#include "queue.h"

QueueHandle_t xQueueHMIMsg;

static portTASK_FUNCTION(AnotherTask, pvParameters) {
	int msgid = 0;
	for(;;) {
		setHMIMsg(msgid, LED_OFF);
		msgid++;
		msgid = ((msgid>=HMI_MSG_SIZE) || (msgid<0)) ? 1 : msgid;
		setHMIMsg(msgid, LED_ON);
		vTaskDelay(1000/portTICK_RATE_MS);
	}
	vTaskDelete(AnotherTask);
}

static portTASK_FUNCTION(HMITask, pvParameters) {
	int timeToShine = 0;
	// Button is reading in a task instead of an interrupt
	// for avoid trigger an interrupt using the Button
	// and letting the scheduler admin the MCU time
	setHMIMsg(HMI_LEDSOFF, 0); // turn off the leds
	for(;;) {
		// Push the button to show the current msgs
		if (Button_GetVal() == 0) {
			// TODO: sense de time pressed in order to enter into a special mode.
			timeToShine = TIMETOSHINE;
		}

		if (timeToShine > 0) {
			refreshHMIMsg();
			timeToShine = timeToShine-HMITaskPeriod;
			if (timeToShine <= 0)
				setHMIMsg(HMI_LEDSOFF, 0); // turn off the leds
		}


		vTaskDelay(HMITaskPeriod/portTICK_RATE_MS);

	}
	vTaskDelete(HMITask);
}

void startmachine() {
	clearLeads();
}

void CreateTasks(void) {
	startmachine();
	if (FRTOS1_xTaskCreate(
	     HMITask,  /* pointer to the task */
	      "HMI", /* task name for kernel awareness debugging */
	      configMINIMAL_STACK_SIZE + 200, /* task stack size */
	      (void*)NULL, /* optional task startup argument */
	      tskIDLE_PRIORITY + 1,  /* initial priority */
	      (xTaskHandle*)NULL /* optional task handle to create */
	    ) != pdPASS) {
	      /*lint -e527 */
	      for(;;){}; /* error! probably out of memory */
	      /*lint +e527 */
	  }
	if (FRTOS1_xTaskCreate(
	     AnotherTask,  /* pointer to the task */
	      "AnotherTask", /* task name for kernel awareness debugging */
	      configMINIMAL_STACK_SIZE, /* task stack size */
	      (void*)NULL, /* optional task startup argument */
	      tskIDLE_PRIORITY + 2,  /* initial priority */
	      (xTaskHandle*)NULL /* optional task handle to create */
	    ) != pdPASS) {
	      /*lint -e527 */
	      for(;;){}; /* error! probably out of memory */
	      /*lint +e527 */
	  }
}

