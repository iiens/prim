#include "headers/interface_ncurses.h" //!< base interface
#include "headers/interface_ncurses_utils.h" //!< this header
#include "../../../headers/utils/translation.h"
#include <string.h> //!< strlen, ...

char* lastMessage = NULL; //!< last message that we printed

void interface_ncurses_showActionField()
{
    // move at bottom left
    attron(A_BOLD); // bold
    mvwprintw(actionWindow, 1, 1, translation_get(TRANSLATE_ACTION_LABEL));
    move(LINES - 1, strlen(translation_get(TRANSLATE_ACTION_LABEL)) + 1);
    attroff(A_BOLD);
    wrefresh(actionWindow);
}

void interface_ncurses_showMessageWithColor( char* message, int color )
{
    interface_ncurses_hideError(); // hide previous error

    // show
    wattron(actionWindow, COLOR_PAIR(color));
    mvwprintw(actionWindow, ERROR_LINE, 1, message);
    wattroff(actionWindow, COLOR_PAIR(color));

    // save
    lastMessage = message;

    // refresh
    wrefresh(actionWindow);
}

void interface_ncurses_showError( ErrorCode e )
{
    char* message; //!< error message
    message = error_getMessage(e); // fetch message
    // show
    interface_ncurses_showMessageWithColor(message, ERROR_COLOR);
}

void interface_ncurses_showMessage( char* message )
{
    // show
    interface_ncurses_showMessageWithColor(message, SUCCESS_COLOR);
}


void interface_ncurses_hideError()
{
    if ( lastMessage == NULL )
        return;
    // delete line
    // we remove the first one, until there is no character
    for ( int i = 0; i < (int) strlen(lastMessage) + 1; ++i ) {
        mvwdelch(actionWindow, ERROR_LINE, 0); //
    }
    // refresh
    wrefresh(actionWindow);
    lastMessage = NULL;
}

char* interface_ncurses_gameTag( char* text, int value, char* buf, char* format )
{
    // create a format like %-30s: %d
    sprintf(format, "%s%d%s", "%.", 30, "s: %d");
    // write using format into buf
    sprintf(buf, format, text, value);
    // return buf
    return buf;
}

char* interface_ncurses_gameTag_type( char* text, void* value, char* buf, char* format, char* type )
{
    // create a format like %-30s: %d
    sprintf(format, "%s%d%s%s", "%.", 30, "s: ", type);
    // write using format into buf
    sprintf(buf, format, text, value);
    // return buf
    return buf;
}

void interface_ncurses_clearAction( char* buf )
{
    // delete each character one by one
    // we don't move x, since characters moves to the left each time we delete one
    for ( int i = 0; i < (int) strlen(buf); ++i ) {
        mvwdelch(actionWindow, 1, strlen(translation_get(TRANSLATE_ACTION_LABEL)));
    }
    // refresh
    wrefresh(actionWindow);
}

void interface_ncurses_show_menu_wait()
{
    wrefresh(mapWindow);
    // hide cursor
    noecho();
    cbreak();
    curs_set(FALSE);
    keypad(mapWindow, TRUE);
    // wait for input
    while ( getch() != BACK_MAPPING[0] );
    // reset
    echo();
    nocbreak();
    curs_set(TRUE);
    keypad(mapWindow, FALSE);
}

int writeLabel( int i, int j, int blocLength, char* tag, char* content )
{
    // tag such as cost:
    wattron(mapWindow, COLOR_PAIR(COLOR_GREEN));
    mvwprintw(mapWindow, 3 + blocLength * i, j, tag);
    wattroff(mapWindow, COLOR_PAIR(COLOR_GREEN));
    j += (int) strlen(tag);
    // value
    mvwprintw(mapWindow, 3 + blocLength * i, j, content);
    j += (int) strlen(content);
    return j;
}

