#include <stdio.h>

#include "files.h"


void saveToFile( board * B, int n ){
    int x = n;
    char cr;
    char s [ 11 ] = "editor/000";
    for( int i = 9; i >= 7; i-- ){
        if( x > 0 ){
            cr = x % 10 + '0';
            x /= 10;
            s [ i ] = cr;
        }else
        {
            break;
        }
    }
    const char * r = s;

    FILE * ff;
    ff = fopen( r, "wb" );

    char wr;

    wr = (char) B->gems;
    fprintf( ff, "%c", wr );
    wr = (char) B->width;
    fprintf( ff, "%c", wr );
    wr = (char) ( B->height - 1 );
    fprintf( ff, "%c", wr );

    for( int i = 0; i < B->width; i++ ){
        for( int j = 0; j < B->height; j++ ){
            wr = (char) B->tiles[ i ][ j ].type->id;
            fprintf( ff, "%c", wr );
        }
    }

    fclose( ff );
}

void readFromFileE( board * B, int n, tile_type ** tltps ){
    int x = n;
    char cr;
    char s [ 11 ] = "editor/000";
    for( int i = 9; i >= 7; i-- ){
        if( x > 0 ){
            cr = x % 10 + '0';
            x /= 10;
            s [ i ] = cr;
        }else
        {
            break;
        }
    }
    const char * r = s;

    FILE * ff;
    ff = fopen( r, "rb" );

    char re;
    int gm;

    fscanf( ff, "%c", &re );
    gm = (int) re;
    fscanf( ff, "%c", &re );
    B->width = (int) re;
    fscanf( ff, "%c", &re );
    B->height = (int) re;

    initBoard( B, tltps, B->width, B->height );

    B->gems = gm;

    for( int i = 0; i < B->width; i++ ){
        for( int j = 0; j < B->height; j++ ){
            fscanf( ff, "%c", &re );
            B->tiles[ i ][ j ].type = &((*tltps)[ (int) re ]);
            if( ( (int) re ) == player ){
                B->plx = i;
                B->ply = j;
            }
        }
    }

    fclose( ff );
}

void readFromFileG( board * B, int n, tile_type ** tltps ){
    int x = n;
    char cr;
    char s [ 11 ] = "levels/000";
    for( int i = 9; i >= 7; i-- ){
        if( x > 0 ){
            cr = x % 10 + '0';
            x /= 10;
            s [ i ] = cr;
        }else
        {
            break;
        }
    }
    const char * r = s;

    FILE * ff;
    ff = fopen( r, "rb" );

    char re;
    int gm;

    fscanf( ff, "%c", &re );
    gm = (int) re;
    fscanf( ff, "%c", &re );
    B->width = (int) re;
    fscanf( ff, "%c", &re );
    B->height = (int) re;

    initBoard( B, tltps, B->width, B->height );

    B->gems = gm;

    for( int i = 0; i < B->width; i++ ){
        for( int j = 0; j < B->height; j++ ){
            fscanf( ff, "%c", &re );
            B->tiles[ i ][ j ].type = &((*tltps)[ (int) re ]);
            if( ( (int) re ) == player ){
                B->plx = i;
                B->ply = j;
            }
        }
    }

    fclose( ff );
}
