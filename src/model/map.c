#include <time.h>
#include "../../headers/map.h"
#include "../../headers/utils/map_utils.h"
#include "../../headers/utils/const.h"

#include <stdio.h>
#include <stdlib.h>

struct Map_S {
    Difficulty difficulty; //!< game difficulty
    int width; //!< int, map width
    int height; //!< int, map height
    Case ***map; //!< a bi dimensional table to refer to the board of game
    int turn; //!< int, an indicator to correspond to the actual turn of the game
    int numberFISE; //!< as the name suggest, its corresponding to the number of FISE
    int numberFISA; //!< as the name suggest, its corresponding to the number of FISA
    int E; //!< a value that measure the energy quantity of the player
    int DD; //!< a value that measure the planet general health
    int productionFISA; //!< int, it correspond to the energy type produced by the FISA, see E_VALUE/DD_VALUE
    Dictionary *team; //!< a list of staffs that the user bought
    int score; //!< a score which indicate number of resources put in the gate
};

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
    m->numberFISA = NUMBER_FISA;
    m->numberFISE = NUMBER_FISE;
    m->team = staff_createStaffDictionary();

    // Initialization of the map according to the difficulty
    m->width = map_utils_getSizeByDifficulty(dif);
    m->height = map_utils_getSizeByDifficulty(dif);
    m->difficulty = dif;

    // Create grid
    m->map = (Case ***) malloc(m->width * sizeof(Case **));
    for (int i = 0; i < m->width; i++) {
        // Creation of each Case
        m->map[i] = (Case **) malloc(m->height * sizeof(Case *));

        // Initialization of boxes
        for (int j = 0; j < m->height; ++j) {
            m->map[i][j] = case_create(i, j);
        }
    }

    // Random gate placement
    gate_x = (int) (rand() % m->width); // NOLINT(cert-msc50-cpp)
    gate_y = (int) (rand() % m->height); // NOLINT(cert-msc50-cpp)
    case_addGate(m->map[gate_x][gate_y]);

    // Random placement of the 2 sources
    for (int i = 0; i < 2; i++) {
        do {
            source_x = (int) (rand() % m->width); // NOLINT(cert-msc50-cpp)
            source_y = (int) (rand() % m->height); // NOLINT(cert-msc50-cpp)
        } while (!case_isEmpty(m->map[source_x][source_y]));

        case_addSource(m->map[source_x][source_y]);
    }

    return m;
}

ErrorCode map_destroy(Map *m) {
    // Destruction of the different arguments of the map
    free(m->team);

    for (int i = 0; i < m->width; i++) {
        for (int j = 0; j < m->height; ++j) {
            case_destroy(m->map[i][j]);
        }
        free(m->map[i]);
    }
    free(m->map);

    // Destroy map
    free(m);
    return NO_ERROR;
}

ErrorCode map_hireFISE(Map *m) {
    // Initialize base values
    int costE = COST_FISE_E;
    int costDD = COST_FISE_DD;

    // Take into account the effects of staff
    map_utils_checkModificationStaff(ON_BUY, (Target) {.other = SUB_FISE}, m, &costE, &costDD);

    // Check that the player has the money
    ErrorCode e = map_utils_tryBuy(m, costE, costDD);
    if (e == NO_ERROR) {
        map_setNumberFISE(m, 1);
        return NO_ERROR;
    } else {
        return e;
    }
}

ErrorCode map_hireFISA(Map *m) {
    // Initialize base values
    int costE = COST_FISA_E;
    int costDD = COST_FISA_DD;

    // Take into account the effects of staff
    map_utils_checkModificationStaff(ON_BUY, (Target) {.other = SUB_FISA}, m, &costE, &costDD);

    // Check that the player has the money
    ErrorCode e = map_utils_tryBuy(m, costE, costDD);
    if (e == NO_ERROR) {
        map_setNumberFISA(m, 1);
        return NO_ERROR;
    } else {
        return e;
    }
}

