#include "../headers/interface_ncurses.h"
#include "../headers/interface_ncurses_utils.h"

void interface_ncurses_showLegend(bool first, int y, Couple* entry)
{
    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    first ? mvwaddstr(gameWindow, y, 1, entry->keys.content.text) :
        waddstr(gameWindow, entry->keys.content.text);
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": ");
    waddstr(gameWindow, entry->values.content.text);
    waddstr(gameWindow, " ");
}

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

    // show legend
    Dictionary* machines = translation_getLegendMachines();

    // then we have
    wattron(gameWindow, COLOR_PAIR(COLOR_RED));
    mvwaddstr(gameWindow, END_BASE + 2, 1, "Legend");
    wattroff(gameWindow, COLOR_PAIR(COLOR_RED));

    interface_ncurses_showLegend(true, END_BASE + 3, dictionary_getCoupleByIndex(machines, 0));
    interface_ncurses_showLegend(false, 0, dictionary_getCoupleByIndex(machines, 1));
    interface_ncurses_showLegend(false, 0, dictionary_getCoupleByIndex(machines, 2));

    interface_ncurses_showLegend(true, END_BASE + 4, dictionary_getCoupleByIndex(machines, 4));
    interface_ncurses_showLegend(false, 0, dictionary_getCoupleByIndex(machines, 5));
    interface_ncurses_showLegend(false, 0, dictionary_getCoupleByIndex(machines, 6));

    interface_ncurses_showLegend(true, END_BASE + 5, dictionary_getCoupleByIndex(machines, 7));
    interface_ncurses_showLegend(false, 0, dictionary_getCoupleByIndex(machines, 8));
    // same line ?
    interface_ncurses_showLegend(true, 0, dictionary_getCoupleByIndex(machines, 9));

    Dictionary* directions = translation_getLegendDirections();

    interface_ncurses_showLegend(true, END_BASE + 7, dictionary_getCoupleByIndex(directions, 0));
    interface_ncurses_showLegend(false, 0, dictionary_getCoupleByIndex(directions, 1));
    interface_ncurses_showLegend(false, 0, dictionary_getCoupleByIndex(directions, 2));

    interface_ncurses_showLegend(true, END_BASE + 8, dictionary_getCoupleByIndex(directions, 3));
    interface_ncurses_showLegend(false, 0, dictionary_getCoupleByIndex(directions, 4));
    interface_ncurses_showLegend(false, 0, dictionary_getCoupleByIndex(directions, 5));

    interface_ncurses_showLegend(true, END_BASE + 9, dictionary_getCoupleByIndex(directions, 6));
    interface_ncurses_showLegend(false, 0, dictionary_getCoupleByIndex(directions, 7));

    free(buf);
    free(format);

    wrefresh(gameWindow);
}