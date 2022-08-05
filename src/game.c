#include <stdlib.h>
#include <allegro.h>

#include "game.h"


bool ifKeyRightPressed(){return key [ KEY_RIGHT ] || key [ KEY_D ];}
bool ifKeyLeftPressed() {return key [ KEY_LEFT ]  || key [ KEY_A ];}
bool ifKeyDownPressed() {return key [ KEY_DOWN ]  || key [ KEY_S ];}
bool ifKeyUpPressed()   {return key [ KEY_UP ]    || key [ KEY_W ];}
bool ifSpacePressed()   {return key [ KEY_SPACE ];}

enum direction pressedKeyDirection(){
    if( ifKeyRightPressed() ) return right;
    if( ifKeyLeftPressed()  ) return left;
    if( ifKeyDownPressed()  ) return down;
    if( ifKeyUpPressed()    ) return up;
    return down;
}

enum direction leftDirection ( enum direction dir ){
    switch( dir ){
        case up:    return left;
        case left:  return down;
        case down:  return right;
        case right: return up;
        default:    return up;
    }
    return up;
}

enum direction rightDirection( enum direction dir ){
    switch( dir ){
        case up:    return right;
        case left:  return up;
        case down:  return left;
        case right: return down;
        default:    return down;
    }
    return down;
}

int dir_x( int x, enum direction dir ){
    switch( dir ){
        case left:  return x - 1;
        case right: return x + 1;
        default:    return x;
    }
    return x;
}

int dir_y( int y, enum direction dir ){
    switch( dir ){
        case up:   return y - 1;
        case down: return y + 1;
        default:   return y;
    }
    return y;
}

void setTileType( tile_type * T, bool a, bool b, bool c, bool d, bool e, bool f, bool g, bool h,
                  bool i, bool j, bool k, bool l, int m, int n, int o, int p, int q, enum explosion_types r,
                  tile_type * s ){
    T->destructible = a;
    T->pushable = b;
    T->slipping = c;
    T->gravity = d;
    T->smashable = e;
    T->rotating = f;
    T->diggable = g;
    T->smashing = h;
    T->exploding = i;
    T->smashing_player = j;
    T->collectible = k;
    T->killing_player = l;
    T->movingSpeed = m;
    T->bmpid = n;
    T->id = o;
    T->pushing_time = p;
    T->value = q;
    T->explosion_type = r;
    T->explosion_tile_type = s;
}

void setTileTypes( tile_type ** T )
{
    (*T) = malloc( tile_types_to_set * sizeof( *(*T) ) );//wyspacjować

    setTileType( &( (*T) [ empty_tile          ] ), true,  false, false, false, false, false, false, false, false, false, false, false, 0,            empty_tile_bmpid,          empty_tile,          0,                 0, none_exs  , &( (*T) [ empty_tile   ] ) );
    setTileType( &( (*T) [ rock                ] ), true,  true,  true,  true,  false, true,  false, true,  false, true,  false, false, rock_speed,   rock_bmpid,                rock,                rock_pushing_time, 0, none_exs  , &( (*T) [ empty_tile   ] ) );
    setTileType( &( (*T) [ indestructible_wall ] ), false, false, false, false, false, false, false, false, false, false, false, false, 0,            indestructible_wall_bmpid, indestructible_wall, 0,                 0, none_exs  , &( (*T) [ empty_tile   ] ) );
    setTileType( &( (*T) [ destructible_wall   ] ), true,  false, false, false, false, false, false, false, false, false, false, false, 0,            destructible_wall_bmpid,   destructible_wall,   0,                 0, none_exs  , &( (*T) [ empty_tile   ] ) );
    setTileType( &( (*T) [ sand                ] ), true,  false, false, false, false, false, true,  false, false, false, false, false, 0,            sand_bmpid,                sand,                0,                 0, none_exs  , &( (*T) [ empty_tile   ] ) );
    setTileType( &( (*T) [ player              ] ), true,  false, false, false, true,  false, false, false, true,  false, false, false, player_speed, player_bmpid,              player,              0,                 0, medium_exs, &( (*T) [ emerald      ] ) );
    setTileType( &( (*T) [ bomb                ] ), true,  true,  true,  true,  true,  true,  false, true,  true,  true,  false, false, rock_speed,   bomb_bmpid,                bomb,                rock_pushing_time, 0, medium_exs, &( (*T) [ empty_tile   ] ) );
    setTileType( &( (*T) [ pushable_wall       ] ), true,  true,  false, false, false, false, false, false, false, false, false, false, rock_speed,   pushable_wall_bmpid,       pushable_wall,       rock_pushing_time, 0, none_exs  , &( (*T) [ empty_tile   ] ) );
    setTileType( &( (*T) [ slippery_wall       ] ), true,  false, true,  false, false, false, false, false, false, false, false, false, 0,            slippery_wall_bmpid,       slippery_wall,       0,                 0, none_exs  , &( (*T) [ empty_tile   ] ) );
    setTileType( &( (*T) [ emerald             ] ), true,  false, true,  true,  false, true,  false, false, false, true,  true,  false, rock_speed,   emerald_bmpid,             emerald,             0,                 1, none_exs  , &( (*T) [ empty_tile   ] ) );
    setTileType( &( (*T) [ blue_emerald        ] ), true,  false, true,  true,  true,  true,  false, false, false, true,  true,  false, rock_speed,   blue_emerald_bmpid,        blue_emerald,        0,                 3, none_exs  , &( (*T) [ empty_tile   ] ) );
    setTileType( &( (*T) [ opp1                ] ), true,  false, false, false, true,  false, false, false, true,  false, false, true,  rock_speed,   opp1a_bmpid,               opp1,                0,                 0, medium_exs, &( (*T) [ empty_tile   ] ) );
    setTileType( &( (*T) [ opp2                ] ), true,  false, false, false, true,  false, false, false, true,  false, false, true,  rock_speed,   opp2a_bmpid,               opp2,                0,                 0, medium_exs, &( (*T) [ emerald      ] ) );
    setTileType( &( (*T) [ opp3                ] ), true,  false, false, false, true,  false, false, false, true,  false, false, true,  rock_speed,   opp3a_bmpid,               opp3,                0,                 0, small_exs,  &( (*T) [ blue_emerald ] ) );
    setTileType( &( (*T) [ exit_tile           ] ), true,  false, false, false, false, false, false, false, false, false, false, false, 0,            exit_bmpid,                exit_tile,           0,                 0, none_exs  , &( (*T) [ empty_tile   ] ) );
    setTileType( &( (*T) [ dynamite            ] ), true,  false, false, false, false, false, false, false, true,  false, true,  false, 0,            dynamite_bmpid,            dynamite,            0,                 0, medium_exs, &( (*T) [ empty_tile   ] ) );
    setTileType( &( (*T) [ dynamite_fire       ] ), true,  false, false, false, false, false, false, false, true,  false, false, false, 0,            dynamite_fire_a_bmpid,     dynamite_fire,       0,                 0, medium_exs, &( (*T) [ empty_tile   ] ) );
}

