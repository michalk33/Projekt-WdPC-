#ifndef RENDER_H
#define RENDER_H

#include <allegro.h>

#include "buttons.h"
#include "game.h"

#define bmps_to_load 21
#define tile_size 40
#define window_x 800
#define window_y 600
#define board_x 600
#define board_y 600
#define board_n 16


typedef struct BMPS{
    BITMAP ** imgs;
} bmps;

int limit( int a, int inf, int sup );
bool LoadBMPS( bmps * B );
void DestroyBMPS( bmps * B );
int renderX( board * B );
int renderY( board * B );
int tileRenderX( board * B, int x, int y );
int tileRenderY( board * B, int x, int y );
void renderBoard( BITMAP * buffer, board * B, bmps * tbmps );
void renderBoardE( BITMAP * buffer, board * B, bmps * tbmps, int cx, int cy );
void renderGame( BITMAP * buffer2, BITMAP * buffer, board * B, bmps * tbmps, button ** buttons, int number_of_buttons );
void renderMainMenu( BITMAP * buffer, button ** buttons, int number_of_buttons );
void renderEditor( BITMAP * buffer2, BITMAP * buffer, board * B, bmps * tbmps, button ** buttons, int number_of_buttons, int cx, int cy );
void renderEditorSubmenu( BITMAP * buffer, button ** buttons, int number_of_buttons, int w, int h );
void renderEditorSubmenu2( BITMAP * buffer, button ** buttons, slot ** slots, int number_of_buttons, int number_slots, int g, tile_type * h, bmps * tbmps );
void renderLevelMenu( BITMAP * buffer, button ** buttons, int number_of_buttons, int n );
bool ifOpp( board * B, int x, int y );
enum bmps_ids oppBmp( board * B, int x, int y );


#endif

