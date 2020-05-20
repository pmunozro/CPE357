#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include "launcher.h"
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <libgen.h>
#include "other.h"

void parent(CLine *cl, int child)
{
   if(cl[child].in > 0)
      close(cl[child].in);
   if(cl[child].out > 0)
      close(cl[child].out);
}
void last_child(CLine *cl, int child, int fd[])
{
   close(fd[1]);
   if(cl[child].in > 0)
   {
      dup2(cl[child].in, STDIN_FILENO);
      close(cl[child].in);
   }
   else
   {
      dup2(fd[0], STDIN_FILENO);
      close(fd[0]);
   }
   if(cl[child].out > 0)
   {
      dup2(cl[child].out, STDOUT_FILENO);
      close(cl[child].out);
   }
   if(execvp(cl[child].args[0], cl[child].args) < 0)
      fprintf(stderr, "cshell: %s: Command not found\n", cl[child].args[0]);
}
void last_one(int val, CLine *cl, int fd[], int child)
{
   int i, status;
   pid_t pid;
   child++;
   if((pid = fork()) < 0)
   {
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   else if(pid == 0)
   {
      last_child(cl, child, fd);
   }
   else
   {
      /*printf("parent closing: %d %d\n", fd[1], fd[0]);*/
      close(fd[1]);
      close(fd[0]);
      parent(cl, child);
      for(i = 0; i < val + 1; i++)
         wait(&status);
   }
}

void do_it(int i, CLine *cl, int child, int fd[], int old)
{
   close(fd[0]);
   /*printf("child closing %d\n", fd[0]);*/
   if(cl[child].in > 0)
   {
      dup2(cl[child].in, STDIN_FILENO);
      close(cl[child].in);
   }
   else
   {
      dup2(old, STDIN_FILENO);
      close(old);
   }
   /*printf("writing to %d\n", fd[1]);*/
   if(cl[child].out > 0)
   {
      /*printf("cl[child] = %d\n", cl[child].out);*/
      dup2(fd[1], STDOUT_FILENO);
      close(cl[child].out);
   }
   else
   {
      dup2(fd[1], STDOUT_FILENO);
      close(fd[1]);
   }
   /*printf("before exec\n");*/
   if(execvp(cl[child].args[0], cl[child].args) < 0)
      fprintf(stderr, "cshell: %s: Command not found\n", cl[child].args[0]);
}

void push_birth(int i, int fd[], CLine *cl, int child)
{
   pid_t pid;
   int old = fd[0];
   /*printf("parent has: %d %d\n", fd[1], fd[0]);*/
   close(fd[1]);
   pipe(fd);
   /*printf("parent now has: %d %d\n", fd[1], fd[0]);*/
   if((pid = fork()) < 0)
   {
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   else if(pid == 0)
   {
      do_it(i, cl, child, fd, old);
   }
   else
   {
      close(old);
      parent(cl, child);
   }
}
int give_birth(int val, CLine *cl, int fd[], int child)
{
   int i;
   for(i = 1; i < val; i++)
   {
      child++;
      push_birth(i, fd, cl, child);
   }
   return child;
}

void create_process(int val, CLine *cl)
{
   int fd[2];
   pid_t pid;
   int child = 0;
   pipe(fd);
   if((pid = fork()) < 0)
   {
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   else if(pid == 0)
   {
      /*printf("child1 closing %d\n", fd[0]);*/
      close(fd[0]);
      if(cl[child].in > 0)
      {
         dup2(cl[child].in, STDIN_FILENO);
         close(cl[child].in);
      }
      if(cl[child].out > 0)
      {
         dup2(cl[child].out, STDOUT_FILENO);
         close(cl[child].out);
      }
      else
      {
         dup2(fd[1], STDOUT_FILENO);
         close(fd[1]);
      }
      if(execvp(cl[child].args[0], cl[child].args) < 0)
         fprintf(stderr, "cshell: %s: Command not found\n", cl[child].args[0]);
   }
   else
   {
      parent(cl, child);
      child = give_birth(val, cl, fd, child);
   }
   last_one(val, cl, fd, child);
}

