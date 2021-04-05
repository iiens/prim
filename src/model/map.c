#include <time.h>
#include "../../headers/map.h"
#include "../../headers/utils/map_utils.h"
#include "../../headers/utils/const.h"

#include <stdio.h>
#include <stdlib.h>

ErrorCode map_tryBuy(Map *m, int costE, int costDD) {
    if (m->E >= costE) {
        if (m->DD >= costDD) {
            m->E = m->E - costE;
            m->DD = m->DD - costDD;

            return NO_ERROR;
        } else {
            return ERROR_NOT_ENOUGH_DD;
        }
    } else {
        return ERROR_NOT_ENOUGH_E;
    }
}

Map *map_create(Difficulty dif) {
    // Initialisation map
    Map *m = (Map *) malloc(sizeof(Map));
    int source_x, source_y, gate_x, gate_y;

    // Initializing the basic values of the game
    m->turn = 1;
    m->productionFISA = E_VALUE;
    m->E = NUMBER_E_DEPART;
    m->DD = NUMBER_DD_DEPART;
    m->score = 0;
    m->pollution = 0;
    m->numberFISA = NUMBER_FISA;
    m->numberFISE = NUMBER_FISE;
    m->numberStaff = 0;
    m->team = NULL;

    // Initialization of the map according to the difficulty
    m->width = map_utils_getSizeByDifficulty(dif);
    m->height = map_utils_getSizeByDifficulty(dif);
    m->difficulty = dif;

    // Create grid
    m->map = (Case **) malloc(m->width * sizeof(Case *));
    for (int i = 0; i < m->width; i++) {
        // Creation of each Case
        m->map[i] = (Case *) malloc(m->height * sizeof(Case));

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

    srandom(time(NULL));
    // Random gate placement
    gate_x = (int) (random() % m->width);
    gate_y = (int) (random() % m->height);
    m->map[gate_x][gate_y].type = CASE_GATE;

    // Random placement of the 2 sources
    for (int i = 0; i < 2; i++) {
        do {
            source_x = (int) (random() % m->width);
            source_y = (int) (random() % m->height);
        } while (m->map[source_x][source_y].type != CASE_VIDE);

        m->map[source_x][source_y].type = CASE_SOURCE;
    }

    return m;
}

ErrorCode map_destroy(Map *m) {
    free(m->team);

    for (int i = 0; i < m->width; i++) {
        free(m->map[i]);
    }
    free(m->map);

    free(m);
    return NO_ERROR;
}

ErrorCode map_hireFISE(Map *m) {
    int costE, costDD;

    costE = COST_FISE_E;
    costDD = COST_FISE_DD;

    // Prendre en compte les effets de staff
    //map_checkCostEffectStaff(m, HIRE, (Target) {.other = SUB_FISE}, &costE, &costDD);

    // Vérifie que le joueur à les sous
    ErrorCode e = map_tryBuy(m, costE, costDD);
    if (e == NO_ERROR) {
        map_setNumberFISE(m, 1);
        return NO_ERROR;
    } else {
        return e;
    }
}

ErrorCode map_hireFISA(Map *m) {
    int costE, costDD;

    costE = COST_FISA_E;
    costDD = COST_FISA_DD;

    // Prendre en compte les effets de staff
    //map_checkCostEffectStaff(m, HIRE, (Target) {.other = SUB_FISA}, &costE, &costDD);

    // Vérifie que le joueur à les sous
    ErrorCode e = map_tryBuy(m, costE, costDD);
    if (e == NO_ERROR) {
        map_setNumberFISA(m, 1);
        return NO_ERROR;
    } else {
        return e;
    }
}

ErrorCode map_changeProductionFISA(Map *m) {
    if (m->productionFISA == E_VALUE) {
        m->productionFISA = DD_VALUE;
    } else {
        m->productionFISA = E_VALUE;
    }

    return NO_ERROR;
}

void productionFise(Map *m) {
    int productionE, productionDD, numberFise;

    productionE = PRODUCTION_FISE_E;
    productionDD = PRODUCTION_FISE_DD;
    numberFise = map_getNumberFISE(m);
    // Prendre en compte les effets de staff
    //map_checkCostEffectStaff(m, CONSTRUCTION, (Target) {.machine = type}, &productionE, &productionDD);
    map_setNumberE(m, productionE * numberFise);
    map_setNumberDD(m, productionDD * numberFise);
}

void productionFisa(Map *m) {
    int productionE, productionDD, numberFisa;

    if (m->turn % NB_TURN_FISA == 0) {
        productionE = PRODUCTION_FISA_E;
        productionDD = PRODUCTION_FISA_DD;
        numberFisa = map_getNumberFISA(m);

        // Prendre en compte les effets de staff
        //map_checkCostEffectStaff(m, CONSTRUCTION, (Target) {.machine = type}, &productionE, &productionDD);

        if (m->productionFISA == E_VALUE) {
            map_setNumberE(m, productionE * numberFisa);
        } else {
            map_setNumberDD(m, productionDD * numberFisa);
        }
    }
}

ErrorCode map_endTurn(Map *m) {
    int nombreTour;

    // Productin des Fise
    productionFise(m);

    // Productin des Fisa
    productionFisa(m);

    // TODO Valentin : Déplacer les ressources

    // TODO Valentin : Générer les ressources avec les sources
    // Vérifier
    nombreTour = NB_TURN_PRODUCTION_SOURCE;
    // Décrémenter les
    if (m->turn % 10 == 0) {
        // récupérer l'emplacement des sources
        // incrémenter m->map[0][0].nbResource + NB_RESSOURCE_PRODUCT_BY_SOURCE;
    }

    // TODO Valentin : La porte prduit des déchêts

    // TODO Valentin : Faire fonctionner les décheteries

    // TODO Valentin : Les collecteurs s'activent

    // TODO Valentin : Suprimerles ressources non collecté

    m->turn++;
    return NO_ERROR;
}

ErrorCode map_isEmpty(const int x, const int y, const Map *m) { return NO_ERROR; }

ErrorCode map_addMachine(MachineStuff type, Orientation orientation, int x, int y, Map *m) {
    int indexM, costE, costDD;
    if (map_isCaseExist(x, y, m) == NO_ERROR) {
        if (map_isEmpty(x, y, m) == NO_ERROR) {

            // Permet de trouver les infos de la machine
            indexM = map_getIndexByMachine(type);

            costE = machine_list[indexM].costE;
            costDD = machine_list[indexM].costDD;

            // Prendre en compte les effets de staff
            //map_checkCostEffectStaff(m, CONSTRUCTION, (Target) {.machine = type}, &costE, &costDD);

            // Vérifie que le joueur à les sous
            ErrorCode e = map_tryBuy(m, costE, costDD);
            if (e == NO_ERROR) {
                Machine *machine = (Machine *) malloc(sizeof(Machine));
                machine->type = type;
                machine->level = 1;
                machine->orientation = orientation;

                m->map[x][y].type = CASE_MACHINE;
                m->map[x][y].in.mach = machine;

                return NO_ERROR;
            } else {
                return e;
            }
        } else {
            return ERROR;
        }
    } else {
        return ERROR_CASE_NOT_FOUND;
    }
}

ErrorCode map_upgradeMachine(int x, int y, Map *m) {
    int indexM, costE, costDD;
    if (map_isCaseExist(x, y, m) == NO_ERROR) {
        if (map_getTypeCase(x, y, m) == CASE_MACHINE) {
            MachineStuff machType = map_getTypeMachine(x, y, m);

            // Permet de trouver les infos de la machine
            indexM = map_getIndexByMachine(machType);

            if (machine_list[indexM].canUpgrade) {

                costE = machine_list[indexM].costUpgradeE;
                costDD = machine_list[indexM].costUpgradeDD;

                // Prendre en compte les effets de staff
                //map_checkCostEffectStaff(m, UPGRADE, (Target) {.machine = machType}, &costE, &costDD);

                // Vérifie que le joueur à les sous
                ErrorCode e = map_tryBuy(m, costE, costDD);
                if (e == NO_ERROR) {
                    m->map[x][y].in.mach->level++;

                    return NO_ERROR;
                } else {
                    return e;
                }
            } else {
                return ERROR_INVALID_ACTION_SEQUENCE;
            }
        } else {
            return ERROR;
        }
    } else {
        return ERROR_CASE_NOT_FOUND;
    }
}

ErrorCode map_destroyMachine(int x, int y, Map *m) {
    int indexM, costE, costDD;
    if (map_isCaseExist(x, y, m) == NO_ERROR) {
        if (map_getTypeCase(x, y, m) == CASE_MACHINE) {
            MachineStuff machType = map_getTypeMachine(x, y, m);

            // Permet de trouver les infos de la machine
            indexM = map_getIndexByMachine(machType);

            costE = machine_list[indexM].costDestroyE;
            costDD = machine_list[indexM].costDestroyDD;

            // Prendre en compte les effets de staff
            //map_checkCostEffectStaff(m, DESTROY, (Target) {.machine = machType}, &costE, &costDD);

            // Vérifie que le joueur à les sous
            ErrorCode e = map_tryBuy(m, costE, costDD);
            if (e == NO_ERROR) {
                free(m->map[x][y].in.mach);
                m->map[x][y].in.mach = NULL;
                m->map[x][y].type = CASE_VIDE;

                return NO_ERROR;
            } else {
                return e;
            }
        } else {
            return ERROR;
        }
    } else {
        return ERROR_CASE_NOT_FOUND;
    }
}

ErrorCode map_buyStaff(Staff s, Map *m) {
    return ERROR_NOT_ENOUGH_E;
}

ErrorCode map_isCaseExist(const int x, const int y, const Map *m) {
    if (x >= 0 && x < m->width) {
        if (y >= 0 && y < m->height) {
            return NO_ERROR;
        }
    }
    return ERROR_CASE_NOT_FOUND;
}

//\////////////////////////////\//
//\/ Functions Getters
//\////////////////////////////\//

int map_getNumberResource(const int x, const int y, const Map *m) {
    int res = -1;
    if (map_isCaseExist(x, y, m) == NO_ERROR) {
        res = m->map[x][y].nbResource;
    }
    return res;
}

int map_getNumberGarbage(const int x, const int y, const Map *m) {
    int res = -1;
    if (map_isCaseExist(x, y, m) == NO_ERROR) {
        res = m->map[x][y].nbGarbage;
    }
    return res;
}

int map_getNumberFISE(const Map *m) { return m->numberFISE; }

int map_getNumberFISA(const Map *m) { return m->numberFISA; }

int map_getNumberE(const Map *m) { return m->E; }

int map_getNumberDD(const Map *m) { return m->DD; }

int map_getPlayerScore(const Map *m) { return m->score; }

int map_getNumberPollution(const Map *m) { return m->pollution; }

Difficulty map_getDifficulty(const Map *m) { return m->difficulty; }

int map_getWidth(const Map *m) { return m->width; }

int map_getHeight(const Map *m) { return m->height; }

int map_getNumberStaff(const Map *m) { return m->numberStaff; }

int map_getNumberTurn( const Map* m ) { return m->turn; }

int map_getProductionFISA( const Map* m ) { return m->productionFISA; }

Case *map_getCase(const int x, const int y, const Map *m) {
    if (map_isCaseExist(x, y, m) == NO_ERROR) {
        return &(m->map[x][y]);
    } else {
        return NULL;
    }
}

CaseType map_getTypeCase(const int x, const int y, const Map *m) {
    if (map_isCaseExist(x, y, m) == NO_ERROR) {
        return m->map[x][y].type;
    } else {
        return -1;
    }
}

MachineStuff map_getTypeMachine(const int x, const int y, const Map *m) {
    if (map_getTypeCase(x, y, m) == CASE_MACHINE) {
        return m->map[x][y].in.mach->type;
    } else {
        return -1;
    }
}

int map_getIndexByMachine(MachineStuff type) {
    int indexM = 0;
    while (indexM < NUMBER_OF_MACHINES && machine_list[indexM].type != type) { indexM++; }

    if (indexM == NUMBER_OF_MACHINES) {
        return -1;
    } else {
        return indexM;
    }
}

//\////////////////////////////\//
//\/ Functions Setters
//\////////////////////////////\//

ErrorCode map_setNumberResource(const int x, const int y, Map *m, int val) {
    if (map_isCaseExist(x, y, m) == NO_ERROR) {
        if (m->map[x][y].nbResource + val >= 0) {
            m->map[x][y].nbResource += val;
            return NO_ERROR;
        } else {
            return ERROR_NEGATIVE_RESULT;
        }
    } else {
        return ERROR_CASE_NOT_FOUND;
    }
}

ErrorCode map_setNumberGarbage(const int x, const int y, Map *m, int val) {
    if (map_isCaseExist(x, y, m) == NO_ERROR) {
        if (m->map[x][y].nbGarbage + val >= 0) {
            m->map[x][y].nbGarbage += val;
            return NO_ERROR;
        } else {
            return ERROR_NEGATIVE_RESULT;
        }
    } else {
        return ERROR_CASE_NOT_FOUND;
    }
}

ErrorCode map_setNumberFISE(Map *m, int val) {
    if (m->numberFISE + val >= 0) {
        m->numberFISE += val;
        return NO_ERROR;
    } else {
        return ERROR_NEGATIVE_RESULT;
    }
}

ErrorCode map_setNumberFISA(Map *m, int val) {
    if (m->numberFISA + val >= 0) {
        m->numberFISA += val;
        return NO_ERROR;
    } else {
        return ERROR_NEGATIVE_RESULT;
    }
}

ErrorCode map_setNumberE(Map *m, int val) {
    if (m->E + val >= 0) {
        m->E += val;
        return NO_ERROR;
    } else {
        return ERROR_NEGATIVE_RESULT;
    }
}

ErrorCode map_setNumberDD(Map *m, int val) {
    if (m->DD + val >= 0) {
        m->DD += val;
        return NO_ERROR;
    } else {
        return ERROR_NEGATIVE_RESULT;
    }
}
