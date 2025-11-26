#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* lens descriptor */
typedef struct lens
{
    float foclen;   /* focal length,mm */
    float fstop;    /* aperture        */
    char brand[30]; /* brand name      */
} LENS;

void question22()
{
    // part a
    LENS lenses[10];
    strcpy(lenses[2].brand, "Remarkatar");
    lenses[2].foclen = 500;
    lenses[2].fstop = 2.0;
    printf("Lens 2: brand %s, focal length %.0f, aperture f/%.1f\n",
           lenses[2].brand, lenses[2].foclen, lenses[2].fstop);

    // part b
    LENS lenses2[10] = {
        [2] = {500, 2.0, "Remarkatar"},
    };
    printf("Lens 2: brand %s, focal length %.0f, aperture f/%.1f\n",
           lenses2[2].brand, lenses2[2].foclen, lenses2[2].fstop);
}
