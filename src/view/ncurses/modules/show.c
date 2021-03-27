//
// Show related functions
//
#include "../../../../headers/interface.h"
#include "../interface_ncurses.h"
#include "../interface_ncurses_utils.h"
#include "../../translation.h"
#include "../../../utils/utils.h"
#include <string.h>

void interface_ncurses_showMap(const Map* map)
{
    wclear(mapWindow); //reset

    char* buf = (char*) malloc(GAME_WIDTH * sizeof(char));
    char* format = (char*) malloc(GAME_WIDTH * sizeof(char));

    char* production =
            map->numberFISA == E_VALUE ? translation_get(TRANSLATE_GAME_E) : translation_get(TRANSLATE_GAME_DD);

    // init_view
    mvwprintw(gameWindow, 1, 1, translation_get(TRANSLATE_GAME_NAME));
    mvwprintw(gameWindow, 2, 1,
              interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_TURN), map->turn, buf, format));
    mvwprintw(gameWindow, 3, 1, interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_E), map->E, buf, format));
    mvwprintw(gameWindow, 4, 1,
              interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_DD), map->DD, buf, format));
    mvwprintw(gameWindow, 5, 1,
              interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_FISE), map->numberFISE, buf, format));
    mvwprintw(gameWindow, 6, 1,
              interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_FISA), map->numberFISA, buf, format));
    mvwprintw(gameWindow, 7, 1,
              interface_ncurses_gameTag_type(translation_get(TRANSLATE_GAME_FISA_MODE), production, buf, format,
                                             "%s"));
    //todo: manage number of staffs
    mvwprintw(gameWindow, 8, 1, interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_STAFFS), 0, buf, format));
    mvwprintw(gameWindow, 9, 1,
              interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_SCORE), map->score, buf, format));
    mvwprintw(gameWindow, 10, 1,
              interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_GARBAGE), map->pollution, buf, format));

    free(buf);
    free(format);

    //         0  1  2  3 ... n
    //       +--+--+--+--+--+--+
    //          +  +  +  +  +  +
    //          +  +  +  +  +  +
    //          +  +  +  +  +  +
    for ( int j = 0; j < map->height; j++ ) {
        mvwprintw(mapWindow, 0, j * 3 + 3, " %2d", j);
        if ( j == 0 ) mvwprintw(mapWindow, 1, 3, "+"); // starting +
        mvwprintw(mapWindow, 1, 4 + j * 3, "--+");
        for ( int i = 0; i < map->width; i++ ) {
            mvwaddstr(mapWindow, i + 2, 4 + j * 3, " ");
            //todo: put item inside
            mvwaddstr(mapWindow, i + 2, 5 + j * 3, (char*) L" ");
            mvwaddstr(mapWindow, i + 2, 6 + j * 3, "+");
        }
    }

    // fill the number before each row
    //         0  1  2  3 ... n
    //       +--+--+--+--+--+--+
    //     0 |  +  +  +  +  +  +
    //     1 |  +  +  +  +  +  +
    //     2 |  +  +  +  +  +  +
    //   ... |  +  +  +  +  +  +
    //     n |  +  +  +  +  +  +
    // we don't put a +--+--+--+--+--+--+ at the end
    // since screens are all ready to short on height
    for ( int j = 0; j < map->height; ++j ) {
        mvwprintw(mapWindow, j + 2, 0, "%3d|", j);
    }

    // show
    wrefresh(mapWindow);
}

