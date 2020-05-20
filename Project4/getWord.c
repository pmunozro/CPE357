#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "getWord.h"
#define OUT 0
#define IN 1

void check(Byte **word)
{
   if(*word == NULL)
   {
      fprintf(stderr, "Cannot allocate memory\n");
      exit(EXIT_FAILURE);
   }
}

int sweep(FILE *file)
{
   int c;
   c = fgetc(file);
   while(isspace(c))
   {
      c = fgetc(file);
   }
   return c;
}
void modify(int *hasPrintable, unsigned *wordLength, int c, Byte **word,
   size_t *size)
{
   if(isprint(c))
   {
      *hasPrintable = 1;
   }
   *wordLength += 1;
   if(*wordLength == *size)
   {
      *size *= 255;
      *word = realloc(*word, *size);
   }
}
int getWord2(Byte **word, unsigned *wordLength, int *hasPrintable)
{
   int c, i = 0, state = 0;
   size_t size = 32;
   *word = malloc(size);
   check(word);
   *wordLength = 0;
   *hasPrintable = 0;
   while((c = getchar()) != EOF)
   {
      if(isspace(c))
      {
         if(state == IN)
         {   
            break;
            state = OUT;
         }
      }
      else
      {
         (*word)[i++] = tolower(c);
         modify(hasPrintable, wordLength, c, word, &size);
         state = IN;
      }
   }
   *word = realloc(*word, *wordLength);
   return c;
}
int getWord(FILE *file, Byte **word, unsigned *wordLength, int *hasPrintable)
{
   int c;
   int i = 0;
   size_t size = 32;
   *word = malloc(size);
   check(word);
   *hasPrintable = 0;
   *wordLength = 0;
   c = sweep(file);
   while(c != EOF)
   {
      if(isspace(c))
      {
         break;
      }
      else
      {
         (*word)[i++] = tolower(c);
         modify(hasPrintable, wordLength, c, word, &size);
      }
      c = fgetc(file);
   }
   *word = realloc(*word, *wordLength);
   return c;
}
