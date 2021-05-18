#include "../nc_headers/interface_ncurses.h"
#include "../nc_headers/interface_ncurses_utils.h"

// show the legend
// here using translation and colors according to tag
void interface_ncurses_showLegendOrientation( bool first, int y, Couple* entry );

// only printing all tags in greens
void interface_ncurses_showLegendMachine( bool first, int y, Couple* entry );

void interface_ncurses_gameMenu( const Map* map )
{
    const int END_BASE = 10; //!< 10 lines of games constants
    char* buf = (char*) malloc(GAME_WIDTH * sizeof(char)); //!< see interface_ncurses_gameTag
    char* format = (char*) malloc(GAME_WIDTH * sizeof(char)); //!< see interface_ncurses_gameTag
    char* production = //!< string for the production mode
            map_getProductionFISA(map) == E_VALUE ? translation_get(TRANSLATE_GAME_E) : translation_get(
                    TRANSLATE_GAME_DD);
    int NUMBER_OF_LINES = 3; //!< number of lines
    int lineMAX[] = {3, 2, 2}; //!< max per line

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
    List* machines = translation_getLegendMachines();

    // then we have
    wattron(gameWindow, COLOR_PAIR(COLOR_RED));
    mvwaddstr(gameWindow, END_BASE + 2, 1, translation_get(TRANSLATE_LEGEND));
    wattroff(gameWindow, COLOR_PAIR(COLOR_RED));

    // show machine legend
    for ( int i = 0; i < NUMBER_OF_LINES; i++ ) {
        int max = lineMAX[i]; //!< current max per line
        int y = END_BASE + 3 + i; //!< first y
        for ( int j = 0; j < max; ++j ) {
            interface_ncurses_showLegendMachine(y != 0, y, elements_toObject(*list_next(&machines)));
            y = 0;
        }
    }

    Dictionary* directions = translation_getLegendDirections();

    interface_ncurses_showLegendOrientation(true, END_BASE + 7, dictionary_getCoupleByIndex(directions, 0));
    interface_ncurses_showLegendOrientation(false, 0, dictionary_getCoupleByIndex(directions, 1));

    interface_ncurses_showLegendOrientation(true, END_BASE + 8, dictionary_getCoupleByIndex(directions, 2));
    interface_ncurses_showLegendOrientation(false, 0, dictionary_getCoupleByIndex(directions, 3));
    interface_ncurses_showLegendOrientation(false, 0, dictionary_getCoupleByIndex(directions, 4));

    interface_ncurses_showLegendOrientation(true, END_BASE + 9, dictionary_getCoupleByIndex(directions, 5));
    interface_ncurses_showLegendOrientation(false, 0, dictionary_getCoupleByIndex(directions, 6));
    interface_ncurses_showLegendOrientation(false, 0, dictionary_getCoupleByIndex(directions, 7));

    free(buf);
    free(format);
    list_destroy(machines);
    dictionary_destroy(directions);

    wrefresh(gameWindow);
}

void interface_ncurses_showLegendMachine( bool first, int y, Couple* entry )
{
    char* tag; //!< S, G, ... a tag that we will explain
    char* content; //!< Gate for G, explain the tag
    attr_t color; //!< tag color

    // it's a machine
    if ( entry->keys.content.number == IS_MACHINE ) {
        MachineStuff s = entry->values.content.number; // machine type
        tag = translation_fetchMachineTypeName(s);
        color = interface_ncurses_utils_getMachineColor(s);
        content = translation_fetchMachineTypeFullName(s);
    } else { // it's not a machine
        CaseType t = entry->values.content.number; // case type
        tag = translation_fetchCaseTypeName(t);
        color = interface_ncurses_utils_getCaseColor(NULL, t);
        content = translation_fetchCaseTypeFullName(t);
    }

    // print \color{color}{tag}: content
    wattron(gameWindow, color);
    first ? mvwaddstr(gameWindow, y, 1, tag) : waddstr(gameWindow, tag);
    wattroff(gameWindow, color);
    waddstr(gameWindow, ": ");
    waddstr(gameWindow, content);
    waddstr(gameWindow, " ");
}

void interface_ncurses_showLegendOrientation( bool first, int y, Couple* entry )
{
    wattron(gameWindow, COLOR_PAIR(COLOR_GREEN));
    first ? mvwaddstr(gameWindow, y, 1, entry->keys.content.text) : waddstr(gameWindow, entry->keys.content.text);
    wattroff(gameWindow, COLOR_PAIR(COLOR_GREEN));
    waddstr(gameWindow, ": ");
    waddstr(gameWindow, entry->values.content.text);
    waddstr(gameWindow, " ");
}