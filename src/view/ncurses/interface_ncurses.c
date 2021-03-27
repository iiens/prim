/*!
 * \file interface_ncurses.c
 * This file is supposed to contains all interface functions that
 * uses ncurses.
 */
#include "../../../headers/interface.h"
#include "../translation.h"
#include "interface_ncurses.h"
#include "interface_ncurses_utils.h"
#include <string.h>
#include <locale.h>

// References
// https://manpages.debian.org/testing/ncurses-doc/keypad.3ncurses.en.html
// https://stackoverflow.com/questions/8108634/global-variables-in-header-file
// https://techlister.com/linux/creating-menu-with-ncurses-in-c/1293/
// https://stackoverflow.com/questions/66540302/c99-utf8-characters-with-ncurses
// https://stackoverflow.com/questions/33322601/clearing-a-field-buffer-in-ncurses

//\////////////////////////////\//
//\/ interface related
//\////////////////////////////\//

int MIN_ROW_SAVED = 17;

// we init the main screen
// 3 sub windows :
// - gameWindow : game info (turn, ...)
// - mapWindow : where we show the map
// - actionWindow : where we allow the user to print something, errors are here too
//
// we also need to init colors, charset, ...
//
ErrorCode interface_ncurses_init()
{
    //allow UTF-8
    setlocale(LC_ALL, "fr_FR.UTF-8");

    //init screen
    if(initscr() == NULL){
        interface_close();
        //Colors aren't supported in this terminal
        return ERROR_INIT_NCURSES_INTERFACE;
    }

    if(LINES > MIN_ROW_SAVED) MIN_ROW_SAVED = LINES;

    if(resize_term(MIN_ROW_SAVED,164) == -1) {
        interface_close();
        fprintf(stderr, "Colors aren't supported in this terminal.\n");
        return false;
    }

    gameWindow = subwin(stdscr, LINES - ACTION_HEIGHT, GAME_WIDTH , 0, 0);
    mapWindow = subwin(stdscr, LINES - ACTION_HEIGHT, COLS - GAME_WIDTH, 0, GAME_WIDTH);
    actionWindow = subwin(stdscr, ACTION_HEIGHT, COLS, LINES - ACTION_HEIGHT, 0);

    box(gameWindow, ACS_VLINE, ACS_HLINE);
    box(actionWindow, ACS_VLINE, ACS_HLINE);
    box(mapWindow, ACS_VLINE, ACS_HLINE);

    //init colors
    if(has_colors() == FALSE) {
        interface_close();
        //Colors aren't supported in this terminal
        return ERROR_NO_NCURSES_COLORS_INTERFACE;
    }
    start_color();

    // declare colors
    // ...
    init_pair(ERROR_COLOR, COLOR_RED, COLOR_BLACK);
    init_pair(SUCCESS_COLOR, COLOR_GREEN, COLOR_BLACK);
    //init_color(CODE_MY, 0,0,0); //todo: here color got
    //init_pair(MY_COLOR, 124, COLOR_BLACK);

    // ...
    keypad(stdscr, TRUE);
    // cbreak(); // don't save into buffer until <enter> pressed
    nocbreak();
    // noecho(); //show printed charaters
    echo();
    clear();

    return NO_ERROR;
}

// here we are supposed
// 1- show the game menu
// 2- show the map
// 3- show input action field
// and save this map in a pointer
Map* lastMap = NULL; //!< init last map
ErrorCode interface_ncurses_reload(const Map* map)
{
    lastMap = (Map *) map;
    interface_showMap(map);
    interface_ncurses_showActionField();
    return NO_ERROR;
}

ErrorCode interface_ncurses_close()
{
    // free main window
    bool r = endwin();
    if(!r) return ERROR_CLOSE_INTERFACE;
    return NO_ERROR;
}

//\////////////////////////////\//
//\/ Show related functions
//\////////////////////////////\//

