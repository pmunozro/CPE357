#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include "hashTable.h"
#include "getWord.h"
#define MAX_ENTRIES 1000
#define MAX_WORDLEN 14 
#define MAX_FREQ 10 

void addWord(HTEntry *entries, Byte *word, Info *info, int wordLength)
{
   int i, j = 0;
   for (i = 0; i < info->unique && info->total != 0; i++)
   {
      if(strcmp(entries[i].data, (char *)word) == 0)
      {
         j = 1;
         entries[i].frequency += 1;
      }
   }
   if(j == 0)
   {
      entries[i].data = word;
      entries[i].frequency = 1;
      entries[i].wordLength = wordLength;
      info->unique += 1;
   }
   info->total += 1;
}
void print(Byte *word, unsigned wordLength)
{
   int i;
   for(i = 0; i < wordLength && i < 30;i++)
   {
      if(isprint(word[i]))
         printf("%c", word[i]);
      else
         printf("%c", '.');
   }
   if(wordLength > 30)
      printf("...");
}
void printWords(HTEntry *entries, Info *info)
{
   int i;
   printf("%d unique words found in %d total words\n", 
      info->unique, info->total);
   for (i = 0; i < info->unique && i < info->nf; i++)
   {
      printf("%10u - ", entries[i].frequency);
      print(entries[i].data, entries[i].wordLength);
      printf("\n");
   }
}
