#include <stdio.h>
#include <time.h>
#include "../../headers/utils/map_utils.h"

ErrorCode map_utils_tryBuy(Map *m, int costE, int costDD) {
    // Check that the player has enough E
    if (map_getNumberE(m) >= costE) {
        // Check that the player has enough DD
        if (map_getNumberDD(m) >= costDD) {
            // Debits the player
            map_setNumberE(m, costE * -1);
            map_setNumberDD(m, costDD * -1);

            // Informs that everything went well
            return NO_ERROR;
        } else {
            // Informs that it lacks DD
            return ERROR_NOT_ENOUGH_DD;
        }
    } else {
        // Informs that it lacks E
        return ERROR_NOT_ENOUGH_E;
    }
}

void map_utils_checkModificationStaff(Mode mode, Target target, Map *m, int *numberE, int *numberDD) {
    // Checking that there is a staff with this mod and this target
    const Staff *staff = staffInfo_getByModeAndType(mode, target);
    if (staff != NULL) {
        // Retrieving staff information
        int idStaff = staff_getStaffID(staff);
        Dictionary *dictionary = map_getStaffDictionary(m);
        int numberStaff = staff_getNumberStaffByID(dictionary, idStaff);
        const Effect *effect = staff_getStaffEffect(staff);

        // Verification that the player has this staff and that the staff has effects
        if (numberStaff > 0 && effect != NULL) {
            // apply modification
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
    // Door search
    for (int i = 0; i < map_getWidth(m); ++i) {
        for (int j = 0; j < map_getHeight(m); ++j) {
            c = map_getCase(i, j, m);
            CaseType type = case_getType(c);
            // Checking the presence of the door
            if (type == CASE_GATE) {
                // Add the number of resources to the door
                if (case_hasBox(c)) {
                    box_setNumberResource(case_getBox(c), resources);
                } else {
                    case_addBox(c, box_create(resources, 0));
                }
                // Pass resources through the Gate
                map_utils_generateGarbage(m);
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
    // Case type recovery
    CaseType caseType = case_getType(c);
    // Checking the presence of a machine
    if (caseType == CASE_MACHINE) {
        // Machine type recovery
        Machine *machine = case_getMachine(c);
        // Returns the result of the comparison between the type of the machine and the desired type
        return machine_getType(machine) == type;
    }
    // Returns false if there is no machine
    return false;
}

/**
 * This function allows you to move a box on an adjacent box in a certain direction
 *
 * @param m Map with current game information
 * @param c Starting point
 * @param outputBox Box to move
 * @param card Direction in which to move the box
 * @return An error to warn of a possible error
 */
ErrorCode map_utils_moveBox(Map *m, Case *c, Box *outputBox, Cardinal card) {
    // Retrieving the coordinates of the box
    int x = case_getX(c);
    int y = case_getY(c);

    // Calculation of changes in coordinates with respect to the new cardinal
    Vector2D modifier = cardinal_modifyXYWithCardinal(card);
    Case *outputCase = map_getCase(x + modifier.x, y + modifier.y, m);
    Box *inputBox;

    // Verification of the existence of the box
    if (outputCase != NULL) {
        // Checking the box type
        if (case_getType(outputCase) != CASE_MACHINE) {
            // If case is not a machine
            // Checking the presence of a box
            if (case_hasBox(outputCase)) {
                // If yes add to the box already present the data of the new box
                inputBox = case_getBox(outputCase);
            } else {
                // If not add the box to the machine
                inputBox = box_create(0, 0);
                case_addBox(outputCase, inputBox);
            }
            box_addB2toB1(inputBox, outputBox);

            return ERROR;
        } else {
            // Otherwise recover the machine
            Machine *outputMachine = case_getMachine(outputCase);

            // Capacity recovery and calculation
            const MachineInfo *machineInfo = machineInfo_getMachineStuff(machine_getType(outputMachine));
            int BaseCapacity = machineInfo_getCapacity(machineInfo);
            if (machineInfo_getCanUpgrade(machineInfo)) {
                const Effect *effect = machineInfo_getEffects(machineInfo);
                int modifiers = effect_getModifierCapacity(effect);
                BaseCapacity = BaseCapacity + modifiers * (machine_getLevel(outputMachine) - 1);
            }

            // Calculates the cardinal opposite to the output
            Cardinal outputCardinal = (card + (NUMBER_CARDINAL / 2)) % NUMBER_CARDINAL;

            // Checking that you are on the machine's entrance
            if (machine_getDirection(outputMachine, outputCardinal) == DIRECTION_IN) {
                // Verification of the existence of a box
                Box *existBox = machine_getBox(outputMachine, outputCardinal);
                if (existBox == NULL) {
                    // Otherwise add the box to the box
                    existBox = box_create(0, 0);
                    machine_addBox(outputMachine, outputCardinal, existBox);
                }
                box_addB2toB1(existBox, outputBox);

                // If the capacity is exceeded, send the waste to the door and destroy the resources
                if (case_getNumberGarbageByCase(outputCase) > BaseCapacity) {
                    map_utils_sendResourcesToGate(m, (BaseCapacity - case_getNumberGarbageByCase(outputCase)) * -1);
                    box_setNumberGarbage(existBox, BaseCapacity - case_getNumberGarbageByCase(outputCase));
                }
                if (case_getNumberResourcesByCase(outputCase) > BaseCapacity) {
                    box_setNumberResource(existBox, BaseCapacity - case_getNumberResourcesByCase(outputCase));
                }

                return ERROR;
            } else {
                return ERROR;
            }
        }
    } else {
        return ERROR_CASE_NOT_FOUND;
    }
}

// Required function for endTurn
void map_utils_productionFise(Map *m) {
    // Initialization of basic production of Fises
    int productionE = PRODUCTION_FISE_E;
    int productionDD = PRODUCTION_FISE_DD;

    // Retrieving the number of Fises owned
    int numberFise = map_getNumberFISE(m);

    // Recovery of possible modifications on the production of Fises
    int modifE = 0;
    int modifDD = 0;
    // Take into account the staff effects
    map_utils_checkModificationStaff(PRODUCTION, (Target) {.other = SUB_FISE}, m, &modifE, &modifDD);

    // Adds the production of fises to the player
    map_setNumberE(m, (productionE + modifE) * numberFise);
    map_setNumberDD(m, (productionDD + modifDD) * numberFise);
}

void map_utils_productionFisa(Map *m) {
    // Checking that it is the turn to produce
    if (map_getNumberTurn(m) % NB_TURN_FISA == 0) {
        // Initialization of basic production of Fisas
        int productionE = PRODUCTION_FISA_E;
        int productionDD = PRODUCTION_FISA_DD;

        // Retrieving the number of Fisas owned
        int numberFisa = map_getNumberFISA(m);

        // Recovery of possible modifications on the production of Fisas
        int modifE = 0;
        int modifDD = 0;
        // Take into account the staff effects
        map_utils_checkModificationStaff(PRODUCTION, (Target) {.other = SUB_FISA}, m, &modifE, &modifDD);

        // Check the resources to be produced and credit the player
        if (map_getProductionFISA(m) == E_VALUE) {
            map_setNumberE(m, (productionE + modifE) * numberFisa);
        } else {
            map_setNumberDD(m, (productionDD + modifDD) * numberFisa);
        }
    }
}

void map_utils_moveResources(Map *m) {
    // Retrieving the tray size
    int width = map_getWidth(m);
    int height = map_getHeight(m);

    // Course of the game board
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            // Case recovery
            Case *conveyorCase = map_getCase(x, y, m);

            // If there is a carpet
            if (map_utils_caseHasMachineType(MS_CONVEYOR_BELT, conveyorCase) ||
                map_utils_caseHasMachineType(MS_CROSS, conveyorCase)) {

                // Machine recovery
                Machine *conveyorMachine = case_getMachine(conveyorCase);

                // Course of all faces
                for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                    // Look for my exit face
                    if (machine_getDirection(conveyorMachine, card) == DIRECTION_OUT) {
                        // Collect the box
                        Box *conveyorBox = machine_getBox(conveyorMachine, card);
                        if (conveyorBox != NULL) {
                            // If there is a box, move it to the next box
                            map_utils_moveBox(m, conveyorCase, conveyorBox, card);
                            machine_destroyBox(conveyorMachine, card);
                        }
                    }
                }
            }
        }
    }
}

void map_utils_generateResources(Map *m) {
    // Initialization of the number of turn before production
    int numberTour = NB_TURN_PRODUCTION_SOURCE;

    // Application of any staff modification
    const Staff *staff = staffInfo_getByModeAndType(PRODUCTION, (Target) {.other = SOURCE});
    const Dictionary *dicoStaff = map_getStaffDictionary(m);
    const Effect *effect = staff_getStaffEffect(staff);
    numberTour = numberTour + (effect_getTurnProduction(effect) *
                               (staff_getNumberStaffByID(dicoStaff, staff_getStaffID(staff))));

    // Checking the validity of modifications
    if (numberTour < effect_getMinTurnProduction(effect)) {
        numberTour = effect_getMinTurnProduction(effect);
    }

    // Lap check
    if (map_getNumberTurn(m) % numberTour == 0) {
        Case *c;
        int generateResource = NB_RESOURCE_PRODUCT_BY_SOURCE;

        // Browse the cells to find the sources
        for (int i = 0; i < map_getWidth(m); ++i) {
            for (int j = 0; j < map_getHeight(m); ++j) {
                c = map_getCase(i, j, m);

                // Checking for the presence of a source
                if (case_getType(c) == CASE_SOURCE) {
                    // Add a box with the number of resources generated
                    case_addBox(c, box_create(generateResource, 0));
                }
            }
        }
    }
}

void map_utils_generateGarbage(Map *m) {
    Case *c;
    CaseType type;

    // Recovery of the dictionary with the different personnel and their number
    const Dictionary *dicoStaff = map_getStaffDictionary(m);

    // Recovery of the multiplier of the number of waste
    const Staff *staffIn = staffInfo_getByModeAndType(SEND_DOOR, (Target) {.other = NONE});
    const Effect *effectIn = staff_getStaffEffect(staffIn);
    int modifierRes =
            effect_getModifierRes(effectIn) * staff_getNumberStaffByID(dicoStaff, staff_getStaffID(staffIn));

    // Checking the minimum for the multiplier
    if (modifierRes <= 0) modifierRes = 1;

    // Recovery of the multiplier of the number of waste
    const Staff *staffOut = staffInfo_getByModeAndType(DOOR_OUT, (Target) {.other = DESTROY_GARBAGE});
    const Effect *effectOut = staff_getStaffEffect(staffOut);
    int modifierThomas = effect_getModifierRes(effectOut);
    int numberThomas = staff_getNumberStaffByID(dicoStaff, staff_getStaffID(staffOut));

    // Browse the map until you find the door
    for (int i = 0; i < map_getWidth(m); ++i) {
        for (int j = 0; j < map_getHeight(m); ++j) {
            c = map_getCase(i, j, m);
            type = case_getType(c);
            // Checking the presence of the door
            if (type == CASE_GATE && case_hasBox(c)) {
                // Recovery of the box
                Box *box = case_getBox(c);
                // Retrieving the number of resources
                int numberR = box_getNumberResource(box);
                // Transformation of resources into waste
                box_setNumberResource(box, numberR * -1);

                // Score increase
                map_setNumberScore(m, numberR * modifierRes);

                // Taking into account Gaël Thomas
                for (int k = 0; k < numberR; ++k) {
                    for (int l = 0; l < numberThomas; ++l) {
                        // Roll the dice
                        int deVal = rand() % modifierThomas; // NOLINT(cert-msc50-cpp)

                        // Checking the die value
                        if (deVal == 0) {
                            numberR--;
                            break;
                        }
                    }
                }

                // Creation of waste
                box_setNumberGarbage(box, numberR);
            }
        }
    }
}

void map_utils_activateRecyclingCenters(Map *m) {
    MachineStuff machineType = MS_RECYCLING_CENTER;
    int numberWasteToResource = NUMBER_WASTE_TO_PRODUCT_RESOURCE;

    // Browse the map to find recycling centers
    Case *c;
    for (int j = 0; j < map_getHeight(m); ++j) {
        for (int i = 0; i < map_getWidth(m); ++i) {
            c = map_getCase(i, j, m);
            // Verification of the presence of recycling centers
            if (map_utils_caseHasMachineType(machineType, c)) {
                Machine *machine = case_getMachine(c);

                // Finding the exit where the resources are present
                for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                    // Checking the output
                    if (machine_getDirection(machine, card) == DIRECTION_OUT) {
                        Box *machineBox = machine_getBox(machine, card);

                        // Checking the presence of a box
                        if (machineBox != NULL) {
                            // Calculates the number of resources generated
                            int numberGarbage = box_getNumberGarbage(machineBox);
                            int numberResource = numberGarbage / numberWasteToResource;
                            int rest = numberGarbage % numberWasteToResource;

                            // Verifying that resources are generated
                            if (numberResource > 0) {
                                // Transformation of waste into resources
                                box_setNumberGarbage(machineBox, rest - numberGarbage);
                                Box *outputBox = box_create(numberResource, 0);

                                // Sends resources on the output
                                map_utils_moveBox(m, c, outputBox, card);
                                box_destroy(outputBox);
                            }
                        }

                        break;
                    }
                }
            }
        }
    }
}

void map_utils_activateCollectors(Map *m) {
    MachineStuff machineType = MS_COLLECTOR;

    // Retrieving basic information from collectors
    const MachineInfo *machineInfo = machineInfo_getMachineStuff(machineType);
    const Effect *effect = machineInfo_getEffects(machineInfo);
    int BaseCapacity = machineInfo_getCapacity(machineInfo);
    int modifiers = effect_getModifierCapacity(effect);

    // Browse the boxes to find the collectors
    Case *collectorCase;
    for (int j = 0; j < map_getHeight(m); ++j) {
        for (int i = 0; i < map_getWidth(m); ++i) {
            // Case recovery
            collectorCase = map_getCase(i, j, m);
            // Checking for the presence of a machine
            if (map_utils_caseHasMachineType(machineType, collectorCase)) {
                Machine *collectorMachine = case_getMachine(collectorCase);

                // Calculates capacity based on level
                int capacity = BaseCapacity + modifiers * (machine_getLevel(collectorMachine) - 1);
                int x = case_getX(collectorCase);
                int y = case_getY(collectorCase);

                Case *sourceCase;
                Box *sourceBox;
                Direction dir;
                Cardinal out;

                // Browse the different facades to find adjacent sources
                List *listSource = list_createEmpty();
                for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                    dir = machine_getDirection(collectorMachine, card);
                    // If the direction is NONE
                    if (dir == DIRECTION_NONE) {
                        // Calculates coordinates of the adjacent cell
                        Vector2D modifier = cardinal_modifyXYWithCardinal(card);
                        sourceCase = map_getCase(x + modifier.x, y + modifier.y, m);
                        // Verification of the existence of the adjacent box
                        if (sourceCase != NULL) {
                            // Then check if there is an adjacent source with a box
                            CaseType caseType = case_getType(sourceCase);
                            if ((caseType == CASE_SOURCE || caseType == CASE_GATE) && case_hasBox(sourceCase)) {
                                sourceBox = case_getBox(sourceCase);

                                // Checking the presence of resource in the box
                                if (box_getNumberResource(sourceBox) > 0 || box_getNumberGarbage(sourceBox) > 0) {
                                    // Adding the box to the source list
                                    Element elt = {
                                            .type = OBJECT,
                                            .content.object = (void *) sourceCase
                                    };
                                    list_addElement(listSource, elt);
                                }
                            }
                        }
                    } else if (dir == DIRECTION_OUT) {
                        // If OUT remember the exit
                        // Assumption that there is always an OUT
                        out = card;
                    }
                }

                // Creation of a temporary box to store the number of recovered resources
                int choiceSource;
                Box *cumulative = box_create(0, 0);
                // As long as there is still the possibility of recovering resources
                // And that there are still resources to recover
                while (capacity > 0 && list_getSize(listSource) > 0) {
                    // Choose a source randomly
                    choiceSource = rand() % list_getSize(listSource); // NOLINT(cert-msc50-cpp)

                    // Retrieve the box from the source
                    Element *elt = list_getByIndex(listSource, choiceSource);
                    sourceBox = case_getBox((Case *) elt->content.object);

                    // Take a resource from the source
                    if (case_getType((Case *) elt->content.object) == CASE_SOURCE) {
                        box_setNumberResource(cumulative, 1);
                        box_setNumberResource(sourceBox, -1);
                    } else {
                        box_setNumberGarbage(cumulative, 1);
                        box_setNumberGarbage(sourceBox, -1);
                    }

                    // Remove the source from the list if it is empty
                    if (box_getNumberResource(sourceBox) <= 0 && box_getNumberGarbage(sourceBox) <= 0) {
                        list_removeByIndex(&listSource, choiceSource);
                    }

                    // Decrease the capacity of the collector
                    capacity--;
                }
                // Destroy the source list
                list_destroy(listSource);

                // If there are resources that have been recovered then send the box to
                // the outlet of the collector
                if (box_getNumberResource(cumulative) > 0 || box_getNumberGarbage(cumulative) > 0) {
                    map_utils_moveBox(m, collectorCase, cumulative, out);
                }
                box_destroy(cumulative);
            }
        }
    }
}

