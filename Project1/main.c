#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "game.h"

Board setBoard(int show)
{
   Board board;
   board.show = show;
   board.seed = seed();
   board.max = max();
   board.pos = positions();
   board.guess = guesses();
   return board;
}
void printError()
{
   fprintf(stderr, "Usage: mastermind [-show]\n");
   exit(EXIT_FAILURE);
}
int display(int argc, char *argv[])
{
   int show = 0;
   if(argc > 2)
   {
      printError();   
   }
   if(argc > 1)
   {
      if(!strcmp(argv[1], "-show"))
      {
         show = 1;   
      }
      else
      {
         printError();
      }
   }
   return show;
}
int valid(Board board, char *u)
{
   int i;
   int val = 0;
   for(i = 0; i < board.pos; i++)
   {
      if((int)u[i] > board.max || (int)u[i] < 65)
      {
         printf("Invalid guess, please try again\n");
         val = 1; 
         break;
      }
   }
   return val;
}
void user(Board board, char *g, int *guess)
{
   char u[9];
   char str[100];
   int i = 0, val = 0;
   while(i < board.pos)
   {
      scanf(" %c", &u[i]);
      i++;
   }
   scanf("%[^\n]", str);
   val = valid(board, u);
   if(val == 0 )
   {
      *guess += 1;
      compare(board, u, g, guess);
   }
}
void playgame(Board board, char *g)
{
   int i = 1;
   if(board.show == 1)
   {
      disp(board, g);
   }
   while(i <= board.guess)
   {
      printf("\nEnter guess %d: ", i);
      user(board, g, &i);
   }
   lose();
}
int main(int argc, char *argv[])
{
   Board board;
   char g[9];
   int show = display(argc, argv);
   board = setBoard(show);
   make_array(board, g);
   playgame(board, g);
   return 0;
}
