#include "buttons.h"
#include "game.h"


void createButton( button * B, int nx, int ny, int nw, int nh, const char * nname ){
    B->x = nx;
    B->y = ny;
    B->w = nw;
    B->h = nh;
    B->name = nname;
}

void createSlot( slot * S, int nx, int ny, tile_type * ntltp ){
    S->x = nx;
    S->y = ny;
    S->tltp = ntltp;
}

bool mouseOnButton( button * B ){
    if(    ( B->x + B->w ) > mouse_x && mouse_x >= B->x
        && ( B->y + B->h ) > mouse_y && mouse_y >= B->y )
            return true;
    return false;
}

bool mouseOnSlot( slot * S ){
    if(    ( S->x + 60 ) > mouse_x && mouse_x >= S->x
        && ( S->y + 60 ) > mouse_y && mouse_y >= S->y )
            return true;
    return false;
}

void showButton( button * B, BITMAP * buffer ){
    if( mouseOnButton( B ) && mouse_b == 1 )
        rectfill( buffer, B->x, B->y, B->x + B->w, B->y + B->h, makecol( 150, 150, 150 ) );
    else if( mouseOnButton( B ) )
        rectfill( buffer, B->x, B->y, B->x + B->w, B->y + B->h, makecol( 185, 185, 185 ) );
    else
        rectfill( buffer, B->x, B->y, B->x + B->w, B->y + B->h, makecol( 200, 200, 200 ) );
    rect( buffer, B->x, B->y, B->x + B->w, B->y + B->h, makecol( 30, 30, 30 ) );
    textout_ex( buffer, font, B->name, B->x + B->w / 2 - text_length( font, B->name ) / 2, B->y + B->h / 2 - text_height( font ) / 2, makecol( 10, 10, 10 ), -1 );
}

void showSlot( slot * S, BITMAP * buffer, tile_type * tltp, BITMAP * bmpp ){
    if( S->tltp->id == tltp->id )
        rectfill( buffer, S->x, S->y, S->x + 60, S->y + 60, makecol( 100, 255, 100 ) );
    else
        rectfill( buffer, S->x, S->y, S->x + 60, S->y + 60, makecol( 100, 150, 100 ) );
    masked_blit( bmpp, buffer, 0, 0, S->x + 10, S->y + 10, 40, 40 );
}
