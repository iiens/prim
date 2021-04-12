/*!
 * \file interface_ncurses.c
 * This file is supposed to contains all interface functions that
 * uses ncurses.
 */
#include "headers/interface_ncurses.h"
#include "headers/interface_ncurses_utils.h"
#include <locale.h>

//\////////////////////////////\//
//\/ interface related
//\////////////////////////////\//

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
    // allow UTF-8
    setlocale(LC_ALL, NC_DEFAULT_LOCALE);

    // init screen
    if ( initscr() == NULL ) {
        interface_close();
        return ERROR_INIT_NCURSES_INTERFACE;
    }

    // too small
    if ( LINES < NC_MIN_ROW ||  COLS < NC_MIN_COL ){
        interface_close();
        return ERROR_INIT_NCURSES_INTERFACE_SIZE;
    }

    // left menu (game menu) should not be too big nor too small
    if ( NC_SCREEN_IS_SMALL )
        GAME_WIDTH = COLS / 2;
    else if ( NC_SCREEN_IS_MEDIUM )
        GAME_WIDTH = (int) (COLS * 0.35);
    else
        GAME_WIDTH = (int) (COLS * 0.25);

    // create windows
    gameWindow = subwin(stdscr, LINES - NC_ACTION_HEIGHT, GAME_WIDTH, 0, 0);
    mapWindow = subwin(stdscr, LINES - NC_ACTION_HEIGHT, COLS - GAME_WIDTH, 0, GAME_WIDTH);
    actionWindow = subwin(stdscr, NC_ACTION_HEIGHT, COLS, LINES - NC_ACTION_HEIGHT, 0);
    fullWindow = subwin(stdscr, LINES - NC_ACTION_HEIGHT, COLS, 0, 0);
    // seems useless but boxing them
    box(gameWindow, ACS_VLINE, ACS_HLINE);
    box(actionWindow, ACS_VLINE, ACS_HLINE);
    box(mapWindow, ACS_VLINE, ACS_HLINE);
    box(fullWindow, ACS_VLINE, ACS_HLINE);

    //init colors
    if ( has_colors() == FALSE ) {
        interface_close();
        //Colors aren't supported in this terminal
        return ERROR_NO_NCURSES_COLORS_INTERFACE;
    }
    // start colors
    start_color();

    // declare colors
    interface_ncurses_utils_init_colors();

    // enable keyboard
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
    interface_ncurses_gameMenu(map); // 1
    interface_ncurses_showMap(map, false, false, false); // 2
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

ErrorCode interface_ncurses_endGame( const __attribute__((unused)) Map* map, ErrorCode e )
{
    clear(); // clear

    char* message; //!< show message

    if ( e == ERROR_GAME_WIN )
        message = translation_get(TRANSLATE_WIN);
    else
        message = translation_get(TRANSLATE_LOST);

    mvaddstr(LINES/2, 0, message);

    getch(); // wait

    refresh(); // show

    return NO_ERROR;
}