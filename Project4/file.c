#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "ui.h"

void Error(char *argv)
{
   char str[100] = "wf: ";
   strcat(str,argv);
   perror(str);
}
void flag_error(char *argv[], int d)
{
   fprintf(stderr, "wf: invalid option: '%s'\n", argv[d]);
   fprintf(stderr, "Usage: wf [-nX] [file...]\n");
   exit(EXIT_FAILURE);
}
void file2(Info *info, char *argv[], int *argc)
{
   FILE *fp;
   fp = fopen(*argv, "r");
   if(fp == NULL)
   {
      Error(*argv);
      /*info->s = 1;*/
   }
   else
   {
      read3(fp, info);
      fclose(fp);
   }
}
void file1(Info *info, char *argv[], int argc)
{
   int i = 1;
   while(*argv != '\0')
   {
      if(i != 0)
      {
         i = 0;
         *argv = flagcheck(argv, info, &i, &argc);
         if(i == 0)
         {
            --argv;
         }
      }
      else
      {
         file2(info, argv, &argc);
         i = 1;
      }
      argv++;
   }
}
