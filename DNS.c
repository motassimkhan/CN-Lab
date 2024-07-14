 strcat(fs, x);
    for (i = 0; i < strlen(a); i++)
    {
        t[0] = a[i];
        t[1] = '\0';
        if (t[0] == sd)
        {
            strcat(fs, s); // Insert ending delimiter before the character
        }
        else if(t[0] == ed){
                strcat(fs,d);
        }
        strcat(fs, t); // Insert the character
    }
