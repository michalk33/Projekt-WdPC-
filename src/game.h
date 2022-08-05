#ifndef GAME_H
#define GAME_H

#include <stdbool.h>


#define tile_types_to_set 17
#define explosion_speed 200
#define player_speed 200
#define rock_speed 200
#define rock_pushing_time 300
#define animation_time_1 100
#define dynf_time 1000
#define dynf_animation_time 10


enum direction{
    up, right, down, left
};

enum tile_types{
    empty_tile, indestructible_wall, destructible_wall, rock, sand, player, bomb, pushable_wall, slippery_wall, emerald,
    opp1, opp2, opp3, blue_emerald, dynamite, dynamite_fire, exit_tile
};

enum bmps_ids{
    empty_tile_bmpid, indestructible_wall_bmpid, destructible_wall_bmpid, rock_bmpid, sand_bmpid, player_bmpid, bomb_bmpid,
    pushable_wall_bmpid, slippery_wall_bmpid, emerald_bmpid, opp1a_bmpid, opp1b_bmpid, opp2a_bmpid, opp2b_bmpid, opp3a_bmpid,
    opp3b_bmpid, blue_emerald_bmpid, dynamite_bmpid, dynamite_fire_a_bmpid, dynamite_fire_b_bmpid, exit_bmpid
};

enum explosion_types{
    small_exs, medium_exs, none_exs
};


typedef struct TILE_TYPE{
    bool destructible;
    bool pushable;
    bool slipping;
    bool gravity;
    bool smashable;
    bool smashing;
    bool rotating;
    bool diggable;
    bool exploding;
    bool smashing_player;
    bool collectible;
    bool killing_player;
    int movingSpeed;
    int bmpid;
    int id;
    int pushing_time;
    int value;
    enum explosion_types explosion_type;
    struct TILE_TYPE * explosion_tile_type;
} tile_type;

typedef struct TILE{
    tile_type * type;
    tile_type * explosion_type;
    bool moving;
    bool slipping;
    bool exploding;
    enum direction movingDirection;
    int movingState;
    int time;
    int time1;
    int state1;
} tile;

typedef struct BOARD{
    int width, height, plx, ply, pushing_time, gems, dyns, dyn_time;
    tile ** tiles;
    bool living, winning, player_on_dynamite;
    enum direction pushing_dir;
} board;


void setTileTypes( tile_type ** T );
void setTileType( tile_type * T, bool a, bool b, bool c, bool d, bool e, bool f, bool g, bool h,
                  bool i, bool j, bool k, bool l, int m, int n, int o, int p, int q, enum explosion_types r,
                  tile_type * s );

bool vertical                 ( enum direction dir );
bool ifPlayerIsMoving         ( board * B );
bool ifTileIsMoving           ( board * B, int x, int y );
bool ifTileIsSlipping         ( board * B, int x, int y );
bool ifTileIsExploding        ( board * B, int x, int y );
bool ifTileDiggable           ( board * B, int x, int y );
bool ifTileSmashable          ( board * B, int x, int y );
bool ifTilePushable           ( board * B, int x, int y );
bool ifTileCollectible        ( board * B, int x, int y );
bool ifTileFree               ( board * B, int x, int y );
bool ifTileFreePlayer         ( board * B, int x, int y );
bool ifTileFreePlayerForOpp   ( board * B, int x, int y );
bool ifPlayerIsLiving         ( board * B );
bool ifKillingPlayer          ( board * B, int x, int y );
bool ifTileBlockedByPlayer    ( board * B, int x, int y );
enum direction playerDirection( board * B );
enum direction tileDirection  ( board * B, int x, int y );
tile_type * tileType          ( board * B, int x, int y );
void removeTile               ( board * B, tile_type ** tltps, int x, int y );
void moveTile                 ( board * B, tile_type ** tltps, int x, int y );
void startMovingTile          ( board * B, int x, int y, enum direction dir );
void stopMovingTile           ( board * B, int x, int y );
void startSlippingTile        ( board * B, int x, int y, enum direction dir );
void startExploding           ( board * B, int x, int y, tile_type * exs_t, tile_type ** tltps );
void burst                    ( board * B, int x, int y, enum explosion_types exs, tile_type * exs_t, tile_type ** tltps );
void runBoard                 ( board * B, tile_type ** tltps );
void destroyTileTypes         ( tile_type ** tltps );
void opp1Run                  ( board * B, int x, int y, tile_type ** tltps );
void opp2Run                  ( board * B, int x, int y, tile_type ** tltps );
void opp3Run                  ( board * B, int x, int y, tile_type ** tltps );
void dynfRun                  ( board * B, int x, int y, tile_type ** tltps );

bool ifKeyRightPressed();
bool ifKeyLeftPressed();
bool ifKeyDownPressed();
bool ifKeyUpPressed();
bool ifSpacePressed();

enum direction pressedKeyDirection();

int dir_x( int x, enum direction dir );
int dir_y( int y, enum direction dir );

enum direction leftDirection ( enum direction dir );
enum direction rightDirection( enum direction dir );

void destroy_board( board * B );

void initBoard( board * B, tile_type ** tltps, int w, int h );
void boardCopy( board * B, board * D );

#endif
