/*
 * crc.h
 *
 *  Created on: Jul 11, 2024
 *      Author: tuna
 */

#ifndef INC_CRC_H_
#define INC_CRC_H_

uint8_t reverseByte(uint8_t byte);
uint16_t crc16_arc(uint8_t *data, size_t length);


#endif /* INC_CRC_H_ */
