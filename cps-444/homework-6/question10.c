#include <stdio.h>

char *pr(char *str)
{
    char *pc;

    pc = str;
    while (*pc)
        putchar(*pc++);
    do
    {
        putchar(*--pc);
    } while (pc - str);
    return (pc);
}

void question10()
{
    const char *x = pr("Ho Ho Ho!");
    printf("\n%s\n", x);
}