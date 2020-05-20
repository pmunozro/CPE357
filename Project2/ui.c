#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ui.h"
#define IN 1
#define OUT 0

void print2(Info *info)
{
   if(info->lf == 1)
   {
      printf("%10u", info->l);
      if(info->wf == 1 || info->cf == 1)
      {
         printf(" ");
      }
   }
   if(info->wf == 1)
   {
      printf("%10u", info->w);
      if(info->cf == 1)
      {
         printf(" ");
      }
   }
   if(info->cf == 1)
   {
      printf("%10u", info->c);
   }
}
void print1(Info *info)
{
   if(info->lf == info->wf && info->lf == info->cf)
   {
      printf("%10u %10u %10u", info->l, info->w, info->c);
   }
   else
   {
      print2(info);
   }
}
void read2(Info *info, int c, int *state)
{
   info->c++;
   if(c == '\n')
   {
      info->l++;
   }
   if(isspace(c))
   {
      *state = OUT;
   }
   else if(*state == OUT && isprint(c))
   {
      *state = IN;
      info->w++;
   }
}
void read3(FILE *file, Info *info)
{
   int c;
   int state = OUT;
   while((c = getc(file)) != EOF)
   {
      read2(info, c, &state);
   }
}
void read1(Info *info)
{
   int c;
   int state = OUT;
   while((c = getchar()) != EOF)
   {
      read2(info, c, &state);
   }
   print1(info);
   printf("\n");
}
char* flagcheck(char *argv[], Info *info, int *i, int *argc)
{
   if(strcmp(*argv, "-c") == 0)
   {
      info->cf = 1;
      *i = 1;
      --*argc;
   }
   if(strcmp(*argv, "-l") == 0)
   {
      info->lf = 1;
      *i = 1;
      --*argc;
   }
   if(strcmp(*argv, "-w") == 0)
   {
      info->wf = 1;
      *i = 1;
      --*argc;
   }
   return *argv;
}

