//
// Show related functions
//
#include <string.h>
#include "../headers/interface_ncurses.h"
#include "../headers/interface_ncurses_utils.h"
#include "../../../utils/utils_fun.h"

bool showResourceSaved;
bool showGarbageSaved;

void interface_ncurses_showMap( const Map* map, bool showResource, bool showGarbage, bool save )
{
    const int HEIGHT = map_getHeight(map); //!< height
    const int WIDTH = map_getWidth(map); //!< width
    char* number;

    if ( save ) {
        // save show resource
        showResourceSaved = showResource;
        showGarbageSaved = showGarbage;
    }

    wclear(mapWindow); //reset

    //         0  1  2  3 ... n
    //       +--+--+--+--+--+--+
    //          +  +  +  +  +  +
    //          +  +  +  +  +  +
    //          +  +  +  +  +  +
    for ( int j = 0; j < HEIGHT; j++ ) {
        mvwprintw(mapWindow, 0, j * 4 + 3, " %2d", j);
        if ( j == 0 )
            mvwprintw(mapWindow, 1, 1, "y +"); // starting +
        mvwprintw(mapWindow, 1, 4 + j * 4, "---+");
        for ( int i = 0; i < WIDTH; i++ ) {
            Case* c = map_getCase(j, i, map); //!< get case
            CaseType t = case_getType(c); //!< get case type to choose color

            attr_t color = interface_ncurses_utils_getCaseColor(c, t); //!< color

            if ( showResourceSaved || showGarbageSaved ){
                if ( showResource ) number = utils_intToString(case_getNumberResourcesByCase(c));
                else number = utils_intToString(case_getNumberGarbageByCase(c));
                // content
                wattron(mapWindow, color);
                mvwaddstr(mapWindow, i + 2, 4 + j * 4, number);
                free(number);
                wattroff(mapWindow, color);
            } else {
                char orientation = interface_utils_parseOrientation(j, i, map); //!< orientation
                // content
                wattron(mapWindow, color);
                mvwaddstr(mapWindow, i + 2, 4 + j * 4, interface_utils_getCaseContent(c,t));
                wattroff(mapWindow, color);
                // orientation
                mvwaddch(mapWindow, i + 2, 5 + j * 4, orientation);
            }

            // trailing +
            mvwaddstr(mapWindow, i + 2, 7 + j * 4,  "+");
        }
    }
    mvwprintw(mapWindow, 0, 2, "x");

    // fill the number before each row
    //         0  1  2  3 ... n
    //       +--+--+--+--+--+--+
    //     0 |  +  +  +  +  +  +
    //     1 |  +  +  +  +  +  +
    //     2 |  +  +  +  +  +  +
    //   ... |  +  +  +  +  +  +
    //     n |  +  +  +  +  +  +
    for ( int j = 0; j < HEIGHT; ++j ) {
        mvwprintw(mapWindow, j + 2, 0, "%3d|", j);
    }

    // fill the number before each row
    //         0  1  2  3 ... n
    //       +--+--+--+--+--+--+
    //     0 |  +  +  +  +  +  +
    //     1 |  +  +  +  +  +  +
    //     2 |  +  +  +  +  +  +
    //   ... |  +  +  +  +  +  +
    //     n |  +  +  +  +  +  +
    //       +--+--+--+--+--+--+
    mvwprintw(mapWindow, HEIGHT + 2, 3, "+");
    for ( int j = 0; j < WIDTH; ++j ) {
        waddstr(mapWindow, "---+");
    }

    // show
    wrefresh(mapWindow);
}

