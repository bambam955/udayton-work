#include <stdio.h>

struct name
{
    char first[20];
    char last[20];
};
struct bem
{
    int limbs;
    struct name title;
    char type[30];
};

void print_bem(struct bem *deb)
{
    printf("%s %s is a %d-limbed %s.\n", deb->title.first, deb->title.last, deb->limbs, deb->type);
}

void question23()
{
    struct bem *pb;
    struct bem deb = {
        6,
        {"Berbnazel", "Gwolkapwolk"},
        "Arcturan"

    };

    pb = &deb;

    // part a
    printf("%d\n", deb.limbs);
    printf("%s\n", pb->type);
    printf("%s\n", pb->type + 2);

    // part c
    print_bem(pb);
}
