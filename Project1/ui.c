#include <stdio.h>
#include "ui.h"

int seed()
{
   int d;
   char str[100];
   printf("Enter the seed for random number generation: ");
   if(scanf(" %d", &d) == 0)
   {
      printf("Seed must be an integer value, please try again\n");
      scanf("%[^\n]", str);
      d = seed();
   }
   scanf("%[^\n]", str);
   return d;
}
int max()
{
   char c;
   char str[100];
   printf("Enter the maximum letter for the game (A-Z): ");
   scanf(" %c", &c);
   if((int)c > 90 || (int)c < 65)
   {
      printf("The letter must be an uppercase A-Z, please try again\n");
      scanf("%[^\n]", str);
      c = max();
   }
   scanf("%[^\n]", str);
   return (int)c;
}
int positions()
{
   int d = 0;
   char str[100];
   printf("Enter the number of positions for the game (1-8): ");
   scanf(" %d", &d);
   if(d > 8 || d < 1)
   {
      printf("The number of positions must be 1-8, please try again\n");
      scanf("%[^\n]", str);
      d = positions();
   }
   scanf("%[^\n]", str);
   return d;
}
int guesses()
{
   int d = 0;
   char str[100];
   printf("Enter the number of guesses allowed for the game: ");
   scanf(" %d", &d);
   if(d < 1)
   {
      printf("The number of guesses must be a positive integer,");
      printf(" please try again\n");
      scanf("%[^\n]", str);
      d = guesses();
   }
   scanf("%[^\n]", str);
   return d;
}

