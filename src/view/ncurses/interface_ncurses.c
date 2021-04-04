/*!
 * \file interface_ncurses.c
 * This file is supposed to contains all interface functions that
 * uses ncurses.
 */
#include "../../../headers/interface.h"
#include "interface_ncurses.h"
#include "interface_ncurses_utils.h"
#include <locale.h>

// References
// https://manpages.debian.org/testing/ncurses-doc/keypad.3ncurses.en.html
// https://stackoverflow.com/questions/8108634/global-variables-in-header-file
// https://techlister.com/linux/creating-menu-with-ncurses-in-c/1293/
// https://stackoverflow.com/questions/66540302/c99-utf8-characters-with-ncurses
// https://stackoverflow.com/questions/33322601/clearing-a-field-buffer-in-ncurses
// adding colors
// - init_color(CODE_MY, 0,0,0);
// - init_pair(MY_COLOR, 124, COLOR_BLACK);

//\////////////////////////////\//
//\/ interface related
//\////////////////////////////\//

int MIN_ROW_SAVED = 17;
int MIN_COL_SAVED = 164;

// we init the main screen
// 3 sub windows :
// - gameWindow : game info (turn, ...)
// - mapWindow : where we show the map
// - actionWindow : where we allow the user to print something, errors are here too
//
// we also need to init colors, charset, ...
//
ErrorCode interface_ncurses_init()
{
    //allow UTF-8
    setlocale(LC_ALL, "fr_FR.UTF-8");

    //init screen
    if ( initscr() == NULL ) {
        interface_close();
        //Colors aren't supported in this terminal
        return ERROR_INIT_NCURSES_INTERFACE;
    }

    if ( LINES > MIN_ROW_SAVED )
        MIN_ROW_SAVED = LINES;

    if ( resize_term(MIN_ROW_SAVED, MIN_COL_SAVED) == -1 ) {
        interface_close();
        return ERROR_INIT_NCURSES_INTERFACE_SIZE;
    }

    gameWindow = subwin(stdscr, LINES - ACTION_HEIGHT, GAME_WIDTH, 0, 0);
    mapWindow = subwin(stdscr, LINES - ACTION_HEIGHT, COLS - GAME_WIDTH, 0, GAME_WIDTH);
    actionWindow = subwin(stdscr, ACTION_HEIGHT, COLS, LINES - ACTION_HEIGHT, 0);

    box(gameWindow, ACS_VLINE, ACS_HLINE);
    box(actionWindow, ACS_VLINE, ACS_HLINE);
    box(mapWindow, ACS_VLINE, ACS_HLINE);

    //init colors
    if ( has_colors() == FALSE ) {
        interface_close();
        //Colors aren't supported in this terminal
        return ERROR_NO_NCURSES_COLORS_INTERFACE;
    }
    start_color();

    // declare colors
    init_pair(ERROR_COLOR, COLOR_RED, COLOR_BLACK);
    init_pair(SUCCESS_COLOR, COLOR_GREEN, COLOR_BLACK);

    // ...
    keypad(stdscr, TRUE);
    // cbreak(); // don't save into buffer until <enter> pressed
    nocbreak();
    // noecho(); //show printed charaters
    echo();
    clear();

    return NO_ERROR;
}

// here we are supposed
// 1- show the game menu
// 2- show the map
// 3- show input action field
// and save this map in a pointer
ErrorCode interface_ncurses_reload( const Map* map )
{
    interface_showMap(map); // 1 and 2
    interface_ncurses_showActionField(); // 3
    return NO_ERROR;
}

ErrorCode interface_ncurses_close()
{
    // free main window
    bool r = endwin();
    if ( !r )
        return ERROR_CLOSE_INTERFACE;
    return NO_ERROR;
}