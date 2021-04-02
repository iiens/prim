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
ErrorCode map_hireFISE(Map* map){ return NO_ERROR; }
ErrorCode map_hireFISA(Map* map){ return NO_ERROR; }
ErrorCode map_changeProductionFISA(Map* map){ return NO_ERROR; }
ErrorCode map_endTurn(Map* map){ map->turn++;return NO_ERROR; }
ErrorCode map_isEmpty(const int x, const int y, const Map* map){ return NO_ERROR; }
ErrorCode map_addMachine(Machine machine, int x, int y, Map* m){ return ERROR;}
ErrorCode map_upgradeMachine(int x, int y, Map* m){ return NO_ERROR;}
ErrorCode map_destroyMachine(int x, int y, Map* m){ return ERROR_CASE_EMPTY;}
ErrorCode map_buyStaff(Staff s, Map* m){ return ERROR_NOT_ENOUGH_E;}

ErrorCode map_isCaseExist( const int x, const int y, const Map* m ){
    if ( x >= 0 && x < m->width ){
         if ( y >= 0 && y < m->height ){
             return NO_ERROR;
         }
     }
    return ERROR_CASE_NOT_FOUND;
}

//\////////////////////////////\//
//\/ Functions Getters
//\////////////////////////////\//

int map_getNumberResource( const int x, const int y, const Map* m ){
    int res = -1;
    if ( map_isCaseExist(x, y, m) == NO_ERROR ){
        res = m->map[x][y].nbResource;
    }
    return res;
}

int map_getNumberGarbage( const int x, const int y, const Map* m ){
    int res = -1;
    if ( map_isCaseExist(x, y, m) == NO_ERROR ){
        res = m->map[x][y].nbGarbage;
    }
    return res;
}

int map_getNumberFISE( const Map* m ){ return m->numberFISE; }
int map_getNumberFISA( const Map* m ){ return m->numberFISA; }
int map_getNumberE( const Map* m ) { return m->E; }
int map_getNumberDD( const Map* m ) { return m->DD; }
int map_getPlayerScore( const Map* m ){ return m->score; }
int map_getNumberPollution( const Map* m ){ return m->pollution; }
Difficulty map_getDifficulty( const Map* m ){ return m->difficulty; }
int map_getWidth( const Map* m ){ return m->width; }
int map_getHeight( const Map* m ){ return m->height; }
int map_getNumberStaff( const Map* m ){ return m->numberStaff; }

Case* map_getCase( const int x, const int y, const Map* m ){
    if ( map_isCaseExist(x, y, m) == NO_ERROR ){
        return &(m->map[x][y]);
    }else{
        return NULL;
    }
}

CaseType map_getTypeCase( const int x, const int y, const Map* m ){
    if ( map_isCaseExist(x, y, m) == NO_ERROR ){
        return m->map[x][y].type;
    }else{
        return -1;
    }
}
MachineStuff map_getTypeMachine( const int x, const int y, const Map* m ){
    if (map_getTypeCase(x, y, m) == CASE_MACHINE){
        return m->map[x][y].in.mach->type;
    }else{
        return -1;
    }
}

//\////////////////////////////\//
//\/ Functions Setters
//\////////////////////////////\//

ErrorCode map_setNumberResource( const int x, const int y, Map* m, int val ){
    int res, tmp = 0;
    if ( map_isCaseExist(x, y, m) == NO_ERROR ){
        if ( (tmp = m->map[x][y].nbResource) + val >= 0 ){
            m->map[x][y].nbResource = tmp + val;
            res = NO_ERROR;
        }else{
            res = ERROR_NEGATIVE_RESULT;
        }
    }else{
        res = ERROR_CASE_NOT_FOUND;
    }
    return res;
}

ErrorCode map_setNumberGarbage( const int x, const int y, Map* m, int val ){
    int res, tmp = 0;
    if ( map_isCaseExist(x, y, m) == NO_ERROR ){
        if ( (tmp = m->map[x][y].nbGarbage) + val >= 0 ){
            m->map[x][y].nbGarbage = tmp + val;
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
        m->numberFISE = tmp + val;
        res = NO_ERROR;
    }else{
        res = ERROR_NEGATIVE_RESULT;
    }
    return res;
}

ErrorCode map_setNumberFISA( Map* m, int val ){
    int res, tmp = 0;
    if ( (tmp = m->numberFISA) + val >= 0 ){
        m->numberFISA = tmp + val;
        res = NO_ERROR;
    }else{
        res = ERROR_NEGATIVE_RESULT;
    }
    return res;
}

ErrorCode map_setNumberE( Map* m, int val ){
    int res, tmp = 0;
    if ( (tmp = m->E) + val >= 0 ){
        m->E = tmp + val;
        res = NO_ERROR;
    }else{
        res = ERROR_NEGATIVE_RESULT;
    }
    return res;
}

ErrorCode map_setNumberDD( Map* m, int val ){
    int res, tmp = 0;
    if ( (tmp = m->DD) + val >= 0 ){
        m->DD = tmp + val;
        res = NO_ERROR;
    }else{
        res = ERROR_NEGATIVE_RESULT;
    }
    return res;
}
