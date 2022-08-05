#include "render.h"

bool ifOpp( board * B, int x, int y ){
    int i = tileType( B, x, y )->id;
    if( i == opp1 || i == opp2 || i == opp3 || i == dynamite_fire ) return false;
    return true;
}


enum bmps_ids oppBmp( board * B, int x, int y ){
    switch( tileType( B, x, y )->id ){
    case opp1:
        if( B->tiles[ x ][ y ].state1 == 0 ) return opp1a_bmpid;
        return opp1b_bmpid;
    case opp2:
        if( B->tiles[ x ][ y ].state1 == 0 ) return opp2a_bmpid;
        return opp2b_bmpid;
    case opp3:
        if( B->tiles[ x ][ y ].state1 == 0 ) return opp3a_bmpid;
        return opp3b_bmpid;
    case dynamite_fire:
        if( B->tiles[ x ][ y ].state1 == 0 ) return dynamite_fire_a_bmpid;
        return dynamite_fire_b_bmpid;
    default:
        return empty_tile_bmpid;
    }
    return empty_tile_bmpid;
}

int limit( int a, int inf, int sup )
{
    if( a < inf ) return inf;
    if( a > sup ) return sup;
                  return a;
}

bool LoadBMPS( bmps * B )
{
    B->imgs = malloc( bmps_to_load * sizeof( *(B->imgs) ) );
    B->imgs[ empty_tile_bmpid ]          = NULL;
    B->imgs[ empty_tile_bmpid ]          = load_bmp( "graphics/empty.bmp", NULL );
    B->imgs[ rock_bmpid ]                = NULL;
    B->imgs[ rock_bmpid ]                = load_bmp( "graphics/rock.bmp", NULL );
    B->imgs[ sand_bmpid ]                = NULL;
    B->imgs[ sand_bmpid ]                = load_bmp( "graphics/sand.bmp", NULL );
    B->imgs[ player_bmpid ]              = NULL;
    B->imgs[ player_bmpid ]              = load_bmp( "graphics/player.bmp", NULL );
    B->imgs[ destructible_wall_bmpid ]   = NULL;
    B->imgs[ destructible_wall_bmpid ]   = load_bmp( "graphics/wall2.bmp", NULL );
    B->imgs[ indestructible_wall_bmpid ] = NULL;
    B->imgs[ indestructible_wall_bmpid ] = load_bmp( "graphics/wall.bmp", NULL );
    B->imgs[ bomb_bmpid ]                = NULL;
    B->imgs[ bomb_bmpid ]                = load_bmp( "graphics/bomb.bmp", NULL );
    B->imgs[ pushable_wall_bmpid ]       = NULL;
    B->imgs[ pushable_wall_bmpid ]       = load_bmp( "graphics/wall4.bmp", NULL );
    B->imgs[ slippery_wall_bmpid ]       = NULL;
    B->imgs[ slippery_wall_bmpid ]       = load_bmp( "graphics/wall3.bmp", NULL );
    B->imgs[ emerald_bmpid ]             = NULL;
    B->imgs[ emerald_bmpid ]             = load_bmp( "graphics/gem.bmp", NULL );
    B->imgs[ opp1a_bmpid ]               = NULL;
    B->imgs[ opp1a_bmpid ]               = load_bmp( "graphics/opp1a.bmp", NULL );
    B->imgs[ opp1b_bmpid ]               = NULL;
    B->imgs[ opp1b_bmpid ]               = load_bmp( "graphics/opp1b.bmp", NULL );
    B->imgs[ opp2a_bmpid ]               = NULL;
    B->imgs[ opp2a_bmpid ]               = load_bmp( "graphics/opp2a.bmp", NULL );
    B->imgs[ opp2b_bmpid ]               = NULL;
    B->imgs[ opp2b_bmpid ]               = load_bmp( "graphics/opp2b.bmp", NULL );
    B->imgs[ opp3a_bmpid ]               = NULL;
    B->imgs[ opp3a_bmpid ]               = load_bmp( "graphics/opp3a.bmp", NULL );
    B->imgs[ opp3b_bmpid ]               = NULL;
    B->imgs[ opp3b_bmpid ]               = load_bmp( "graphics/opp3b.bmp", NULL );
    B->imgs[ blue_emerald_bmpid ]        = NULL;
    B->imgs[ blue_emerald_bmpid ]        = load_bmp( "graphics/gem2.bmp", NULL );
    B->imgs[ exit_bmpid ]                = NULL;
    B->imgs[ exit_bmpid ]                = load_bmp( "graphics/exit.bmp", NULL );
    B->imgs[ dynamite_fire_a_bmpid ]     = NULL;
    B->imgs[ dynamite_fire_a_bmpid ]     = load_bmp( "graphics/dynfa.bmp", NULL );
    B->imgs[ dynamite_fire_b_bmpid ]     = NULL;
    B->imgs[ dynamite_fire_b_bmpid ]     = load_bmp( "graphics/dynfb.bmp", NULL );
    B->imgs[ dynamite_bmpid ]            = NULL;
    B->imgs[ dynamite_bmpid ]            = load_bmp( "graphics/dyn.bmp", NULL );
    for( int i = 0; i < bmps_to_load; i++ )
        if( B->imgs[ i ] == NULL ) return false;
    return true;
}