void interface_ncurses_showMachinesList()
{
    const int size = 5 + 5 + 3 + 3; //!< we allow 5 number as, result is "n E n DD" (3 are spaces and 3 are letters)
    char* p = (char*) malloc(size * sizeof(char)); //!< cost value
    char* pUpgrade = (char*) malloc(size * sizeof(char)); //!< cost upgrade value
    char* pDestroy = (char*) malloc(size * sizeof(char)); //!< cost destroy value
    int blocLength = 3; //!< number of line per machine

    if ( (NUMBER_OF_MACHINES * 3 + 4) < LINES )
        blocLength++;

    WINDOW* window;
    if ( NC_SCREEN_IS_MEDIUM ) {
        window = fullWindow; // we print in all the window (hiding game window)
    } else {
        window = mapWindow; // or just in the map window
    }

    //clear
    wclear(window);
    wrefresh(window);
    interface_ncurses_clearAction(" ");

    //title
    interface_ncurses_initListWindow(window, translation_get(TRANSLATE_MACHINE_LIST_TITLE));

    // print each machine
    for ( int i = 0; i < NUMBER_OF_MACHINES; ++i ) {
        int j = 0; //!< in which column we should add the next part, see below with cost line
        const MachineInfo* m = machineInfo_getMachineStuff(i + 1);
        char* desc = machineInfo_getDescription(m);
        char* name = translation_fetchMachineTypeFullName(machineInfo_getType(m));
        attr_t color = interface_ncurses_utils_getMachineColor(machineInfo_getType(m));
        char* orientation = machineInfo_getDefaultOrientationMessage(m);
        int id = machineInfo_getType(m);
        // size is two strings + 1 (size of id)
        char* head = (char*) malloc((
                strlen(translation_get(TRANSLATE_ID_TAG)) + 2 /* 2 digits */
                + 5 /*(=). */ + 1 /* \0 */ ) * sizeof(char)); //!< header of this machine
        sprintf(head, "(%s=%d). ",  translation_get(TRANSLATE_ID_TAG), id);

        // write prices
        sprintf(p, "%5d E %5d DD", machineInfo_getCostE(m), machineInfo_getCostDD(m));
        if ( machineInfo_getCanUpgrade(m) )
            sprintf(pUpgrade, "%5d E %5d DD", machineInfo_getCostUpgradeE(m), machineInfo_getCostUpgradeDD(m));
        sprintf(pDestroy, "%5d E %5d DD", machineInfo_getCostDestroyE(m), machineInfo_getCostDestroyDD(m));

        // machine header (in the right color)
        wattron(window, color);
        mvwaddstr(window, 2 + blocLength * i, 0, name);
        wattroff(window, color);
        waddstr(window, " ");
        waddstr(window, head);
        wattron(window, COLOR_PAIR(COLOR_YELLOW));
        waddstr(window, orientation);
        wattroff(window, COLOR_PAIR(COLOR_YELLOW));
        // machine description
        mvwaddstr(window, 3 + blocLength * i, 0, desc);

        // write in one line
        // >>> cost: vE vDD >>> cost upgrade: vE vDD >>> cost destroy: vE vDD
        // with v the value
        // cost:, ... are put in green
        //cost:
        j = interface_ncurses_utils_writeLabel(window, i, j, blocLength, translation_get(TRANSLATE_ML_COST_TAG), p); //cost
        if ( machineInfo_getCanUpgrade(m) )
            j = interface_ncurses_utils_writeLabel(window, i, j, blocLength, translation_get(TRANSLATE_ML_COST_UP_TAG),
                                                   pUpgrade); //cost upgrade
        interface_ncurses_utils_writeLabel(window, i, j, blocLength, translation_get(TRANSLATE_ML_COST_DESTROY_TAG),
                                           pDestroy); // cost destroy

        // free
        free(head);
    }

    // free all
    free(p);
    free(pUpgrade);
    free(pDestroy);

    interface_ncurses_show_menu_wait(window);
}

