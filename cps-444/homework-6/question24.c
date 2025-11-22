#include <stdlib.h>

struct gas
{
    float distance;
    float gals;
    float mpg;
};

// part a
struct gas calc_mpg(struct gas g)
{
    const float mpg = g.distance / g.gals;
    g.mpg = mpg;
    return g;
}

// part b
struct gas *calc_mpg_addr(struct gas *g)
{
    const float mpg = g->distance / g->gals;
    g->mpg = mpg;
    return g;
}

void question24()
{
    // part a
    struct gas g = {200, 10};
    g = calc_mpg(g);
    printf("%.1f miles, %.1f gals, %.2f mpg\n", g.distance, g.gals, g.mpg);

    // part b
    struct gas *g2 = malloc(sizeof(struct gas));
    g2->distance = 300;
    g2->gals = 3;
    g2 = calc_mpg_addr(g2);
    printf("%.1f miles, %.1f gals, %.2f mpg\n", g2->distance, g2->gals, g2->mpg);
}
