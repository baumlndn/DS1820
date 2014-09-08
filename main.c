/*
 * main.c
 *
 *  Created on: 30.08.2014
 *      Author: baumlndn
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "ds1820.h"

#define   EEPReadByte(addr)         eeprom_read_byte((uint8_t *)addr)
#define   EEPWriteByte(addr, val)   eeprom_write_byte((uint8_t *)addr, val)

int main(void)
{
	uint16_t temp_meas;

	DS1820_Init();

	DDRA |= (1<<2);

	temp_meas = DS1820_GetTemp();

	EEPWriteByte(0x20,(uint8_t) (temp_meas & 0x00FF));
	EEPWriteByte(0x21,(uint8_t) ( (temp_meas & 0xFF00)>>8 ));

    for(;;)
    {
    	(void) DS1820_GetTemp();
    	_delay_ms(1000);
    	PORTA ^= (1<<2);
    }
    return 0;               /* never reached */
}