bool vertical( enum direction dir ){
    return dir == up || dir == down;
}

bool ifPlayerIsMoving( board * B ){
    return B->tiles[ B->plx ][ B->ply ].moving;
}

bool ifTileIsMoving( board * B, int x, int y ){
    return B->tiles[ x ][ y ].moving;
}

bool ifTileIsSlipping( board * B, int x, int y ){
    return B->tiles[ x ][ y ].slipping;
}

bool ifTileIsExploding( board * B, int x, int y ){
    return B->tiles[ x ][ y ].exploding;
}

bool ifTileDiggable( board * B, int x, int y ){
    return tileType( B, x, y )->diggable;
}

bool ifTileSmashable( board * B, int x, int y ){
    return tileType( B, x, y )->smashable;
}

bool ifTilePushable( board * B, int x, int y ){
    return tileType( B, x, y )->pushable;
}

bool ifTileCollectible( board * B, int x, int y ){
    return tileType( B, x, y )->collectible;
}

bool ifTileFree( board * B, int x, int y ){
    if ( tileType( B, x, y )->id != empty_tile )                                                                                                          return false;
    if ( ifTileIsExploding( B, x, y ) )                                                                                                                   return false;
    if ( x > 0             && B->tiles[ x - 1 ][ y ].movingState >= 0 && ifTileIsMoving( B, x - 1, y     ) && tileDirection( B, x - 1, y     ) == right ) return false;
    if ( x < B->width - 1  && B->tiles[ x + 1 ][ y ].movingState >= 0 && ifTileIsMoving( B, x + 1, y     ) && tileDirection( B, x + 1, y     ) == left  ) return false;
    if ( y > 0             && B->tiles[ x ][ y - 1 ].movingState >= 0 && ifTileIsMoving( B, x    , y - 1 ) && tileDirection( B, x    , y - 1 ) == down  ) return false;
    if ( y < B->height - 1 && B->tiles[ x ][ y + 1 ].movingState >= 0 && ifTileIsMoving( B, x    , y + 1 ) && tileDirection( B, x    , y + 1 ) == up    ) return false;
    if ( x > 0             && B->tiles[ x - 1 ][ y ].movingState < 0  && ifTileIsMoving( B, x - 1, y     ) && tileDirection( B, x - 1, y     ) == left  ) return false;
    if ( x < B->width - 1  && B->tiles[ x + 1 ][ y ].movingState < 0  && ifTileIsMoving( B, x + 1, y     ) && tileDirection( B, x + 1, y     ) == right ) return false;
    if ( y > 0             && B->tiles[ x ][ y - 1 ].movingState < 0  && ifTileIsMoving( B, x    , y - 1 ) && tileDirection( B, x    , y - 1 ) == up    ) return false;
    if ( y < B->height - 1 && B->tiles[ x ][ y + 1 ].movingState < 0  && ifTileIsMoving( B, x    , y + 1 ) && tileDirection( B, x    , y + 1 ) == down  ) return false;
    return true;
}

bool ifTileFreePlayer( board * B, int x, int y ){
    if ( tileType( B, x, y )->id != empty_tile )                                                                                                                                                   return false;
    if ( ifTileIsExploding( B, x, y ) )                                                                                                                                                            return false;
    if ( x > 0             && B->tiles[ x - 1 ][ y ].movingState >= 0 && ifTileIsMoving( B, x - 1, y     ) && tileDirection( B, x - 1, y     ) == right )                                          return false;
    if ( x < B->width - 1  && B->tiles[ x + 1 ][ y ].movingState >= 0 && ifTileIsMoving( B, x + 1, y     ) && tileDirection( B, x + 1, y     ) == left  )                                          return false;
    if ( y > 0             && B->tiles[ x ][ y - 1 ].movingState >= 0 && ifTileIsMoving( B, x    , y - 1 ) && tileDirection( B, x    , y - 1 ) == down  )                                          return false;
    if ( y < B->height - 1 && B->tiles[ x ][ y + 1 ].movingState >= 0 && ifTileIsMoving( B, x    , y + 1 ) && tileDirection( B, x    , y + 1 ) == up    )                                          return false;
    if ( x > 0             && B->tiles[ x - 1 ][ y ].movingState < 0  && ifTileIsMoving( B, x - 1, y     ) && tileDirection( B, x - 1, y     ) == left  && tileType( B, x - 1, y )->id != player ) return false;
    if ( x < B->width - 1  && B->tiles[ x + 1 ][ y ].movingState < 0  && ifTileIsMoving( B, x + 1, y     ) && tileDirection( B, x + 1, y     ) == right && tileType( B, x + 1, y )->id != player ) return false;
    if ( y > 0             && B->tiles[ x ][ y - 1 ].movingState < 0  && ifTileIsMoving( B, x    , y - 1 ) && tileDirection( B, x    , y - 1 ) == up    )                                          return false;
    if ( y < B->height - 1 && B->tiles[ x ][ y + 1 ].movingState < 0  && ifTileIsMoving( B, x    , y + 1 ) && tileDirection( B, x    , y + 1 ) == down  )                                          return false;
    return true;
}

