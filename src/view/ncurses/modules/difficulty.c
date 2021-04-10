#include "../../../../headers/utils/map_utils.h"
#include "../headers/interface_ncurses.h"
#include "../headers/interface_ncurses_utils.h"
#include <string.h>

//
// So we will show the 3 difficulties
// easy
// medium
// hard
//
// and some of them may be disabled if the screen is too small.
//
// Selected one is highlighted.
//

Difficulty interface_ncurses_chooseDifficulty()
{
    const int N_DIFFICULTIES = difficulty_getNumberOfDifficulties(); //!< number of difficulties
    const int TITLE_LINE = 2; //!< y of title line
    const int CONTENT_LINE_START = 4; //!< y of content line (first line)
    int* disabled; //!< disabled difficulties since screen is to small
    int* size; //!< size of a difficulty
    int max = -1; //!< will contains the size of the biggest word, used for style
    char** difficulties = NULL; //!< will contains the difficulties as text that we will show
    char* item = NULL; //!< buffer of current item, used for style
    char* format; //!< format of the difficulty
    int current = 0; //!< current selected difficulty
    int ch; //!< current char read
    bool leave = false; //!< leave branch
    const int TOP = ACTION_HEIGHT + 8 + 10; //!< min height

    // write title, centered
    mvaddstr(TITLE_LINE, COLS / 2 - strlen(translation_get(TRANSLATE_CHOICE_DIFF)) / 2,
             translation_get(TRANSLATE_CHOICE_DIFF));

    // fill difficulties, sizes, disabled
    difficulties = (char**) malloc(N_DIFFICULTIES * sizeof(char*));
    size = (int*) malloc(N_DIFFICULTIES * sizeof(int));
    disabled = (int*) malloc(N_DIFFICULTIES * sizeof(int));
    for ( int i = 1; i <= N_DIFFICULTIES; ++i ) {
        Difficulty d = difficulty_getLVL(i); //!< get difficulty
        // get translation
        char* translation = translation_getDifficulty(d);
        difficulties[i-1] = translation;
        // get the max size
        max = max( (int) strlen(translation), max);
        // get size (map)
        size[i-1] = map_utils_getSizeByDifficulty(d);
        size[i-1] = max(TOP, size[i-1]);
        // disabled
        disabled[i-1] = -1;
    }

    // init item
    item = (char*) malloc(max * sizeof(char));

    //
    // show difficulties menu
    //

    // 10 is the size of the format
    format = (char*) malloc(10 * sizeof(char));
    sprintf(format, "%s%d%s", "%-", max, "s");

    for ( int i = 0; i < N_DIFFICULTIES; i++ ) {
        if ( i == current )
            attron(A_STANDOUT); // highlight current
        else
            attroff(A_STANDOUT);
        // put in buffer, same spacing for all
        sprintf(item, format, difficulties[i]);
        // put in the screen
        if ( LINES < size[i] ) {
            // add red message and disabled
            disabled[i] = i;
            mvprintw(i + 1 + CONTENT_LINE_START, 2, "%s", item);
            attron(COLOR_PAIR(ERROR_COLOR));
            mvprintw(i + 1 + CONTENT_LINE_START, 2 + max + 2, " %s", translation_get(TRANSLATE_SCREEN_TOO_SMALL));
            attroff(COLOR_PAIR(ERROR_COLOR));
        } else {
            // normal print
            mvprintw(i + 1 + CONTENT_LINE_START, 2, "%s", item);
        }
    }
    refresh(); //refresh view

    // set everything to process input
    noecho(); // no echo of characters
    keypad(stdscr, TRUE); // already enable here, but just in case
    cbreak(); // disabled, we activate it to process char as they are typed
    curs_set(FALSE); // hide cursor

    // get the input
    while ( true ) {
        ch = getch();
        if ( ch == 'q' ) {
            // we leave
            interface_close();
            exit(0); // todo: this ends program on q
        }
        // un-highlight current
        attron(A_NORMAL);
        // put in buffer, same spacing for all
        sprintf(item, format, difficulties[current]);
        // put in the screen
        mvprintw(current + 1 + CONTENT_LINE_START, 2, "%s", item);
        attroff(A_NORMAL);

        // change current
        switch ( ch ) { // NOLINT(hicpp-multiway-paths-covered)
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
                for ( int i = 0; i < N_DIFFICULTIES; i++ ) {
                    if ( disabled[i] == current ) {
                        leave = false;
                    }
                }
                break;
        }

        if ( leave )
            break;

        // highlight current
        attron(A_STANDOUT);
        // put in buffer, same spacing for all
        sprintf(item, format, difficulties[current]);
        // put in the screen
        mvprintw(current + 1 + CONTENT_LINE_START, 2, "%s", item);
        attroff(A_STANDOUT);
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

    switch ( current ) {
        case 0:
            return DIFFICULTY_EASY;
        case 1:
            return DIFFICULTY_MEDIUM;
        case 2:
            return DIFFICULTY_HARD;
        default:
            return DIFFICULTY_EASY;
    }

}