ErrorCode map_changeProductionFISA(Map *m) {
    // Check the previous production
    if (m->productionFISA == E_VALUE) {
        m->productionFISA = DD_VALUE;
    } else {
        m->productionFISA = E_VALUE;
    }

    return NO_ERROR;
}

ErrorCode map_endTurn(Map *m) {
    // Production of Fise
    map_utils_productionFise(m);

    // Production of Fisa
    map_utils_productionFisa(m);

    // Move resources
    map_utils_moveResources(m);

    // Generation of resources
    map_utils_generateResources(m);

    // The door produces waste
    map_utils_generateGarbage(m);

    // Operate waste reception centers
    map_utils_activateRecyclingCenters(m);

    // The collectors activate
    map_utils_activateCollectors(m);

    // Destroy the no-collected resources
    map_utils_resetResourcesGarbage(m);

    map_utils_moveResourcesInMachine(m);

    // Minus pollution to DD
    int numberPollution = map_getNumberPollution(m);
    int numberDD = map_getNumberDD(m);
    if (numberDD < numberPollution) {
        return ERROR_GAME_LOST;
    }
    map_setNumberDD(m, numberPollution * -1);

    // Checking if the player has won
    if (map_getPlayerScore(m) > NUMBER_RESOURCE_WIN){
        return ERROR_GAME_WIN;
    }

    // Turn increment
    m->turn++;
    return NO_ERROR;
}

ErrorCode map_addMachine(MachineStuff machType, int rotation, int x, int y, Map *m) {
    // Check that the box exists
    if (map_isCaseExist(x, y, m) == NO_ERROR) {
        Case *c = map_getCase(x, y, m);
        // Check that the box is empty
        if (case_isEmpty(c)) {
            //Retrieving Machine Information
            const MachineInfo *machineInfo = machineInfo_getMachineInfoByType(machType);
            int costE = machineInfo_getCostE(machineInfo);
            int costDD = machineInfo_getCostDD(machineInfo);

            // Allows you to find machine info
            map_utils_checkModificationStaff(CONSTRUCTION, (Target) {.machine = machType}, m, &costE, &costDD);

            // Check that the player has the money
            ErrorCode e = map_utils_tryBuy(m, costE, costDD);
            if (e == NO_ERROR) {
                // Created the machine
                Machine *machine = machine_create(machType);
                // Turn the machine the right way
                machine_rotateMachine(machine, rotation);
                // Add machine to box
                case_addMachine(c, machine);

                return NO_ERROR;
            } else {
                return e;
            }
        } else {
            return ERROR_CASE_NOT_EMPTY;
        }
    } else {
        return ERROR_CASE_NOT_FOUND;
    }
}

ErrorCode map_upgradeMachine(int x, int y, Map *m) {
    // Check that the box exists
    if (map_isCaseExist(x, y, m) == NO_ERROR) {
        Case *c = map_getCase(x, y, m);
        // Check that there is a machine on the square
        if (case_getType(c) == CASE_MACHINE) {
            // Recovery of the machine and its information
            Machine *machine = case_getMachine(c);
            MachineStuff machType = machine_getType(machine);

            const MachineInfo *machineInfo = machineInfo_getMachineInfoByType(machType);

            // Checking that the machine can be improved
            if (machineInfo_getCanUpgrade(machineInfo)) {
                // Recovering the base upgrade cost
                int costE = machineInfo_getCostUpgradeE(machineInfo);
                int costDD = machineInfo_getCostUpgradeDD(machineInfo);

                // Allows you to apply staff changes
                map_utils_checkModificationStaff(UPGRADE, (Target) {.machine = machType}, m, &costE, &costDD);

                // Check that the player has the money
                ErrorCode e = map_utils_tryBuy(m, costE, costDD);
                if (e == NO_ERROR) {
                    // Improve the machine
                    machine_incrementLevel(machine);

                    return NO_ERROR;
                } else {
                    return e;
                }
            } else {
                return ERROR_INVALID_ACTION_SEQUENCE;
            }
        } else {
            return ERROR_CASE_CANT_BE_UPGRADED;
        }
    } else {
        return ERROR_CASE_NOT_FOUND;
    }
}

