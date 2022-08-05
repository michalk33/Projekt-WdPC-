#include "editor.h"

#include <allegro.h>

int columnNumber(){
    for( int i = 0; i < 15; i++ ){
        if( mouse_x >= i * 40 && mouse_x < i * 40 + 40 ){
            return i;
        }
    }
    return -1;
}

int rowNumber(){
    for( int i = 0; i < 15; i++ ){
        if( mouse_y >= i * 40 && mouse_y < i * 40 + 40 ){
            return i;
        }
    }
    return -1;
}

void runEditor( int * wtime, int * xc, int * yc, board * B, int * mb, tile_type * cht, tile_type ** tltps ){
    int tx, ty;
    if( (*wtime) <= 0 ){
        if( ifKeyDownPressed() ){
            (*yc)++;
            if( (*yc) > B->height - 16 ) (*yc) = B->height - 16;
            (*wtime) = wait_time;
        }else
        if( ifKeyUpPressed() ){
            (*yc)--;
            if( (*yc) < 0 ) (*yc) = 0;
            (*wtime) = wait_time;
        }else
        if( ifKeyRightPressed() ){
            (*xc)++;
            if( (*xc) > B->width - 15 ) (*xc) = B->width - 15;
            (*wtime) = wait_time;
        }else
        if( ifKeyLeftPressed() ){
            (*xc)--;
            if( (*xc) < 0 ) (*xc) = 0;
            (*wtime) = wait_time;
        }
    }
    if( (*mb) == 1 && mouse_b == 0 ){
        tx = columnNumber();
        ty = rowNumber();
        if( tx != -1 && ty != -1 ){
            tx += (*xc);
            ty += (*yc);
            if( tx != 0 && ty != 0 && tx < B->width - 1 && ty < B->height - 2 ){
                if( (B->tiles[ tx ][ ty ].type)->id != player )
                    B->tiles[ tx ][ ty ].type = cht;
                if( cht->id == player ){
                    B->tiles[ B->plx ][ B->ply ].type = &((*tltps)[ empty_tile ]);
                    B->plx = tx;
                    B->ply = ty;
                }
            }
        }
    }
}
