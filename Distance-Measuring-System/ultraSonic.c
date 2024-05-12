/*
 * ultraSonic.c
 *
 *  Created on: Oct 13, 2022
 *      Author: USER
 */
#include"std_types.h"
#include"gpio.h"
#include"ultraSonic.h"
#include"icu.h"
#include<util/delay.h>
#include<math.h>

extern Icu_ConfigType *g_Icu_Configuration;

uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;
uint16 g_timePeriod = 0;
uint16 g_timePeriodPlusHigh = 0;

void Ultrasonic_edgeProcessing(void){
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = Icu_getInputCaptureValue();
		/* Detect rising edge */
		Icu_setEdgeDetectionType(RISING);
		g_edgeCount = 0;
	}
}

void Ultrasonic_init(void){
	Icu_init(g_Icu_Configuration);
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(TriggerPin_PORT_ID, TriggerPin_PIN_ID, PIN_OUTPUT);	//Set Trigger Pin output
}

void Ultrasonic_Trigger(void){
	GPIO_writePin(TriggerPin_PORT_ID, TriggerPin_PIN_ID, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TriggerPin_PORT_ID, TriggerPin_PIN_ID, LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void){
	Ultrasonic_Trigger();
	uint16 distance = (uint16)ceil((g_timeHigh/58.8));
	return distance;
}