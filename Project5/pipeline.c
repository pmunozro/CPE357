#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "launcher.h"

void error()
{
   fprintf(stderr, "Usage: pipeline path -p processes\n");
   fprintf(stderr, "Where: path is some \"random child\"");
   fprintf(stderr, " and processes is 2 to 10, inclusive\n");
   exit(EXIT_FAILURE);
}

int check3(char *argv[], int *val, int i)
{
   if(1 == sscanf(argv[i+1], "%d", val))
      if(*val > 1 && *val < 11)
      {
         create_process(*val, argv);
         return 1;
      }
   return 0;
}
int check2(char *argv[], int i, int *val)
{
   if(0 == strcmp(argv[i], "-p"))
   {
      if(argv[i+1] != NULL)
         if(check3(argv, val, i) == 1)
            return 1;
   }
   return 0;
}

void checkArg(char *argv[], int *val)
{
   int i;
   for(i = 1; argv[i] != NULL; i++)
   {
      if(check2(argv, i, val) == 1)
         return;
   }
   error();
}
int main(int argc, char *argv[])
{
   int val;
   if(argc != 4)
   {
      error();
   }
   checkArg(argv, &val);
   /*create_process(val, argv);*/
   return 0;
}
