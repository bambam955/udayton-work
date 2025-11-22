#include <stdio.h>

const char *find_char(const char *str, char c)
{
    const char *ptr = str;
    while (*ptr != '\0')
    {
        if (*ptr == c)
            return ptr;
        ++ptr;
    }
    return NULL;
}

void question14()
{
    const char *searches = "abcdefghijklmnopqrstuvwxyz";
    const char *str = "Philadelphia hippopotamus";

    const char *ptr = searches;
    while (*ptr != '\0')
    {
        const char *res = find_char(str, *ptr);
        if (res != NULL)
            printf("%c", *res);
        ++ptr;
    }

    printf("\n");
}
