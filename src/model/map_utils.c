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

    // Récupération des coordonnées de la case
    int x = case_getX(c);
    int y = case_getY(c);

    // Calcul des modifications des coordonnées par rapport au cardinal de la nouvelle
    Vector2D modifier = map_utils_modifyXYWithCardinal(card);
    Case *outputCase = map_getCase(x + modifier.x, y + modifier.y, m);
    Box* inputBox;

    // Vérification de léxistence de la case
    if (outputCase != NULL) {
        // Vérification du type de la case
        if (case_getType(outputCase) != CASE_MACHINE) {
            fprintf(stderr, "   => Case non machine\n");
            // Si case n'est pas une machine
            // Vérification de la présence d'une box
            if (case_hasBox(outputCase)) {
                fprintf(stderr, "   => Case avec Box\n");
                // Si oui ajouter à la box déjà présente les données de la nouvelle box
                inputBox = case_getBox(outputCase);
            } else {
                fprintf(stderr, "   => Case sans Box\n");
                // Si non ajouter la box à la machine
                inputBox = box_create(0,0);
                case_addBox(outputCase, inputBox);
            }
            box_addB2toB1(inputBox, outputBox);

            return ERROR;
        } else {
            fprintf(stderr, "   => Case machine\n");
            // Sinon récupérer la machine
            Machine *outputMachine = case_getMachine(outputCase);

            // Calcule du cardinal opposé à la sortie
            Cardinal outputCardinal = (card + (NUMBER_CARDINAL / 2)) % NUMBER_CARDINAL;

            // Vérification que l'on est bien sur l'ntré de la machine
            if (machine_getDirection(outputMachine, outputCardinal) == DIRECTION_IN) {
                fprintf(stderr, "   => Case In\n");
                // Verification de l'existence d'une box
                Box *existBox = machine_getBox(outputMachine, outputCardinal);
                if (existBox == NULL) {
                    // Sinon ajouter la box à la case
                    existBox = box_create(0,0);
                    machine_addBox(outputMachine, outputCardinal, existBox);
                }
                box_addB2toB1(existBox, outputBox);

                return ERROR;
            } else {
                return ERROR; // TODO change Error
            }
        }
    } else {
        return ERROR_CASE_NOT_FOUND;
    }
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

    // Parcours du plateau de jeu
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            // Recupération de la case
            Case *conveyorCase = map_getCase(x, y, m);

            // Si il y a un tapis
            if (map_utils_caseHasMachineType(MS_CONVEYOR_BELT, conveyorCase) ||
                map_utils_caseHasMachineType(MS_CROSS, conveyorCase)) {

                // Récupération de la machine
                Machine *conveyorMachine = case_getMachine(conveyorCase);

                // Parcours de toutes les faces
                for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                    // Chercher ma face de sortie
                    if (machine_getDirection(conveyorMachine, card) == DIRECTION_OUT) {
                        // Récupérer la box
                        Box *conveyorBox = machine_getBox(conveyorMachine, card);
                        if (conveyorBox != NULL) {
                            // Si il y a une box la déplacer sur la case suivante
                            if (map_utils_moveBox(m, conveyorCase, conveyorBox, card) != NO_ERROR) {
                                machine_destroyBox(conveyorMachine, card);
                            }
                        }
                    }
                }
            }
        }
    }

    map_utils_moveResourcesInMachine(m);
}

void map_utils_generateResources(Map *m) {
    fprintf(stderr, "=> map_utils_generateResources\n");
    int numberTour = 1;

    // TODO Valentin : attendre
    //map_checkModifyCost(PRODUCTION, (Target) {.other = SUB_FISA}, m, &numberTour, NULL);

    // Vérification du tours
    if (map_getNumberTurn(m) % numberTour == 0) {
        Case *c;
        int generateResource = NB_RESOURCE_PRODUCT_BY_SOURCE;

        // Verifier staff

        // Parcours des case pour trouver les source
        for (int i = 0; i < map_getWidth(m); ++i) {
            for (int j = 0; j < map_getHeight(m); ++j) {
                c = map_getCase(i, j, m);
                if (case_getType(c) == CASE_SOURCE) { // Si source alors
                    fprintf(stderr, "Sources généré : \n");
                    // Ajouter une box avec le nombre de ressources généré
                    case_addBox(c, box_create(generateResource, 0));
                }
            }
        }
    }
}

