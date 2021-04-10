/*!
 * \file interface_ncurses_utils.h
 * \author Quentin Ra
 * \see interface_ncurses.h
 *
 * Utilities functions for interface_ncurses.
 */
#ifndef PRIM_INTERFACE_NCURSES_UTILS_H
#define PRIM_INTERFACE_NCURSES_UTILS_H

#include <curses.h> //!< curse library
#include "interface_ncurses_constants.h" //!< all of our constants

WINDOW* gameWindow; //!< score, turn, ... information window
WINDOW* mapWindow; //!< game map window
WINDOW* actionWindow; //!< input action window
WINDOW* fullWindow; //!< full screen window (without action window ofc)

typedef void* (* Closure)( char* buff, bool* leave, ErrorCode* error ); //!< closure function

// utilities functions

/*! true is there is a last message, false else */
bool interface_ncurses_utils_hasLastMessage();

/*!
 * Show/Fill action field window
 */
void interface_ncurses_showActionField();

/*!
 * Convenience method to show a tag in show_map
 * @param[in] text tag name
 * @param[in] value tag value
 * @param[out] buf buffer (we will put the text in)
 * @param[out] format (we will put the format in)
 * @return
 */
char* interface_ncurses_gameTag( char* text, int value, char* buf, char* format );

/**
 * @see interface_ncurses_gameTag
 * @param text same as in interface_ncurses_gameTag
 * @param value same as in interface_ncurses_gameTag
 * @param buf same as in interface_ncurses_gameTag
 * @param format same as in interface_ncurses_gameTag
 * @param type %d for int, %s for char*... this is associated with value type
 * @return same as in interface_ncurses_gameTag
 */
char* interface_ncurses_gameTag_type( char* text, void* value, char* buf, char* format, char* type );

/*!
* Clear last actionWindow
* @param buf last actionWindow text
*/
void interface_ncurses_clearAction( char* buf );

/**
 * Wait function.
 * This function is waiting the user to press 'b' (back code).
 * It got created to be used in show_... like functions.
 * @param window the window we are waiting for
 */
void interface_ncurses_show_menu_wait(WINDOW* window);

/**
* Write some label in green in mapWindow
* frame at i,j coordinates
* @param window the window
* @param i y value
* @param j x value
* @param blocLength size of a bloc
* @param tag label/tag put in green, : me be added by yourself
* @param content content put right after the label
* @return x value after adding the label+text
*/
int interface_ncurses_utils_writeLabel( WINDOW* window, int i, int j, int blocLength, char* tag, char* content );

/**
 * Clean mapWindow and put in a title in the center. This method
 * is used when showing a list of something. We will use 'b' to go back.
 * @param window since the new version, mapWindow can be replaced by fullWindow
 * @param title a title
 */
void interface_ncurses_initListWindow( WINDOW* window, char* title );

/**
 * Show some message
 * @param message
 */
void interface_ncurses_showMessage( char* message );

/**
 * Take an init and a check function.
 * Ask for input until check is done.
 * @param init null or a closure that init the view, called after setting things up
 * @param check function that checks whether input is valid (then return) or not (ask again)
 * @return the result of the check function, if the check is successful
 */
void* interface_ncurses_showInActionField( Closure init, Closure check );

/**
 * Return one letter with what's inside this case
 * @param t case type
 * @param c case
 * @return the text
 */
char* interface_utils_getCaseContent( Case* c, CaseType t );

/**
 * Return orientation as a char
 * @param map the map
 * @param x col
 * @param y row
 * @return a char representation the orientation
 */
char interface_utils_parseOrientation( int x, int y, const Map* map );

// init
/**
 * Init all of ncurses colors
 * used in the interface.
 *
 * @see NCursesColors
 */
void interface_ncurses_utils_init_colors();

/**
 * Get a color for a case
 * @param c a case
 * @param t the type of the content
 * @return a color
 */
attr_t interface_ncurses_utils_getCaseColor(Case* c, CaseType t);

/**
 * Returns the color a of machine
 * @param t a machine
 * @return the color
 */
attr_t interface_ncurses_utils_getMachineColor(MachineStuff t);

// view
/*! Show game menu
 * @param map for the game info */
void interface_ncurses_gameMenu( const Map* map );

#endif //PRIM_INTERFACE_NCURSES_UTILS_H
