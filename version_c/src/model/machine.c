/*!
 * \file machine.c
 * \author Ramzy ZEBRIR and Antoine MAN
 * \version 0.1
 * \date 01/03/2021
 * \see machine_info.h
 *
 * Contains main information about all of the machine
 */


#include <stdio.h>
#include <stdlib.h>
#include "../../headers/data/machine.h"

struct Machine_S {
    MachineStuff type; //!< number associate to the type of the machine
    int level; //!< Represent the level of improvement of the machineFacade
    Facade **interface; //!< Represent the orientation of the machine
}; //!< Machine which contains the main information about a machine

/*
 * function to get the type of the machine
 */
MachineStuff machine_getType(const Machine *machine) { return machine->type; }

/*
 * function to get the level of the machine
 */
int machine_getLevel(const Machine *machine) { return machine->level; }

/*
 * a function to get a default orientation for a machine
 */
Facade **facade_defaultFacade(MachineStuff s) {
    Facade **interface = (Facade **) malloc(NUMBER_CARDINAL * sizeof(Facade *));

    // We create a facade for each machine wall
    for (Cardinal i = 0; i < NUMBER_CARDINAL; ++i) {
        interface[i] = facade_create(i);
    }

    // Give a default orientation for each machine (IN, OUT, NONE)
    switch (s) {

        // Resources move out by the south
        case MS_COLLECTOR:
            facade_setDirection(interface[SOUTH], DIRECTION_OUT);
            break;

            // Resources move in by all direction except South which is the exit
        case MS_CONVEYOR_BELT:
            facade_setDirection(interface[NORTH], DIRECTION_IN);
            facade_setDirection(interface[EAST], DIRECTION_IN);
            facade_setDirection(interface[SOUTH], DIRECTION_OUT);
            facade_setDirection(interface[WEST], DIRECTION_IN);
            break;

            // Resources move in by the north and the east and they move out by the south and the west
        case MS_CROSS:
            facade_setDirection(interface[NORTH], DIRECTION_IN);
            facade_setDirection(interface[EAST], DIRECTION_IN);
            facade_setDirection(interface[SOUTH], DIRECTION_OUT);
            facade_setDirection(interface[WEST], DIRECTION_OUT);
            break;

            // Resources move in by all direction except South which is the exit
        case MS_RECYCLING_CENTER:
            facade_setDirection(interface[NORTH], DIRECTION_IN);
            facade_setDirection(interface[EAST], DIRECTION_IN);
            facade_setDirection(interface[SOUTH], DIRECTION_OUT);
            facade_setDirection(interface[WEST], DIRECTION_IN);
            break;

            // Resources move in by all direction
        case MS_JUNKYARD:
            facade_setDirection(interface[NORTH], DIRECTION_IN);
            facade_setDirection(interface[EAST], DIRECTION_IN);
            facade_setDirection(interface[SOUTH], DIRECTION_IN);
            facade_setDirection(interface[WEST], DIRECTION_IN);
            break;
        default:
            return NULL;
    }
    return interface;
}

/*
 * Function to create a new machine according to the type machine given
 */
Machine *machine_create(MachineStuff type) {
    Machine *mach = (Machine *) malloc(sizeof(Machine));
    mach->type = type;
    mach->level = MACHINE_DEFAULT_LVL;
    mach->interface = facade_defaultFacade(type);
    return mach;
}

/*
 * A function to free allocated resources in memory in order to stock a machine
 */
ErrorCode machine_destroyMachine(Machine *mach) {
    // free every facade of the machine
    for (Cardinal i = 0; i < NUMBER_CARDINAL; ++i) {
        facade_destroy(mach->interface[i]);
    }
    free(mach);
    return NO_ERROR;
}

/*
 * This function rotate the orientation of a machine in clockwise
 */
