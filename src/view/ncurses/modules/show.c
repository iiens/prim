//
// Show related functions
//
#include <string.h>
#include "../headers/interface_ncurses.h"
#include "../headers/interface_ncurses_utils.h"
#include "../../../utils/utils_fun.h"

void interface_ncurses_showMap( const Map* map )
{
    const int HEIGHT = map_getHeight(map); //!< height
    const int WIDTH = map_getWidth(map); //!< width

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
            Case* c = map_getCase(j, i, map);
            CaseType t = case_getType(c);

            /*char* content = interface_utils_getCaseContent(j, i, map); //!< case content
            char orientation = interface_utils_parseOrientation(j, i, map); //!< orientation
            mvwaddstr(mapWindow, i + 2, 4 + j * 3, content);
            mvwaddch(mapWindow, i + 2, 5 + j * 3, orientation);*/

            attr_t color; //!< color
            switch ( t ) { //todo: legend
                case CASE_VIDE: color = COLOR_PAIR(COLOR_MAGENTA); break;
                case CASE_GATE: color = COLOR_PAIR(COLOR_CYAN); break;
                case CASE_SOURCE: color = COLOR_PAIR(COLOR_YELLOW); break;
                case CASE_MACHINE:
                    switch ( machine_getType(case_getMachine(c)) ) {
                        case MS_COLLECTOR:
                            color = COLOR_PAIR(COLOR_GREEN);
                            break;
                        case MS_CONVEYOR_BELT:
                        case MS_CROSS:
                            color = COLOR_PAIR(COLOR_WHITE);
                            break;
                        case MS_RECYCLING_CENTER:
                            color = COLOR_PAIR(COLOR_RED);
                            break;
                        case MS_JUNKYARD:
                            color = COLOR_PAIR(COLOR_BLUE);
                            break;
                    }

                    break;
            }
            wattron(mapWindow, color);
            mvwaddstr(mapWindow, i + 2, 4 + j * 4, interface_utils_getCaseContent(c,t));
            wattroff(mapWindow, color);
            wattron(mapWindow, COLOR_PAIR(COLOR_MAGENTA));
            mvwaddstr(mapWindow, i + 2, 7 + j * 4,  "+");
            wattroff(mapWindow, COLOR_PAIR(COLOR_MAGENTA));
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

void interface_ncurses_showMachinesList() //todo: remake without buffers
{
    const int size = 5 + 5 + 3 + 3; //!< we allow 5 number as, result is "n E n DD" (3 are spaces and 3 are letters)
    char* p = (char*) malloc(size * sizeof(char)); //!< cost value
    char* pUpgrade = (char*) malloc(size * sizeof(char)); //!< cost upgrade value
    char* pDestroy = (char*) malloc(size * sizeof(char)); //!< cost destroy value
    int blocLength = 3; //!< number of line per machine

    if ( (NUMBER_OF_MACHINES * 3 + 4) < LINES )
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
        const MachineInfo* m = machineInfo_getMachineStuff(i + 1);
        char* desc = machineInfo_getDescription(m);
        char* name = translation_getMachineType(machineInfo_getType(m));
        int id = machineInfo_getType(m);
        // size is two strings + 1 (size of id)
        char* head = (char*) malloc(
                (strlen(name) + 1 + 1 + 10) * sizeof(char)); //!< header of this machine
        sprintf(head, " %s (%s=%d)", name, translation_get(TRANSLATE_ID_TAG) ,id);

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
        mvwaddstr(mapWindow, 3 + blocLength * i, 0, desc);

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
    Dictionary* dictionary = map_getStaffDictionary(map);
    bool input = false; //!< stop input and reload view ?
    bool leave = false; //!< stop this menu and go back ?

    if ( (rowPerPage * 3 + 6) < LINES )
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
        mvwaddstr(mapWindow, 2, 0, translation_get(TRANSLATE_STAFF_TAG));
        waddstr(mapWindow, " ");
        number = utils_intToString(start);
        waddstr(mapWindow, number);
        free(number);
        number = utils_intToString(min(start + rowPerPage - 1, STAFF_COUNT));
        waddstr(mapWindow, " ");
        waddstr(mapWindow, translation_get(TRANSLATE_TO_TAG));
        waddstr(mapWindow, " ");
        waddstr(mapWindow, number);
        waddstr(mapWindow, " ");
        waddstr(mapWindow, translation_get(TRANSLATE_ON_TAG));
        waddstr(mapWindow, " ");
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
            waddstr(mapWindow, " (");
            waddstr(mapWindow, translation_get(TRANSLATE_ID_TAG));
            waddstr(mapWindow, "=");
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
            waddstr(mapWindow, " DD). ");
            waddstr(mapWindow, translation_get(TRANSLATE_OWNED_TAG));
            waddstr(mapWindow,": ");
            wattroff(mapWindow, COLOR_PAIR(COLOR_GREEN));
            wattron(mapWindow, COLOR_PAIR(COLOR_RED));
            number = utils_intToString(staff_getNumberStaffByID(dictionary, staff_getStaffID(s)));
            waddstr(mapWindow, number);
            wattroff(mapWindow, COLOR_PAIR(COLOR_RED));
            free(number);
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
    keypad(mapWindow, FALSE);
}

void interface_ncurses_listActions()
{
    const UserActionMapping* m; //!< store mapping
    char* actionName; //!< action name
    char* mapping; //!< action mapping

    //clear
    wclear(mapWindow);
    interface_ncurses_clearAction(" ");

    //title
    interface_ncurses_initListWindow(translation_get(TRANSLATE_ACTION_LIST_TITLE));

    for ( int i = 0, j = 2; i < mapping_getSize(); j++ ) {
        // two per line
        for ( int k = 0; k < 2; k++ ) {
            int start = 0; //!< starting point
            if ( k == 1 )
                start = getmaxx(mapWindow) / 2; // second start at the middle of the screen
            m = mapping_get(i); // fetch
            actionName = translation_actionFetchName(m->actionID);
            mapping = m->key;
            // action
            // we print a name in green then :
            // then we print in red
            wattron(mapWindow, COLOR_PAIR(COLOR_GREEN));
            mvwaddstr(mapWindow, j, start, actionName);
            wattroff(mapWindow, COLOR_PAIR(COLOR_GREEN));
            waddstr(mapWindow, ":");
            wattron(mapWindow, COLOR_PAIR(COLOR_RED));
            waddstr(mapWindow, " `");
            waddstr(mapWindow, mapping);
            waddstr(mapWindow, "`");
            wattroff(mapWindow, COLOR_PAIR(COLOR_RED));
            i++;
        }
    }

    interface_ncurses_show_menu_wait();
}