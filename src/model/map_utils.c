#include <stdio.h>
#include "../../headers/utils/map_utils.h"
#include "../../headers/utils/const.h"
#include "../../headers/utils/utils.h"

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

void map_utils_sendResourcesToGate(Map *m, int resources) {
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

                    case_addBox(c, box_create(0, resources));
                    map_utils_generateGarbage(m);

                    case_addBox(c, saveBox);
                } else {
                    case_addBox(c, box_create(0, resources));
                    map_utils_generateGarbage(m);
                }
            }
        }
    }
}

// Code factorization function for this file
/**
 * This function allows you to check if a machine of a specific type is present in a space
 *
 * @param type of machine
 * @param c c the box to check
 * @return returns boolean if there is a machine of the right type
 */
bool map_utils_caseHasMachineType(MachineStuff type, Case *c) {
    CaseType caseType = case_getType(c);
    if (caseType == CASE_MACHINE) {
        Machine *machine = case_getMachine(c);
        return machine_getType(machine) == type;
    }
    return false;
}

// TODO Valentin : peut être déplacer dans interface qui gères les cardinals ??
// TODO Valentin : Possibilité de rendre générique ??
/**
 * Allows in relation to a cardinal to return the modifications to be made on the coordinates
 *
 * @param cardinal
 * @return Vector2D
 */
Vector2D map_utils_modifyXYWithCardinal(Cardinal cardinal) {
    switch (cardinal) {
        case NORTH:
            return (Vector2D) {.x = 0, .y = -1};
        case EAST:
            return (Vector2D) {.x = 1, .y = 0};
        case SOUTH:
            return (Vector2D) {.x = 0, .y = +1};
        case WEST:
            return (Vector2D) {.x = -1, .y = 0};
        default:
            return (Vector2D) {.x = 0, .y = 0};
    }
}

// TODO Valentin : modifier pour ne plus avoir à passer la box
ErrorCode map_utils_moveBox(Map *m, Case *c, Box *outputBox, Cardinal card) {
    fprintf(stderr, "=> map_utils_moveBox\n");
    fprintf(stderr, "Case x:%d y:%d Card:%d R:%d G:%d\n", case_getX(c), case_getY(c), card,
            box_getNumberResource(outputBox), box_getNumberGarbage(outputBox));
    int x = case_getX(c);
    int y = case_getY(c);
    Vector2D modifier = map_utils_modifyXYWithCardinal(card);
    Case *outputCase = map_getCase(x + modifier.x, y + modifier.y, m);

    if (outputCase != NULL) {
        if (case_getType(outputCase) != CASE_MACHINE) {
            if (case_hasBox(outputCase)) {
                box_addB2toB1(case_getBox(outputCase), outputBox);
                return ERROR; // TODO change Error
            } else {
                case_addBox(outputCase, outputBox);
            }
        } else {
            Machine *outputMachine = case_getMachine(outputCase);
            Cardinal outputCardinal = (card + (NUMBER_CARDINAL / 2)) % NUMBER_CARDINAL;
            if (machine_getDirection(outputMachine, outputCardinal) == DIRECTION_IN) {
                Box *existBox = machine_getBox(outputMachine, card);
                if (existBox != NULL) {
                    box_addB2toB1(existBox, outputBox);
                    return ERROR; // TODO change Error
                } else {
                    machine_addBox(outputMachine, outputCardinal, outputBox);
                }
            } else {
                return ERROR; // TODO change Error
            }
        }
    } else {
        return ERROR_CASE_NOT_FOUND;
    }

    return NO_ERROR;
}

// Required function for endTurn
/**
 * Produce DD and E by fise
 *
 * @param m
 */
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

/**
 * Produce DD or E by fisa
 *
 * @param m
 */
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
    fprintf(stderr, "=> map_utils_moveResources\n");
    int width = map_getWidth(m);
    int height = map_getHeight(m);

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Case *conveyorCase = map_getCase(x, y, m);

            if (map_utils_caseHasMachineType(MS_CONVEYOR_BELT, conveyorCase) ||
                map_utils_caseHasMachineType(MS_CROSS, conveyorCase)) {
                Machine *conveyorMachine = case_getMachine(conveyorCase);

                for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                    if (machine_getDirection(conveyorMachine, card) == DIRECTION_OUT) {
                        Box *conveyorBox = machine_getBox(conveyorMachine, card);
                        if (conveyorBox != NULL) {
                            if (map_utils_moveBox(m, conveyorCase, conveyorBox, card) != NO_ERROR) {
                                free(conveyorBox);
                            }
                        }
                    }
                }
            }
        }
    }

    //map_utils_moveResourcesInMachine(m);
}

void map_utils_generateResources(Map *m) {
    fprintf(stderr, "=> map_utils_generateResources\n");
    int numberTour = 1;

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
                    fprintf(stderr, "Sources généré : \n");
                    case_addBox(c, box_create(generateResource, 0));
                }
            }
        }
    }
}

