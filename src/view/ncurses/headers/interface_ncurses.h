/*!
 * \file interface_ncurses.h
 * \author Quentin Ra
 * \see interface.h
 *
 * This header contains any functions related to the interactions
 * between the player and the game, using ncurses.
 */

#ifndef PRIM_INTERFACE_NCURSES_H
#define PRIM_INTERFACE_NCURSES_H

#include "../../../../headers/interface.h"
#include <curses.h>

//\////////////////////////////\//
//\/ interface declarations
//\////////////////////////////\//

/*! @see interface_init
 * @return see interface_init */
ErrorCode interface_ncurses_init();

/*! @see interface_reload
 * @param map see interface_reload
 * @return see interface_reload */
ErrorCode interface_ncurses_reload( const Map* map );

/*! @see interface_close
 * @return see interface_close */
ErrorCode interface_ncurses_close();

//\////////////////////////////\//
//\/ game interface declarations
//\////////////////////////////\//

/*! @see interface_chooseDifficulty
 * @return see interface_chooseDifficulty */
Difficulty interface_ncurses_chooseDifficulty();

/*! @see interface_showMap
 * @param map see interface_showStaffList */
void interface_ncurses_showMap( const Map* map );

/*! @see interface_showStaffList
 * @param map see interface_showStaffList */
void interface_ncurses_showStaffList( const Map* map );

/*! @see interface_showMachinesList */
void interface_ncurses_showMachinesList();

/*! @see interface_list_actions */
void interface_ncurses_listActions();

/*! @see interface_chooseAction
 * @return see interface_chooseAction */
Action interface_ncurses_chooseAction();

/*! @see interface_askAddMachine
 * @return see interface_askAddMachine */
MachineSpec interface_ncurses_askAddMachine();

/*! @see interface_askMachineLocation
 * @return see interface_askMachineLocation */
Vector2D* interface_ncurses_askMachineLocation();

/*! @see interface_askBuyStaff
 * @return see interface_askBuyStaff */
int interface_ncurses_askBuyStaff();

/*! @see interface_showError
 * @param e see interface_showError */
void interface_ncurses_showError( ErrorCode e );

/*! @see interface_hideError */
void interface_ncurses_hideError();

#endif //PRIM_INTERFACE_NCURSES_H