void interface_ncurses_showStaffList( const Map* map )
{
    const int TAKEN = NC_ACTION_HEIGHT + 2; // title + space right after
    const int STAFF_COUNT = NUMBER_OF_STAFFS; //!< number of staff
    int rowPerPage = 4; //!< number of row per page
    int start = 1; //!< we are starting from this index
    int ch; //!< character read
    int blocLength = 2; //!< number of line per staff
    char* number; //!< parsed number
    Dictionary* dictionary = map_getStaffDictionary(map);
    bool input = false; //!< stop input and reload view ?
    bool leave = false; //!< stop this menu and go back ?

    WINDOW* window;
    if ( NC_SCREEN_IS_MEDIUM ) {
        window = fullWindow; // we print in all the window (hiding game window)
    } else {
        window = mapWindow; // or just in the map window
    }

    if ( (rowPerPage * 3 + 6) < LINES )
        blocLength++; //increase since we can

    while ( (rowPerPage+1)*blocLength < LINES - TAKEN )
        rowPerPage++;

    // hide cursor
    noecho();
    cbreak();
    curs_set(FALSE);
    keypad(window, TRUE);
    wclear(window);

    // we will print staffs
    // then wait.
    // if the user changed page, we do a turn in the do while
    // else if it's b, we leave
    // else we wait for one of the two previous case in the while
    do {
        wclear(window);
        // init window
        interface_ncurses_initListWindow(window, translation_get(TRANSLATE_STAFF_LIST_TITLE));

        wattron(window, COLOR_PAIR(COLOR_RED));
        mvwaddstr(window, 2, 0, translation_get(TRANSLATE_STAFF_TAG));
        waddstr(window, " ");
        number = utils_intToString(start);
        waddstr(window, number);
        free(number);
        number = utils_intToString(min(start + rowPerPage - 1, STAFF_COUNT));
        waddstr(window, " ");
        waddstr(window, translation_get(TRANSLATE_TO_TAG));
        waddstr(window, " ");
        waddstr(window, number);
        waddstr(window, " ");
        waddstr(window, translation_get(TRANSLATE_ON_TAG));
        waddstr(window, " ");
        free(number);
        number = utils_intToString(STAFF_COUNT);
        waddstr(window, number);
        free(number);
        waddstr(window, ".");
        waddstr(window, translation_get(TRANSLATION_PRESS_ARROW_CHANGE_PAGE));
        wattroff(window, COLOR_PAIR(COLOR_RED));

        for ( int i = 0, j = start; i < rowPerPage && j <= STAFF_COUNT; i++, j++ ) {
            Staff* s = (Staff*) staff_getStaffByID(j);
            wattron(window, COLOR_PAIR(COLOR_GREEN));
            mvwaddstr(window, 4 + i * blocLength, 0, staff_getStaffName(s));
            waddstr(window, " (");
            waddstr(window, translation_get(TRANSLATE_ID_TAG));
            waddstr(window, "=");
            number = utils_intToString(staff_getStaffID(s));
            waddstr(window, number);
            waddstr(window, ") (");
            free(number);
            number = utils_intToString(staff_getStaffCostE(s));
            waddstr(window, number);
            waddstr(window, " E ");
            free(number);
            number = utils_intToString(staff_getStaffCostDD(s));
            waddstr(window, number);
            free(number);
            waddstr(window, " DD). ");
            waddstr(window, translation_get(TRANSLATE_OWNED_TAG));
            waddstr(window,": ");
            wattroff(window, COLOR_PAIR(COLOR_GREEN));
            wattron(window, COLOR_PAIR(COLOR_RED));
            number = utils_intToString(staff_getNumberStaffByID(dictionary, staff_getStaffID(s)));
            waddstr(window, number);
            wattroff(window, COLOR_PAIR(COLOR_RED));
            free(number);
            mvwaddstr(window, 5 + i * blocLength, 0, staff_getStaffDescription(s));
        }

        wrefresh(window);

        // wait for input
        while ( !input ) {
            ch = getch();
            switch ( ch ) { // NOLINT(hicpp-multiway-paths-covered)
                // page before
                case KEY_LEFT:
                    // we don't want to change our rowPerPage
                    // if last page didn't have enough rows
                    start -= rowPerPage;
                    if ( start < 1 )
                        start = 1;
                    input = true;
                    break;
                    // page after
                case KEY_RIGHT:
                    start += rowPerPage;
                    if ( start > STAFF_COUNT )
                        start -= rowPerPage; // go back
                    input = true;
                    break;
                    // back
                case 'b':
                    input = leave = true;
                    break;
                    // ignore
                default:
                    break;
            }
        }
        input = false;
    } while ( !leave );

    // reset
    echo();
    nocbreak();
    curs_set(TRUE);
    keypad(window, FALSE);
}

void interface_ncurses_listActions()
{
    const UserActionMapping* m; //!< store mapping
    char* actionName; //!< action name
    char* mapping; //!< action mapping
    int cols = 2; //!< number of columns

    WINDOW* window;
    if ( NC_SCREEN_IS_MEDIUM ) {
        window = fullWindow; // we print in all the window (hiding game window)
        cols = 1;
    } else {
        window = mapWindow; // or just in the map window
    }

    //clear
    wclear(window);
    interface_ncurses_clearAction(" ");

    //title
    interface_ncurses_initListWindow(window, translation_get(TRANSLATE_ACTION_LIST_TITLE));

    for ( int i = 0, j = 2; i < mapping_getSize(); j++ ) {
        // two per line
        for ( int k = 0; k < cols; k++ ) {
            int start = 0; //!< starting point
            if ( k == 1 )
                start = getmaxx(window) / 3; // second start at the middle of the screen
            m = mapping_get(i); // fetch
            actionName = translation_actionFetchName(m->actionID);
            mapping = m->key;
            // action
            // we print a name in green then :
            // then we print in red
            wattron(window, COLOR_PAIR(COLOR_GREEN));
            mvwaddstr(window, j, start, actionName);
            wattroff(window, COLOR_PAIR(COLOR_GREEN));
            waddstr(window, ":");
            wattron(window, COLOR_PAIR(COLOR_RED));
            waddstr(window, " `");
            waddstr(window, mapping);
            waddstr(window, "`");
            wattroff(window, COLOR_PAIR(COLOR_RED));
            i++;
        }
    }

    interface_ncurses_show_menu_wait(window);
}