bool ifTileFreePlayerForOpp( board * B, int x, int y ){
    if ( tileType( B, x, y )->id != empty_tile )                                                                                                                                                       return false;
    if ( ifTileIsExploding( B, x, y ) )                                                                                                                                                                return false;
    if ( x > 0             && B->tiles[ x - 1 ][ y ].movingState >= 0 && ifTileIsMoving( B, x - 1, y     ) && tileDirection( B, x - 1, y     ) == right )                                              return false;
    if ( x < B->width - 1  && B->tiles[ x + 1 ][ y ].movingState >= 0 && ifTileIsMoving( B, x + 1, y     ) && tileDirection( B, x + 1, y     ) == left  )                                              return false;
    if ( y > 0             && B->tiles[ x ][ y - 1 ].movingState >= 0 && ifTileIsMoving( B, x    , y - 1 ) && tileDirection( B, x    , y - 1 ) == down  )                                              return false;
    if ( y < B->height - 1 && B->tiles[ x ][ y + 1 ].movingState >= 0 && ifTileIsMoving( B, x    , y + 1 ) && tileDirection( B, x    , y + 1 ) == up    )                                              return false;
    if ( x > 0             && B->tiles[ x - 1 ][ y ].movingState < 0  && ifTileIsMoving( B, x - 1, y     ) && tileDirection( B, x - 1, y     ) == left  && tileType( B, x - 1, y     )->id != player ) return false;
    if ( x < B->width - 1  && B->tiles[ x + 1 ][ y ].movingState < 0  && ifTileIsMoving( B, x + 1, y     ) && tileDirection( B, x + 1, y     ) == right && tileType( B, x + 1, y     )->id != player ) return false;
    if ( y > 0             && B->tiles[ x ][ y - 1 ].movingState < 0  && ifTileIsMoving( B, x    , y - 1 ) && tileDirection( B, x    , y - 1 ) == up    && tileType( B, x    , y - 1 )->id != player ) return false;
    if ( y < B->height - 1 && B->tiles[ x ][ y + 1 ].movingState < 0  && ifTileIsMoving( B, x    , y + 1 ) && tileDirection( B, x    , y + 1 ) == down  && tileType( B, x    , y + 1 )->id != player ) return false;
    return true;
}

bool ifPlayerIsLiving( board * B ){
    return B->living;
}

bool ifKillingPlayer( board * B, int x, int y ){
    if( !ifTileIsMoving( B, x, y ) || vertical( tileDirection( B, x, y ) ) ){
        if( tileType( B, x + 1, y )->id == player || tileType( B, x - 1, y )->id == player ){
            if( !ifPlayerIsMoving( B ) || vertical( playerDirection( B ) ) ){
                return true;
            }
        }
    }

    if( !ifTileIsMoving( B, x, y ) || !vertical( tileDirection( B, x, y ) ) ){
        if( tileType( B, x, y + 1 )->id == player || tileType( B, x, y - 1 )->id == player ){
            if( !ifPlayerIsMoving( B ) || !vertical( playerDirection( B ) ) ){
                return true;
            }
        }
    }

    return false;
}

bool ifTileBlockedByPlayer( board * B, int x, int y ){
    if ( x > 0             && B->tiles[ x - 1 ][ y ].movingState >= 0 && ifTileIsMoving( B, x - 1, y     ) && tileDirection( B, x - 1, y     ) == right && tileType( B, x - 1, y     )->id == player ) return true;
    if ( x < B->width - 1  && B->tiles[ x + 1 ][ y ].movingState >= 0 && ifTileIsMoving( B, x + 1, y     ) && tileDirection( B, x + 1, y     ) == left  && tileType( B, x + 1, y     )->id == player ) return true;
    if ( y > 0             && B->tiles[ x ][ y - 1 ].movingState >= 0 && ifTileIsMoving( B, x    , y - 1 ) && tileDirection( B, x    , y - 1 ) == down  && tileType( B, x    , y - 1 )->id == player ) return true;
    if ( y < B->height - 1 && B->tiles[ x ][ y + 1 ].movingState >= 0 && ifTileIsMoving( B, x    , y + 1 ) && tileDirection( B, x    , y + 1 ) == up    && tileType( B, x    , y + 1 )->id == player ) return true;
    return false;
}

enum direction playerDirection( board * B ){
    return B->tiles[ B->plx ][ B->ply ].movingDirection;
}

enum direction tileDirection( board * B, int x, int y ){
    return B->tiles[ x ][ y ].movingDirection;
}

tile_type * tileType( board * B, int x, int y ){
    return B->tiles[ x ][ y ].type;
}

void initBoard( board * B, tile_type ** tltps, int w, int h )
{
    B->width = w;
    B->height = h + 1;
    B->plx = 1;
    B->ply = 1;
    B->gems = 0;
    B->dyns = 0;
    B->living = true;
    B->winning = false;
    B->player_on_dynamite = false;
    B->dyn_time = 0;
    B->pushing_time = 0;
    B->tiles = malloc( B->width * sizeof( *(B->tiles) ) );

    for( int i = 0; i < B->width; i++ )
        (B->tiles) [ i ] = malloc( B->height * sizeof( *((B->tiles) [ i ]) ) );

    for( int i = 0; i < B->width; i++ ){
    for( int j = 0; j < B->height; j++ )
    {
        if( i == 0 || i == B->width - 1 || j == 0 || j >= B->height - 2 ){
            B->tiles[ i ][ j ].type = &((*tltps)[indestructible_wall]);
        }
        else
        {
            B->tiles[ i ][ j ].type = &((*tltps)[sand]);
        }
        B->tiles[ i ][ j ].moving = false;
        B->tiles[ i ][ j ].slipping = false;
        B->tiles[ i ][ j ].exploding = false;
        B->tiles[ i ][ j ].movingDirection = up;
        B->tiles[ i ][ j ].explosion_type = &((*tltps)[empty_tile]);
        B->tiles[ i ][ j ].movingState = 0;
        B->tiles[ i ][ j ].time = 0;
        B->tiles[ i ][ j ].time1 = 0;
        B->tiles[ i ][ j ].state1 = 0;
    }
    }
    B->tiles[ B->plx ] [ B->ply ].type = &((*tltps)[player]);
}

void boardCopy( board * B, board * D )
{
    B->width = D->width;
    B->height = D->height;
    B->plx = D->plx;
    B->ply = D->ply;
    B->gems = D->gems;
    B->dyns = D->dyns;
    B->living = D->living;
    B->winning = D->winning;
    B->player_on_dynamite = D->player_on_dynamite;
    B->dyn_time = D->dyn_time;
    B->pushing_time = D->pushing_time;
    B->tiles = malloc( B->width * sizeof( *(B->tiles) ) );

    for( int i = 0; i < B->width; i++ )
        (B->tiles) [ i ] = malloc( B->height * sizeof( *((B->tiles) [ i ]) ) );

    for( int i = 0; i < B->width; i++ ){
    for( int j = 0; j < B->height; j++ )
    {
        B->tiles[ i ][ j ].type = D->tiles[ i ][ j ].type;
        B->tiles[ i ][ j ].moving = D->tiles[ i ][ j ].moving;
        B->tiles[ i ][ j ].slipping = D->tiles[ i ][ j ].slipping;
        B->tiles[ i ][ j ].exploding = D->tiles[ i ][ j ].exploding;
        B->tiles[ i ][ j ].movingDirection = D->tiles[ i ][ j ].movingDirection;
        B->tiles[ i ][ j ].explosion_type = D->tiles[ i ][ j ].explosion_type;
        B->tiles[ i ][ j ].movingState = D->tiles[ i ][ j ].movingState;
        B->tiles[ i ][ j ].time = D->tiles[ i ][ j ].time;
        B->tiles[ i ][ j ].time1 = D->tiles[ i ][ j ].time1;
        B->tiles[ i ][ j ].state1 = D->tiles[ i ][ j ].state1;
    }
    }
}