ErrorCode map_utils_generateGarbage(Map *m) {
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

void map_utils_activateRecyclingCenters(Map *m) {
    MachineStuff machineType = MS_RECYCLING_CENTER;

    Case *c;
    for (int j = 0; j < map_getHeight(m); ++j) {
        for (int i = 0; i < map_getWidth(m); ++i) {
            c = map_getCase(i, j, m);
            if (map_utils_caseHasMachineType(machineType, c)) {
                Machine *machine = case_getMachine(c);

                for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                    if (machine_getDirection(machine, card) == DIRECTION_OUT) {
                        Box *machineBox = machine_getBox(machine, card);
                        int numberGarbage = box_getNumberGarbage(machineBox);
                        int numberResource = numberGarbage / NUMBER_WASTE_TO_PRODUCT_RESOURCE;
                        int rest = numberGarbage % NUMBER_WASTE_TO_PRODUCT_RESOURCE;
                        box_setNumberGarbage(machineBox, rest - numberGarbage);

                        if (numberResource > 0) {
                            Box *outputBox = box_create(numberResource, 0);
                            if (map_utils_moveBox(m, c, outputBox, card) != NO_ERROR) {
                                free(outputBox);
                            }
                        }
                    }
                }
            }
        }
    }

    /* for (int j = 0; j < map_getHeight(m); ++j) {
         for (int i = 0; i < map_getWidth(m); ++i) {
             c = map_getCase(i, j, m);
             if (case_getType(c) == CASE_MACHINE) {
                 Machine *machine = case_getMachine(c);
                 Direction direction;
                 Cardinal out;

                 if (machine_getType(machine) == MS_CROSS) {
                     for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                         direction = machine_getDirection(machine, card);
                         if (direction == DIRECTION_IN) {
                             Box *inBox = machine_getBox(machine, card);
                             if (inBox != NULL) {
                                 Box *outputBox = machine_getBox(machine,
                                                                 (card + (NUMBER_CARDINAL / 2)) % NUMBER_CARDINAL);
                                 if (outputBox == NULL) {
                                     outputBox = box_create(0, 0);
                                 }
                                 box_addB2toB1(outputBox, inBox);
                                 machine_destroyBox(machine, card);
                             }
                         }
                     }
                 } else {
                     Box *cumulBox = box_create(0, 0);
                     for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                         direction = machine_getDirection(machine, card);
                         if (direction == DIRECTION_OUT) {
                             out = card;
                         } else if (direction == DIRECTION_IN) {
                             Box *tmp = machine_getBox(machine, card);
                             if (tmp != NULL) {
                                 box_addB2toB1(cumulBox, tmp);
                                 machine_destroyBox(machine, card);
                             }
                         }
                     }

                     Box *tmp = machine_getBox(machine, out);
                     if (tmp != NULL) {
                         box_addB2toB1(tmp, cumulBox);
                         free(cumulBox);
                     } else {
                         machine_addBox(machine, out, cumulBox);
                     }
                 }
             }
         }
     }*/
}

void map_utils_activateCollectors(Map *m) {
    fprintf(stderr, "=> map_utils_activateCollectors\n");
    MachineStuff machineType = MS_COLLECTOR;
    const MachineInfo *machineInfo = machineInfo_getMachineStuff(machineType);
    const Effect *effect = machineInfo_getEffects(machineInfo);
    int BaseCapacity = machineInfo_getCapacity(machineInfo);
    int modifiers = effect_getModifierCapacity(effect);

    Case *collectorCase;
    for (int j = 0; j < map_getHeight(m); ++j) {
        for (int i = 0; i < map_getWidth(m); ++i) {
            collectorCase = map_getCase(i, j, m);
            if (map_utils_caseHasMachineType(machineType, collectorCase)) {
                Machine *collectorMachine = case_getMachine(collectorCase);

                int capacity = BaseCapacity + modifiers * (machine_getLevel(collectorMachine) - 1);
                int x = case_getX(collectorCase);
                int y = case_getY(collectorCase);
                Case *sourceCase;
                Box *sourceBox;
                Direction dir;
                Cardinal out;

                List *listSource = list_createEmpty();
                for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                    dir = machine_getDirection(collectorMachine, card);
                    if (dir == DIRECTION_NONE) {
                        Vector2D modifier = map_utils_modifyXYWithCardinal(card);
                        sourceCase = map_getCase(x + modifier.x, y + modifier.y, m);
                        if (sourceCase != NULL) {
                            if (case_getType(sourceCase) == CASE_SOURCE && case_hasBox(sourceCase)) {
                                sourceBox = case_getBox(sourceCase);
                                if (box_getNumberResource(sourceBox) > 0 || box_getNumberGarbage(sourceBox) > 0) {
                                    Element elt = {
                                            .type = OBJECT,
                                            .content.object = (void *) sourceCase
                                    };
                                    list_addElement(listSource, elt);
                                }
                            }
                        }
                    } else if (dir == DIRECTION_OUT) {
                        out = card;
                    }
                }

                int choiceSource;
                Box *cumulative = box_create(0, 0);
                //fprintf(stderr, "liste source %d\n", list_getSize(listSource));
                while (capacity > 0 && list_getSize(listSource) > 0) {
                    choiceSource = rand() % list_getSize(listSource); // NOLINT(cert-msc50-cpp)

                    Element *elt = list_getByIndex(listSource, choiceSource);
                    sourceBox = case_getBox((Case *) elt->content.object);
                    //fprintf(stderr, "Source x:%d y:%d => Resources %d\n", case_getX((Case *) elt->content.object),
                    //case_getY((Case *) elt->content.object), box_getNumberResource(sourceBox));
                    box_setNumberResource(cumulative, 1);
                    box_setNumberResource(sourceBox, -1);

                    if (box_getNumberResource(sourceBox) <= 0) {
                        list_removeByIndex(listSource, choiceSource);
                    }

                    capacity--;
                }
                list_destroy(listSource);

                fprintf(stderr, "Cumulative => Resources %d\n", box_getNumberResource(cumulative));
                if (box_getNumberResource(cumulative) > 0) {
                    map_utils_moveBox(m, collectorCase, cumulative, out);
                } else {
                    free(cumulative);
                }
            }
        }
    }
}

