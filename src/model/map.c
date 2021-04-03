#include <time.h>
#include "../../headers/map.h"
#include "../../headers/utils/map_utils.h"

#include <stdio.h>
#include <stdlib.h>

Map* map_create(Difficulty dif){
    // Initialisation map
    Map* m = (Map*) malloc(sizeof(Map));
    int source_x, source_y, gate_x, gate_y;

    // Initializing the basic values of the game
    m->turn = 1;
    m->productionFISA = E_VALUE;
    m->E = 100;
    m->DD = 100;
    m->score = 0;
    m->pollution = 0;
    m->numberFISA = 5;
    m->numberFISE = 5;
    m->numberStaff = 0;
    m->team = NULL;

    // Initialization of the map according to the difficulty
    m->width = map_utils_getSizeByDifficulty(dif);
    m->height = map_utils_getSizeByDifficulty(dif);
    m->difficulty = dif;

    // Create grid
    m->map = (Case**)malloc(m->width*sizeof(Case*));
    for (int i = 0; i < m->width; i++) {
        // Creation of each Case
        m->map[i] = (Case*)malloc(m->height*sizeof(Case));

        // Initialization of boxes
        for (int j = 0; j < m->height; ++j) {
            m->map[i][j].x = i;
            m->map[i][j].y = j;
            m->map[i][j].nbGarbage = 0;
            m->map[i][j].nbResource = 0;
            m->map[i][j].type = CASE_VIDE;
            m->map[i][j].in.other = NULL;
        }
    }

    srandom( time( NULL ) );
    // Random gate placement
    gate_x = (int) (random() % m->width);
    gate_y = (int) (random() % m->height);
    m->map[gate_x][gate_y].type = CASE_GATE;

    // Random placement of the 2 sources
    for (int i = 0; i < 2; i++){
        do {
            source_x = (int) (random() % m->width);
            source_y = (int) (random() % m->height);
        } while (m->map[source_x][source_y].type != CASE_VIDE);

        m->map[source_x][source_y].type = CASE_SOURCE;
    }

    return m;
}

ErrorCode map_destroy(Map* m){
    free(m->team);

    for (int i = 0; i < m->width; i++) {
        free(m->map[i]);
    }
    free(m->map);

    free(m);
    return NO_ERROR;
}

ErrorCode map_hireFISE(Map* m){
    if (m->E >= 50) {
        if (m->DD >= 20) {
            m->E = m->E - 50;
            m->DD = m->DD - 20;

            m->numberFISE++;
        } else {
            return ERROR_NOT_ENOUGH_DD;
        }
    } else {
        return ERROR_NOT_ENOUGH_E;
    }

    return NO_ERROR;
}

ErrorCode map_hireFISA(Map* m){
    if (m->E >= 50) {
        if (m->DD >= 20) {
            m->E = m->E - 50;
            m->DD = m->DD - 20;

            m->numberFISA++;
        } else {
            return ERROR_NOT_ENOUGH_DD;
        }
    } else {
        return ERROR_NOT_ENOUGH_E;
    }

    return NO_ERROR;
}

ErrorCode map_changeProductionFISA(Map* m){
    if (m->productionFISA == E_VALUE) {
        m->productionFISA = DD_VALUE;
    } else {
        m->productionFISA = E_VALUE;
    }

    return NO_ERROR;
}

ErrorCode map_endTurn(Map* m){

    // TODO Valentin : Déplacer les ressources
    // TODO Valentin : Gagner les sous des fise et des Fisa au besoin.
    // TODO Valentin : Générer les ressources avec les sources
    // TODO Valentin : Faire fonctionner les décheteries
    m->turn++;
    return NO_ERROR;
}

ErrorCode map_isEmpty(const int x, const int y, const Map* m){return NO_ERROR;}

ErrorCode map_addMachine(MachineStuff type, int x, int y, Map* m){
    int index, costE, costDD, numberMachine;
    if (map_isCaseExist(x,y,m) == NO_ERROR) {
        if (map_isEmpty(x,y,m) == NO_ERROR) {

            index = 0;
            while (machine_list[index].type != type) {index++;}

            numberMachine = 0;
            for (int i = 0; i < m->width; ++i) {
                for (int j = 0; j < m->height; ++j) {
                    if (m->map[i][j].type == CASE_MACHINE && m->map[i][j].in.mach->type == type) {
                        numberMachine++;
                    }
                }
            }

            if (machine_list[index].canUpgrade == 1) {
                costE = machine_list[index].costE - (numberMachine + machine_list[index].effects->modifierE);
                if (costE < machine_list[index].effects->min_costE) {
                    costE = machine_list[index].effects->min_costE;
                }
                costDD = machine_list[index].costDD - (numberMachine + machine_list[index].effects->modifierDD);
                if (costDD < machine_list[index].effects->min_costDD) {
                    costDD = machine_list[index].effects->min_costDD;
                }
            } else {
                costE = machine_list[index].costE;
                costDD = machine_list[index].costDD;
            }

            if (m->E >= costE) {
                if (m->DD >= costDD) {
                    Machine * machine = (Machine*)malloc(sizeof (Machine));
                    machine->type = type;
                    machine->level = 1;
                    machine->capacity = 0;

                    return NO_ERROR;
                } else {
                    return ERROR_NOT_ENOUGH_DD;
                }
            } else {
                return ERROR_NOT_ENOUGH_E;
            }
        } else {
            return ERROR;
        }
    } else {
        return ERROR_CASE_NOT_FOUND;
    }
}

ErrorCode map_upgradeMachine(int x, int y, Map* m){
    if (map_isCaseExist(x,y,m) == NO_ERROR) {
        if (map_getTypeCase(x,y,m) == CASE_MACHINE) {
            MachineStuff machType = map_getTypeMachine(x,y,m);


            // TODO Valentin : Faire le traitement par type de machine

            return NO_ERROR;
        } else {
            return ERROR;
        }
    } else {
        return ERROR_CASE_NOT_FOUND;
    }
}

ErrorCode map_destroyMachine(int x, int y, Map* m){
    if (map_isCaseExist(x,y,m) == NO_ERROR) {
        if (map_getTypeCase(x,y,m) == CASE_MACHINE) {

            free(m->map[x][y].in.mach);
            m->map[x][y].in.mach = NULL;
            m->map[x][y].type = CASE_VIDE;

            return NO_ERROR;
        } else {
            return ERROR;
        }
    } else {
        return ERROR_CASE_NOT_FOUND;
    }
}

ErrorCode map_buyStaff(Staff s, Map* m){
    return ERROR_NOT_ENOUGH_E;
}

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
