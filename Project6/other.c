#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <libgen.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include "other.h"
#include "launcher.h"

int openFile(const char *fileName, const char *mode)
{
   int fd, flags;

   if (0 == strcmp("r", mode))
      flags = O_RDONLY;
   else if (0 == strcmp("w", mode))
   {
      flags = O_WRONLY | O_CREAT | O_TRUNC;
   }
   if (-1 == (fd = open(fileName, flags, 0666)))
   {
      fprintf(stderr, "cshell: Unable to open file for input\n");
   } 
   return fd;
}

void only_child(CLine *cl, int d)
{
   pid_t pid;
   /*int status;*/
   if((pid = fork()) < 0)
   {
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   else if(pid == 0)
   {
      
      if(cl[d].in > 0)
      {
         dup2(cl[d].in, STDIN_FILENO);
         close(cl[d].in);
      }
      if(cl[d].out > 0)
      {
         dup2(cl[d].out, STDOUT_FILENO);
         close(cl[d].out);
      }
      if(execvp(cl[d].args[0], cl[d].args) < 0)
         fprintf(stderr, "cshell: %s: Command not found\n", cl[d].args[0]);
   }
   else
   {
      wait(NULL);
   }
}
void execute(CLine *cl, int d)
{
   if(d == 0)
      only_child(cl, d);
   else
      create_process(d, cl);
}
