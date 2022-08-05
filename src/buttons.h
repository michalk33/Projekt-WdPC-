#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdbool.h>
#include <allegro.h>

#include "game.h"

typedef struct BUTTON{
    int x, y, w, h;
    const char * name;
} button;

typedef struct SLOT{
    int x, y;
    tile_type * tltp;
} slot;

bool mouseOnButton( button * B );

bool mouseOnSlot( slot * S );

void showButton( button * B, BITMAP * buffer );

void showSlot( slot * S, BITMAP * buffer, tile_type * tltp, BITMAP * bmpp );

void createButton( button * B, int nx, int ny, int nw, int nh, const char * nname );

void createSlot( slot * S, int nx, int ny, tile_type * ntltp );

#endif
