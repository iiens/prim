#include "../headers/interface_ncurses.h"
#include "../headers/interface_ncurses_utils.h"

void interface_ncurses_gameMenu( const Map* map )
{
    const int END_BASE = 10; //!< 10 lines of games constants
    char* buf = (char*) malloc(GAME_WIDTH * sizeof(char)); //!< see interface_ncurses_gameTag
    char* format = (char*) malloc(GAME_WIDTH * sizeof(char)); //!< see interface_ncurses_gameTag
    char* production = //!< string for the production mode
            map_getProductionFISA(map) == E_VALUE ? translation_get(TRANSLATE_GAME_E) : translation_get(
                    TRANSLATE_GAME_DD);

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
              interface_ncurses_gameTag(translation_get(TRANSLATE_GAME_GARBAGE), map_getNumberPollution(map), buf,
                                        format));

    //    Dictionary* machines;
    //    machines = dictionary_create(7);
    //    dictionary_addElement(machines,
    //                          (Element) {.content = {.text = "S"}, .type = TEXT},
    //                          (Element) {.content = {.text = "Source"}, .type = TEXT});
    //    dictionary_addElement(machines,
    //                          (Element) {.content = {.text = "S"}, .type = TEXT},
    //                          (Element) {.content = {.text = "Source"}, .type = TEXT});

    // then we have
    //todo: redo plz
    wattron(gameWindow, COLOR_PAIR(COLOR_RED));
    mvwaddstr(gameWindow, END_BASE + 2, 1, "Legend");
    wattroff(gameWindow, COLOR_PAIR(COLOR_RED));

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    mvwaddstr(gameWindow, END_BASE + 3, 1, "S");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": Source ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, "G");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": Gate ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    mvwaddstr(gameWindow, END_BASE + 4, 1, "C");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": Collector ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, "B");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": CONVEYOR BELT ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    mvwaddstr(gameWindow, END_BASE + 5, 1, "X");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": Cross ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, "R");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": RECYCLING CENTER ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    mvwaddstr(gameWindow, END_BASE + 6, 1, "J");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": JUNKYARD ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    mvwaddstr(gameWindow, END_BASE + 8, 1, "4");
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
    mvwaddstr(gameWindow, END_BASE + 9, 1, "2");
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
    mvwaddstr(gameWindow, END_BASE + 10, 1, "1");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": BOTTOM LEFT ");

    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, "3");
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": BOTTOM RIGHT ");

    free(buf);
    free(format);

    wrefresh(gameWindow);
}