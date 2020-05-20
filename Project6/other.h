#ifndef OTHER_H
#define OTHER_H

typedef struct
{
   char **args;
   int in, out;
}CLine;

int openFile(const char *filename, const char *mode);
void execute(CLine *cl, int d);

#endif
