#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include "launcher.h"
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <libgen.h>

char* getPath(char *argv[])
{
   int i = 1;
   char *path;
   if(argv[i] != NULL)
      if(strcmp(argv[i], "-p") == 0)
         i += 2;

   path = malloc((strlen(argv[i]) + 1) * sizeof(char));
   if(path == NULL)
      exit(EXIT_FAILURE);
   strcpy(path, argv[i]);
   return path;
}

void last_one(int val, char *fread, char *path, int fd[])
{
   int i, status;
   pid_t pid;
   if((pid = fork()) < 0)
   {
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   else if(pid == 0)
   {
      close(fd[1]);
      execl(path, basename(path), "-i", fread, "-o", "1", (char*)NULL);
      fprintf(stderr, "exec failure");
      exit(EXIT_FAILURE);
   }
   else
   {
      free(path);
      free(fread);
      close(fd[1]);
      close(fd[0]);
      for(i = 0; i < val; i++)
         wait(&status);
   }
}

void do_it(int i, char *path)
{
   char read[2];
   if(i%2 == 1)
   {
      sprintf(read, "%d", 3);
      close(4);
   }
   else
   {
      sprintf(read, "%d", 4);
      close(3);
   }
   execl(path, basename(path), "-i", read, "-o", "5", (char*)NULL);
   fprintf(stderr, "exec failure");
   exit(EXIT_FAILURE);
}

void push_birth(int i, char *fread, int fd[], char *path)
{
   pid_t pid;
   close(fd[1]);
   pipe(fd);
   sprintf(fread, "%d", fd[0]);
   if((pid = fork()) < 0)
   {
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   else if(pid == 0)
   {
      do_it(i, path);
   }
   else
   {
      if(i%2 == 1)
         close(3);
      else
         close(4);
   }
}
void give_birth(int val, char *fread, char *path, int fd[])
{
   int i;
   for(i = 1; i < val - 1; i++)
   {
      push_birth(i, fread, fd, path);
   }
}

void create_process(int val, char *argv[])
{
   int fd[2];
   pid_t pid;
   char *fread = malloc(2 * sizeof(char)); 
   char *path = getPath(argv);
   pipe(fd);
   sprintf(fread, "%d", fd[0]);
   if((pid = fork()) < 0)
   {
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   else if(pid == 0)
   {
      close(fd[0]);
      execl(path, basename(path), "-i", "0", "-o", "4", (char*)NULL);
      fprintf(stderr, "exec failure");
      exit(EXIT_FAILURE);
   }
   else
   {
      give_birth(val, fread, path, fd);
   }
   last_one(val, fread, path, fd);
}

