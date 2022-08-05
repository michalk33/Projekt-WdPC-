#include "buttons.h"
#include "render.h"
#include "editor.h"
#include "files.h"
#include "game.h"
#include "run.h"


void run( volatile long * spd, timer_function speeincr )
{
    tile_type * chosenType;
    bool running = true;
    bool subState = true;
    int mb = 0;
    int nbw, nbh, edx, edy;
    int waitTime = 0;
    int currentLevel;
    enum run_state runState = main_menu;
    BITMAP * buffer  = NULL;
    BITMAP * buffer2 = NULL;
    bmps tilesBmps;
    tile_type * tileTypes;
    board Board;
    board BoardE;

    allegro_init();
    install_keyboard();
    set_color_depth( 16 );
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, window_x, window_y, 0, 0 );
    set_palette( default_palette );
    install_timer();
    install_int_ex( speeincr, BPS_TO_TIMER( frames_per_second ) );
    install_mouse();
    show_mouse( screen );
    unscare_mouse();

    if( !LoadBMPS( &tilesBmps ) ){
        DestroyBMPS( &tilesBmps );
        allegro_exit();
        return;
    }

    setTileTypes( &tileTypes );
    buffer  = create_bitmap( window_x, window_y );
    buffer2 = create_bitmap( board_x, board_y );

    chosenType = &(tileTypes[ empty_tile ]);

    button * game_buttons;
    button * main_menu_buttons;
    button * editor_buttons;
    button * editor_submenu_buttons;
    button * editor_submenu2_buttons;
    button * level_menu_buttons;

    game_buttons = malloc( number_of_game_buttons * sizeof( *game_buttons ) );
    main_menu_buttons = malloc( number_of_main_menu_buttons * sizeof( *main_menu_buttons ) );
    editor_buttons = malloc( number_of_editor_buttons * sizeof( *editor_buttons ) );
    editor_submenu_buttons = malloc( number_of_editor_submenu_buttons * sizeof( *editor_submenu_buttons ) );
    editor_submenu2_buttons = malloc( number_of_editor_submenu2_buttons * sizeof( *editor_submenu2_buttons ) );
    level_menu_buttons = malloc( number_of_level_menu_buttons * sizeof( *level_menu_buttons ) );

    createButton( &(game_buttons[ 0 ]), 650, 50, 100, 20, "RETURN" );
    createButton( &(game_buttons[ 1 ]), 650, 80, 100, 20, "RESTART" );
    createButton( &(game_buttons[ 2 ]), 650, 110, 100, 20, "NEXT LEVEL" );

    createButton( &(main_menu_buttons[ 0 ]), 350, 260, 100, 20, "PLAY" );
    createButton( &(main_menu_buttons[ 1 ]), 350, 290, 100, 20, "EDIT" );
    createButton( &(main_menu_buttons[ 2 ]), 350, 320, 100, 20, "EXIT" );

    createButton( &(editor_buttons[ 0 ]), 650, 50, 100, 20, "RETURN" );
    createButton( &(editor_buttons[ 1 ]), 650, 80, 100, 20, "PLAY" );
    createButton( &(editor_buttons[ 2 ]), 650, 110, 100, 20, "SAVE" );
    createButton( &(editor_buttons[ 3 ]), 650, 140, 100, 20, "NEW" );
    createButton( &(editor_buttons[ 4 ]), 650, 170, 100, 20, "MENU" );

    createButton( &(editor_submenu_buttons[ 0 ]), 320, 245, 20, 20, "-" );
    createButton( &(editor_submenu_buttons[ 1 ]), 460, 245, 20, 20, "+" );
    createButton( &(editor_submenu_buttons[ 2 ]), 320, 275, 20, 20, "-" );
    createButton( &(editor_submenu_buttons[ 3 ]), 460, 275, 20, 20, "+" );
    createButton( &(editor_submenu_buttons[ 4 ]), 350, 305, 100, 20, "CREATE" );
    createButton( &(editor_submenu_buttons[ 5 ]), 350, 335, 100, 20, "RETURN" );

    createButton( &(editor_submenu2_buttons[ 0 ]), 250, 90, 20, 20, "-" );
    createButton( &(editor_submenu2_buttons[ 1 ]), 530, 90, 20, 20, "+" );
    createButton( &(editor_submenu2_buttons[ 2 ]), 350, 120, 100, 20, "RETURN" );

    createButton( &(level_menu_buttons[ 0 ]), 320, 260, 20, 20, "-" );
    createButton( &(level_menu_buttons[ 1 ]), 460, 260, 20, 20, "+" );
    createButton( &(level_menu_buttons[ 2 ]), 350, 290, 100, 20, "NEXT" );
    createButton( &(level_menu_buttons[ 3 ]), 350, 320, 100, 20, "RETURN" );

    slot * editor_slots;

    editor_slots = malloc( number_of_slots * sizeof( *editor_slots ) );

    createSlot( &(editor_slots[ 0  ]), 160, 200, &(tileTypes [ empty_tile ]) );
    createSlot( &(editor_slots[ 1  ]), 220, 200, &(tileTypes [ sand ]) );
    createSlot( &(editor_slots[ 2  ]), 280, 200, &(tileTypes [ rock ]) );
    createSlot( &(editor_slots[ 3  ]), 340, 200, &(tileTypes [ bomb ]) );
    createSlot( &(editor_slots[ 4  ]), 400, 200, &(tileTypes [ indestructible_wall ]) );
    createSlot( &(editor_slots[ 5  ]), 460, 200, &(tileTypes [ destructible_wall ]) );
    createSlot( &(editor_slots[ 6  ]), 520, 200, &(tileTypes [ slippery_wall ]) );
    createSlot( &(editor_slots[ 7  ]), 580, 200, &(tileTypes [ pushable_wall ]) );
    createSlot( &(editor_slots[ 8  ]), 160, 260, &(tileTypes [ dynamite ]) );
    createSlot( &(editor_slots[ 9  ]), 220, 260, &(tileTypes [ emerald ]) );
    createSlot( &(editor_slots[ 10 ]), 280, 260, &(tileTypes [ blue_emerald ]) );
    createSlot( &(editor_slots[ 11 ]), 340, 260, &(tileTypes [ opp1 ]) );
    createSlot( &(editor_slots[ 12 ]), 400, 260, &(tileTypes [ opp2 ]) );
    createSlot( &(editor_slots[ 13 ]), 460, 260, &(tileTypes [ opp3 ]) );
    createSlot( &(editor_slots[ 14 ]), 520, 260, &(tileTypes [ exit_tile ]) );
    createSlot( &(editor_slots[ 15 ]), 580, 260, &(tileTypes [ player ]) );

    while( running ){
		while( (*spd) > 0 ){

            switch( runState ){
                case main_menu:
                    if( mb == 1 && mouse_b == 0 ){
                        for( int i = 0; i < number_of_main_menu_buttons; i++ ){
                            if( mouseOnButton( &(main_menu_buttons[ i ]) ) ){
                                switch( i ){
                                    case 0:
                                        runState = level_menu;
                                        subState = true;
                                        currentLevel = 0;
                                        break;
                                    case 1:
                                        runState = level_menu;
                                        subState = false;
                                        currentLevel = 0;
                                        break;
                                    case 2:
                                        running = false;
                                        break;
                                }
                                break;
                            }
                        }
                    }
                    break;
                case level_menu:
                    if( mb == 1 && mouse_b == 0 ){
                        for( int i = 0; i < number_of_level_menu_buttons; i++ ){
                            if( mouseOnButton( &(level_menu_buttons[ i ]) ) ){
                                switch( i ){
                                    case 0:
                                        if( currentLevel > 0 ) currentLevel--;
                                        break;
                                    case 1:
                                        if( subState ){
                                            if( currentLevel < number_of_levels - 1 ) currentLevel++;
                                        }else
                                        {
                                            if( currentLevel < number_of_editor_levels - 1 ) currentLevel++;
                                        }
                                        break;
                                    case 2:
                                        if( subState ){
                                            runState = game_menu;
                                            readFromFileG( &Board, currentLevel, &tileTypes );
                                        }else
                                        {
                                            runState = editor_menu;
                                            edx = 0;
                                            edy = 0;
                                            readFromFileE( &BoardE, currentLevel, &tileTypes );
                                        }
                                        break;
                                    case 3:
                                        runState = main_menu;
                                        break;
                                }
                                break;
                            }
                        }
                    }
                    break;
                case game_menu:
                    if( !Board.winning )
                        runBoard( &Board, &tileTypes );
                    if( mb == 1 && mouse_b == 0 ){
                        for( int i = 0; i < number_of_game_buttons; i++ ){
                            if( mouseOnButton( &(game_buttons[ i ]) ) ){
                                switch( i ){
                                    case 0:
                                        runState = subState ? main_menu : editor_menu;
                                        destroy_board( &Board );
                                        break;
                                    case 1:
                                        destroy_board( &Board );
                                        if( !subState )
                                            boardCopy( &Board, &BoardE );
                                        else
                                            readFromFileG( &Board, currentLevel, &tileTypes );
                                        break;
                                    case 2:
                                        if( currentLevel < number_of_levels - 1 && subState && Board.winning ){
                                            currentLevel++;
                                            destroy_board( &Board );
                                            readFromFileG( &Board, currentLevel, &tileTypes );
                                        }
                                        break;
                                }
                                break;
                            }
                        }
                    }
                    break;
                case editor_menu:
                    runEditor( &waitTime, &edx, &edy, &BoardE, &mb, chosenType, &tileTypes );
                    if( mb == 1 && mouse_b == 0 ){
                        for( int i = 0; i < number_of_editor_buttons; i++ ){
                            if( mouseOnButton( &(editor_buttons[ i ]) ) ){
                                switch( i ){
                                    case 0:
                                        runState = main_menu;
                                        destroy_board( &BoardE );
                                        break;
                                    case 1:
                                        runState = game_menu;
                                        boardCopy( &Board, &BoardE );
                                        break;
                                    case 2:
                                        saveToFile( &BoardE, currentLevel );
                                        break;
                                    case 3:
                                        runState = editor_submenu;
                                        nbw = 15;
                                        nbh = 15;
                                        break;
                                    case 4:
                                        runState = editor_submenu2;
                                        break;
                                }
                                break;
                            }
                        }
                    }
                    break;
                case editor_submenu:
                    if( mb == 1 && mouse_b == 0 ){
                        for( int i = 0; i < number_of_editor_submenu_buttons; i++ ){
                            if( mouseOnButton( &(editor_submenu_buttons[ i ]) ) ){
                                switch( i ){
                                    case 0:
                                        if( nbw > 15 ) nbw--;
                                        break;
                                    case 1:
                                        if( nbw < 100 ) nbw++;
                                        break;
                                    case 2:
                                        if( nbh > 15 ) nbh--;
                                        break;
                                    case 3:
                                        if( nbh < 100 ) nbh++;
                                        break;
                                    case 4:
                                        runState = editor_menu;
                                        destroy_board( &BoardE );
                                        initBoard( &BoardE, &tileTypes, nbw, nbh );
                                        edx = 0;
                                        edy = 0;
                                        break;
                                    case 5:
                                        runState = editor_menu;
                                        break;
                                }
                                break;
                            }
                        }
                    }
                    break;
                case editor_submenu2:
                    if( mb == 1 && mouse_b == 0 ){
                        for( int i = 0; i < number_of_editor_submenu2_buttons; i++ ){
                            if( mouseOnButton( &(editor_submenu2_buttons[ i ]) ) ){
                                switch( i ){
                                    case 0:
                                        if( BoardE.gems > 0 ) BoardE.gems--;
                                        break;
                                    case 1:
                                        if( BoardE.gems < 100 ) BoardE.gems++;
                                        break;
                                    case 2:
                                        runState = editor_menu;
                                        break;
                                }
                                break;
                            }
                        }
                        for( int i = 0; i < number_of_slots; i++ ){
                            if( mouseOnSlot( &(editor_slots[ i ]) ) ){
                                chosenType = editor_slots[ i ].tltp;
                                break;
                            }
                        }
                    }
                    break;
            }

            mb = mouse_b;

            if( waitTime > 0 ) waitTime--;

            (*spd)--;
		}
        clear_to_color( buffer, makecol( 220, 220, 200 ) );
        switch( runState ){
            case main_menu:
                renderMainMenu( buffer, &main_menu_buttons, number_of_main_menu_buttons );
                break;
            case game_menu:
                renderGame( buffer2, buffer, &Board, &tilesBmps, &game_buttons, number_of_game_buttons );
                break;
            case editor_menu:
                renderEditor( buffer2, buffer, &BoardE, &tilesBmps, &editor_buttons, number_of_editor_buttons, edx, edy );
                break;
            case editor_submenu:
                renderEditorSubmenu( buffer, &editor_submenu_buttons, number_of_editor_submenu_buttons, nbw, nbh );
                break;
            case editor_submenu2:
                renderEditorSubmenu2( buffer, &editor_submenu2_buttons, &editor_slots, number_of_editor_submenu2_buttons, number_of_slots, BoardE.gems, chosenType, &tilesBmps );
                break;
            case level_menu:
                renderLevelMenu( buffer, &level_menu_buttons, number_of_level_menu_buttons, currentLevel );
                break;
        }
		blit( buffer, screen, 0, 0, 0, 0, window_x, window_y );
    }

    free( game_buttons );
    free( main_menu_buttons );
    free( editor_buttons );
    free( editor_submenu_buttons );
    free( editor_submenu2_buttons );
    free( editor_slots );
    destroy_bitmap( buffer );
    destroy_bitmap( buffer2 );
    DestroyBMPS( &tilesBmps );
    destroyTileTypes( &tileTypes );
    allegro_exit();
}