void interface_ncurses_showMap(const Map* map)
{
    wclear(mapWindow); //reset

    char* buf = (char*) malloc(GAME_WIDTH * sizeof(char));
    char* format = (char*) malloc(GAME_WIDTH * sizeof(char));

    char* production = map->numberFISA==E_VALUE?translation_get(TRANSLATE_GAME_E):translation_get(TRANSLATE_GAME_DD);

    // init_view
    mvwprintw(gameWindow, 1, 1, translation_get(TRANSLATE_GAME_NAME));
    mvwprintw(gameWindow, 2, 1, interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_TURN), map->turn, buf, format));
    mvwprintw(gameWindow, 3, 1, interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_E), map->E, buf, format));
    mvwprintw(gameWindow, 4, 1, interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_DD), map->DD, buf, format));
    mvwprintw(gameWindow, 5, 1, interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_FISE), map->numberFISE, buf, format));
    mvwprintw(gameWindow, 6, 1, interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_FISA), map->numberFISA, buf, format));
    mvwprintw(gameWindow, 7, 1, interface_ncurses_gameTag_type(translation_get(TRANSLATE_GAME_FISA_MODE), production, buf, format, "%s"));
    //todo: manage number of staffs
    mvwprintw(gameWindow, 8, 1, interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_STAFFS), 0, buf, format));
    mvwprintw(gameWindow, 9, 1, interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_SCORE), map->score, buf, format));
    mvwprintw(gameWindow, 10, 1, interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_GARBAGE), map->pollution, buf, format));

    free(buf);
    free(format);

    //         0  1  2  3 ... n
    //       +--+--+--+--+--+--+
    //          +  +  +  +  +  +
    //          +  +  +  +  +  +
    //          +  +  +  +  +  +
    for (int j = 0; j < map->height; j++) {
        mvwprintw(mapWindow, 0, j*3+3, " %2d", j);
        if(j==0) mvwprintw(mapWindow, 1, 3, "+"); // starting +
        mvwprintw(mapWindow, 1, 4+j*3, "--+");
        for (int i = 0; i < map->width; i++) {
            mvwaddstr(mapWindow, i+2, 4+j*3, " ");
            //todo: put item inside
            mvwaddstr(mapWindow, i+2, 5+j*3,  (char*) L" ");
            mvwaddstr(mapWindow, i+2, 6+j*3, "+");
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
    for (int j = 0; j < map->height; ++j) {
        mvwprintw(mapWindow, j+2, 0, "%3d|", j);
    }

    // show
    wrefresh(mapWindow);
}

void interface_ncurses_showMachinesList()
{
    const int LINE_COUNT = NUMBER_OF_MACHINES;
    const int size = 5+5+3+3; //!< we allow 5 number as, result is "n E n DD" (3 are spaces and 3 are letters)
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
    for (int i = 0; i < LINE_COUNT; ++i) {
        int j=0; //!< in which column we should add the next part, see below with cost line
        MachineInfo m = machine_list[i];
        char* desc = m.description;
        char* name = translation_getMachineType(m.type);
        int id = m.type;
        // size is two strings + 1 (size of id)
        char* head = (char*) malloc((strlen(name)+1+strlen(desc)+1+10) * sizeof(char)); //!< header of this machine
        sprintf(head, " %s (id=%d) : %s", name, id, desc);

        // write prices
        sprintf(p, "%5d E %5d DD", m.costE, m.costDD);
        if(m.canUpgrade) sprintf(pUpgrade, "%5d E %5d DD", m.costUpgradeE, m.costUpgradeDD);
        sprintf(pDestroy, "%5d E %5d DD", m.costDestroyE, m.costDestroyDD);

        // "Machine:" - in red
        wattron(mapWindow, COLOR_PAIR(COLOR_RED));
        mvwprintw(mapWindow, 2+2*i , 0, translation_get(TRANSLATE_ML_MACHINE_TAG));
        wattroff(mapWindow, COLOR_PAIR(COLOR_RED));
        // machine description
        mvwprintw(mapWindow, 2+2*i , (int) strlen(translation_get(TRANSLATE_ML_MACHINE_TAG)), head);

        // write in one line
        // >>> cost: vE vDD >>> cost upgrade: vE vDD >>> cost destroy: vE vDD
        // with v the value
        // cost:, ... are put in green
        //cost:
        j = writeLabel(i, j, translation_get(TRANSLATE_ML_COST_TAG), p); //cost
        if(m.canUpgrade) j = writeLabel(i, j, translation_get(TRANSLATE_ML_COST_UP_TAG), pUpgrade); //cost upgrade
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
    bool input = false; //!< stop input and reload view ?
    bool leave = false; //!< stop this menu and go back ?
    char* buff = (char*) malloc(
            (strlen(translation_get(TRANSLATION_LIST_STAFF_INDEX))+3*3+(int)strlen(translation_get(TRANSLATION_PRESS_ARROW_CHANGE_PAGE)))
                *
            sizeof(char)
            ); //!< buffer that show the number of the page we are on
    //example "Laurence Bourard (id=8) (200 E 100 DD)";
    int textLength = 100 /* max name size */ + 7 /* spaces */
                     + 4 /* ( and ) */ + 11 /* id= E and DD and Owned: */
                     + 3*5 /* 3 numbers, 5 chars max*/; //!< size of the teacher name buffer
    char* teacherHeader = (char*) malloc(textLength*sizeof(char)); //!< teacher name header buffer

    //todo: unused
    (void)(map);

    // hide cursor
    noecho(); cbreak(); curs_set(FALSE); keypad(mapWindow, TRUE);

    // we will print staffs
    // then wait.
    // if the user changed page, we do a turn in the do while
    // else if it's b, we leave
    // else we wait for one of the two previous case in the while
    do {
        // init window
        interface_ncurses_initListWindow(translation_get(TRANSLATE_STAFF_LIST_TITLE));

        wattron(mapWindow, COLOR_PAIR(COLOR_RED));
        sprintf(buff, translation_get(TRANSLATION_LIST_STAFF_INDEX), start+1, start+(min(rowPerPage, rowPerPage)), max);
        strcat(buff, translation_get(TRANSLATION_PRESS_ARROW_CHANGE_PAGE));
        mvwprintw(mapWindow, 2, 0, buff);
        wattroff(mapWindow, COLOR_PAIR(COLOR_RED));

        for (int i = 0, j=start ; i < rowPerPage; i++, j++) {
            Staff s = staff_list[j];
            //todo: use j to print the right staffs and fill with the right data
            wattron(mapWindow, COLOR_PAIR(COLOR_GREEN));
            // using format described above textLength
            sprintf(teacherHeader, "%s (id=%d) (%d E %d DD). Owned: %d", s.name, s.id, s.costE, s.costDD, 0);
            mvwprintw(mapWindow, 4+i*2, 0, teacherHeader);
            wattroff(mapWindow, COLOR_PAIR(COLOR_GREEN));
            mvwprintw(mapWindow, 5+i*2, 0, s.description);
        }

        wrefresh(mapWindow);

        // wait for input
        while (!input){
            ch = getch();
            switch (ch) { // NOLINT(hicpp-multiway-paths-covered)
                // page before
                case KEY_LEFT:
                    // we don't want to change our rowPerPage
                    // if last page didn't have enough rows
                    if (start%rowPerPage != 0) start-= (start%rowPerPage);
                    else start = max(start-rowPerPage, 0);
                    input = true;
                    break;
                // page after
                case KEY_RIGHT:
                    start = min(start+rowPerPage, max-rowPerPage);
                    input = true;
                    break;
                // back
                case 'b': input = leave = true; break;
                // ignore
                default:
                    break;
            }
        }
        input = false;
    } while (!leave);

    // free
    free(buff);
    free(teacherHeader);

    // reset
    echo();nocbreak();curs_set(TRUE);keypad(mapWindow, FALSE);
}

//\////////////////////////////\//
//\/ ask for user input
//\////////////////////////////\//

Difficulty interface_ncurses_chooseDifficulty()
{
    return DIFFICULTY_EASY; //todo: temp
    const int N_DIFFICULTIES = 3; //!< number of difficulties
    const int TITLE_LINE = 2; //!< y of title line
    const int CONTENT_LINE_START = 4; //!< y of content line (first line)
    int* disabled; //!< disabled difficulties since screen is to small
    int max; //!< will contains the size of the biggest word, used for style
    char** difficulties = NULL; //!< will contains the difficulties as text that we will show
    char* item = NULL; //!< buffer of current item, used for style
    char* format; //!< format of the difficulty
    int current = 0; //!< current selected difficulty
    int ch; //!< current char read
    bool leave = false; //!< leave branch

    // find biggest value
    max = max((int) strlen(translation_get(TRANSLATE_DIF_M)), (int) strlen(translation_get(TRANSLATE_DIF_H)));
    max = max((int) strlen(translation_get(TRANSLATE_DIF_E)), (int) max);

    // write title, centered
    mvaddstr(TITLE_LINE,COLS / 2 - strlen(translation_get(TRANSLATE_CHOICE_DIFF)) / 2,TRANSLATE_CHOICE_DIFF);

    // fill difficulties
    difficulties = (char**) malloc(N_DIFFICULTIES * sizeof(char*));
    difficulties[0] = translation_get(TRANSLATE_DIF_E);
    difficulties[1] = translation_get(TRANSLATE_DIF_M);
    difficulties[2] = translation_get(TRANSLATE_DIF_H);

    // disabled
    disabled = (int*) malloc(N_DIFFICULTIES * sizeof(int));
    for (int i = 0; i < N_DIFFICULTIES; ++i) disabled[i] = -1;

    // init item
    item = (char*)  malloc(max * sizeof(char));

    // show difficulties menu
    format = (char*) malloc(10*sizeof(char));
    sprintf(format, "%s%d%s",  "%-", max, "s");
    for (int i = 0; i < N_DIFFICULTIES; i++) {
        if( i == current ) attron( A_STANDOUT ); // highlight current
        else attroff( A_STANDOUT );
        // put in buffer, same spacing for all
        sprintf(item, format,  difficulties[i]);
        // put in the screen
        //todo: Calistro: getSizeByDifficulty instead of 10,20,30
        if ( (LINES <= 10+ACTION_HEIGHT && i==0) ||
             (LINES <= 20+ACTION_HEIGHT && i==1) ||
             (LINES <= 30+ACTION_HEIGHT && i==2) ){
            disabled[i] = i;
            mvprintw(i+1+CONTENT_LINE_START, 2, "%s", item);
            attron(COLOR_PAIR(ERROR_COLOR));
            mvprintw(i+1+CONTENT_LINE_START,2+max+2, " %s", TRANSLATE_SCREEN_TOO_SMALL);
            attroff(COLOR_PAIR(ERROR_COLOR));
        } else {
            mvprintw(i+1+CONTENT_LINE_START, 2, "%s", item );
        }
    }
    refresh(); //refresh view

    // set everything to process input
    noecho(); // no echo of characters
    keypad(stdscr , TRUE); // already enable here, but just in case
    cbreak(); // disabled, we activate it to process char as they are typed
    curs_set(FALSE); // hide cursor

    // get the input
    while(true){
        ch = getch();
        if(ch == 'q'){
            // we leave
            interface_ncurses_close();
            exit(0); // todo: this ends program on q
        }
        // un-highlight current
        attron(A_NORMAL);
        // put in buffer, same spacing for all
        sprintf(item, format,  difficulties[current]);
        // put in the screen
        mvprintw(current+1+CONTENT_LINE_START, 2, "%s", item );
        attroff(A_NORMAL);

        // change current
        switch(ch) { // NOLINT(hicpp-multiway-paths-covered)
            case KEY_UP: //arrow up
                current--;
                current = max(current, 0);
                break;
            case KEY_DOWN: //arrow down
                current++;
                current = min(current, N_DIFFICULTIES);
                break;
            case KEY_SEND: // enter, send, etc.
            case KEY_ENTER:
            case 10: // enter on my keyboard :(
                leave = true;
                // is_disabled ? if yes we don't leave
                for (int i = 0; i < N_DIFFICULTIES; i++) {
                    if(disabled[i] == current){
                        leave = false;
                    }
                }
                break;
        }

        if(leave) break;

        // highlight current
        attron( A_STANDOUT );
        // put in buffer, same spacing for all
        sprintf(item, format,  difficulties[current]);
        // put in the screen
        mvprintw(current+1+CONTENT_LINE_START, 2, "%s", item );
        attroff( A_STANDOUT );
    }

    // reset everything
    echo();
    nocbreak();
    curs_set(TRUE);
    clear(); // clear screen
    // free
    free(disabled);
    free(difficulties);
    free(item);
    free(format);

    switch (current) {
        case 0: return DIFFICULTY_EASY;
        case 1: return DIFFICULTY_MEDIUM;
        case 2: return DIFFICULTY_HARD;
        default: return DIFFICULTY_EASY;
    }
}

typedef void* (*Closure)(char* buff, bool* leave, ErrorCode* error);

void* interface_ncurses_showInActionField(Closure init, Closure check){
    bool leave = false; //!< do we need to leave ?
    void* result = NULL; //!< function result
    ErrorCode error; //!< error code
    if(init != NULL) init(NULL, NULL, NULL);
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
            if(read != '\n'){
                buf[cursor] = (char) read;
            }
            cursor++;
            if(cursor == ACTION_BUF_SIZE-1) { // same as enter
                break;
            }
        } while (read != '\n');
        // end str
        buf[cursor] = '\0';

        result = check(buf, &leave, &error);
        if(leave){ // leave set as true ?
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
    } while (true);
}

void* interface_ncurses_chooseActionClosureCheck(char* buff, bool* leave, ErrorCode* error){
    for (int i = 0; i < USER_MAPPING_SIZE; ++i) {
        if(strcmp(buff, user_mapping[i].key) == 0){ //same
            *leave = true;
            // return acton
            Action* a = (Action*) malloc(sizeof(Action));
            *a = user_mapping[i].actionID;
            return a;
        }
    }
    // set error
    *error = ERROR_INVALID_ACTION_SEQUENCE;
    return NULL;
}

Action interface_ncurses_chooseAction()
{
    Action* a = ((Action*) interface_ncurses_showInActionField(
            NULL,
            interface_ncurses_chooseActionClosureCheck
    ));
    // we need to do that since we use void* and Action* to match this constraint
    Action action = *a;
    free(a);
    return action;
}

//
// Ask machine location
//

/** Callback on init  */
void* interface_ncurses_askMachineLocationClosureInit(){
    interface_ncurses_showMessage(translation_get(TRANSLATE_INPUT_MACHINE_LOCATION));
    return NULL;
}

/** Callback on check  */
void* interface_ncurses_askMachineLocationClosureCheck(char* buff, bool* leave, ErrorCode* error){
    // he wants to go back
    if(strcmp(buff,"b") == 0){
        back = true;
        *leave = TRUE;
        return NULL;
    } else {
        const int MAX_NUMBER_LENGTH = 8; //!< 2^MAX_NUMBER_LENGTH is the max int length
        int i = 0; //!< position in buffer
        int j = 0; //!< position in each number n1,n2
        int length = (int) strlen(buff); //!< int length
        char* n1; //!< will contains number1
        char* n2; //!< will contains number2
        char* endPtr; //!<  error pointer
        int v1; //!< first value
        int v2; //!< second value


        if(length < 10) { // not some weird long number
            // creates buffers
            n1 = (char*) malloc(MAX_NUMBER_LENGTH*sizeof(char));
            n2 = (char*) malloc(MAX_NUMBER_LENGTH*sizeof(char));

            // first number
            for ( i = 0; i < length && buff[i] != ',' ; i++,j++ ) {
                n1[j] = buff[i];
            }
            // second number
            i++;
            for (j=0; i < length; i++ ) {
                n2[j] = buff[i];
            }

            // convert and return
            v1 = (int) strtol(n1, &endPtr, 10);
            if(endPtr == NULL){
                v2 = (int) strtol(n2, &endPtr, 10);
                if(endPtr == NULL){
                    Vector2D* v = (Vector2D*) malloc(sizeof(Vector2D));
                    v->x = v1;
                    v->y = v2;
                    free(n1);
                    free(n2);
                    return v;
                }

            }

            // free
            free(n1);
            free(n2);
        }
    }

    // set error
    *error = ERROR_INVALID_LOCATION_SEQUENCE;
    return NULL;
}

Vector2D* interface_ncurses_askMachineLocation(){
    Vector2D* v = (Vector2D*) interface_ncurses_showInActionField(
            interface_ncurses_askMachineLocationClosureInit,
            interface_ncurses_askMachineLocationClosureCheck
    );
    interface_ncurses_hideError(); // hides
    return v;
}