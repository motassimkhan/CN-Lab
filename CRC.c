#include <stdio.h>
#include <string.h>

#define POLYNOMIAL 0xD8  // 11011 followed by 0's

void calculateCRC(char data[], char crc[]) {
    int len = strlen(data);
    strcpy(crc, data); // Copy data to crc
    for (int i = 0; i < len; i++) {
        if (crc[i] == '1') { // If bit is 1, perform XOR with the polynomial
            for (int j = 0; j < 8; j++) {
                crc[i + j] = crc[i + j] == POLYNOMIAL >> (7 - j) & 1 ? '0' : '1';
            }
        }
    }
}

int main() {
    char data[100], crc[108];

    printf("Enter data: ");
    scanf("%s", data);

    int len = strlen(data);
    for (int i = 0; i < 7; i++) {
        data[len + i] = '0'; // Append 7 zero bits to the data
    }
    data[len + 7] = '\0';

    calculateCRC(data, crc);

    printf("CRC: ");
    for (int i = 0; i < 7; i++) {
        printf("%c", crc[len + i]);
    }
    printf("\n");

    return 0;
}