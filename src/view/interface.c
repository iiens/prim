/*!
 * This file is like the design pattern adaptor
 * also called wrapper.
 *
 * But since we are in C, we need to put a
 * if(...) then call method, we can't do something
 * more efficient and generic.
 */

#include "../../headers/interface.h"
#include "ncurses/interface_ncurses.h"

//todo: maybe allow this value to be changed in a option
// of our main (such as ./prim --no-ncurses
bool useNCurses = true; //!< true if we will use ncurses

//\////////////////////////////\//
//\/ interface related
//\////////////////////////////\//

// init
ErrorCode interface_init()
{
    if ( useNCurses ) {
        return interface_ncurses_init();
    }
    return ERROR_INIT_INTERFACE;
}

// reload
ErrorCode interface_reload( const Map* map )
{
    if ( useNCurses ) {
        return interface_ncurses_reload(map);
    }
    return ERROR_INIT_INTERFACE;
}

// close
ErrorCode interface_close()
{
    if ( useNCurses ) {
        return interface_ncurses_close();
    }
    return ERROR_INIT_INTERFACE;
}

//\////////////////////////////\//
//\/ Show related functions
//\////////////////////////////\//

void interface_showMap( const Map* map )
{
    if ( useNCurses ) {
        interface_ncurses_showMap(map);
        return;
    }
}

void interface_showStaffList( const Map* map )
{
    if ( useNCurses ) {
        interface_ncurses_showStaffList(map);
        return;
    }
}

void interface_showMachinesList()
{
    if ( useNCurses ) {
        interface_ncurses_showMachinesList();
        return;
    }
}

void interface_listActions()
{
    if ( useNCurses ) {
        interface_ncurses_listActions();
        return;
    }
}

//\////////////////////////////\//
//\/ ask for user input
//\////////////////////////////\//

// action
Action interface_chooseAction()
{
    if ( useNCurses ) {
        return interface_ncurses_chooseAction();
    }
    return ACTION_EXIT;
}

// difficulty
Difficulty interface_chooseDifficulty()
{
    if ( useNCurses ) {
        return interface_ncurses_chooseDifficulty();
    }
    return DIFFICULTY_EASY;
}

MachineSpec interface_askAddMachine()
{
    if ( useNCurses ) {
        return interface_ncurses_askAddMachine();
    }
    back = true; // go back
    return (MachineSpec) {};
}

Vector2D* interface_askMachineLocation()
{
    if ( useNCurses ) {
        return interface_ncurses_askMachineLocation();
    }
    back = true; // go back
    return NULL;
}

Staff* interface_askBuyStaff()
{
    if ( useNCurses ) {
        return interface_ncurses_askBuyStaff();
    }
    back = true;
    return NULL;
}

//\////////////////\//
//\/ others
//\///////////////\//

void interface_showError( ErrorCode e )
{
    if ( useNCurses ) {
        interface_ncurses_showError(e);
        return;
    }
}