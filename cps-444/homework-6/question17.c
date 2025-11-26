#include <stdio.h>

int index_of(const char s1[], const char s2[])
{
    const char *s1_ptr = s1;
    while (*s1_ptr)
    {
        int s2_index;
        while (*(s2 + s2_index))
        {
            if (*(s2 + s2_index) != *(s1_ptr + s2_index))
                break;
            s2_index++;
        }
        if (*(s2 + s2_index) == 0)
        {
            return s1_ptr - s1;
        }
        s1_ptr++;
    }

    return -1;
}

void question17()
{
    const char *inputs[3] = {"i detest all cats", "dogs", "Lemurs from Madagascar"};
    const char *searches[3] = {"detest", "cats", "from Mad"};
    for (int i = 0; i < 3; ++i)
    {
        printf("%d\n", index_of(inputs[i], searches[i]));
    }
}
