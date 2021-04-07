#include "../../headers/utils/map_utils.h"
#include "../../headers/utils/const.h"

//todo: Ramzy constant ?
int map_utils_getSizeByDifficulty(Difficulty d) {
    switch (d) { // NOLINT(hicpp-multiway-paths-covered)
        case DIFFICULTY_EASY:
            return 10;
        case DIFFICULTY_MEDIUM:
            return 20;
        case DIFFICULTY_HARD:
            return 30;
    }
    return -1;
}

// TODO Valentin ; faire documentation en anglais
ErrorCode map_tryBuy(Map *m, int costE, int costDD) {
    if (map_getNumberE(m) >= costE) {
        if (map_getNumberDD(m) >= costDD) {
            map_setNumberE(m, (costE * -1));
            map_setNumberDD(m, costDD * -1);

            return NO_ERROR;
        } else {
            return ERROR_NOT_ENOUGH_DD;
        }
    } else {
        return ERROR_NOT_ENOUGH_E;
    }
}

void map_checkModifyCost(Mode mode, Target target, Map *m, int *numberE, int *numberDD) {
    const Staff *staff = staffInfo_getByModeAndType(mode, target);
    if (staff != NULL) {
        int idStaff = staff_getStaffID(staff);
        Dictionary * dictionary = map_getStaffDictionary(m);
        int numberStaff = staff_getNumberStaffByID(dictionary, idStaff);
        const Effect *effect = staff_getStaffEffect(staff);

        if (numberStaff > 0 && effect != NULL) {

            switch (mode) {
                case CONSTRUCTION:
                case UPGRADE:
                case DESTROY: {
                    int modifyE = effect_getModifierE(effect);
                    int modifyDD = effect_getModifierDD(effect);
                    int minE = effect_getMinCostE(effect);
                    int minDD = effect_getMinCostDD(effect);

                    *numberE = *numberE - (modifyE * numberStaff);
                    if (*numberE < minE) {
                        *numberE = minE;
                    }
                    *numberDD = *numberDD - (modifyDD * numberStaff);
                    if (*numberDD < minDD) {
                        *numberDD = minDD;
                    }
                }
                    break;
                case PRODUCTION:
                    *numberE = effect_getModifierE(effect) * numberStaff;
                    *numberDD = effect_getModifierDD(effect) * numberStaff;
                    break;
                case HIRE:
                case ON_BUY:
                case SEND_DOOR:
                case DOOR_OUT:
                case ON_TURN:
                default:
                    break;

            }
        }
    }
}

bool caseHasMachineType(MachineStuff type, Case *c) {
    Machine *machine = case_getMachine(c);
    if (machine != NULL && machine_getType(machine) == type) {
        return true;
    } else {
        return false;
    }
}

Case *getLastConveyorBelt(Map *m, Case *c) { // NOLINT(misc-no-recursion)
    // TODO Valentin : Corriger
    /*Machine *machine = case_getMachine(c);
    Orientation *orientation = machine_getOrientation(machine);
    int x = case_getX(c);
    int y = case_getY(c);

    int nextX, nextY, dSave;

    if (machine_getOrientationBottom(orientation) == DIRECTION_OUT) {
        nextX = x;
        nextY = y - 1;
        dSave = 0;
    } else if (machine_getOrientationLeft(orientation) == DIRECTION_OUT) {
        nextX = x - 1;
        nextY = y;
        dSave = 1;
    } else if (machine_getOrientationTop(orientation) == DIRECTION_OUT) {
        nextX = x;
        nextY = y + 1;
        dSave = 2;
    } else if (machine_getOrientationRight(orientation) == DIRECTION_OUT) {
        nextX = x + 1;
        nextY = y;
        dSave = 3;
    } else return NULL;

    Case *next = map_getCase(nextX, nextY, m);
    if (next != NULL) {
        if (caseHasMachineType(MS_CONVEYOR_BELT, next) || caseHasMachineType(MS_CROSS, next)) {
            Machine *nextMachine = case_getMachine(next);
            Orientation *nextOrientation = machine_getOrientation(nextMachine);

            switch (dSave) { // NOLINT(hicpp-multiway-paths-covered)
                case 0:
                    if (machine_getOrientationBottom(nextOrientation) == DIRECTION_IN) {
                        return getLastConveyorBelt(m, next);
                    }
                    return c;
                case 1:
                    if (machine_getOrientationLeft(nextOrientation) == DIRECTION_IN) {
                        return getLastConveyorBelt(m, next);
                    }
                    return c;
                case 2:
                    if (machine_getOrientationTop(nextOrientation) == DIRECTION_IN) {
                        return getLastConveyorBelt(m, next);
                    }
                    return c;
                case 3:
                    if (machine_getOrientationRight(nextOrientation) == DIRECTION_IN) {
                        return getLastConveyorBelt(m, next);
                    }
                    return c;
            }

        }
        return c;
    }
    return c;*/
}

// Fonction EndTurn
void productionFise(Map *m) {
    int productionE = PRODUCTION_FISE_E;
    int productionDD = PRODUCTION_FISE_DD;

    int numberFise = map_getNumberFISE(m);

    int modifE = 0;
    int modifDD = 0;
    // Prendre en compte les effets de staff
    map_checkModifyCost(PRODUCTION, (Target) {.other = SUB_FISE}, m, &modifE, &modifDD);

    map_setNumberE(m, (productionE + modifE) * numberFise);
    map_setNumberDD(m, (productionDD + modifDD) * numberFise);
}