void removeTile( board * B, tile_type ** tltps, int x, int y ){
    B->tiles[ x ][ y ].type = &((*tltps) [ empty_tile ]);
    B->tiles[ x ][ y ].movingState = 0;
    B->tiles[ x ][ y ].moving = false;
}

void moveTile( board * B, tile_type ** tltps, int x, int y ){
    int nx = x, ny = y;
    B->tiles[ x ][ y ].moving = false;
    switch( ((B->tiles) [ x ] [ y ]).movingDirection ){
        case up    : ny--; break;
        case right : nx++; break;
        case down  : ny++; break;
        case left  : nx--; break;
    }
    if( (B->tiles[ x ][ y ].type)->id == player ){
        B->plx = nx;
        B->ply = ny;
    }
    B->tiles[ nx ][ ny ].type            = B->tiles[ x ][ y ].type;
    B->tiles[ x  ][ y  ].type            = &((*tltps) [empty_tile]);
    B->tiles[ nx ][ ny ].moving          = true;
    B->tiles[ nx ][ ny ].slipping        = B->tiles[ x ][ y ].slipping;
    B->tiles[ x  ][ y  ].slipping        = false;
    B->tiles[ nx ][ ny ].movingDirection = B->tiles[ x ][ y ].movingDirection;
    B->tiles[ nx ][ ny ].movingState     = B->tiles[ x ][ y ].movingState;
    B->tiles[ x  ][ y  ].movingState     = 0;
    B->tiles[ nx ][ ny ].state1          = B->tiles[ x ][ y ].state1;
    B->tiles[ x  ][ y  ].state1          = 0;
    B->tiles[ nx ][ ny ].time1           = B->tiles[ x ][ y ].time1;
    B->tiles[ x  ][ y  ].time1           = 0;
}

void startMovingTile( board * B, int x, int y, enum direction dir ){
    B->tiles[ x ][ y ].moving          = true;
    B->tiles[ x ][ y ].movingState     = 0;
    B->tiles[ x ][ y ].movingDirection = dir;
}

void stopMovingTile( board * B, int x, int y ){
    B->tiles[ x ][ y ].moving      = false;
    B->tiles[ x ][ y ].slipping    = false;
    B->tiles[ x ][ y ].movingState = 0;
}

void startSlippingTile( board * B, int x, int y, enum direction dir ){
    startMovingTile( B, x, y, dir );
    B->tiles[ x ][ y ].slipping = true;
}

void startExploding( board * B, int x, int y, tile_type * exs_t, tile_type ** tltps ){
    if( tileType( B, x, y )->destructible ){
        if( !( ifTileIsExploding( B, x, y ) && B->tiles[ x ][ y ].explosion_type != &((*tltps) [empty_tile]) ) ){
            B->tiles[ x ][ y ].explosion_type = exs_t;
        }
        B->tiles[ x ][ y ].exploding = true;
        B->tiles[ x ][ y ].time      = explosion_speed;
        if( x == B->plx && y == B->ply ){
            B->living = false;
        }
    }
}

void burst( board * B, int x, int y, enum explosion_types exs, tile_type * exs_t, tile_type ** tltps ){
    B->tiles[ x ][ y ].type = &((*tltps) [empty_tile]);
    switch( exs ){
        case small_exs:
            startExploding( B, x, y, exs_t, tltps );
            break;
        case medium_exs:
            startExploding( B, x - 1, y - 1, exs_t, tltps );
            startExploding( B, x    , y - 1, exs_t, tltps );
            startExploding( B, x + 1, y - 1, exs_t, tltps );
            startExploding( B, x - 1, y    , exs_t, tltps );
            startExploding( B, x    , y    , exs_t, tltps );
            startExploding( B, x + 1, y    , exs_t, tltps );
            startExploding( B, x - 1, y + 1, exs_t, tltps );
            startExploding( B, x    , y + 1, exs_t, tltps );
            startExploding( B, x + 1, y + 1, exs_t, tltps );
            break;
        case none_exs:
            break;
    }
}