ErrorCode map_destroyMachine(int x, int y, Map *m) {
    // Check that the box exists
    if (map_isCaseExist(x, y, m) == NO_ERROR) {
        Case *c = map_getCase(x, y, m);
        // Check that there is a machine on the square
        if (case_getType(c) == CASE_MACHINE) {
            // Recovery of the machine and its information
            Machine *machine = case_getMachine(c);
            MachineStuff machType = machine_getType(machine);

            // Recovering the base destroy cost
            const MachineInfo *machineInfo = machineInfo_getMachineInfoByType(machType);
            int costE = machineInfo_getCostDestroyE(machineInfo);
            int costDD = machineInfo_getCostDestroyDD(machineInfo);

            // Allows you to apply staff changes
            map_utils_checkModificationStaff(DESTROY, (Target) {.machine = machType}, m, &costE, &costDD);

            // Check that the player has the money
            ErrorCode e = map_utils_tryBuy(m, costE, costDD);
            if (e == NO_ERROR) {
                // Send the waste to the door
                Box *checkBox;
                for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                    checkBox = machine_getBox(machine, card);
                    if (checkBox != NULL) {
                        map_utils_sendResourcesToGate(m, box_getNumberGarbage(checkBox));
                    }
                }

                // Destroy machine
                case_setEmpty(c);

                return NO_ERROR;
            } else {
                return e;
            }
        } else {
            return ERROR_CASE_CANT_BE_DESTROYED;
        }
    } else {
        return ERROR_CASE_NOT_FOUND;
    }
}

ErrorCode map_buyStaff(int idStaff, Map *m) {
    const Staff *staff = staff_getStaffByID(idStaff);
    // Check the existence of staff
    if (staff != NULL) {
        // Recovery of the basic price of the staff
        int costE = staff_getStaffCostE(staff);
        int costDD = staff_getStaffCostDD(staff);

        // Check that the player has the money
        ErrorCode e = map_utils_tryBuy(m, costE, costDD);
        if (e == NO_ERROR) {
            // Add staff to player
            Dictionary *dictionary = map_getStaffDictionary(m);
            staff_hireStaff(dictionary, idStaff);

            // If the staff takes immediate action, do so
            switch (idStaff) {
                case 14:
                    // Parourir toutes les cases
                    e = staff_actionAnneLaureLigozat(m, 14);
                    break;
                case 15:
                    // Parourir toutes les cases
                    e = staff_actionChristopheMouilleron(m, 15);
                    break;
                case 24:
                    // Parourir toutes les cases
                    e = staff_actionLaurentPrevel(m, 24);
                    break;
                default:
                    e = NO_ERROR;
                    break;
            }

            // If the action of the staff to fail reimburse the player
            if (e != NO_ERROR) {
                map_setNumberE(m, costE);
                map_setNumberDD(m, costDD);
                return e;
            }

            return NO_ERROR;
        } else {
            return e;
        }
    } else {
        return ERROR_INVALID_STAFF_NUMBER;
    }
}

/*
 * A function to verify if the located case exist
 */
ErrorCode map_isCaseExist(const int x, const int y, const Map *m) {
    if (x >= 0 && x < m->width) {
        if (y >= 0 && y < m->height) {
            return NO_ERROR;
        }
    }
    return ERROR_CASE_NOT_FOUND;
}

/*
 * a function to get the number of FISE
 */
int map_getNumberFISE(const Map *m) { return m->numberFISE; }

/*
 * a function to get the number of FISA
 */
int map_getNumberFISA(const Map *m) { return m->numberFISA; }

/*
 * a function to get the number of E
 */
int map_getNumberE(const Map *m) { return m->E; }

/*
 * a function to get the number of DD
 */
int map_getNumberDD(const Map *m) { return m->DD; }

/*
 * a function to get the player score
 */
