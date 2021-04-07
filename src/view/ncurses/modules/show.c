//
// Show related functions
//
#include "../../../../headers/interface.h"
#include "../interface_ncurses.h"
#include "../interface_ncurses_utils.h"
#include "../../../../headers/utils/translation.h"
#include "../../../utils/utils_fun.h"
#include <string.h>

void interface_ncurses_showMap( const Map* map )
{
    const int END_BASE = 10; //!< 10 lines of games constants
    const int HEIGHT = map_getHeight(map); //!< height
    const int WIDTH = map_getWidth(map); //!< width
    char* buf = (char*) malloc(GAME_WIDTH * sizeof(char)); //!< see interface_ncurses_gameTag
    char* format = (char*) malloc(GAME_WIDTH * sizeof(char)); //!< see interface_ncurses_gameTag
    char* production = //!< string for the production mode
            map_getProductionFISA(map) == E_VALUE ? translation_get(TRANSLATE_GAME_E) : translation_get(TRANSLATE_GAME_DD);

    wclear(mapWindow); //reset
    wclear(gameWindow); //reset

    // init_view
    mvwprintw(gameWindow, 1, 1, translation_get(TRANSLATE_GAME_NAME));
    mvwprintw(gameWindow, 2, 1,
              interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_TURN), map_getNumberTurn(map), buf, format));
    mvwprintw(gameWindow, 3, 1,
              interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_E), map_getNumberE(map), buf, format));
    mvwprintw(gameWindow, 4, 1,
              interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_DD), map_getNumberDD(map), buf, format));
    mvwprintw(gameWindow, 5, 1,
              interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_FISE), map_getNumberFISE(map), buf, format));
    mvwprintw(gameWindow, 6, 1,
              interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_FISA), map_getNumberFISA(map), buf, format));
    mvwprintw(gameWindow, 7, 1,
              interface_ncurses_gameTag_type(translation_get(TRANSLATE_GAME_FISA_MODE), production, buf, format, "%s"));
    mvwprintw(gameWindow, 9, 1,
              interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_SCORE), map_getPlayerScore(map), buf, format));
    // END_BASE = 10
    mvwprintw(gameWindow, END_BASE, 1,
              interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_GARBAGE), map_getNumberPollution(map), buf, format));

    // then we have
    //todo: redo plz
    wattron(gameWindow, COLOR_PAIR(COLOR_RED));
    mvwaddstr(gameWindow, END_BASE+2, 1, "Legend");
    wattroff(gameWindow, COLOR_PAIR(COLOR_RED));

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    mvwaddstr(gameWindow, END_BASE+3, 1, "S");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": Source ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, "G");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": Gate ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    mvwaddstr(gameWindow, END_BASE+4, 1, "C");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": Collector ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, "B");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": CONVEYOR BELT ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    mvwaddstr(gameWindow, END_BASE+5, 1, "X");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": Cross ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, "R");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": RECYCLING CENTER ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    mvwaddstr(gameWindow, END_BASE+6, 1, "J");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": JUNKYARD ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    mvwaddstr(gameWindow, END_BASE+8, 1, "4");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": LEFT ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, "6");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": RIGHT ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, "8");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": TOP ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    mvwaddstr(gameWindow, END_BASE+9, 1, "2");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": BOTTOM ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, "7");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": TOP LEFT ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, "9");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": TOP RIGHT ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    mvwaddstr(gameWindow, END_BASE+10, 1, "1");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": BOTTOM LEFT ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, "3");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": BOTTOM RIGHT ");

    free(buf);
    free(format);

    //         0  1  2  3 ... n
    //       +--+--+--+--+--+--+
    //          +  +  +  +  +  +
    //          +  +  +  +  +  +
    //          +  +  +  +  +  +
    for ( int j = 0; j < HEIGHT; j++ ) {
        mvwprintw(mapWindow, 0, j * 3 + 3, " %2d", j);
        if ( j == 0 )
            mvwprintw(mapWindow, 1, 1, "y +"); // starting +
        mvwprintw(mapWindow, 1, 4 + j * 3, "--+");
        for ( int i = 0; i < WIDTH; i++ ) {
            char* content = interface_utils_getCaseContent(j, i, map); //!< case content
            char orientation = interface_utils_parseOrientation(j, i, map); //!< orientation
            mvwaddstr(mapWindow, i + 2, 4 + j * 3, content);
            mvwaddch(mapWindow, i + 2, 5 + j * 3, orientation);
            mvwaddstr(mapWindow, i + 2, 6 + j * 3, "+");
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
    mvwprintw(mapWindow, HEIGHT+2, 3, "+");
    for ( int j = 0; j < WIDTH; ++j ) {
        waddstr(mapWindow, "--+");
    }

    // show
    wrefresh(mapWindow);
}

void interface_ncurses_showMachinesList() //todo: remake without buffers
{
    const int size = 5 + 5 + 3 + 3; //!< we allow 5 number as, result is "n E n DD" (3 are spaces and 3 are letters)
    char* p = (char*) malloc(size * sizeof(char)); //!< cost value
    char* pUpgrade = (char*) malloc(size * sizeof(char)); //!< cost upgrade value
    char* pDestroy = (char*) malloc(size * sizeof(char)); //!< cost destroy value
    int blocLength = 2; //!< number of line per machine

    if ( (NUMBER_OF_MACHINES*3+4) < LINES )
        blocLength++;

    //clear
    wclear(mapWindow);
    wrefresh(mapWindow);
    interface_ncurses_clearAction(" ");

    //title
    interface_ncurses_initListWindow(translation_get(TRANSLATE_MACHINE_LIST_TITLE));

    // print each machine
    for ( int i = 0; i < NUMBER_OF_MACHINES; ++i ) {
        int j = 0; //!< in which column we should add the next part, see below with cost line
        const MachineInfo* m = machineInfo_getMachineStuff(i+1);
        char* desc = machineInfo_getDescription(m);
        char* name = translation_getMachineType(machineInfo_getType(m));
        int id = machineInfo_getType(m);
        // size is two strings + 1 (size of id)
        char* head = (char*) malloc(
                (strlen(name) + 1 + strlen(desc) + 1 + 10) * sizeof(char)); //!< header of this machine
        sprintf(head, " %s (id=%d) : %s", name, id, desc);

        // write prices
        sprintf(p, "%5d E %5d DD", machineInfo_getCostE(m), machineInfo_getCostDD(m));
        if ( machineInfo_getCanUpgrade(m) )
            sprintf(pUpgrade, "%5d E %5d DD", machineInfo_getCostUpgradeE(m), machineInfo_getCostUpgradeDD(m));
        sprintf(pDestroy, "%5d E %5d DD", machineInfo_getCostDestroyE(m), machineInfo_getCostDestroyDD(m));

        // "Machine:" - in red
        wattron(mapWindow, COLOR_PAIR(COLOR_RED));
        mvwprintw(mapWindow, 2 + blocLength * i, 0, translation_get(TRANSLATE_ML_MACHINE_TAG));
        wattroff(mapWindow, COLOR_PAIR(COLOR_RED));
        // machine description
        mvwprintw(mapWindow, 2 + blocLength * i, (int) strlen(translation_get(TRANSLATE_ML_MACHINE_TAG)), head);

        // write in one line
        // >>> cost: vE vDD >>> cost upgrade: vE vDD >>> cost destroy: vE vDD
        // with v the value
        // cost:, ... are put in green
        //cost:
        j = writeLabel(i, j, blocLength, translation_get(TRANSLATE_ML_COST_TAG), p); //cost
        if ( machineInfo_getCanUpgrade(m) )
            j = writeLabel(i, j, blocLength, translation_get(TRANSLATE_ML_COST_UP_TAG), pUpgrade); //cost upgrade
        writeLabel(i, j, blocLength, translation_get(TRANSLATE_ML_COST_DESTROY_TAG), pDestroy); // cost destroy

        // free
        free(head);
    }

    // free all
    free(p);
    free(pUpgrade);
    free(pDestroy);

    interface_ncurses_show_menu_wait();
}

void interface_ncurses_showStaffList( const Map* map )
{
    const int rowPerPage = 4; //!< number of row per page, todo: fetch from screen size
    const int STAFF_COUNT = NUMBER_OF_STAFFS; //!< number of staff
    int start = 1; //!< we are starting from this index
    int ch; //!< character read
    int blocLength = 2; //!< number of line per staff
    char* number; //!< parsed number
    bool input = false; //!< stop input and reload view ?
    bool leave = false; //!< stop this menu and go back ?

    //todo: unused
    // and seems to be an error
    (void) (map);

    if ( (rowPerPage*3+6) < LINES )
        blocLength++;

    // hide cursor
    noecho();
    cbreak();
    curs_set(FALSE);
    keypad(mapWindow, TRUE);
    wclear(mapWindow);

    // we will print staffs
    // then wait.
    // if the user changed page, we do a turn in the do while
    // else if it's b, we leave
    // else we wait for one of the two previous case in the while
    do {
        // init window
        interface_ncurses_initListWindow(translation_get(TRANSLATE_STAFF_LIST_TITLE));

        wattron(mapWindow, COLOR_PAIR(COLOR_RED));
        mvwaddstr(mapWindow, 2, 0, "Staff ");
        number = utils_intToString(start);
        waddstr(mapWindow, number);
        free(number);
        number = utils_intToString(min(start + rowPerPage - 1, STAFF_COUNT));
        waddstr(mapWindow, " to ");
        waddstr(mapWindow, number);
        waddstr(mapWindow, " on ");
        free(number);
        number = utils_intToString(STAFF_COUNT);
        waddstr(mapWindow, number);
        free(number);
        waddstr(mapWindow, ".");
        waddstr(mapWindow, translation_get(TRANSLATION_PRESS_ARROW_CHANGE_PAGE));
        wattroff(mapWindow, COLOR_PAIR(COLOR_RED));

        for ( int i = 0, j = start; i < rowPerPage && j <= STAFF_COUNT; i++, j++ ) {
            Staff* s = (Staff*) staff_getStaffByID(j);
            wattron(mapWindow, COLOR_PAIR(COLOR_GREEN));
            mvwaddstr(mapWindow, 4 + i * blocLength, 0, staff_getStaffName(s));
            waddstr(mapWindow, " (id=");
            number = utils_intToString(staff_getStaffID(s));
            waddstr(mapWindow, number);
            waddstr(mapWindow, ") (");
            free(number);
            number = utils_intToString(staff_getStaffCostE(s));
            waddstr(mapWindow, number);
            waddstr(mapWindow, " E ");
            free(number);
            number = utils_intToString(staff_getStaffCostDD(s));
            waddstr(mapWindow, number);
            free(number);
            waddstr(mapWindow, " DD). Owned: ");
            waddstr(mapWindow, "0");
            wattroff(mapWindow, COLOR_PAIR(COLOR_GREEN));
            mvwaddstr(mapWindow, 5 + i * blocLength, 0, staff_getStaffDescription(s));
        }

        wrefresh(mapWindow);

        // wait for input
        while ( !input ) {
            ch = getch();
            switch ( ch ) { // NOLINT(hicpp-multiway-paths-covered)
                // page before
                case KEY_LEFT:
                    // we don't want to change our rowPerPage
                    // if last page didn't have enough rows
                    start -= rowPerPage;
                    if ( start < 1 ) start = 1;
                    input = true;
                    break;
                    // page after
                case KEY_RIGHT:
                    start += rowPerPage;
                    if ( start > STAFF_COUNT ) start -= rowPerPage; // go back
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
    keypad(mapWindow, FALSE);
}

void interface_ncurses_listActions()
{
    char* actionName; //!< action name
    char* mapping; //!< action mapping

    //clear
    wclear(mapWindow);
    wrefresh(mapWindow);
    interface_ncurses_clearAction(" ");

    //title
    interface_ncurses_initListWindow(translation_get(TRANSLATE_ACTION_LIST_TITLE));

    int mid = getmaxx(mapWindow) / 2;

    for ( int i = 0, j = 2; i < USER_MAPPING_SIZE; i++, j++ ) {
        actionName = translation_actionFetchName(user_mapping[i].actionID);
        mapping = user_mapping[i].key;
        // first action
        wattron(mapWindow, COLOR_PAIR(COLOR_GREEN));
        mvwaddstr(mapWindow, j, 0, actionName);
        wattroff(mapWindow, COLOR_PAIR(COLOR_GREEN));
        waddstr(mapWindow, ":");
        wattron(mapWindow, COLOR_PAIR(COLOR_RED));
        waddstr(mapWindow, " `");
        waddstr(mapWindow, mapping);
        waddstr(mapWindow, "`");
        wattroff(mapWindow, COLOR_PAIR(COLOR_RED));
        i++;
        // second action
        actionName = translation_actionFetchName(user_mapping[i].actionID);
        mapping = user_mapping[i].key;
        wattron(mapWindow, COLOR_PAIR(COLOR_GREEN));
        mvwaddstr(mapWindow, j, mid, actionName);
        wattroff(mapWindow, COLOR_PAIR(COLOR_GREEN));
        waddstr(mapWindow, ":");
        wattron(mapWindow, COLOR_PAIR(COLOR_RED));
        waddstr(mapWindow, " `");
        waddstr(mapWindow, mapping);
        waddstr(mapWindow, "`");
        wattroff(mapWindow, COLOR_PAIR(COLOR_RED));
    }

    interface_ncurses_show_menu_wait();
}