void runBoard( board * B, tile_type ** tltps ){
    for( int i = 1; i < B->width - 1; i++ ){
        for( int j = B->height - 1; j >= 0; j-- ){
            if( tileType( B, i, j )->killing_player ){//czy gracz został dotknięty przez przeciwnika
                if( ifKillingPlayer( B, i, j ) ){
                    burst( B, B->plx, B->ply, tileType( B, B->plx, B->ply )->explosion_type, tileType( B, B->plx, B->ply )->explosion_tile_type, tltps );
                    burst( B, i, j, tileType( B, i, j )->explosion_type, tileType( B, i, j )->explosion_tile_type, tltps );
                }
            }
            if( ifTileIsExploding( B, i, j ) )
            {//eksplozja
                B->tiles[ i ][ j ].time--;
                if( B->tiles[ i ][ j ].time <= 0 ){

                    B->tiles[ i ][ j ].moving      = false;
                    B->tiles[ i ][ j ].slipping    = false;
                    B->tiles[ i ][ j ].exploding   = false;
                    B->tiles[ i ][ j ].movingState = 0;
                    B->tiles[ i ][ j ].time        = 0;
                    B->tiles[ i ][ j ].time1       = 0;
                    B->tiles[ i ][ j ].state1      = 0;

                    if( tileType( B, i, j )->exploding ){
                        B->tiles[ i ][ j ].explosion_type = &((*tltps) [empty_tile]);
                        burst( B, i, j, tileType( B, i, j )->explosion_type, tileType( B, i, j )->explosion_tile_type, tltps );
                    }else
                    {
                        B->tiles[ i ][ j ].type           = B->tiles[ i ][ j ].explosion_type;
                        B->tiles[ i ][ j ].explosion_type = &((*tltps) [empty_tile]);
                    }
                }
            }
            if( ifTileIsMoving( B, i, j ) && !ifTileIsExploding( B, i, j ) )
            {//ruch
                if( B->tiles[ i ][ j ].movingState >= 0 ){
                    B->tiles[ i ][ j ].movingState++;
                    if( B->tiles[ i ][ j ].movingState > tileType( B, i, j )->movingSpeed / 2 ){

                        B->tiles[ i ][ j ].movingState -= tileType( B, i, j )->movingSpeed;

                        if( tileDirection( B, i, j ) == right || tileDirection( B, i, j ) == up ){
                            B->tiles[ i ][ j ].movingState--;
                        }

                        if( tileType( B, i, j )->id == player && B->player_on_dynamite ){//gracz schodzi z bomby
                            moveTile( B, tltps, i, j );
                            B->tiles[ i ][ j ].moving      = false;
                            B->tiles[ i ][ j ].slipping    = false;
                            B->tiles[ i ][ j ].exploding   = false;
                            B->tiles[ i ][ j ].movingState = 0;
                            B->tiles[ i ][ j ].time        = 0;
                            B->tiles[ i ][ j ].time1       = B->dyn_time;
                            B->tiles[ i ][ j ].state1      = ( B->dyn_time / dynf_animation_time ) % 2;
                            B->tiles[ i ][ j ].type        = &((*tltps)[dynamite_fire]);
                            B->player_on_dynamite = false;
                            B->dyn_time = 0;
                        }else
                        {
                            moveTile( B, tltps, i, j );
                        }

                    }
                }else
                {
                    B->tiles[ i ][ j ].movingState++;
                    if( B->tiles[ i ][ j ].movingState >= 0 ){
                        stopMovingTile( B, i, j );
                        if( tileDirection( B, i, j ) == down && tileType( B, i, j )->gravity && tileType( B, i, j )->smashing )
                        {//miażdżenie
                            if( tileType( B, i, j + 1 )->smashable ){
                                burst( B, i, j + 1, tileType( B, i, j + 1 )->explosion_type, tileType( B, i, j + 1 )->explosion_tile_type, tltps );
                                if( tileType( B, i, j )->exploding && tileType( B, i, j )->smashable ){
                                    burst( B, i, j, tileType( B, i, j )->explosion_type, tileType( B, i, j )->explosion_tile_type, tltps );
                                }
                            }else
                            if( tileType( B, i, j + 2 )->smashable && tileDirection( B, i, j + 2 ) == up && B->tiles[ i ][ j + 2 ].movingState > 0 ){
                                moveTile( B, tltps, i, j + 2 );
                                burst( B, i, j + 1, tileType( B, i, j + 1 )->explosion_type, tileType( B, i, j + 1 )->explosion_tile_type, tltps );
                                if( tileType( B, i, j )->exploding && tileType( B, i, j )->smashable ){
                                    burst( B, i, j, tileType( B, i, j )->explosion_type, tileType( B, i, j )->explosion_tile_type, tltps );
                                }
                            }else
                            if( tileType( B, i + 1, j + 1 )->smashable && ifTileIsMoving( B, i + 1, j + 1 )
                            && tileDirection( B, i + 1, j + 1 ) == left && B->tiles[ i + 1 ][ j + 1 ].movingState > 0 )
                            {
                                burst( B, i + 1, j + 1, tileType( B, i + 1, j + 1 )->explosion_type, tileType( B, i + 1, j + 1 )->explosion_tile_type, tltps );
                                if( tileType( B, i, j )->exploding && tileType( B, i, j )->smashable ){
                                    burst( B, i, j, tileType( B, i, j )->explosion_type, tileType( B, i, j )->explosion_tile_type, tltps );
                                }
                            }else
                            if( tileType( B, i - 1, j + 1 )->smashable && ifTileIsMoving( B, i - 1, j + 1 )
                                && tileDirection( B, i - 1, j + 1 ) == right && B->tiles[ i - 1 ][ j + 1 ].movingState > 0 )
                            {
                                burst( B, i - 1, j + 1, tileType( B, i - 1, j + 1 )->explosion_type, tileType( B, i - 1, j + 1 )->explosion_tile_type, tltps );
                                if( tileType( B, i, j )->exploding && tileType( B, i, j )->smashable ){
                                    burst( B, i, j, tileType( B, i, j )->explosion_type, tileType( B, i, j )->explosion_tile_type, tltps );
                                }
                            }
                        }
                        if( tileDirection( B, i, j ) == down && tileType( B, i, j )->gravity && tileType( B, i, j )->smashing_player )
                        {//miażdżenie gracza
                            if( tileType( B, i, j + 1 ) == &((*tltps) [player]) ) {
                                burst( B, i, j + 1, tileType( B, i, j + 1 )->explosion_type, tileType( B, i, j + 1 )->explosion_tile_type, tltps );
                                if( tileType( B, i, j )->exploding && tileType( B, i, j )->smashable ){
                                    burst( B, i, j, tileType( B, i, j )->explosion_type, tileType( B, i, j )->explosion_tile_type, tltps );
                                }
                            }else
                            if( tileType( B, i, j + 2 ) == &((*tltps) [player]) && tileDirection( B, i, j + 2 ) == up
                                && B->tiles[ i ][ j + 2 ].movingState > 0 ){
                                moveTile( B, tltps, i, j + 2 );
                                burst( B, i, j + 1, tileType( B, i, j + 1 )->explosion_type, tileType( B, i, j + 1 )->explosion_tile_type, tltps );
                                if( tileType( B, i, j )->exploding && tileType( B, i, j )->smashable ){
                                    burst( B, i, j, tileType( B, i, j )->explosion_type, tileType( B, i, j )->explosion_tile_type, tltps );
                                }
                            }else
                            if( tileType( B, i + 1, j + 1 ) == &((*tltps) [player]) && ifTileIsMoving( B, i + 1, j + 1 )
                                && tileDirection( B, i + 1, j + 1 ) == left && B->tiles[ i + 1 ][ j + 1 ].movingState > 0 )
                            {
                                burst( B, i + 1, j + 1, tileType( B, i + 1, j + 1 )->explosion_type, tileType( B, i + 1, j + 1 )->explosion_tile_type, tltps );
                                if( tileType( B, i, j )->exploding && tileType( B, i, j )->smashable ){
                                    burst( B, i, j, tileType( B, i, j )->explosion_type, tileType( B, i, j )->explosion_tile_type, tltps );
                                }
                            }else
                            if( tileType( B, i - 1, j + 1 ) == &((*tltps) [player]) && ifTileIsMoving( B, i - 1, j + 1 )
                                && tileDirection( B, i - 1, j + 1 ) == right && B->tiles[ i - 1 ][ j + 1 ].movingState > 0 )
                            {
                                burst( B, i - 1, j + 1, tileType( B, i - 1, j + 1 )->explosion_type, tileType( B, i - 1, j + 1 )->explosion_tile_type, tltps );
                                if( tileType( B, i, j )->exploding && tileType( B, i, j )->smashable ){
                                    burst( B, i, j, tileType( B, i, j )->explosion_type, tileType( B, i, j )->explosion_tile_type, tltps );
                                }
                            }
                        }
                        if( tileDirection( B, i, j ) == down && tileType( B, i, j )->gravity
                            && tileType( B, i, j )->smashable && tileType( B, i, j )->exploding
                            && !ifTileIsExploding( B, i, j ) )
                        {//uderzenie i wybuch
                            if( !ifTileFreePlayer( B, i, j + 1 ) && !( !ifTileIsExploding( B, i, j + 1 )
                                && tileType( B, i, j + 1 ) == &((*tltps) [empty_tile]) && tileDirection( B, i, j + 2 ) == down
                                && ifTileIsMoving( B, i, j + 2 ) && B->tiles[ i ][ j + 2 ].movingState < 0 ) )
                            {
                                burst( B, i, j, tileType( B, i, j )->explosion_type, tileType( B, i, j )->explosion_tile_type, tltps );
                            }
                        }
                    }
                }

                if( tileType( B, i, j )->killing_player ){//czy gracz został dotknięty przez przeciwnika
                    if( ifKillingPlayer( B, i, j ) ){
                        burst( B, B->plx, B->ply, tileType( B, B->plx, B->ply )->explosion_type, tileType( B, B->plx, B->ply )->explosion_tile_type, tltps );
                        burst( B, i, j, tileType( B, i, j )->explosion_type, tileType( B, i, j )->explosion_tile_type, tltps );
                    }
                }

            }
        }
    }
    for( int i = 1; i < B->width - 1; i++ ){
        for( int j = B->height - 1; j >= 0; j-- ){
            if( !ifTileIsMoving( B, i, j ) && tileType( B, i, j )->gravity
                && ifTileFree( B, i, j + 1 ) && !ifTileIsExploding( B, i, j ) )
            {//spadanie
                startMovingTile( B, i, j, down );
            }
            if( !ifTileIsMoving( B, i, j ) && !ifTileIsExploding( B, i, j ) && !ifTileIsSlipping( B, i, j - 1 )
                && !( ifTileIsSlipping( B, i - 1, j - 1 ) && tileDirection( B, i - 1, j - 1 ) == left  && B->tiles[ i - 1 ][ j - 1 ].movingState < 0 )
                && !( ifTileIsSlipping( B, i + 1, j - 1 ) && tileDirection( B, i + 1, j - 1 ) == right && B->tiles[ i + 1 ][ j - 1 ].movingState < 0 )
                && tileType( B, i, j )->gravity && tileType( B, i, j )->slipping && tileType( B, i, j + 1 )->slipping )
            {//ślizganie
                if( ifTileFree( B, i + 1, j ) && ifTileFree( B, i + 1, j + 1 ) )
                    startSlippingTile( B, i, j, right );
                else if( ifTileFree( B, i - 1, j ) && ifTileFree( B, i - 1, j + 1 ) )
                    startSlippingTile( B, i, j, left );
                if( ifTileIsMoving( B, i, j ) )
                    B->tiles[ i ][ j ].movingState++;
            }
        }
    }
    for( int i = 1; i < B->width - 1; i++ ){
        for( int j = B->height - 1; j >= 0; j-- ){
            switch( tileType( B, i, j )->id )
            {//przeciwnicy
                case opp1:
                    opp1Run( B, i, j, tltps );
                    break;
                case opp2:
                    opp2Run( B, i, j, tltps );
                    break;
                case opp3:
                    opp3Run( B, i, j, tltps );
                    break;
                case dynamite_fire:
                    dynfRun( B, i, j, tltps );
                    break;
                default:
                    break;
            }
        }
    }
    if( B->pushing_time > 0 && pressedKeyDirection() != B->pushing_dir ){
        B->pushing_time = 0;
    }
    if( B->pushing_time > 0 ){//pchanie
        B->pushing_time--;
        if( B->pushing_time <= 0 ){
            B->pushing_time = 0;
            if( B->living ){
                switch( B->pushing_dir ){
                    case up:
                        if( ifTilePushable( B, B->plx, B->ply - 1 ) && !ifTileIsExploding( B, B->plx, B->ply - 1 ) && !ifTileIsMoving( B, B->plx, B->ply - 1 ) && ifTileFree( B, B->plx, B->ply - 2 ) ){
                            startMovingTile( B, B->plx, B->ply, up );
                            startMovingTile( B, B->plx, B->ply - 1, up );
                            B->tiles[ B->plx ][ B->ply - 1 ].movingState = 1;
                        }
                        break;
                    case down:
                        if( ifTilePushable( B, B->plx, B->ply + 1 ) && !ifTileIsExploding( B, B->plx, B->ply + 1 ) && !ifTileIsMoving( B, B->plx, B->ply + 1 ) && ifTileFree( B, B->plx, B->ply + 2 ) ){
                            startMovingTile( B, B->plx, B->ply, down );
                            startMovingTile( B, B->plx, B->ply + 1, down );
                            B->tiles[ B->plx ][ B->ply + 1 ].movingState = 1;
                        }
                        break;
                    case right:
                        if( ifTilePushable( B, B->plx + 1, B->ply ) && !ifTileIsExploding( B, B->plx + 1, B->ply ) && !ifTileIsMoving( B, B->plx + 1, B->ply ) && ifTileFree( B, B->plx + 2, B->ply ) ){
                            startMovingTile( B, B->plx, B->ply, right );
                            startMovingTile( B, B->plx + 1, B->ply, right );
                            B->tiles[ B->plx + 1 ][ B->ply ].movingState = 1;
                        }
                        break;
                    case left:
                        if( ifTilePushable( B, B->plx - 1, B->ply ) && !ifTileIsExploding( B, B->plx - 1, B->ply ) && !ifTileIsMoving( B, B->plx - 1, B->ply ) && ifTileFree( B, B->plx - 2, B->ply ) ){
                            startMovingTile( B, B->plx, B->ply, left );
                            startMovingTile( B, B->plx - 1, B->ply, left );
                            B->tiles[ B->plx - 1 ][ B->ply ].movingState = 1;
                        }
                        break;
                }
            }
        }
    }

    if( B->player_on_dynamite ){
        B->dyn_time++;
        if( B->dyn_time >= dynf_time ){
            B->dyn_time = 0;
            B->player_on_dynamite = false;
            burst( B, B->plx, B->ply, (*tltps)[player].explosion_type, (*tltps)[player].explosion_tile_type, tltps );
        }
    }

    if( B->living )
    {
        if( !ifTileIsExploding( B, B->plx, B->ply ) && B->dyns > 0 && ifSpacePressed() && !B->player_on_dynamite ){//podkładanie dynamitu
            B->player_on_dynamite = true;
            B->dyn_time = 0;
            B->dyns--;
        }
        if( !(B->tiles[ B->plx ][ B->ply ].moving) && B->pushing_time <= 0 && B->gems <= 0 ){//wyjście
            if( ifKeyUpPressed()    && tileType( B, B->plx, B->ply - 1 )->id == exit_tile && !ifTileIsExploding( B, B->plx, B->ply - 1 ) ) B->winning = true;
            else if( ifKeyRightPressed() && tileType( B, B->plx + 1, B->ply )->id == exit_tile && !ifTileIsExploding( B, B->plx + 1, B->ply ) ) B->winning = true;
            else if( ifKeyDownPressed()  && tileType( B, B->plx, B->ply + 1 )->id == exit_tile && !ifTileIsExploding( B, B->plx, B->ply + 1 ) ) B->winning = true;
            else if( ifKeyLeftPressed()  && tileType( B, B->plx - 1, B->ply )->id == exit_tile && !ifTileIsExploding( B, B->plx - 1, B->ply ) ) B->winning = true;
        }
        if( !(B->tiles[ B->plx ][ B->ply ].moving) && B->pushing_time <= 0 ){//ruch
            if( ifKeyUpPressed()    && ifTileFree( B, B->plx    , B->ply - 1 ) ) startMovingTile( B, B->plx, B->ply, up );
            else if( ifKeyRightPressed() && ifTileFree( B, B->plx + 1, B->ply     ) ) startMovingTile( B, B->plx, B->ply, right );
            else if( ifKeyDownPressed()  && ifTileFree( B, B->plx    , B->ply + 1 ) ) startMovingTile( B, B->plx, B->ply, down );
            else if( ifKeyLeftPressed()  && ifTileFree( B, B->plx - 1, B->ply     ) ) startMovingTile( B, B->plx, B->ply, left );
        }
        if( !(B->tiles[ B->plx ][ B->ply ].moving) && B->pushing_time <= 0 ){//zbieranie
            if(     ifKeyUpPressed()
                &&  ifTileCollectible( B, B->plx, B->ply - 1 )
                && !ifTileIsExploding( B, B->plx, B->ply - 1 )
                && !ifTileIsMoving( B, B->plx, B->ply - 1 ) ){
                startMovingTile( B, B->plx, B->ply, up );
                B->gems -= tileType( B, B->plx, B->ply - 1 )->value;
                if( tileType( B, B->plx, B->ply - 1 )->id == dynamite ) B->dyns++;
                removeTile( B, tltps, B->plx, B->ply - 1 );
            }else
            if(     ifKeyRightPressed()
                &&  ifTileCollectible( B, B->plx + 1, B->ply )
                && !ifTileIsExploding( B, B->plx + 1, B->ply )
                && !ifTileIsMoving( B, B->plx + 1, B->ply ) ){
                startMovingTile( B, B->plx    , B->ply, right );
                B->gems -= tileType( B, B->plx + 1, B->ply )->value;
                if( tileType( B, B->plx + 1, B->ply )->id == dynamite ) B->dyns++;
                removeTile( B, tltps, B->plx + 1, B->ply );
            }else
            if(     ifKeyDownPressed()
                &&  ifTileCollectible( B, B->plx, B->ply + 1 )
                && !ifTileIsExploding( B, B->plx, B->ply + 1 )
                && !ifTileIsMoving( B, B->plx, B->ply + 1 ) ){
                startMovingTile( B, B->plx, B->ply, down );
                B->gems -= tileType( B, B->plx, B->ply + 1 )->value;
                if( tileType( B, B->plx, B->ply + 1 )->id == dynamite ) B->dyns++;
                removeTile( B, tltps, B->plx, B->ply + 1 );
            }else
            if(     ifKeyLeftPressed()
                &&  ifTileCollectible( B, B->plx - 1, B->ply )
                && !ifTileIsExploding( B, B->plx - 1, B->ply )
                && !ifTileIsMoving( B, B->plx - 1, B->ply ) ){
                startMovingTile( B, B->plx, B->ply, left );
                B->gems -= tileType( B, B->plx - 1, B->ply )->value;
                if( tileType( B, B->plx - 1, B->ply )->id == dynamite ) B->dyns++;
                removeTile( B, tltps, B->plx - 1, B->ply );
            }
        }
        if( !(B->tiles[ B->plx ][ B->ply ].moving) && B->pushing_time <= 0 ){//kopanie
            if( ifKeyUpPressed() && ifTileDiggable( B, B->plx, B->ply - 1 ) && !ifTileIsExploding( B, B->plx, B->ply - 1 ) ){
                startMovingTile( B, B->plx, B->ply, up );
                removeTile( B, tltps, B->plx, B->ply - 1 );
            }else
            if( ifKeyRightPressed() && ifTileDiggable( B, B->plx + 1, B->ply ) && !ifTileIsExploding( B, B->plx + 1, B->ply ) ){
                startMovingTile( B, B->plx, B->ply, right );
                removeTile( B, tltps, B->plx + 1, B->ply );
            }else
            if( ifKeyDownPressed() && ifTileDiggable( B, B->plx, B->ply + 1 ) && !ifTileIsExploding( B, B->plx, B->ply + 1 ) ){
                startMovingTile( B, B->plx, B->ply, down );
                removeTile( B, tltps, B->plx, B->ply + 1 );
            }else
            if( ifKeyLeftPressed() && ifTileDiggable( B, B->plx - 1, B->ply ) && !ifTileIsExploding( B, B->plx - 1, B->ply ) ){
                startMovingTile( B, B->plx, B->ply, left );
                removeTile( B, tltps, B->plx - 1, B->ply );
            }
        }
        if( !(B->tiles[ B->plx ][ B->ply ].moving) && B->pushing_time <= 0 ){//pchanie
            if( ifKeyUpPressed() && ifTilePushable( B, B->plx, B->ply - 1 ) && !ifTileIsExploding( B, B->plx, B->ply - 1 ) && !ifTileIsMoving( B, B->plx, B->ply - 1 ) ){
                B->pushing_time = tileType( B, B->plx, B->ply - 1 )->pushing_time;
                B->pushing_dir = up;
            }else
            if( ifKeyRightPressed() && ifTilePushable( B, B->plx + 1, B->ply ) && !ifTileIsExploding( B, B->plx + 1, B->ply ) && !ifTileIsMoving( B, B->plx + 1, B->ply ) ){
                B->pushing_time = tileType( B, B->plx + 1, B->ply )->pushing_time;
                B->pushing_dir = right;
            }else
            if( ifKeyDownPressed() && ifTilePushable( B, B->plx, B->ply + 1 ) && !ifTileIsExploding( B, B->plx, B->ply + 1 ) && !ifTileIsMoving( B, B->plx, B->ply + 1 ) ){
                B->pushing_time = tileType( B, B->plx, B->ply + 1 )->pushing_time;
                B->pushing_dir = down;
            }else
            if( ifKeyLeftPressed() && ifTilePushable( B, B->plx - 1, B->ply ) && !ifTileIsExploding( B, B->plx - 1, B->ply ) && !ifTileIsMoving( B, B->plx - 1, B->ply ) ){
                B->pushing_time = tileType( B, B->plx - 1, B->ply )->pushing_time;
                B->pushing_dir = left;
            }
        }
    }
}

