#include <stdio.h>
#include "../../headers/utils/map_utils.h"
#include "../../headers/utils/const.h"
#include "../../headers/data/box.h"

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
ErrorCode map_utils_tryBuy(Map *m, int costE, int costDD) {
    if (map_getNumberE(m) >= costE) {
        if (map_getNumberDD(m) >= costDD) {
            map_setNumberE(m, costE * -1);
            map_setNumberDD(m, costDD * -1);

            return NO_ERROR;
        } else {
            return ERROR_NOT_ENOUGH_DD;
        }
    } else {
        return ERROR_NOT_ENOUGH_E;
    }
}

void map_utils_checkModifyCost(Mode mode, Target target, Map *m, int *numberE, int *numberDD) {
    const Staff *staff = staffInfo_getByModeAndType(mode, target);
    if (staff != NULL) {
        int idStaff = staff_getStaffID(staff);
        Dictionary *dictionary = map_getStaffDictionary(m);
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

                    *numberE = *numberE + (modifyE * numberStaff);
                    if (*numberE < minE) {
                        *numberE = minE;
                    }
                    *numberDD = *numberDD + (modifyDD * numberStaff);
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

bool map_utils_caseHasMachineType(MachineStuff type, Case *c) {
    CaseType caseType = case_getType(c);
    if (caseType == CASE_MACHINE) {
        Machine *machine = case_getMachine(c);
        if (machine_getType(machine) == type) {
            return true;
        }
    }
    return false;
}

Case *map_utils_getLastConveyorBelt(Map *m, Case *c) { // NOLINT(misc-no-recursion)
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

Cardinal map_utils_getCardinalWithDirection(const Machine *machine, Direction direction) {
    Direction dir = facade_getDirection(machine, NORTH);
    if (dir == direction) {

    }
    dir = facade_getDirection(machine, EAST);
    if (dir == direction) {

    }
    dir = facade_getDirection(machine, SOUTH);
    if (dir == direction) {

    }
    dir = facade_getDirection(machine, NORTH);
    if (dir == direction) {

    }

}

// Fonction EndTurn
void map_utils_productionFise(Map *m) {
    int productionE = PRODUCTION_FISE_E;
    int productionDD = PRODUCTION_FISE_DD;

    int numberFise = map_getNumberFISE(m);

    int modifE = 0;
    int modifDD = 0;
    // Prendre en compte les effets de staff
    map_utils_checkModifyCost(PRODUCTION, (Target) {.other = SUB_FISE}, m, &modifE, &modifDD);

    map_setNumberE(m, (productionE + modifE) * numberFise);
    map_setNumberDD(m, (productionDD + modifDD) * numberFise);
}

void map_utils_productionFisa(Map *m) {
    if (map_getNumberTurn(m) % NB_TURN_FISA == 0) {
        int productionE = PRODUCTION_FISA_E;
        int productionDD = PRODUCTION_FISA_DD;

        int numberFisa = map_getNumberFISA(m);

        int modifE = 0;
        int modifDD = 0;
        // Prendre en compte les effets de staff
        map_utils_checkModifyCost(PRODUCTION, (Target) {.other = SUB_FISA}, m, &modifE, &modifDD);

        if (map_getProductionFISA(m) == E_VALUE) {
            map_setNumberE(m, (productionE + modifE) * numberFisa);
        } else {
            map_setNumberDD(m, (productionDD + modifDD) * numberFisa);
        }
    }
}

void map_utils_moveResources(Map *m) {
    //Parcourir tous les tapis et déplacer les box de l'interface OUT de la machine sur l'interface IN de la suivante suivant
    // Création d'une fonction qui process une machine et donc déplace toutes les Box de l'interface IN vers OUT de la même machine

    int width = map_getWidth(m);
    int height = map_getHeight(m);

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Case *cursor = map_getCase(x, y, m);

            if (map_utils_caseHasMachineType(MS_CONVEYOR_BELT, cursor) ||
                map_utils_caseHasMachineType(MS_CROSS, cursor)) {
                // Aller jusqu'à la case qui n'a pas de successeur
                cursor = map_utils_getLastConveyorBelt(m, cursor);

                // Move carton
                while (cursor != NULL) {
                    // Récupérer le précédent
                }
            }
        }
    }
}

void map_utils_generateResources(Map *m) {
    int numberTour = NB_TURN_PRODUCTION_SOURCE;

    // TODO Valentin : attendre
    //map_checkModifyCost(PRODUCTION, (Target) {.other = SUB_FISA}, m, &numberTour, NULL);

    if (map_getNumberTurn(m) % numberTour == 0) {
        Case *c;
        int generateResource = NB_RESOURCE_PRODUCT_BY_SOURCE;

        // Verifier staff

        for (int i = 0; i < map_getWidth(m); ++i) {
            for (int j = 0; j < map_getHeight(m); ++j) {
                c = map_getCase(i, j, m);
                if (case_getType(c) == CASE_SOURCE) {
                    case_addBox(c, box_create(generateResource, 0));
                }
            }
        }
    }
}

ErrorCode map_utils_sendResourcesToGate(Map *m) {
    Case *c;
    CaseType type;
    for (int i = 0; i < map_getWidth(m); ++i) {
        for (int j = 0; j < map_getHeight(m); ++j) {
            c = map_getCase(i, j, m);
            type = case_getType(c);
            if (type == CASE_GATE && case_hasBox(c)) {
                Box *box = case_getBox(c);
                int numberR = box_getNumberResource(box);
                box_setNumberGarbage(box, numberR);
                map_setNumberScore(m, numberR);
                box_setNumberResource(box, numberR * -1);
            }
        }
    }

    return NO_ERROR;
}

void map_utils_activateCollectors(Map *m) {
    MachineStuff machineType = MS_COLLECTOR;
    const MachineInfo *machineInfo = machineInfo_getMachineStuff(machineType);
    const Effect *effect = machineInfo_getEffects(machineInfo);
    int BaseCapacity = machineInfo_getCapacity(machineInfo);
    int modifiers = effect_getModifierCapacity(effect);

    Case *c;
    for (int j = 0; j < map_getHeight(m); ++j) {
        for (int i = 0; i < map_getWidth(m); ++i) {
            c = map_getCase(i, j, m);
            if (map_utils_caseHasMachineType(machineType, c)) {
                Machine *machine = case_getMachine(c);
                Box *cumulative = box_create(0, 0);

                int capacity = BaseCapacity + modifiers * machine_getLevel(machine);
                int x = case_getX(c);
                int y = case_getY(c);
                Case *next;
                Direction dir;
                Cardinal out;
                List * listSource = NULL;

                dir = facade_getDirection(machine, NORTH);
                if (dir == DIRECTION_NONE) {
                    next = map_getCase(x, y + 1, m);
                    if (case_getType(next) == CASE_SOURCE && case_hasBox(c)) {
                        list_addElement(listSource, {
                                .type = OBJECT,
                                .content.object = next
                        });
                    }
                } else if (dir == DIRECTION_OUT) {
                    out = NORTH;
                }
                dir = facade_getDirection(machine, NORTH);
                if (dir == DIRECTION_NONE) {
                    next = map_getCase(x + 1, y, m);
                    if (case_getType(next) == CASE_SOURCE && case_hasBox(c)) {
                        //list_addElement(listSource, elem);
                    }
                } else if (dir == DIRECTION_OUT) {
                    out = EAST;
                }
                dir = facade_getDirection(machine, NORTH);
                if (dir == DIRECTION_NONE) {
                    next = map_getCase(x, y - 1, m);
                    if (case_getType(next) == CASE_SOURCE && case_hasBox(c)) {
                        //list_addElement(listSource, elem);
                    }
                } else if (dir == DIRECTION_OUT) {
                    out = SOUTH;
                }
                dir = facade_getDirection(machine, NORTH);
                if (dir == DIRECTION_NONE) {
                    next = map_getCase(x - 1, y, m);
                    if (case_getType(next) == CASE_SOURCE && case_hasBox(c)) {
                        //list_addElement(listSource, elem);
                    }
                } else if (dir == DIRECTION_OUT) {
                    out = WEST;
                }

                // temps que capacity > 0 and il reste des ressources
                // TODO Valentin
            }
        }
    }
}

void map_utils_resetResourcesGarbage(Map *m) {
    Case *c, *gate;
    Box *box = box_create(0, 0);
    Box *tmpBox;

    for (int i = 0; i < map_getWidth(m); ++i) {
        for (int j = 0; j < map_getHeight(m); ++j) {
            c = map_getCase(i, j, m);
            CaseType type = case_getType(c);
            if (type == CASE_GATE) {
                gate = c;
            } else if (case_hasBox(c)) {
                tmpBox = case_getBox(c);
                box_setNumberGarbage(box, box_getNumberGarbage(tmpBox));

                case_deleteBox(c);
            }
        }
    }

    if (case_hasBox(gate)) {
        box_addB2toB1(case_getBox(gate), box);
        free(box);
    } else {
        case_addBox(gate, box);
    }
}

// Fonction specifique Staff
ErrorCode staff_actionAnneLaureLigozat(Map *m, int idStaff) {
    // Récupération du staff et de son effet
    const Staff *staff = staff_getStaffByID(idStaff);
    const Effect *effect = staff_getStaffEffect(staff);
    int coefficient = effect_getModifierRes(effect);

    // Parcourir toutes les cases pour supprimer la moitie des déchets
    Case *c;
    int numberG, rest, div;
    for (int i = 0; i < map_getWidth(m); ++i) {
        for (int j = 0; j < map_getHeight(m); ++j) {
            Box *box;
            c = map_getCase(i, j, m);
            CaseType type = case_getType(c);

            if (case_hasBox(c)) {
                box = case_getBox(c);
                numberG = box_getNumberGarbage(box);

                div = (numberG * coefficient) / 100;

                box_setNumberGarbage(box, div * -1);
            } else if (type == CASE_MACHINE) {
                Machine *machine = case_getMachine(c);

                // Remplacer 4 par define ou getNumberFacade
                for (int k = 0; k < 4; ++k) {
                    box = facade_getBox(machine, 0);
                    numberG = box_getNumberGarbage(box);

                    div = (numberG * coefficient) / 100;

                    box_setNumberGarbage(box, div * -1);
                }
            }
        }
    }


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

    if (map_getNumberFISE(m) >= fiseGraduate) {
        if (map_getNumberFISA(m) >= fisaGraduate) {
            // Nouveau nombre de fise et fisa
            map_setNumberFISE(m, (fiseGraduate * -1));
            map_setNumberFISA(m, (fisaGraduate * -1));

            // Envoie des ressource à la porte
            Case *c;
            for (int i = 0; i < map_getWidth(m); ++i) {
                for (int j = 0; j < map_getHeight(m); ++j) {
                    c = map_getCase(i, j, m);
                    CaseType type = case_getType(c);
                    if (type == CASE_GATE) {
                        if (case_hasBox(c)) {
                            Box *saveBox = box_create(0, 0);
                            box_addB2toB1(saveBox, case_getBox(c));
                            case_setEmpty(c);

                            case_addBox(c, box_create(0, fiseGraduate + fisaGraduate));
                            map_utils_sendResourcesToGate(m);

                            case_addBox(c, saveBox);
                        } else {
                            case_addBox(c, box_create(0, fiseGraduate + fisaGraduate));
                            map_utils_sendResourcesToGate(m);
                        }
                    }
                }
            }
        } else {
            // TODO VAlentin : Changer avec erreur de pas assez de fisa
            return ERROR_NOT_ENOUGH_DD;
        }
    } else {
        // TODO VAlentin : Changer avec erreur de pas assez de fise
        return ERROR_NOT_ENOUGH_E;
    }

    return NO_ERROR;
}