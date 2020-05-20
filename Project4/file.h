#ifndef FILE_H
#define FILE_H

typedef struct
{
   int total, unique, w;
   int nf, cf, wf;
   char *s;
}Info;


void Error(char *argv);
void flag_error(char *argv[], int d);
void skip(char *argv[], int *i);
void file1(Info *info, char *argv[], int argc);
void file2(Info *info, char *argv[], int *argc);

#endif