void destroyTileTypes( tile_type ** tltps ){
    free( (*tltps) );
}

void opp1Run( board * B, int x, int y, tile_type ** tltps )
{
    int nx, ny;
    enum direction dir;
    B->tiles[ x ][ y ].time1++;
    if( B->tiles[ x ][ y ].time1 >= animation_time_1 ){
        B->tiles[ x ][ y ].time1 = 0;
        B->tiles[ x ][ y ].state1++;
        B->tiles[ x ][ y ].state1 %= 2;
    }
    if( !ifTileIsMoving( B, x, y ) && !ifTileIsExploding( B, x, y ) ){
        dir = tileDirection( B, x, y );
        dir = leftDirection( dir );
        for( int i = 0; i < 4; i++ ){
            nx = dir_x( x, dir );
            ny = dir_y( y, dir );
            if( ifTileBlockedByPlayer( B, nx, ny ) ){
                burst( B, B->plx, B->ply, tileType( B, B->plx, B->ply )->explosion_type, tileType( B, B->plx, B->ply )->explosion_tile_type, tltps );
                burst( B, x, y, tileType( B, x, y )->explosion_type, tileType( B, x, y )->explosion_tile_type, tltps );
                break;
            }
            if( ifTileFreePlayerForOpp( B, nx, ny ) ){
                startMovingTile( B, x, y, dir );
                break;
            }
            dir = rightDirection( dir );
        }
    }
}

