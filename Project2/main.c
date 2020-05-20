#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "file.h"

Info setInfo()
{
   Info info;
   info.l = 0;
   info.w = 0;
   info.c = 0;
   info.lf = 0;
   info.wf = 0;
   info.cf = 0;
   info.s = 0;
   return info;
}
void flag(Info *info, char *argv[], int d)
{
   char c;
   c = argv[d][1];
   if(c == 99)
   {
      info->cf = 1; 
   }
   else if(c == 108)
   {
      info->lf = 1;
   }
   else if(c == 119)
   {
      info->wf = 1;
   }
   else
   {
      flag_error(argv, d);
   }
}
void setflag(Info *info, char *argv[], int *argc)
{
   int d = 0;
   while(argv[d] != NULL)
   {
      if(argv[d][0] == '-')
      {
         flag(info, argv, d);
      }
      d++;
   }
}
void checkArgs(int argc, char *argv[], Info *info)
{
   if(argc > 1)
   {
      setflag(info, argv, &argc);
      if(argc == 1)
      {
         read1(info);
      }
      else
      {
         file1(info, ++argv, argc);
      }
   }
   else
   {
      read1(info);
   }
}
int main(int argc, char *argv[])
{
   Info info = setInfo();
   checkArgs(argc, argv, &info);
   return 0;
}
