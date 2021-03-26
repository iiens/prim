#include "../../headers/map.h"

//todo: create map_utils and move this
// maybe some constants ?
int map_utils_getSizeByDifficulty(Difficulty d){
    switch (d) {
        case DIFFICULTY_EASY:
            return 10;
            break;
        case DIFFICULTY_MEDIUM:
            return 20;
            break;
        case DIFFICULTY_HARD:
            return 30;
            break;
    }
}

//todo: default implementation
Map* map_create(Difficulty dif){
    Map* m = (Map*) malloc(sizeof(Map));
    m->width = map_utils_getSizeByDifficulty(dif);
    m->height = map_utils_getSizeByDifficulty(dif);
    m->difficulty = dif;
    m->turn = 1;
    m->productionFISA = E_VALUE;
    m->E = 100;
    m->DD = 100;
    m->score = 0;
    m->pollution = 0;
    m->numberFISA = 5;
    m->numberFISE = 5;
    return m;
}

ErrorCode map_destroy(Map* map){ free(map); return NO_ERROR; }
ErrorCode map_hireFISE(const Map* map){ return NO_ERROR; }
ErrorCode map_hireFISA(const Map* map){ return NO_ERROR; }
ErrorCode map_changeProductionFISA(){ return NO_ERROR; }
ErrorCode map_endTurn(Map* map){ map->turn++;return NO_ERROR; }
ErrorCode map_isEmpty(int x, int y, Map* map){ return NO_ERROR; }
ErrorCode map_addMachine(const Machine machine, const int x, const int y, Map* m){ return ERROR;}
ErrorCode map_upgradeMachine(const int x, const int y, Map* m){ return NO_ERROR;}
ErrorCode map_destroyMachine(const int x, const int y, Map* m){ return ERROR_CASE_EMPTY;}
ErrorCode map_buyStaff(Staff s, Map* m){ return NO_ERROR;}
