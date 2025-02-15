/*
 * process.c
 *
 *  Created on: Jul 8, 2024
 *      Author: tuna
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void decimalToChar(const uint8_t *decArray, char **charArray, uint8_t *uintArray, size_t size) {
    char dtc[size];// This buffer might not be necessary if you directly use decArray
    int j = 0;

    for (size_t i = 0; i < size; i++) {
        dtc[i] = (char)decArray[i];  // Convert each decimal value to a character
    }

    // Corrected loop to iterate through dtc array
    for(size_t i = 0 ; i < size; i+=2) {
        charArray[j] = (char *)malloc(5 * sizeof(char));
        if (charArray[j] == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        charArray[j][0] = '0';
        charArray[j][1] = 'x';
        strncpy(charArray[j] + 2, &dtc[i], 2);  // Correct usage of strncpy
        charArray[j][4] = '\0';
        uintArray[j] = (uint8_t)charArray[j];
        j++;
    }
}