ErrorCode map_utils_generateGarbage(Map *m) {
    Case *c;
    CaseType type;

    //Parcours des case jusqu'à trouver la porte
    for (int i = 0; i < map_getWidth(m); ++i) {
        for (int j = 0; j < map_getHeight(m); ++j) {
            c = map_getCase(i, j, m);
            type = case_getType(c);
            if (type == CASE_GATE && case_hasBox(c)) { // Si porte avec box alors
                // Récupération du nombre de la box
                Box *box = case_getBox(c);
                // Récupération du nombre de resdources
                int numberR = box_getNumberResource(box);
                // Transformation des ressources en déchets
                box_setNumberGarbage(box, numberR);
                box_setNumberResource(box, numberR * -1);

                // TODO Valentin : Gestion staff

                // augmentation du score
                map_setNumberScore(m, numberR);
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

    // Récupération des information de base des collecteur
    const MachineInfo *machineInfo = machineInfo_getMachineStuff(machineType);
    const Effect *effect = machineInfo_getEffects(machineInfo);
    int BaseCapacity = machineInfo_getCapacity(machineInfo);
    int modifiers = effect_getModifierCapacity(effect);

    // Parcours des cases pour trouver les collecteurs
    Case *collectorCase;
    for (int j = 0; j < map_getHeight(m); ++j) {
        for (int i = 0; i < map_getWidth(m); ++i) {
            // Récupération de la case
            collectorCase = map_getCase(i, j, m);
            if (map_utils_caseHasMachineType(machineType, collectorCase)) { // Si il y a une machine sur la case Alors
                Machine *collectorMachine = case_getMachine(collectorCase);

                // Calcule de la capacité en fonction du niveau
                int capacity = BaseCapacity + modifiers * (machine_getLevel(collectorMachine) - 1);
                int x = case_getX(collectorCase);
                int y = case_getY(collectorCase);

                Case *sourceCase;
                Box *sourceBox;
                Direction dir;
                Cardinal out;

                // Parcours des diférentes facade afin de trouver des source adjacente
                List *listSource = list_createEmpty();
                for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                    dir = machine_getDirection(collectorMachine, card);
                    // Si la direction est NONE
                    if (dir == DIRECTION_NONE) {
                        // Calcule des coordonnées de la case adjacente
                        Vector2D modifier = map_utils_modifyXYWithCardinal(card);
                        sourceCase = map_getCase(x + modifier.x, y + modifier.y, m);
                        // Vérifiacation de l'exitence de la case adjacente
                        if (sourceCase != NULL) {
                            // alors vérifier si il y a une source adjacent avec une box
                            if (case_getType(sourceCase) == CASE_SOURCE && case_hasBox(sourceCase)) {
                                sourceBox = case_getBox(sourceCase);
                                // Vérification de la présence de ressource dans la box
                                // TODO Valentin : Possiblement à enlever
                                if (box_getNumberResource(sourceBox) > 0 || box_getNumberGarbage(sourceBox) > 0) {
                                    // Ajour=t de la case à la liste de source
                                    Element elt = {
                                            .type = OBJECT,
                                            .content.object = (void *) sourceCase
                                    };
                                    list_addElement(listSource, elt);
                                }
                            }
                        }
                    } else if (dir == DIRECTION_OUT) {
                        // Si OUT se souvenir de la sortie
                        // Hypothèse qu'il y a toujours un OUT
                        out = card;
                    }
                }

                // Création d'une box temporaire pour stocker le nombre de ressource récupéré
                int choiceSource;
                Box *cumulative = box_create(0, 0);
                // Temps qu'il y a encore possibilité de récupérer des ressources
                // Et qu'il y a encore des ressources à récupéré
                while (capacity > 0 && list_getSize(listSource) > 0) {
                    // Choisir un source aléatoirement
                    choiceSource = rand() % list_getSize(listSource); // NOLINT(cert-msc50-cpp)

                    // Récupérer la box sur la source
                    Element *elt = list_getByIndex(listSource, choiceSource);
                    sourceBox = case_getBox((Case *) elt->content.object);

                    // Prendre une ressource de la source
                    box_setNumberResource(cumulative, 1);
                    box_setNumberResource(sourceBox, -1);

                    // Supprimer la source de la liste si elle est vide
                    if (box_getNumberResource(sourceBox) <= 0) {
                        list_removeByIndex(listSource, choiceSource);
                    }

                    // Diminué la capacité du collecteur
                    capacity--;
                }
                // Détruire la liste de source
                list_destroy(listSource);

                fprintf(stderr, "Cumulative => Resources %d\n", box_getNumberResource(cumulative));
                // Si il y a des ressources qui ont été récupéré alors envoyer la box vers
                // la sortie du collecteur
                if (box_getNumberResource(cumulative) > 0) {
                    if (map_utils_moveBox(m, collectorCase, cumulative, out) != NO_ERROR) {
                        box_destroy(cumulative);
                    }
                } else {
                    box_destroy(cumulative);
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
            box_destroy(box);
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

    // Parcours de toutes les cases du plateau
    for (int j = 0; j < map_getHeight(m); ++j) {
        for (int i = 0; i < map_getWidth(m); ++i) {
            // Récupréation de la case
            c = map_getCase(i, j, m);
            // Vérification de la présence d'une machine
            if (case_getType(c) == CASE_MACHINE) {
                // Récupération de la machine
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
                    // Création d'un box temporaire afin de stocker l'ensemble des Ressources / garbages
                    Box *cumulBox = box_create(0, 0);
                    Cardinal out;

                    // Parcours de toutes les face
                    for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                        // Vérification de la direction
                        direction = machine_getDirection(machine, card);
                        if (direction == DIRECTION_OUT) {
                            // Si OUT sauvegarde de la face
                            out = card;
                        } else if (direction == DIRECTION_IN) {
                            // Sinon vérification de la présence d'une boite
                            Box *tmp = machine_getBox(machine, card);
                            if (tmp != NULL) {
                                // Si ouii ajouter les valeurs à la box temporaire
                                box_addB2toB1(cumulBox, tmp);
                                // Supprimer la box
                                machine_destroyBox(machine, card);
                            }
                        }
                    }

                    // Verification de la présence de ressources
                    if (box_getNumberGarbage(cumulBox) > 0 || box_getNumberResource(cumulBox) > 0) {
                        // Vérification de la présence d'un Box sur la sortie
                        Box *tmp = machine_getBox(machine, out);
                        if (tmp != NULL) {
                            // Si oui ajouter les données
                            box_addB2toB1(tmp, cumulBox);
                            box_destroy(cumulBox);
                        } else {
                            // Ajout de la box à la face de sortie
                            machine_addBox(machine, out, cumulBox);
                        }
                    } else {
                        // Destruction de la box
                        box_destroy(cumulBox);
                    }

                    // TODO Valentin : Temporaire
                    for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
                        direction = machine_getDirection(machine, card);
                        fprintf(stderr,"Case x:%d y:%d card:%d dir:%d => ", case_getX(c), case_getY(c), card, direction);
                        Box *tmp = machine_getBox(machine, card);
                        if (tmp != NULL) {
                            fprintf(stderr, "Ok R:%d G:%d\n", box_getNumberResource(tmp),
                                    box_getNumberGarbage(tmp));
                        } else {
                            fprintf(stderr, "Non Ok\n");
                        }
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