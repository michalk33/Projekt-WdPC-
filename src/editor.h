#ifndef EDITOR_H
#define EDITOR_H

#include "game.h"


#define wait_time 50


int columnNumber();
int rowNumber();

void runEditor( int * wtime, int * xc, int * yc, board * B, int * mb, tile_type * cht, tile_type ** tltps );

#endif
