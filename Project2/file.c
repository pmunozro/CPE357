#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "ui.h"

void Error(char *argv)
{
   char str[100] = "swc: ";
   strcat(str,argv);
   perror(str);
}
void flag_error(char *argv[], int d)
{
   fprintf(stderr, "swc: invalid option: '%s'\n", argv[d]);
   fprintf(stderr, "Usage: swc [-l|-w|-c]... [file]...\n");
   exit(EXIT_FAILURE);
}
Info setDiv(Info *div, Info *info)
{
   div->l = 0;
   div->w = 0;
   div->c = 0;
   div->lf = info->lf;
   div->wf = info->wf;
   div->cf = info->cf;
   return *div;
}
void file2(Info *info, char *argv[], int *argc)
{
   FILE *fp;
   Info div = setDiv(&div, info);
   fp = fopen(*argv, "r");
   if(fp == NULL)
   {
      Error(*argv);
      info->s = 1;
   }
   else
   {
      read3(fp, &div);
      fclose(fp);
      print1(&div);
      printf(" %s\n", *argv);
   }
   info->c += div.c;
   info->w += div.w;
   info->l += div.l;
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
   extra(info, argc);
}
void extra(Info *info, int argc)
{
   if(argc == 1)
   {
      read1(info);
   }
   if(argc > 2)
   {
      print1(info);
      printf(" total\n");
   }
   if(info->s == 1)
   {
      exit(EXIT_FAILURE);
   }
   exit(EXIT_SUCCESS);
}