void DestroyBMPS( bmps * B )
{
    for( int i = 0; i < bmps_to_load; i++ )
        destroy_bitmap( (B->imgs) [ i ] );
    free( B->imgs );
}

int renderX( board * B )
{
    int r = B->plx * tile_size;
    r += tile_size / 2;
    if( ifPlayerIsMoving( B ) && ifPlayerIsLiving( B ) && !vertical( playerDirection( B ) ) ){
        double l = B->tiles[ B->plx ][ B->ply ].movingState;
        l /= (B->tiles[ B->plx ][ B->ply ].type)->movingSpeed;
        l *= tile_size;
        int t = l;
        if( playerDirection( B ) == left )
            t = -t;
        r += t;
    }
    r -= board_x / 2;
    return limit( r, 0, B->width * tile_size - board_x );
}

int renderY( board * B )
{
    int r = B->ply * tile_size;
    r += tile_size / 2;
    if( ifPlayerIsMoving( B ) && ifPlayerIsLiving( B ) && vertical( playerDirection( B ) ) ){
        double l = B->tiles[ B->plx ][ B->ply ].movingState;
        l /= (B->tiles[ B->plx ][ B->ply ].type)->movingSpeed;
        l *= tile_size;
        int t = l;
        if( playerDirection( B ) == up )
            t = -t;
        r += t;
    }
    r -= board_y / 2;
    return limit( r, 0, ( B->height - 1 ) * tile_size - board_y );
}

int tileRenderX( board * B, int x, int y ){
    if( ifTileIsMoving( B, x, y ) && !vertical( tileDirection( B, x, y ) ) ){
        double l = B->tiles[ x ][ y ].movingState;
        l /= tileType( B, x, y )->movingSpeed;
        l *= tile_size;
        if( tileDirection( B, x, y ) == left )
            l = -l;
        return (int) l;
    }
    return 0;
}

int tileRenderY( board * B, int x, int y ){
    if( ifTileIsMoving( B, x, y ) && vertical( tileDirection( B, x, y ) ) ){
        double l = ((B->tiles) [ x ] [ y ]).movingState;
        l /= tileType( B, x, y )->movingSpeed;
        l *= tile_size;
        if( tileDirection( B, x, y ) == up )
            l = -l;
        return (int) l;
    }
    return 0;
}

