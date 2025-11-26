#include <stddef.h>
#include <stdio.h>

const char *mystrncpy(char s1[], const char s2[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        if (s2 + i != NULL)
        {
            s1[i] = s2[i];
        }
        else
        {
            s1[i] = '\0';
        }
    }

    return s1;
}

void question16()
{
    const char *inputs[3] = {"i detest all cats", "dogs", "Lemurs from Madagascar"};
    for (int i = 0; i < 3; ++i)
    {
        char copy[15] = {0};
        mystrncpy(copy, inputs[i], 10);
        puts(copy);
    }
}
