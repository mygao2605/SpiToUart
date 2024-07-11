/*
 * Data.h
 *
 *  Created on: Jul 9, 2024
 *      Author: tuna
 */

#ifndef INC_DATA_H_
#define INC_DATA_H_
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>
 enum {
	START =0,
	READING =1,
	READING_END =2,

};

typedef struct {
	uint8_t u8BuffRead[256];
	uint8_t modbus_state;
	uint8_t data_pointer;
	uint8_t byte_count;
	uint8_t idBoard;
	uint8_t	idPackage;
	uint32_t idMess;
	uint16_t lengdata;
	uint8_t	data[256];
	uint16_t crc;
	uint8_t flag_mesSpecial;
	uint8_t flag_update;
	uint32_t delay_ID;
}S_FRAME_RX485;
extern S_FRAME_RX485		sFrameRx;
void RS485Process(void);


#endif /* INC_DATA_H_ */