void map_utils_resetResourcesGarbage(Map *m) {
    Case *c, *gate = NULL;
    Box *box = box_create(0, 0);
    Box *tmpBox;

    // Browse the map to find the boxes
    for (int i = 0; i < map_getWidth(m); ++i) {
        for (int j = 0; j < map_getHeight(m); ++j) {
            c = map_getCase(i, j, m);
            CaseType type = case_getType(c);

            // Checking the presence of the door
            if (type == CASE_GATE) {
                gate = c;
            } else if (case_hasBox(c)) { // Verification of the presence of a box on an empty box
                // Recovery of the box
                tmpBox = case_getBox(c);
                // Adding your waste to the temporary box
                box_setNumberGarbage(box, box_getNumberGarbage(tmpBox));
                // Destruction of the box with uncollected resources
                case_deleteBox(c);
            }
        }
    }

    // Add recovered waste to the door
    if (gate != NULL) {
        if (case_hasBox(gate)) {
            box_addB2toB1(case_getBox(gate), box);
            box_destroy(box);
        } else {
            case_addBox(gate, box);
        }
    }
}

void map_utils_moveResourcesInMachine(Map *m) {
    Case *c;
    Direction direction;

    // Browse the map until you find machines
    for (int j = 0; j < map_getHeight(m); ++j) {
        for (int i = 0; i < map_getWidth(m); ++i) {
            // Case recovery
            c = map_getCase(i, j, m);
            // Checking for the presence of a machine
            if (case_getType(c) == CASE_MACHINE) {
                // Machine recovery
                Machine *machine = case_getMachine(c);

                // Checking whether the machine is a cross or not
                if (machine_getType(machine) == MS_CROSS) {
                    // Course from all sides
                    for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                        direction = machine_getDirection(machine, card);
                        // Checking the direction of the facade
                        if (direction == DIRECTION_IN) {
                            // Otherwise check for the presence of a box
                            Box *inBox = machine_getBox(machine, card);
                            if (inBox != NULL) {
                                // Calculation of the opposite facade
                                Cardinal out = (card + (NUMBER_CARDINAL / 2)) % NUMBER_CARDINAL;
                                // Recovery of the box
                                Box *outputBox = machine_getBox(machine, out);
                                if (outputBox == NULL) {
                                    // Creation of a box if there was none
                                    outputBox = box_create(0, 0);
                                    machine_addBox(machine, out, outputBox);
                                }
                                // Add resources from the IN box to the OUT box
                                box_addB2toB1(outputBox, inBox);
                                // Destroy IN box
                                machine_destroyBox(machine, card);
                            }
                        }
                    }
                } else {
                    // Creation of a temporary box to store all Resources / Garbage
                    Box *cumulBox = box_create(0, 0);
                    Cardinal out = NORTH;

                    // Course from all sides
                    for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                        // Management check
                        direction = machine_getDirection(machine, card);
                        if (direction == DIRECTION_OUT) {
                            // If OUT saves the face
                            out = card;
                        } else if (direction == DIRECTION_IN) {
                            // Otherwise check for the presence of a box
                            Box *tmp = machine_getBox(machine, card);
                            if (tmp != NULL) {
                                // If yes add the values to the temporary box
                                box_addB2toB1(cumulBox, tmp);
                                // Delete the box
                                machine_destroyBox(machine, card);
                            }
                        }
                    }

                    // Checking for the presence of resources
                    if (box_getNumberGarbage(cumulBox) > 0 || box_getNumberResource(cumulBox) > 0) {
                        // Checking the presence of a Box on the output
                        Box *tmp = machine_getBox(machine, out);
                        if (tmp != NULL) {
                            // If yes add the data
                            box_addB2toB1(tmp, cumulBox);
                            box_destroy(cumulBox);
                        } else {
                            // Addition of the box to the exit face
                            machine_addBox(machine, out, cumulBox);
                        }
                    } else {
                        // Destruction of the box
                        box_destroy(cumulBox);
                    }
                }
            }
        }
    }

}

