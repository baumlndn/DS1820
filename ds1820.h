/*
 * ds1820.h
 *
 *  Created on: 07.09.2014
 *      Author: baumlndn
 */

#ifndef DS1820_H_
#define DS1820_H_

#include <avr/io.h>
#include <util/delay.h>

#include "conf.h"

#define DS1820_SEARCH_ROM			0xF0
#define DS1820_READ_ROM				0x33
#define DS1829_MATCH_ROM			0x55
#define DS1820_SKIP_ROM				0xCC
#define DS1820_ALARM_SEARCH			0xEC
#define DS1820_CONVERT_T			0x44
#define DS1820_WRITE_SCRATCHPAD		0x4E
#define DS1820_READ_SCRATCHPAD		0xBE
#define DS1820_COPY_SCRATCHPAD		0x48
#define DS1820_RECALL_E2			0xB8
#define DS1820_READ_POWER_SUPPLY	0xB4

#define DS1820_POS					(1<<DS1820_BIT)

#define DS1820_SET					DS1820_PORT |=  (DS1820_POS)
#define DS1820_CLR					DS1820_PORT &= ~(DS1820_POS)
#define DS1820_READ					(DS1820_PIN & DS1820_POS)

void     DS1820_Init();
void     DS1820_WriteByte(uint8_t data);
uint8_t  DS1820_ReadByte();
uint16_t DS1820_GetTemp();
void     DS1820_Reset();

#endif /* DS1820_H_ */
