/* include libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 126

int main (int argc, char *argv[])
{
   if (argc < 2) return 1;
   char buffer[BUF_SIZE];

   // Validate input before using it
   if (strnlen(argv[1], BUF_SIZE) >= BUF_SIZE)
   {
      fputs("Input is too long", stderr);
      exit(1);
   }
   strncpy(buffer, argv[1], BUF_SIZE);
   printf("%s\n", buffer);
   return 0;
}
