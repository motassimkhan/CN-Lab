#include <stdio.h>
#include <string.h>

#define N strlen(gen_poly)

char data[28], check_value[28], gen_poly[10];
int data_length, i, j;

void XOR()
{
    for (j = 1; j < N; j++)
        check_value[j] = (check_value[j] == gen_poly[j]) ? '0' : '1';
}

void crc()
{
    for (i = 0; i < N; i++)
        check_value[i] = data[i];
    do
    {
        if (check_value[0] == '1')
            XOR();
        memmove(check_value, check_value + 1, N - 1);
        check_value[N - 1] = data[i++];
    } while (i <= data_length + N - 1);
}

int main()
{
    printf("\nEnter data to be transmitted: ");
    scanf("%s", data);
    printf("\nEnter the Generating polynomial: ");
    scanf("%s", gen_poly);

    data_length = strlen(data);
    for(int i = 1; i< strlen(gen_poly); i++)
    {
        strcat(data,"0");
    }
    //strcat(data, "0000000000" + 10 - (N - 1));

    crc();

    printf("\nCRC or Check value is: %s", check_value);
    strncpy(data + data_length, check_value, N - 1);

    printf("\nFinal data to be sent: %s\n", data);

    return 0;
}