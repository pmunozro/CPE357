#ifndef GETWORD_H
#define GETWORD_H
#include <stdio.h>
#include "ui.h"
typedef unsigned char Byte;

int getWord(FILE *file, Byte **word, unsigned *wordLength, int *hasPrintable);
int getWord2(Byte **word, unsigned *wordLength, int *hasPrintable);

#endif

