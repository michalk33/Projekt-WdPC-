#ifndef RUNPROJECT_H
#define RUNPROJECT_H


#define frames_per_second 1000
#define number_of_game_buttons 3
#define number_of_main_menu_buttons 3
#define number_of_editor_buttons 5
#define number_of_editor_submenu_buttons 6
#define number_of_editor_submenu2_buttons 3
#define number_of_level_menu_buttons 4
#define number_of_slots 16
#define number_of_levels 10
#define number_of_editor_levels 10

enum run_state{
    main_menu, game_menu, editor_menu, editor_submenu, editor_submenu2, level_menu
};

typedef void( * timer_function )();

void run( volatile long * spd, timer_function speeincr );


#endif
