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
ErrorCode map_hireFISE( Map* map){ return NO_ERROR; }
ErrorCode map_hireFISA( Map* map){ return NO_ERROR; }
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

int map_getNumberResource( int x, int y, Map* m ){
    int res = -1;
    if ( map_isCaseExist(x, y, m) == NO_ERROR ){
        res = m->map[x][y].nbResource;
    }
    return res;
}

int map_getNumberGarbage( int x, int y, Map* m ){
    int res = -1;
    if ( map_isCaseExist(x, y, m) == NO_ERROR ){
        res = m->map[x][y].nbGarbage;
    }
    return res;
}

int map_getNumberFISE( Map* m ){ return m->numberFISE; }
int map_getNumberFISA( Map* m ){ return m->numberFISA; }
int map_getNumberE( Map* m ) { return m->E; }
int map_getNumberDD( Map* m ) { return m->DD; }

ErrorCode map_setNumberResource( int x, int y, Map* m, int val ){
    int res, tmp = 0;
    if ( map_isCaseExist(x, y, m) == NO_ERROR ){
        if ( (tmp = m->map[x][y].nbResource) + val >= 0 ){
            tmp = tmp + val;
            res = NO_ERROR;
        }else{
            res = ERROR_NEGATIVE_RESULT;
        }
    }else{
    res = ERROR_CASE_NOT_FOUND;
    }
    return res;
}

ErrorCode map_setNumberGarbage( int x, int y, Map* m, int val ){
    int res, tmp = 0;
    if ( map_isCaseExist(x, y, m) == NO_ERROR ){
        if ( (tmp = m->map[x][y].nbGarbage) + val >= 0 ){
            tmp = tmp + val;
            res = NO_ERROR;
        }else{
            res = ERROR_NEGATIVE_RESULT;
        }
    }else{
        res = ERROR_CASE_NOT_FOUND;
    }
    return res;
}
ErrorCode map_setNumberFISE( Map* m, int val){
    int res, tmp = 0;
    if ( (tmp = m->numberFISE) + val >= 0 ){
        tmp = tmp + val;
        res = NO_ERROR;
    }else{
        res = ERROR_NEGATIVE_RESULT;
    }
    return res;
}

ErrorCode map_setNumberFISA( Map* m, int val ){
    int res, tmp = 0;
    if ( (tmp = m->numberFISA) + val >= 0 ){
        tmp = tmp + val;
        res = NO_ERROR;
    }else{
        res = ERROR_NEGATIVE_RESULT;
    }
    return res;
}

ErrorCode map_setNumberE( Map* m, int val ){
    int res, tmp = 0;
    if ( (tmp = m->E) + val >= 0 ){
        tmp = tmp + val;
        res = NO_ERROR;
    }else{
        res = ERROR_NEGATIVE_RESULT;
    }
    return res;
}

ErrorCode map_setNumberDD( Map* m, int val ){
    int res, tmp = 0;
    if ( (tmp = m->DD) + val >= 0 ){
        tmp = tmp + val;
        res = NO_ERROR;
    }else{
        res = ERROR_NEGATIVE_RESULT;
    }
    return res;
}