void opp2Run( board * B, int x, int y, tile_type ** tltps )
{
    int nx, ny;
    enum direction dir;
    B->tiles[ x ][ y ].time1++;
    if( B->tiles[ x ][ y ].time1 >= animation_time_1 ){
        B->tiles[ x ][ y ].time1 = 0;
        B->tiles[ x ][ y ].state1++;
        B->tiles[ x ][ y ].state1 %= 2;
    }
    if( !ifTileIsMoving( B, x, y ) && !ifTileIsExploding( B, x, y ) ){
        dir = tileDirection( B, x, y );
        dir = rightDirection( dir );
        for( int i = 0; i < 4; i++ ){
            nx = dir_x( x, dir );
            ny = dir_y( y, dir );
            if( ifTileBlockedByPlayer( B, nx, ny ) ){
                burst( B, B->plx, B->ply, tileType( B, B->plx, B->ply )->explosion_type, tileType( B, B->plx, B->ply )->explosion_tile_type, tltps );
                burst( B, x, y, tileType( B, x, y )->explosion_type, tileType( B, x, y )->explosion_tile_type, tltps );
                break;
            }
            if( ifTileFreePlayerForOpp( B, nx, ny ) ){
                startMovingTile( B, x, y, dir );
                break;
            }
            dir = leftDirection( dir );
        }
    }
}