void renderBoard( BITMAP * buffer, board * B, bmps * tbmps ){
    clear_to_color( buffer, makecol( 0, 255, 0 ) );
    int a, b, c, d;
    c = renderX( B );
    d = renderY( B );
    a = c / tile_size;
    b = d / tile_size;
    for( int i = limit( a - 2, 0, B->width );  i < a + board_n && i < B->width; i++ ){
    for( int j = limit( b - 2, 0, B->height ); j < b + board_n && j < B->height; j++ )
    {
            blit( (tbmps->imgs) [ empty_tile ], buffer, 0, 0, 40 * i - c, 40 * j - d, 40, 40 );
            if( !ifTileIsMoving( B, i, j ) && !ifTileIsExploding( B, i, j ) ){
                if( ifOpp( B, i, j ) ){
                    masked_blit( (tbmps->imgs) [ (B->tiles[ i ][ j ].type)->bmpid ], buffer, 0, 0, 40 * i - c, 40 * j - d, 40, 40 );
                }else
                {
                   masked_blit( (tbmps->imgs) [ oppBmp( B, i, j ) ], buffer, 0, 0, 40 * i - c, 40 * j - d, 40, 40 );
                }
            }
    }
    }
    for( int i = limit( a - 2, 0, B->width );  i < a + board_n && i < B->width; i++ ){
    for( int j = limit( b - 2, 0, B->height ); j < b + board_n && j < B->height; j++ )
    {
            if( ifTileIsMoving( B, i, j ) && !ifTileIsExploding( B, i, j ) ){
                if( ifOpp( B, i, j ) ){
                    masked_blit( (tbmps->imgs) [ (B->tiles[ i ][ j ].type)->bmpid ], buffer, 0, 0, 40 * i - c + tileRenderX( B, i, j ), 40 * j - d + tileRenderY( B, i, j ), 40, 40 );
                }else
                {
                    masked_blit( (tbmps->imgs) [ oppBmp( B, i, j ) ], buffer, 0, 0, 40 * i - c + tileRenderX( B, i, j ), 40 * j - d + tileRenderY( B, i, j ), 40, 40 );
                }
            }
    }
    }
    for( int i = limit( a - 2, 0, B->width );  i < a + board_n && i < B->width; i++ ){
    for( int j = limit( b - 2, 0, B->height ); j < b + board_n && j < B->height; j++ )
    {
            if( ifTileIsExploding( B, i, j ) )
                rectfill( buffer, 40 * i - c, 40 * j - d, 40 * i - c + 40, 40 * j - d + 40, makecol( 255, 255, 200 ) );
    }
    }
}

void renderBoardE( BITMAP * buffer, board * B, bmps * tbmps, int cx, int cy ){
    clear_to_color( buffer, makecol( 0, 255, 0 ) );
    int a, b, c, d;
    c = cx * tile_size;
    d = cy * tile_size;
    a = cx;
    b = cy;
    for( int i = limit( a - 2, 0, B->width );  i < a + board_n && i < B->width; i++ ){
    for( int j = limit( b - 2, 0, B->height ); j < b + board_n && j < B->height; j++ )
    {
            blit( (tbmps->imgs) [ empty_tile ], buffer, 0, 0, 40 * i - c, 40 * j - d, 40, 40 );
            if( !ifTileIsMoving( B, i, j ) && !ifTileIsExploding( B, i, j ) ){
                if( ifOpp( B, i, j ) ){
                    masked_blit( (tbmps->imgs) [ (B->tiles[ i ][ j ].type)->bmpid ], buffer, 0, 0, 40 * i - c, 40 * j - d, 40, 40 );
                }else
                {
                   masked_blit( (tbmps->imgs) [ oppBmp( B, i, j ) ], buffer, 0, 0, 40 * i - c, 40 * j - d, 40, 40 );
                }
            }
    }
    }
}

