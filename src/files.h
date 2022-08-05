#ifndef FILESPROJECT_H
#define FILESPROJECT_H

#include "game.h"

void saveToFile( board * B, int n );
void readFromFileE( board * B, int n, tile_type ** tltps );
void readFromFileG( board * B, int n, tile_type ** tltps );

#endif
