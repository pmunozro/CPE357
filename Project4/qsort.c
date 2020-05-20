#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getWord.h"
#include "hashTable.h"

int cmpfunc(const void * a, const void * b)
{
   int diff = 0;
   HTEntry *htentryA = (HTEntry *)a;
   HTEntry *htentryB = (HTEntry *)b;
   
   diff = htentryB->frequency - htentryA->frequency;
   if(diff == 0 && htentryB->data != NULL)
   {
      diff = strcmp(htentryA->data, htentryB->data);
   }
   return diff;
}
void qsortHTEntries(HTEntry *entries, int numberOfEntries)
{
   qsort(entries, numberOfEntries, sizeof(HTEntry), cmpfunc);
}
