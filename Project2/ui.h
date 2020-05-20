#ifndef UI_H
#define UI_H
#include "file.h"

void print2(Info *info);
void print1(Info *info);
void read2(Info *info, int c, int *state);
void read3(FILE *file, Info *info);
void read1(Info *info);
char* flagcheck(char *argv[], Info *info, int *i, int *argc);

#endif