int map_getPlayerScore(const Map *m) { return m->score; }

/*
 * a function to get the difficulty of the map
 */
Difficulty map_getDifficulty(const Map *m) { return m->difficulty; }

/*
 * a function to get map width
 */
int map_getWidth(const Map *m) { return m->width; }

/*
 * a function to get map height
 */
int map_getHeight(const Map *m) { return m->height; }

/*
 * a function to get the number of turn
 */
int map_getNumberTurn(const Map *m) { return m->turn; }

/*
 * a function to get the production of FISA
 */
int map_getProductionFISA(const Map *m) { return m->productionFISA; }

/*
 * a function to get the staff dictionary
 */
Dictionary *map_getStaffDictionary(const Map *m) { return m->team; }

/*
 * a function to get a case of the map
 */
Case *map_getCase(const int x, const int y, const Map *m) {
    if (map_isCaseExist(x, y, m) == NO_ERROR) {
        return m->map[x][y];
    } else {
        return NULL;
    }
}

/*
 * This function get the pollution number
 * In order to have this information, we have to sum each case garbage
 * A garbage is contained on the case (in a box) or in a facade machine (in a box)
 */
int map_getNumberPollution(const Map *m) {
    int nbGarbage = 0;
    // Process each case of the map
    for (int i = 0; i < m->height; ++i) {
        for (int j = 0; j < m->width; ++j) {
            Case *c = map_getCase(i, j, m);

            // Garbage contained in a box on the case
            if (case_hasBox(c)) {
                nbGarbage += box_getNumberGarbage(case_getBox(c));

            // Garbage contained in a machine
            // We have to sum garbage of each facade of the machine
            } else if (case_getType(c) == CASE_MACHINE) {
                Machine *machine = case_getMachine(c);
                MachineStuff machineType = machine_getType(machine);

                // We don't take garbage from a junkyard into account
                if (machineType != MS_JUNKYARD) {
                    for (Cardinal k = 0; k < NUMBER_CARDINAL; ++k) {
                        if (machine_getBox(machine, k) != NULL) {
                            nbGarbage += box_getNumberGarbage(machine_getBox(machine, k));
                        }
                    }
                };
            }
        }
    }
    return nbGarbage;
}

/*
 * This function set the number of FISE recruited by the player.
 */
ErrorCode map_setNumberFISE(Map *m, int val) {
    if (m->numberFISE + val >= 0) {
        m->numberFISE += val;
        return NO_ERROR;
    } else {
        return ERROR_NEGATIVE_RESULT;
    }
}

/*
 * This function set the number of FISA recruited by the player.
 */
ErrorCode map_setNumberFISA(Map *m, int val) {
    if (m->numberFISA + val >= 0) {
        m->numberFISA += val;
        return NO_ERROR;
    } else {
        return ERROR_NEGATIVE_RESULT;
    }
}

/*
 * This function set the number of E posseded by the player.
 */
ErrorCode map_setNumberE(Map *m, int val) {
    if (m->E + val >= 0) {
        m->E += val;
        return NO_ERROR;
    } else {
        return ERROR_NEGATIVE_RESULT;
    }
}

/*
 * This function set the number of DD posseded by the player.
 */
ErrorCode map_setNumberDD(Map *m, int val) {
    if (m->DD + val >= 0) {
        m->DD += val;
        return NO_ERROR;
    } else {
        return ERROR_NEGATIVE_RESULT;
    }
}

/*
 * This function set the score
 */
ErrorCode map_setNumberScore(Map *m, int val) {
    if (m->score + val >= 0) {
        m->score += val;
        return NO_ERROR;
    } else {
        return ERROR_NEGATIVE_RESULT;
    }
}

/*
 * This function set the turn
 */
ErrorCode map_setNumberTurn(Map *m, int val) {
    if (m->turn + val >= 0) {
        m->turn += val;
        return NO_ERROR;
    } else {
        return ERROR_NEGATIVE_RESULT;
    }
}