// Specific Staff function
ErrorCode staff_actionAnneLaureLigozat(Map *m, int idStaff) {
    // Staff recovery and its effect
    const Staff *staff = staff_getStaffByID(idStaff);
    const Effect *effect = staff_getStaffEffect(staff);
    int coefficient = effect_getModifierRes(effect);

    // Browse the map to remove half of the garbage
    Case *c;
    int numberG, div;
    for (int i = 0; i < map_getWidth(m); ++i) {
        for (int j = 0; j < map_getHeight(m); ++j) {
            // Case recovery
            Box *box;
            c = map_getCase(i, j, m);
            CaseType type = case_getType(c);

            // Checking the presence of a box
            if (case_hasBox(c)) {
                // Recovery of the box
                box = case_getBox(c);
                numberG = box_getNumberGarbage(box);

                // Application of the coefficient
                div = (numberG * coefficient) / 100;

                box_setNumberGarbage(box, div * -1);
            } else if (type == CASE_MACHINE) { // Checking for the presence of a machine
                // Machine recovery
                Machine *machine = case_getMachine(c);

                // Checking for the presence of boxes on the Cardinals
                for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                    box = machine_getBox(machine, card);
                    if (box != NULL) {
                        // Recovery of the box
                        numberG = box_getNumberGarbage(box);

                        // Application of the coefficient
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
    // Staff recovery and its effect
    const Staff *staff = staff_getStaffByID(idStaff);
    const Effect *effect = staff_getStaffEffect(staff);

    // Recovering the number of Fise and Fisa
    int modifierFise = effect_getModifierFISE(effect);
    int modifierFisa = effect_getModifierFISA(effect);

    // Addition of Fise and Fisa
    map_setNumberFISE(m, modifierFise);
    map_setNumberFISA(m, modifierFisa);

    return NO_ERROR;
}

ErrorCode staff_actionLaurentPrevel(Map *m, int idStaff) {
    // Staff recovery and its effect
    const Staff *staff = staff_getStaffByID(idStaff);
    const Effect *effect = staff_getStaffEffect(staff);
    int coefficient = effect_getModifierRes(effect);

    // Retrieving the number of Fise and Fisa
    int numberFise = map_getNumberFISE(m);
    int numberFisa = map_getNumberFISA(m);

    // Calculate the number of graduates
    int fiseGraduate = numberFise * coefficient;
    int fisaGraduate = numberFisa * coefficient;

    // Check that there are enough graduates
    if (map_getNumberFISE(m) >= fiseGraduate) {
        if (map_getNumberFISA(m) >= fisaGraduate) {
            // New number of Fise and Fisa
            map_setNumberFISE(m, (fiseGraduate * -1));
            map_setNumberFISA(m, (fisaGraduate * -1));

            // Send resources to the gate
            map_utils_sendResourcesToGate(m, fiseGraduate + fisaGraduate);
        } else {
            return ERROR_NOT_ENOUGH_DD;
        }
    } else {
        return ERROR_NOT_ENOUGH_E;
    }

    return NO_ERROR;
}