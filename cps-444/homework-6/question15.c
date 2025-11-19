#include <stdio.h>

int contains(const char *str, char c)
{
    char *ptr = str;
    while (*ptr != '\0')
    {
        if (*ptr == c)
            return 1;
        ++ptr;
    }
    return 0;
}

void question15()
{
    const char *searches = "abcdefghijklmnopqrstuvwxyz";
    const char *str = "Philadelphia hippopotamus";

    char *ptr = searches;
    while (*ptr != '\0')
    {
        int res = contains(str, *ptr);
        printf("%d", res);
        ++ptr;
    }

    printf("\n");
}
