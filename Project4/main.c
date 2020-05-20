#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "file.h"
#include "getWord.h"
#include "hashTable.h"

Info setInfo()
{
   Info info;
   info.total = 0;
   info.w = 0;
   info.unique = 0;
   info.nf = 10;
   info.wf = 0;
   info.cf = 0;
   info.s = NULL;
   return info;
}
void flag(Info *info, char *argv[], int d)
{
   char c;
   int n;
   c = argv[d][1];
   if(c == 'n')
   {
      n = argv[d][2];
      info->nf = n - 48;
      strcpy(info->s,argv[d]);
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