void interface_ncurses_showMachinesList()
{
    const int LINE_COUNT = NUMBER_OF_MACHINES;
    const int size = 5 + 5 + 3 + 3; //!< we allow 5 number as, result is "n E n DD" (3 are spaces and 3 are letters)
    char* p = (char*) malloc(size * sizeof(char)); //!< cost value
    char* pUpgrade = (char*) malloc(size * sizeof(char)); //!< cost upgrade value
    char* pDestroy = (char*) malloc(size * sizeof(char)); //!< cost destroy value

    //clear
    wclear(mapWindow);
    wrefresh(mapWindow);
    interface_ncurses_clearAction(" ");

    //title
    interface_ncurses_initListWindow(translation_get(TRANSLATE_MACHINE_LIST_TITLE));

    // print each machine
    for ( int i = 0; i < LINE_COUNT; ++i ) {
        int j = 0; //!< in which column we should add the next part, see below with cost line
        MachineInfo m = machine_list[i];
        char* desc = m.description;
        char* name = translation_getMachineType(m.type);
        int id = m.type;
        // size is two strings + 1 (size of id)
        char* head = (char*) malloc(
                (strlen(name) + 1 + strlen(desc) + 1 + 10) * sizeof(char)); //!< header of this machine
        sprintf(head, " %s (id=%d) : %s", name, id, desc);

        // write prices
        sprintf(p, "%5d E %5d DD", m.costE, m.costDD);
        if ( m.canUpgrade ) sprintf(pUpgrade, "%5d E %5d DD", m.costUpgradeE, m.costUpgradeDD);
        sprintf(pDestroy, "%5d E %5d DD", m.costDestroyE, m.costDestroyDD);

        // "Machine:" - in red
        wattron(mapWindow, COLOR_PAIR(COLOR_RED));
        mvwprintw(mapWindow, 2 + 2 * i, 0, translation_get(TRANSLATE_ML_MACHINE_TAG));
        wattroff(mapWindow, COLOR_PAIR(COLOR_RED));
        // machine description
        mvwprintw(mapWindow, 2 + 2 * i, (int) strlen(translation_get(TRANSLATE_ML_MACHINE_TAG)), head);

        // write in one line
        // >>> cost: vE vDD >>> cost upgrade: vE vDD >>> cost destroy: vE vDD
        // with v the value
        // cost:, ... are put in green
        //cost:
        j = writeLabel(i, j, translation_get(TRANSLATE_ML_COST_TAG), p); //cost
        if ( m.canUpgrade )
            j = writeLabel(i, j, translation_get(TRANSLATE_ML_COST_UP_TAG), pUpgrade); //cost upgrade
        writeLabel(i, j, translation_get(TRANSLATE_ML_COST_DESTROY_TAG), pDestroy); // cost destroy

        // free
        free(head);
    }

    // free all
    free(p);
    free(pUpgrade);
    free(pDestroy);

    interface_ncurses_show_menu_wait();
}