void machine_rotateMachine(Machine *machine, int rotation) {
    Box *tmpBox;
    Direction tmpDirection;
    rotation = (rotation % NUMBER_CARDINAL) + NUMBER_CARDINAL;

    //      North -----> East
    //       / \          |
    //        |           V
    //      West <----- South
    //
    for (int rot = 0; rot < (rotation % NUMBER_CARDINAL); rot++) {
        tmpDirection = facade_getDirection(machine->interface[NORTH]);
        tmpBox = facade_getBox(machine->interface[NORTH]);

        // North facade become West facade
        facade_setDirection(machine->interface[NORTH], facade_getDirection(machine->interface[WEST]));
        facade_setBox(machine->interface[NORTH], facade_getBox(machine->interface[WEST]));

        // West facade become South facade
        facade_setDirection(machine->interface[WEST], facade_getDirection(machine->interface[SOUTH]));
        facade_setBox(machine->interface[WEST], facade_getBox(machine->interface[SOUTH]));

        // South facade become East facade
        facade_setDirection(machine->interface[SOUTH], facade_getDirection(machine->interface[EAST]));
        facade_setBox(machine->interface[SOUTH], facade_getBox(machine->interface[EAST]));

        // East facade become North facade
        facade_setDirection(machine->interface[EAST], tmpDirection);
        facade_setBox(machine->interface[EAST], tmpBox);
    }
}

/*
 * This function upgrade a machine by incrementing his level
 */
void machine_incrementLevel(Machine *m) { m->level++; }

/*
 * A function to know if the direction given in argument is equals to
 * the north direction of the machine
 */
bool machine_isOrientationTop(const Machine *mach, Direction d) {
    return machine_getDirection(mach, NORTH) == d;
}

/*
 * A function to know if the direction given in argument is equals to
 * the north direction and the east direction of the machine
 */
bool machine_isOrientationTopRight(const Machine *mach, Direction d) {
    return machine_getDirection(mach, NORTH) == d && machine_getDirection(mach, EAST) == d;
}

/*
 * A function to know if the direction given in argument is equals to
 * the east direction of the machine
 */
bool machine_isOrientationRight(const Machine *mach, Direction d) {
    return machine_getDirection(mach, EAST) == d;
}

/*
 * A function to know if the direction given in argument is equals to
 * the east direction and the south direction of the machine
 */
bool machine_isOrientationBottomRight(const Machine *mach, Direction d) {
    return machine_getDirection(mach, SOUTH) == d && machine_getDirection(mach, EAST) == d;
}

/*
 * A function to know if the direction given in argument is equals to
 * the south direction of the machine
 */
bool machine_isOrientationBottom(const Machine *mach, Direction d) {
    return machine_getDirection(mach, SOUTH) == d;
}

/*
 * A function to know if the direction given in argument is equals to
 * the south direction and the west direction of the machine
 */
bool machine_isOrientationBottomLeft(const Machine *mach, Direction d) {
    return machine_getDirection(mach, SOUTH) == d && machine_getDirection(mach, WEST) == d;
}

/*
 * A function to know if the direction given in argument is equals to
 * the west direction of the machine
 */
bool machine_isOrientationLeft(const Machine *mach, Direction d) {
    return machine_getDirection(mach, WEST) == d;
}

/*
 * A function to know if the direction given in argument is equals to
 * the west direction and the north direction of the machine
 */
bool machine_isOrientationTopLeft(const Machine *mach, Direction d) {
    return machine_getDirection(mach, NORTH) == d && machine_getDirection(mach, WEST) == d;
}

/*
 * A function to know if the number of rotation is correct
 * Between 0 and NUMBER_CARDINAL(4)
 */
bool machine_isRotationCorrect(int rotation) {
    return rotation >= 0 && rotation < NUMBER_CARDINAL;
}

/*
 * A function to get the direction of a facade machine according to the cardinal
 */
Direction machine_getDirection(const Machine *machine, Cardinal card) {
    return facade_getDirection(machine->interface[card]);
}

/*
 * A function to get a box of a facade machine according to the cardinal
 */
Box *machine_getBox(const Machine *machine, Cardinal card) {
    return facade_getBox(machine->interface[card]);
}

/*
 * A function to add a box to the facade machine according to the cardinal
 */
void machine_addBox(Machine *machine, Cardinal card, Box *box) {
    facade_setBox(machine->interface[card], box);
}

/*
 * A function to destroy a box of the facade machine according to the cardinal
 */
void machine_destroyBox(Machine *machine, Cardinal card) {
    Box *tmp = facade_getBox(machine->interface[card]);

    // Verify if there is a box in the facade machine
    if (tmp != NULL) {
        free(tmp);
        facade_setBox(machine->interface[card], NULL);
    }
}