void productionFisa(Map *m) {
    if (map_getNumberTurn(m) % NB_TURN_FISA == 0) {
        int productionE = PRODUCTION_FISA_E;
        int productionDD = PRODUCTION_FISA_DD;

        int numberFisa = map_getNumberFISA(m);

        int modifE = 0;
        int modifDD = 0;
        // Prendre en compte les effets de staff
        map_checkModifyCost(PRODUCTION, (Target) {.other = SUB_FISA}, m, &modifE, &modifDD);

        if (map_getProductionFISA(m) == E_VALUE) {
            map_setNumberE(m, (productionE + modifE) * numberFisa);
        } else {
            map_setNumberDD(m, (productionDD + modifDD) * numberFisa);
        }
    }
}

void moveResources(Map *m) {
    int width = map_getWidth(m);
    int height = map_getHeight(m);

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Case *cursor = map_getCase(x, y, m);

            if (caseHasMachineType(MS_CONVEYOR_BELT, cursor) || caseHasMachineType(MS_CROSS, cursor)) {
                // Aller jusqu'à la case qui n'a pas de successeur
                cursor = getLastConveyorBelt(m, cursor);

                // Move carton
                while (cursor != NULL) {
                    // Récupérer le précédent
                }
            }
        }
    }
}


void generateResources(Map *m) {
    int numberTour = NB_TURN_PRODUCTION_SOURCE;

    // Verifier Staff

    if (map_getNumberTurn(m) % numberTour == 0) {
        Case *c;
        int generateResource = 3;

        // Verifier staff

        for (int i = 0; i < map_getWidth(m); ++i) {
            for (int j = 0; j < map_getHeight(m); ++j) {
                c = map_getCase(i, j, m);
                if (case_getType(c) == CASE_SOURCE) {
                    //case_setNumberResource(c, generateResource);
                }
            }
        }
    }
}


ErrorCode map_sendResourcesToGate(Map *m, int resources) {
    return NO_ERROR;
}

void activateCollectors(Map *m) {
    // TODO Valentin : Corriger
    /*Case *c;
    for (int i = 0; i < map_getWidth(m); ++i) {
        for (int j = 0; j < map_getHeight(m); ++j) {
            c = map_getCase(i, j, m);
            CaseType type = case_getType(c);
            if (type == CASE_MACHINE) {
                Machine *machine = case_getMachine(c);
                if (machine_getType(machine) == MS_COLLECTOR) {
                    Orientation *orientation = machine_getOrientation(machine);
                    int x = case_getX(c);
                    int y = case_getY(c);
                    Case *next;

                    if (machine_getOrientationBottom(orientation) == DIRECTION_NONE) {
                        next = map_getCase(x, y, m);
                        if (case_getType(next) == CASE_SOURCE) {
                            // TODO Valentin : réfléchir au déplacement des ressources
                        }
                    }
                    if (machine_getOrientationLeft(orientation) == DIRECTION_NONE) {
                    }
                    if (machine_getOrientationTop(orientation) == DIRECTION_NONE) {
                    }
                    if (machine_getOrientationRight(orientation) == DIRECTION_NONE) {
                    }
                }
            }
        }
    }*/
}

void resetResourcesGarbage(Map *m) {
    Case *c, *gate;
    int numberResources, numberGarbage, allGarbage = 0;
    for (int i = 0; i < map_getWidth(m); ++i) {
        for (int j = 0; j < map_getHeight(m); ++j) {
            c = map_getCase(i, j, m);
            CaseType type = case_getType(c);
            if (type == CASE_GATE) {
                gate = c;
            } else if (type != CASE_MACHINE) {
                /*numberResources = case_getNumberResource(c);
                case_setNumberResource(c, (numberResources * -1));

                numberGarbage = case_getNumberGarbage(c);
                allGarbage += numberGarbage;
                case_setNumberGarbage(c, (numberGarbage * -1));*/
            }
        }
    }

    //case_setNumberGarbage(gate, allGarbage);
}

// Fonction specifique Staff
ErrorCode staff_actionAnneLaureLigozat(Map *m, int idStaff) {
    // Parcourir toutes les cases pour supprimer la moitie des déchets
    return NO_ERROR;
}

ErrorCode staff_actionChristopheMouilleron(Map *m, int idStaff) {
    // Récupération du staff et de son effet
    const Staff *staff = staff_getStaffByID(idStaff);
    const Effect *effect = staff_getStaffEffect(staff);

    // Recupération du nombre de fise et fisa
    int modifierFise = effect_getModifierFISE(effect);
    int modifierFisa = effect_getModifierFISA(effect);

    // Ajout des fise et fisa
    map_setNumberFISE(m, modifierFise);
    map_setNumberFISA(m, modifierFisa);

    return NO_ERROR;
}

ErrorCode staff_actionLaurentPrevel(Map *m, int idStaff) {
    // Récupération du staff et de son effet
    const Staff *staff = staff_getStaffByID(idStaff);
    const Effect *effect = staff_getStaffEffect(staff);
    int coefficient = effect_getModifierRes(effect);

    // Récupération du nomnre de fise et fisa
    int numberFise = map_getNumberFISE(m);
    int numberFisa = map_getNumberFISA(m);

    // Calcule du nombre de diplomé
    int fiseGraduate = numberFise * coefficient;
    int fisaGraduate = numberFisa * coefficient;

    // Nouveau nombre de fise et fisa
    map_setNumberFISE(m, (fiseGraduate * -1));
    map_setNumberFISA(m, (fisaGraduate * -1));

    // Envoie des ressource à la porte
    map_sendResourcesToGate(m, fisaGraduate + fiseGraduate);
    return NO_ERROR;
}