void renderGame( BITMAP * buffer2, BITMAP * buffer, board * B, bmps * tbmps, button ** buttons, int number_of_buttons ){
    renderBoard( buffer2, B, tbmps );
    blit( buffer2, buffer, 0, 0, 0, 0, board_x, board_y );
    for( int i = 0; i < number_of_buttons; i++ ){
        showButton( &((*buttons)[ i ]), buffer );
    }
    masked_blit( (tbmps->imgs) [ emerald_bmpid ], buffer, 0, 0, 640, 350, 40, 40 );
    masked_blit( (tbmps->imgs) [ dynamite_bmpid ], buffer, 0, 0, 640, 400, 40, 40 );
    int x = B->gems;
    char cr;
    char s [ 4 ] = "000";
    for( int i = 2; i >= 0; i-- ){
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
    textout_ex( buffer, font, r, 700 - text_length( font, r ) / 2, 370 - text_height( font ) / 2, makecol( 10, 10, 10 ), -1 );
    x = B->dyns;
    char s2 [ 4 ] = "000";
    for( int i = 2; i >= 0; i-- ){
        if( x > 0 ){
            cr = x % 10 + '0';
            x /= 10;
            s2 [ i ] = cr;
        }else
        {
            break;
        }
    }
    const char * r2 = s2;
    textout_ex( buffer, font, r2, 700 - text_length( font, r2 ) / 2, 420 - text_height( font ) / 2, makecol( 10, 10, 10 ), -1 );
}

void renderMainMenu( BITMAP * buffer, button ** buttons, int number_of_buttons ){
    for( int i = 0; i < number_of_buttons; i++ ){
        showButton( &((*buttons)[ i ]), buffer );
    }
}

void renderEditor( BITMAP * buffer2, BITMAP * buffer, board * B, bmps * tbmps, button ** buttons, int number_of_buttons, int cx, int cy ){
    renderBoardE( buffer2, B, tbmps, cx, cy );
    blit( buffer2, buffer, 0, 0, 0, 0, board_x, board_y );
    for( int i = 0; i < number_of_buttons; i++ ){
        showButton( &((*buttons)[ i ]), buffer );
    }
}

void renderEditorSubmenu( BITMAP * buffer, button ** buttons, int number_of_buttons, int w, int h ){
    for( int i = 0; i < number_of_buttons; i++ ){
        showButton( &((*buttons)[ i ]), buffer );
    }

    int x = w;
    char cr;
    char s [ 11 ] = "Width: 000";
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
    textout_ex( buffer, font, r, 400 - text_length( font, r ) / 2, 255 - text_height( font ) / 2, makecol( 10, 10, 10 ), -1 );

    x = h;
    char s2 [ 12 ] = "Height: 000";
    for( int i = 10; i >= 8; i-- ){
        if( x > 0 ){
            cr = x % 10 + '0';
            x /= 10;
            s2 [ i ] = cr;
        }else
        {
            break;
        }
    }
    const char * r2 = s2;
    textout_ex( buffer, font, r2, 400 - text_length( font, r2 ) / 2, 285 - text_height( font ) / 2, makecol( 10, 10, 10 ), -1 );
}

void renderEditorSubmenu2( BITMAP * buffer, button ** buttons, slot ** slots, int number_of_buttons, int number_slots, int g, tile_type * h, bmps * tbmps ){
    for( int i = 0; i < number_of_buttons; i++ ){
        showButton( &((*buttons)[ i ]), buffer );
    }
    for( int i = 0; i < number_slots; i++ ){
        showSlot( &((*slots)[ i ]), buffer, h, tbmps->imgs [ (*slots)[ i ].tltp->bmpid ] );
    }

    int x = g;
    char cr;
    char s [ 31 ] = "Number of gems to collect: 000";
    for( int i = 29; i >= 27; i-- ){
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
    textout_ex( buffer, font, r, 400 - text_length( font, r ) / 2, 100 - text_height( font ) / 2, makecol( 10, 10, 10 ), -1 );
}

void renderLevelMenu( BITMAP * buffer, button ** buttons, int number_of_buttons, int n ){
    for( int i = 0; i < number_of_buttons; i++ ){
        showButton( &((*buttons)[ i ]), buffer );
    }

    int x = n;
    char cr;
    char s [ 11 ] = "Level: 000";
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

    textout_ex( buffer, font, r, 400 - text_length( font, r ) / 2, 270 - text_height( font ) / 2, makecol( 10, 10, 10 ), -1 );
}
