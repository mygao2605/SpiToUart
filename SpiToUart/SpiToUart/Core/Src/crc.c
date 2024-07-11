/*
 * crc.c
 *
 *  Created on: Jul 11, 2024
 *      Author: tuna
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

uint8_t reverseByte(uint8_t byte)
{
    byte = (byte & 0xF0) >> 4 | (byte & 0x0F) << 4;
    byte = (byte & 0xCC) >> 2 | (byte & 0x33) << 2;
    byte = (byte & 0xAA) >> 1 | (byte & 0x55) << 1;
    return byte;
}
uint16_t crc16_arc(uint8_t *data, size_t length)
{
    uint16_t crc = 0x0000;
    uint16_t polynomial = 0x8005;

    for (size_t i = 0; i < length; i++)
    {
        crc ^= (uint16_t)reverseByte(data[i]) << 8;

        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x8000)
            {
                crc = (crc << 1) ^ polynomial;
            }
            else
            {
                crc = crc << 1;
            }
        }
    }

    return reverseByte(crc >> 8) | (reverseByte(crc & 0x00FF) << 8);
}
