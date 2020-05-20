#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "ui.h"
#include "getWord.h"
#include "hashTable.h"
#define IN 1
#define OUT 0
#define MAX_ENTRIES 10000

void read3(FILE *file, Info *info)
{
   HTEntry entries[MAX_ENTRIES];
   Byte *word = NULL;
   unsigned wordLength = 0;
   int hasPrintable = 0;
   while(getWord(file, &word, &wordLength, &hasPrintable) != EOF)
   {
      addWord(entries, word, info, wordLength);
   }
   qsortHTEntries(entries, info->total);
   printWords(entries, info);
}
void read1(Info *info)
{
   HTEntry entries[MAX_ENTRIES];
   Byte *word = NULL;
   unsigned wordLength = 0;
   int hasPrintable = 0;
   while(getWord2(&word, &wordLength, &hasPrintable) != EOF)
   {
      addWord(entries, word, info, wordLength);
   }
   qsortHTEntries(entries, info->total);
   printWords(entries, info);
}
char* flagcheck(char *argv[], Info *info, int *i, int *argc)
{
   if(strcmp(*argv, "-n") == 0)
   {
      *i = 1;
      --*argc;
   }
   return *argv;
}

