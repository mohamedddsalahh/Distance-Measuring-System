/*
 * main.c
 *
 *  Created on: Oct 13, 2022
 *      Author: USER
 */
#include"icu.h"
#include"lcd.h"
#include"ultraSonic.h"
#include"std_types.h"
#include<avr/io.h>

Icu_ConfigType *g_Icu_Configuration = 0;
void main(void){
	uint16 value =0;
	Icu_ConfigType IcuConfiguration = {F_CPU_8, RISING};
	g_Icu_Configuration = &IcuConfiguration;
	SREG |= (1<<7);
	Ultrasonic_init();
	LCD_init();


	while(1){
		LCD_moveCursor(0, 0);
	//	LCD_displayString("Distance = ");
		/* display the distance on LCD screen */
		value = Ultrasonic_readDistance();
		LCD_intgerToString(value);
		LCD_displayString(" cm");
	//	_delay_ms(1);
	}

}