void interface_ncurses_showStaffList(const Map* map)
{
    const int rowPerPage = 4; //!< number of row per page, todo: fetch from screen size
    int start = 0; //!< we are starting from this index
    int max = NUMBER_OF_STAFFS; //!< number of staff
    int ch; //!< character read
    char* number; //!< parsed number
    bool input = false; //!< stop input and reload view ?
    bool leave = false; //!< stop this menu and go back ?
    char* buff = (char*) malloc(
            (strlen(translation_get(TRANSLATION_LIST_STAFF_INDEX)) + 3 * 3 +
             (int) strlen(translation_get(TRANSLATION_PRESS_ARROW_CHANGE_PAGE)))
            *
            sizeof(char)
    ); //!< buffer that show the number of the page we are on
    //example "Laurence Bourard (id=8) (200 E 100 DD)";
    int textLength = 100 /* max name size */ + 7 /* spaces */
                     + 4 /* ( and ) */ + 11 /* id= E and DD and Owned: */
                     + 3 * 5 /* 3 numbers, 5 chars max*/; //!< size of the teacher name buffer
    char* teacherHeader = (char*) malloc(textLength * sizeof(char)); //!< teacher name header buffer

    //todo: unused
    (void) (map);

    // hide cursor
    noecho();
    cbreak();
    curs_set(FALSE);
    keypad(mapWindow, TRUE);

    // we will print staffs
    // then wait.
    // if the user changed page, we do a turn in the do while
    // else if it's b, we leave
    // else we wait for one of the two previous case in the while
    do {
        // init window
        interface_ncurses_initListWindow(translation_get(TRANSLATE_STAFF_LIST_TITLE));

        wattron(mapWindow, COLOR_PAIR(COLOR_RED));
        sprintf(buff, translation_get(TRANSLATION_LIST_STAFF_INDEX), start + 1,
                start + (min(rowPerPage, rowPerPage)),
                max);
        strcat(buff, translation_get(TRANSLATION_PRESS_ARROW_CHANGE_PAGE));
        mvwprintw(mapWindow, 2, 0, buff);
        wattroff(mapWindow, COLOR_PAIR(COLOR_RED));

        for ( int i = 0, j = start; i < rowPerPage; i++, j++ ) {
            Staff s = staff_list[j];
            wattron(mapWindow, COLOR_PAIR(COLOR_GREEN));
            mvwaddstr(mapWindow, 4 + i * 2, 0, s.name);
            waddstr(mapWindow, " (id=");
            number = utils_intToString(s.id);
            waddstr(mapWindow, number);
            waddstr(mapWindow, ") (");
            free(number); number = utils_intToString(s.costE);
            waddstr(mapWindow, number);
            waddstr(mapWindow, " E ");
            free(number); number = utils_intToString(s.costDD);
            waddstr(mapWindow, number);
            free(number);
            waddstr(mapWindow, " DD). Owned: ");
            waddstr(mapWindow, "0");
            wattroff(mapWindow, COLOR_PAIR(COLOR_GREEN));
            mvwaddstr(mapWindow, 5 + i * 2, 0, s.description);
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
                    if ( start % rowPerPage != 0 ) start -= (start % rowPerPage);
                    else start = max(start - rowPerPage, 0);
                    input = true;
                    break;
                    // page after
                case KEY_RIGHT:
                    start = min(start + rowPerPage, max - rowPerPage);
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

    // free
    free(buff);
    free(teacherHeader);

    // reset
    echo();
    nocbreak();
    curs_set(TRUE);
    keypad(mapWindow, FALSE);
}

void interface_ncurses_listActions()
{
    char* line; //!< a line that we will print
    char* actionName; //!< action name
    char* mapping;
    // we will print two columns
    char* action1; //!< action_name: mapping -- action2
    char* action2; //!< and action is another action_name: mapping

    //clear
    wclear(mapWindow);
    wrefresh(mapWindow);
    interface_ncurses_clearAction(" ");

    //title
    interface_ncurses_initListWindow(translation_get(TRANSLATE_ACTION_LIST_TITLE));

    int mid = getmaxx(mapWindow)/2;

    for ( int i = 0, j = 2; i < USER_MAPPING_SIZE; i++, j++ ) {
        actionName = actions_utils_fetchAction(user_mapping[i].actionID);
        mapping = user_mapping[i].key;
        // first action
        wattron(mapWindow, COLOR_PAIR(COLOR_GREEN));
        mvwaddstr(mapWindow, j, 0, actionName);
        wattroff(mapWindow, COLOR_PAIR(COLOR_GREEN));
        waddstr(mapWindow,":");
        wattron(mapWindow, COLOR_PAIR(COLOR_RED));
        waddstr(mapWindow, " `");
        waddstr(mapWindow, mapping);
        waddstr(mapWindow, "`");
        wattroff(mapWindow, COLOR_PAIR(COLOR_RED));
        i++;
        // second action
        actionName = actions_utils_fetchAction(user_mapping[i].actionID);
        mapping = user_mapping[i].key;
        wattron(mapWindow, COLOR_PAIR(COLOR_GREEN));
        mvwaddstr(mapWindow, j, mid, actionName);
        wattroff(mapWindow, COLOR_PAIR(COLOR_GREEN));
        waddstr(mapWindow,":");
        wattron(mapWindow, COLOR_PAIR(COLOR_RED));
        waddstr(mapWindow, " `");
        waddstr(mapWindow, mapping);
        waddstr(mapWindow, "`");
        wattroff(mapWindow, COLOR_PAIR(COLOR_RED));
    }

    interface_ncurses_show_menu_wait();
}