#include <stdio.h>
#include <string.h>

void question8()
{
    char food[] = "Yummy";
    char *ptr;

    ptr = food + strlen(food);
    while (--ptr >= food)
        puts(ptr);
}
