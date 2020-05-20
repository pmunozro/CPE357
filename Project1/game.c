#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "game.h"
#include "ui.h"

void disp(Board board, char *g)
{
   int i;
   printf("Initialized Game Board: ");
   for(i = 0; i < board.pos; i++)
   {
      printf("%c", g[i]);
   }
   printf("\n");
}
void make_array(Board board, char *g)
{
   int i;
   srand(board.seed);
   for(i = 0; i < board.pos; i++)
   {
      g[i] = (rand()%(board.max-64)) + 65;
   }
}
void compare(Board board, char *u, char *g, int *guess)
{
   int exact = 0, inexact = 0;
   char cp[9];
   strncpy(cp, g, board.pos);
   find_exact(board, u, cp, &exact);
   find_inexact(board, u, cp, &inexact);
   if(exact == board.pos)
   {
      win(guess);
   }
   else
   {
      printf("Nope, %d exact guesses and %d inexact guesses\n", exact, inexact);
   }
}
void find_exact(Board board, char *u, char *cp, int *exact)
{
   int i;
   for(i = 0; i < board.pos; i++)
   {
      if(u[i] == cp[i])
      {
         *exact += 1;
         cp[i] = '\0';
         u[i] = 'a';
      }
   }
}
void find_inexact(Board board, char *u, char *cp, int *inexact)
{
   int i, j;
   for(i = 0; i < board.pos; i++)
   {
      for(j = 0; j < board.pos; j++)
      {
         if(u[i] == cp[j])
         {
            *inexact += 1;
            cp[j] = '\0';
            j = board.pos;
         }
      }
   }
}
void lose()
{
   printf("\nGame over, you ran out of guesses. Better luck next time!\n");
   exit(0);
}
void win(int *guess)
{
   *guess -= 1;
   printf("\nWow, you won in %d guesses - well done!\n", *guess);
   exit(0);
}
