/* include libraries */
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
   if (argc < 2) {
      fprintf(stderr, "Usage: %s <input>\n", argv[0]);
      exit(1);
   }
   printf("%s\n", argv[1]);
}