void interface_ncurses_initListWindow( char* title )
{
    //clear
    wclear(mapWindow);
    wrefresh(mapWindow);
    interface_ncurses_clearAction(" ");

    //title centered
    mvwaddstr(mapWindow, 0, 0, title);
    waddstr(mapWindow, " ");
    waddstr(mapWindow, translation_get(TRANSLATE_GO_BACK_B));
}

void* interface_ncurses_showInActionField( Closure init, Closure check )
{
    bool leave = false; //!< do we need to leave ?
    void* result = NULL; //!< function result
    ErrorCode error = ERROR_INVALID_ACTION_SEQUENCE; //!< error code
    if ( init != NULL )
        init(NULL, NULL, NULL);
    do {
        char buf[ACTION_BUF_SIZE] = "";
        int read;
        int cursor = 0; //read <-> buf cursor

        // move at bottom left
        attron(A_BOLD); // bold
        mvwprintw(actionWindow, 1, 1, translation_get(TRANSLATE_ACTION_LABEL));
        move(MIN_ROW_SAVED - 1, strlen(translation_get(TRANSLATE_ACTION_LABEL)) + 1);
        attroff(A_BOLD);
        wrefresh(gameWindow);
        wrefresh(actionWindow);

        do {
            // read char by char
            read = getch();
            if ( read != '\n' ) {
                buf[cursor] = (char) read;
            }
            cursor++;
            if ( cursor == ACTION_BUF_SIZE - 1 ) { // same as enter
                break;
            }
        } while ( read != '\n' );
        // end str
        buf[cursor] = '\0';

        result = check(buf, &leave, &error);
        if ( leave ) { // leave set as true ?
            // clean inputted actionWindow
            interface_ncurses_clearAction(buf);
            interface_ncurses_hideError();
            // return result
            return result;
        }

        // clean inputted actionWindow
        interface_ncurses_clearAction(buf);

        // show error in red
        interface_showError(error);

        wrefresh(actionWindow);
        // and do again
    } while ( true );
}

char* interface_utils_getCaseContent( int x, int y, const Map* map )
{
    Case* c = map_getCase(x, y, map);
    CaseType t = case_getType(c);
    char* response = translation_fetchCaseTypeName(t);
    if ( response != NULL )
        // it's not a machine
        return response;
    else
        // it's a machine
        return translation_fetchMachineTypeName(machine_getType(case_getMachine(c)));
}

char interface_utils_parseOrientation( int x, int y, const Map* map )
{
    Case* c = map_getCase(x, y, map);
    if ( case_getType(c) == CASE_MACHINE ) {
        Machine* m = case_getMachine(c);
        MachineStuff s = machine_getType(m);; //!< machine stuff
        Direction d = DIRECTION_IN;
        switch ( s ) { // NOLINT(hicpp-multiway-paths-covered)
            case MS_COLLECTOR:
            case MS_CONVEYOR_BELT:
            case MS_RECYCLING_CENTER:
                d = DIRECTION_OUT;
                if ( machine_isOrientationTop(m, d) )
                    return L'8';
                if ( machine_isOrientationBottom(m, d) )
                    return L'2';
                if ( machine_isOrientationLeft(m, d) )
                    return L'4';
                if ( machine_isOrientationRight(m, d) )
                    return L'6';
                break;
            case MS_CROSS:
                if ( machine_isOrientationBottomRight(m, d) )
                    return L'3';
                if ( machine_isOrientationBottomLeft(m, d) )
                    return L'1';
                if ( machine_isOrientationTopLeft(m, d) )
                    return L'7';
                if ( machine_isOrientationTopRight(m, d) )
                    return L'9';
                break;
            case MS_JUNKYARD:
                return 'A'; // all
        }
    }
    return L' ';
}

void interface_ncurses_utils_init_colors()
{
    // colors goes from 0 to 255
    for ( short i = 0; i < 255; i++ ) {
        // init
        init_color(i, 0, 0, 0);
        // new color as foreground, black as background
        init_pair(i, i, COLOR_BLACK);
    }
}