void opp3Run( board * B, int x, int y, tile_type ** tltps )
{
    int nx, ny;
    enum direction dir;
    B->tiles[ x ][ y ].time1++;
    if( B->tiles[ x ][ y ].time1 >= animation_time_1 ){
        B->tiles[ x ][ y ].time1 = 0;
        B->tiles[ x ][ y ].state1++;
        B->tiles[ x ][ y ].state1 %= 2;
    }
    if( !ifTileIsMoving( B, x, y ) && !ifTileIsExploding( B, x, y ) ){
        dir = tileDirection( B, x, y );
        dir = rightDirection( dir );
        for( int i = 0; i < 4; i++ ){
            nx = dir_x( x, dir );
            ny = dir_y( y, dir );
            if( ifTileBlockedByPlayer( B, nx, ny ) ){
                burst( B, B->plx, B->ply, tileType( B, B->plx, B->ply )->explosion_type, tileType( B, B->plx, B->ply )->explosion_tile_type, tltps );
                burst( B, x, y, tileType( B, x, y )->explosion_type, tileType( B, x, y )->explosion_tile_type, tltps );
                break;
            }
            if( ifTileFreePlayerForOpp( B, nx, ny ) ){
                startMovingTile( B, x, y, dir );
                break;
            }
            dir = leftDirection( dir );
        }
    }
}

void dynfRun( board * B, int x, int y, tile_type ** tltps ){
    B->tiles[ x ][ y ].time1++;
    if( B->tiles[ x ][ y ].time1 % dynf_animation_time == 0 ){
        B->tiles[ x ][ y ].state1++;
        B->tiles[ x ][ y ].state1 %= 2;
    }
    if( B->tiles[ x ][ y ].time1 >= dynf_time ){
        burst( B, x, y, tileType( B, x, y )->explosion_type, tileType( B, x, y )->explosion_tile_type, tltps );
    }
}

void destroy_board( board * B ){
    for( int i = 0; i < B->width; i++ ){
        free( B->tiles[i] );
    }
    free( B->tiles );
}
