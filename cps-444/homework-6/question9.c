#include <stdio.h>
#include <string.h>

void question9()
{
    char goldwyn[40] = "art of it all ";
    char samuel[40] = "I read p";
    const char *quote = "the way through.";

    strcat(goldwyn, quote);
    strcat(samuel, goldwyn);
    puts(samuel);
}
