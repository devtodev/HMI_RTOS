
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

static portTASK_FUNCTION(HMITask, pvParameters) {
	int ledCursor = 0, state = 0, btn = 0;

	for(;;) {
		btn = Button_GetVal();
		if (btn == 0)
		{
			ledCursor++;
			ledCursor = ((ledCursor>7) || (ledCursor<0)) ? 0 : ledCursor;
			setLed(ledCursor);
		}
		vTaskDelay(100/portTICK_RATE_MS);
	}
	vTaskDelete(HMITask);
}

void CreateTasks(void) {
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
}

