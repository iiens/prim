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
    #include "../../../headers/map.h" //!< map, since we are using the Map (show, ...)

    #define ERROR_COLOR 1 //!< error color code
    #define SUCCESS_COLOR 2 //!< success color code

    #define ACTION_HEIGHT 2 //!< height of action window
    #define GAME_WIDTH (COLS/4) //!< height of action window

    #define ACTION_BUF_SIZE 30 //!< maximum size of an action mapping

    #define ERROR_LINE 0 //!< error line in action window

    #define BACK_MAPPING "b" //!< back value used everywhere

    WINDOW* gameWindow; //!< score, turn, ... information window
    WINDOW* mapWindow; //!< game map window
    WINDOW* actionWindow; //!< input action window

    extern int MIN_ROW_SAVED; //!< number of row saved
    extern int MIN_COL_SAVED; //!< number of cols saved
    extern char* lastMessage;

    typedef void* (* Closure)( char* buff, bool* leave, ErrorCode* error ); //!< closure function

    // utilities functions
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
     */
    void interface_ncurses_show_menu_wait();

    /**
    * Write some label in green in mapWindow
    * frame at i,j coordinates
    * @param i y value
    * @param j x value
    * @param tag label/tag put in green, : me be added by yourself
    * @param content content put right after the label
    * @return x value after adding the label+text
    */
    int writeLabel( int i, int j, char* tag, char* content );

    /**
     * Clean mapWindow and put in a title in the center. This method
     * is used when showing a list of something. We will use 'b' to go back.
     * @param title a title
     */
    void interface_ncurses_initListWindow( char* title );

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
     * @param x col
     * @param y row
     * @param map map
     * @return
     */
    char* interface_utils_getCaseContent( int x, int y, const Map* map );

#endif //PRIM_INTERFACE_NCURSES_UTILS_H
