#ifndef FILE_H
#define FILE_H

typedef struct
{
   int l, c, w;
   int lf, cf, wf;
   int s;
}Info;


void Error(char *argv);
void flag_error(char *argv[], int d);
Info setDiv(Info *div, Info *info);
void skip(char *argv[], int *i);
void file1(Info *info, char *argv[], int argc);
void file2(Info *info, char *argv[], int *argc);
void extra(Info *info, int argc);

#endif
