/*
 * ds1820.c
 *
 *  Created on: 07.09.2014
 *      Author: baumlndn
 */

#include "ds1820.h"

void DS1820_Init()
{
	/* Set DS1820 pin as output and set output to 1 */
	DS1820_DDR  |= DS1820_POS;
	DS1820_PORT |= DS1820_POS;
}

void DS1820_WriteByte(uint8_t data)
{
	uint8_t mask = 0x01;

	while (mask != 0x00)
	{
		if ((data & mask) != 0x00)
		{
			// write 1
			DS1820_CLR;
			_delay_us(5);
			DS1820_SET;
			_delay_us(60);
		}
		else
		{
			// write 0
			DS1820_CLR;
			_delay_us(60);
			DS1820_SET;
			_delay_us(5);
		}

		mask = mask<<1;
	}
}

uint8_t  DS1820_ReadByte()
{
	uint8_t counter;
	uint8_t ret_val = 0x00;

	for (counter=0;counter<8;counter++)
	{
		/* Read one bit */
		DS1820_CLR;
		_delay_us(5);
		DS1820_SET;
		_delay_us(5);
		if (DS1820_READ != 0x00)
		{
			ret_val |= (1<<counter);
		}
		_delay_us(60);
	}
	return ret_val;
}

void DS1820_Reset()
{
	DS1820_CLR;
	_delay_us(500);
	DS1820_SET;
	_delay_us(500);
}

uint16_t DS1820_GetTemp()
{
	uint16_t ret_val_u16 = 0;
	DS1820_Reset();
	DS1820_WriteByte(DS1820_SKIP_ROM);
	DS1820_WriteByte(DS1820_CONVERT_T);
	_delay_ms(2000);
	DS1820_Reset();
	DS1820_WriteByte(DS1820_SKIP_ROM);
	DS1820_WriteByte(DS1820_READ_SCRATCHPAD);

	ret_val_u16  = DS1820_ReadByte();
	ret_val_u16 |= (DS1820_ReadByte()<<8);

	return ret_val_u16;
}
