#ifndef GAME_H
#define GAME_H

typedef struct
{
   int seed;
   int max;
   int pos;
   int guess;
   int show;
}Board;

void disp(Board board, char *g);
void make_array(Board board, char *g);
void compare(Board board, char *u, char *g, int *guess);
void find_exact(Board board, char *u, char *cp, int *exact);
void find_inexact(Board board, char *u, char *cp, int *inexact);
void lose();
void win(int *guess);

#endif
