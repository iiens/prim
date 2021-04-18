/*!
 * \file interface_ncurses.h
 * \author Quentin Ra
 * \see interface.h
 *
 * This header contains any constants used in the interface.
 *
 */
#ifndef PRIM_INTERFACE_NCURSES_CONSTANTS_H
#define PRIM_INTERFACE_NCURSES_CONSTANTS_H

/*
 * CONFIG
 */

#define NC_DEFAULT_LOCALE "en_US.UTF-8"

/*
 * SIZE
 */

#define NC_MIN_ROW 23 //!< number of row saved
#define NC_MIN_COL 90 //!< number of cols saved

#define NC_ACTION_HEIGHT 2 //!< height of action window
#define NC_ACTION_BUF_SIZE 30 //!< maximum size of an action mapping

//todo: make something better
int GAME_WIDTH; //!< height of action window
#define NC_SCREEN_IS_SMALL COLS < 109
#define NC_SCREEN_IS_MEDIUM COLS < 164

/*
 * COLORS
 */

//todo: handle colors better
#define NC_ERROR_COLOR 1 //!< error color code
#define NC_SUCCESS_COLOR 2 //!< success color code

#endif //PRIM_INTERFACE_NCURSES_CONSTANTS_H
