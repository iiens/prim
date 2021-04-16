/*!
 * \file case.c
 * \author Antoine Man
 * \version 0.1
 * \date 11/03/2021
 * \see map.h
 * \see machine.h
 * \see error.h
 * \see box.h
 *
 * Contains all the types that a case can contain and all
 * interactions possible with it
 *
 */

#include "../../headers/data/case.h"
#include "stdlib.h"
#include "stdio.h"

struct Case_S {
    int x; //!< int, case abscissa
    int y; //!< int, case ordinate
    void *in; //!< void* in, it correspond to the object contained in the case (box, machine)
    CaseType type; //!< type of object contained in the case
}; //!< it correspond to a case of the board game

/*
 * A function to get the case abscissa
 */
int case_getX(const Case *c) { return c->x; }

/*
 * A function to get the case ordinate
 */
int case_getY(const Case *c) { return c->y; }

/*
 * Comparison between bits in order to know the type case
 */
CaseType case_getType(const Case *c) {
    return c->type & 0xFFFFFFFE;
}

/*
 * Return the machine of the case if there is a machine
 */
Machine *case_getMachine(const Case *c) {
    return (Machine *) c->in;
}

/*
 * return the box of the case if there is a box
 */
Box *case_getBox(const Case *c) {
    return (Box *) c->in;
}

/*
 * Resources of a case are contained in a box or in machine facades
 */
int case_getNumberResourcesByCase(const Case *c) {
    int nbResources = 0;
    Box *box;
    CaseType type = case_getType(c);

    // Verify if there is a case on the case
    if (case_hasBox(c)) {
        box = case_getBox(c);
        nbResources = box_getNumberResource(box);

        // Verify if there is a machine on the case
    } else if (type == CASE_MACHINE) {
        Machine *machine = case_getMachine(c);

        // Sum resources number for each facade of a machine
        for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
            box = machine_getBox(machine, card);
            if (box != NULL) {
                nbResources += box_getNumberResource(box);
            }
        }
    }
    return nbResources;
}

/*
 * Garbage of a case are contained in a box or in machine facades
 */
int case_getNumberGarbageByCase(const Case *c) {
    int nbGarbage = 0;
    Box *box;
    CaseType type = case_getType(c);

    // Verify if there is a box on the case
    if (case_hasBox(c)) {
        box = case_getBox(c);
        nbGarbage = box_getNumberGarbage(box);

        // Verify if there is a machine on the case
    } else if (type == CASE_MACHINE) {
        Machine *machine = case_getMachine(c);

        // Sum garbage number for each facade of a machine
        for (Cardinal card = 0; card < NUMBER_CARDINAL; ++card) {
            box = machine_getBox(machine, card);
            if (box != NULL) {
                nbGarbage += box_getNumberGarbage(box);
            }
        }
    }
    return nbGarbage;
}

/*
 * Add a machine on a case if the case is empty
 */
void case_addMachine(Case *c, Machine *mach) {
    if (case_isEmpty(c) && c->in == NULL) {
        c->type = CASE_MACHINE;
        c->in = mach;
    }
}

/*
 * Add a gate on a case if the case is empty
 */
void case_addGate(Case *c) {
    if (case_isEmpty(c)) {
        c->type = CASE_GATE;
    }
}

/*
 * Add a source on a case if the case is empty
 */
void case_addSource(Case *c) {
    if (case_isEmpty(c)) {
        c->type = CASE_SOURCE;
    }
}

/*
 * Add a box on a case if the case don't have a box yet
 */
void case_addBox(Case *c, Box *box) {
    if (c->type != CASE_MACHINE && !(case_hasBox(c))) {
        c->type = c->type | 0x01;
        c->in = box;
    }
}

/*
 * A function to remove the box on a located case
 */
ErrorCode case_deleteBox(Case *c) {
    // Verify if there is a box on the case
    if (case_hasBox(c)) {
        free(c->in);
        c->type = c->type & 0xFFFFFFFE;
        c->in = NULL;
    }
    return NO_ERROR;
}

/*
 * A function to remove everything on the case
 */
void case_setEmpty(Case *c) {

    // Verify if there is a box on the case
    if (case_hasBox(c)) {
        free(c->in);

        // Verify if there is a machine on the case
    } else if (case_getType(c) == CASE_MACHINE) {
        machine_destroyMachine((Machine *) c->in);
    }
    c->type = CASE_VIDE;
    c->in = NULL;
}

/*
 * A function to create a new case
 */
Case *case_create(int x, int y) {
    Case *c = (Case *) malloc(sizeof(Case));
    c->type = CASE_VIDE;
    c->in = NULL;
    c->x = x;
    c->y = y;
    return c;
}

/*
 * A function to know if there is something on the case (box, machine)
 */
bool case_isEmpty(const Case *c) {
    return c->type == CASE_VIDE;
}

/*
 * Comparison between bits in order to know if case have a box
 */
bool case_hasBox(const Case *c) {
    return (c->type & 0x01) == 0x01;
}

/*
 * A function to free allocated resources in memory in order to
 * stock the case.
 */
void case_destroy(Case *c) {
    case_setEmpty(c);
    free(c);
}