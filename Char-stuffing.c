#include <stdio.h>
#include <string.h>

int main()
{
    char a[30], fs[60] = "", t[3], sd, ed, x[3], s[3], d[3], y[3];
    int i;

    printf("Enter the characters: ");
    scanf("%s", a);
    getchar();
    printf("Enter char for starting delimiter: ");
    scanf("%c", &sd);
    getchar();
    printf("Enter char for ending delimiter: ");
    scanf("%c", &ed);

    x[0] = s[0] = s[1] = sd;
    x[1] = s[2] = '\0';
    y[0] = d[0] = d[1] = ed;
    d[2] = y[1] = '\0';

    strcat(fs, x);
    for (i = 0; i < strlen(a); i++)
    {
        t[0] = a[i];
        t[1] = '\0';
        if (t[0] == sd)
        {
            strcat(fs, s);
        }
        else if (t[0] == ed)
        {
            strcat(fs,d);
        }
        strcat(fs, t);
    }
    strcat(fs, y); // Ending with the ending delimiter

    printf("\nAfter Stuffing: %s\n", fs);
    return 0;
}

