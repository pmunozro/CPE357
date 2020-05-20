#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <libgen.h>
#include <sys/types.h>
#include <signal.h>
#include "other.h"

void error(int *k)
{
   if(*k == 1)
      fprintf(stderr, "cshell: Invalid pipe\n");
   else
      fprintf(stderr, "cshell: Syntax error\n");
}
int check2(int *k, char *word)
{
   int f = 1;
   if(word == NULL)
   {
      f = 0;
   }
   else
   {
      if(strcmp(word, "|") == 0)
         f = 0;
      else if(strcmp(word, "<") == 0)
         f = 0;
      else if(strcmp(word, ">") == 0)
         f = 0;
   }
   if(f == 0)
   {
      error(k);
      return 0;
   }
   return 1;
}
int check3(CLine *cl, int *d, int *i, char *word, int *k)
{
   int inFD;
   int outFD;
   word = strtok(NULL, " \n");    
   if(!check2(k, word))
      return 0;    
   if(*k == 1)
   {             
      cl[*d].args[*i] = word;
      (*i)++;
   }            
   else if(*k == 2)
   {           
      if((inFD = openFile(word, "r")) < 0)
         return 0;         
      cl[*d].in = inFD;
   }                 
   else if(*k == 3)
   {              
      if((outFD = openFile(word, "w")) < 0)
         return 0;                           
      cl[*d].out = outFD;              
   }
   return 1;
}
int check(CLine *cl, int *d, int *i, char *word, int *k)
{
   if(*k == 0)
   {
      cl[*d].args[*i] = word;
      (*i)++;
   }
   else
   {
      if(!check3(cl, d, i, word, k))
         return 0;
      *k = 0;
   }
   if(*i > 11)
   {
      fprintf(stderr, "cshell: %s: Too many arguments\n", cl[*d].args[0]);
      return 0;
   }
   if(*d > 19)
   {
      fprintf(stderr, "cshell: Too many commands\n");
      return 0;
   }
   return 1;
}
int parse2(CLine *cl, int *d, int *i, char *word, int *k)
{
   if(strcmp(word, "|") == 0)
   {
      (*d)++;
      *i = 0;
      *k = 1;
   }
   else if(strcmp(word, "<") == 0)
   {
      *k = 2;
   }
   else if(strcmp(word, ">") == 0)
   {
      *k = 3;
   }
   if(!check(cl, d, i, word, k))
      return 0;
   return 1;
}
void parse(char *line, CLine *cl)
{
   char *word;
   int i = 0;
   int d;
   int k = 0;
   int p = 0;
   d = 0;
   word = strtok(line, " \n");
   while(word != NULL)
   {
      if((p = parse2(cl, &d, &i, word, &k)) == 0)
         break;
      word = strtok(NULL, " \n");
   }
   if(p == 1)
      execute(cl, d);
}

void clear(CLine *cl)
{
   int d;
   for(d = 0; d < 25; d++)
      free(cl[d].args);
   free(cl);
}
CLine* set(CLine *cl)
{
   int d;
   cl = malloc(sizeof(CLine*) * 100);
   for(d = 0; d < 25; d++)
      cl[d].args = malloc(sizeof(CLine*) * 50);
   return cl;
}
int get_line(CLine *cl)
{
   int c;
   int p = 1;
   char line[1100];
   setbuf(stdout, NULL);
   printf(":-) ");
   cl = set(cl);
   fgets(line, 1100, stdin);
   if(feof(stdin))
   {
      printf("exit\n");
      clear(cl);
      return 0;
   }
   if(strcmp(line, "exit\n") == 0)
   {
      clear(cl);
      return 0;
   }
   if(strlen(line) > 1023)
   {
      fprintf(stderr, "cshell: Command line too long\n");
      p = 0;
      clear(cl);
   }
   if(p == 1)
   {
      parse(line, cl);
   }
   else
      while((c = getchar()) != '\n' && c != EOF);
   return 1;
}
int main()
{
   CLine *cl = NULL;
   while(get_line(cl));
   return 0;
}
