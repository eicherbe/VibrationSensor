#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "libLCD/hd44780.h"
#include "IO_Macros.h"
#include <stdio.h>

#define VIBRATION_PIN PD2

int main(void)
{
	int triggers = 0;

	//Setup
	LCD_Setup();
	DDRD &= ~(1 << VIBRATION_PIN); // Set VIBRATION_PIN as input

	//Print two lines with class info to check if LCD working
	uint8_t line;
	for (line = 0; line < 2; line++)
	{
		LCD_GotoXY(0, line);
		if (line == 0)
		{
			LCD_PrintString("ECE 484 line: ");
			LCD_PrintInteger(LCD_GetY());
		}
		else 
		{
			LCD_PrintString("LCD[");
			LCD_PrintInteger(LCD_GetY());
			LCD_PrintString("] working!!!");
		}
	}

	/* delay before keyboard interrupt polling */
	_delay_ms(1000);
	LCD_Clear();
	
	while (1)
	{			int sensorValue = PIND & (1 << VIBRATION_PIN);
				if(sensorValue) {
					triggers = triggers + 1;
				}
				/* print column on top and row on bottom */
				LCD_Clear();
				LCD_GotoXY(0,0);
				LCD_PrintString("# of triggers");
				LCD_GotoXY(0,1);
				LCD_PrintInteger(triggers);
				_delay_ms(50);
	}
	return 0;
}
