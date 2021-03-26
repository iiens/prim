#include "../../headers/map.h"
#include "../../headers/utils/map_utils.h"

//todo: default implementation
//todo créer la grille Case source et gate
//todo créer le staff
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

ErrorCode map_isCaseExist( int x, int y, Map* m ){
    if ( x >= 0 && x < m->width ){
         if ( y >= 0 && y < m->height ){
             return NO_ERROR;
         }
     }
    return ERROR_CASE_NOT_FOUND;
}

int map_getnumberResource( int x, int y, Map* m ){
    int res = -1;
    if ( map_isCaseExist(x, y, m) == NO_ERROR ){
        res = m->map[x][y].nbResource;
    }
    return res;
}

int map_getnumberGarbage( int x, int y, Map* m ){
    int res = -1;
    if ( map_isCaseExist(x, y, m) == NO_ERROR ){
        res = m->map[x][y].nbGarbage;
    }
    return res;
}

int map_getnumberFISE( Map* m ){ return m->numberFISE; }
int map_getnumberFISA( Map* m ){ return m->numberFISA; }
int map_getnumberE( Map* m ) { return m->E; }
int map_getnumberDD( Map* m ) { return m->DD; }
