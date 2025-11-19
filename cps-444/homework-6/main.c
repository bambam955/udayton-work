#include <stdio.h>
#include "mydefs.h"

#define NUM_QUESTIONS 8

int main()
{
    for (int i = 0; i < NUM_QUESTIONS; ++i)
    {
        printf("\n===== QUESTION %d =====\n", i + 1);
        questions[i]();
    }
    return 0;
}