void map_utils_resetResourcesGarbage(Map *m) {
    fprintf(stderr, "=> map_utils_resetResourcesGarbage\n");
    Case *c, *gate = NULL;
    Box *box = box_create(0, 0);
    Box *tmpBox;

    for (int i = 0; i < map_getWidth(m); ++i) {
        for (int j = 0; j < map_getHeight(m); ++j) {
            c = map_getCase(i, j, m);
            CaseType type = case_getType(c);
            //fprintf(stderr, "Case Type x:%d y:%d => type %d\n", i, j, type);
            if (type == CASE_GATE) {
                gate = c;
            } else if (case_hasBox(c)) {
                fprintf(stderr, "Case Reset x:%d y:%d\n", i, j);
                tmpBox = case_getBox(c);
                box_setNumberGarbage(box, box_getNumberGarbage(tmpBox));
                fprintf(stderr, " => Resources %d / Garbage : %d\n", box_getNumberResource(tmpBox),
                        box_getNumberGarbage(tmpBox));

                case_deleteBox(c);
            }
        }
    }

    if (gate != NULL) {
        if (case_hasBox(gate)) {
            box_addB2toB1(case_getBox(gate), box);
            free(box);
        } else {
            case_addBox(gate, box);
        }
    } else {
        fprintf(stderr, "Gate non trouvé !!\n");
    }
}

void map_utils_moveResourcesInMachine(Map *m) {
    fprintf(stderr, "=> map_utils_moveResourcesInMachine\n");
    Case *c;
    Direction direction;

    for (int j = 0; j < map_getHeight(m); ++j) {
        for (int i = 0; i < map_getWidth(m); ++i) {
            c = map_getCase(i, j, m);

            if (case_getType(c) == CASE_MACHINE) {
                Machine *machine = case_getMachine(c);

                if (machine_getType(machine) == MS_CROSS) {
                    for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                        direction = machine_getDirection(machine, card);
                        if (direction == DIRECTION_IN) {
                            Box *inBox = machine_getBox(machine, card);
                            if (inBox != NULL) {
                                Box *outputBox = machine_getBox(machine,
                                                                (card + (NUMBER_CARDINAL / 2)) % NUMBER_CARDINAL);
                                if (outputBox == NULL) {
                                    outputBox = box_create(0, 0);
                                }
                                box_addB2toB1(outputBox, inBox);
                                machine_destroyBox(machine, card);
                            }
                        }
                    }
                } else {
                    Box *cumulBox = box_create(0, 0);
                    Cardinal out;
                    for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                        direction = machine_getDirection(machine, card);
                        if (direction == DIRECTION_OUT) {
                            out = card;
                        } else if (direction == DIRECTION_IN) {
                            Box *tmp = machine_getBox(machine, card);
                            if (tmp != NULL) {
                                box_addB2toB1(cumulBox, tmp);
                                machine_destroyBox(machine, card);
                            }
                        }
                    }

                    fprintf(stderr, "Case x:%d y:%d R:%d G:%d\n", i, j, box_getNumberResource(cumulBox),
                            box_getNumberGarbage(cumulBox));
                    Box *tmp = machine_getBox(machine, out);
                    if (tmp != NULL) {
                        box_addB2toB1(tmp, cumulBox);
                        free(cumulBox);
                    } else {
                        machine_addBox(machine, out, cumulBox);
                    }
                }
            }
        }
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
    int numberG, div;
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
                for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                    box = machine_getBox(machine, card);
                    if (box != NULL) {
                        numberG = box_getNumberGarbage(box);

                        div = (numberG * coefficient) / 100;

                        box_setNumberGarbage(box, div * -1);
                    }
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
            map_utils_sendResourcesToGate(m, fiseGraduate + fisaGraduate);
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