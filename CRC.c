#include <stdio.h>
#include <string.h>

#define N strlen(gen_poly)

char data[28], check_value[28], gen_poly[10];
int data_length, i, j;

void XOR() {
    for (j = 1; j < N; j++)
        check_value[j] = (check_value[j] == gen_poly[j]) ? '0' : '1';
}

void crc() {
    for (i = 0; i < N; i++)
        check_value[i] = data[i];
    do {
        if (check_value[0] == '1')
            XOR();
        memmove(check_value, check_value + 1, N - 1);
        check_value[N - 1] = data[i++];
    } while (i <= data_length + N - 1);
}

void receiver() {
    printf("Enter the received data: ");
    scanf("%s", data);
    crc();
    printf((strchr(check_value, '1')) ? "\nError detected\n\n" : "\nNo error detected\n\n");
}

int main() {
    printf("\nEnter data to be transmitted: ");
    scanf("%s", data);
    printf("\nEnter the Generating polynomial: ");
    scanf("%s", gen_poly);

    data_length = strlen(data);
    strcat(data, "0000000000" + 10 - (N - 1));  // Add N-1 zeros

    crc();

    printf("\nCRC or Check value is: %s", check_value);
    strncpy(data + data_length, check_value, N - 1);

    printf("\nFinal data to be sent: %s\n", data);
    receiver();

    return 0;
}
