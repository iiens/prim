#include <stdio.h>
#include <stdlib.h>

#include "../../headers/data/machine.h"

struct Machine_S {
    MachineStuff type; //!< number associate to the type of the machine
    int level; //!< Represent the level of improvement of the machineFacade
    Facade **interface; //!< Represent the orientation of the machine
}; //!< Machine

Facade **facade_defaultFacade(MachineStuff s) {
    Facade **interface = (Facade **) malloc(NUMBER_CARDINAL * sizeof(Facade *));

    for (Cardinal i = 0; i < NUMBER_CARDINAL; ++i) {
        interface[i] = facade_create(i);
    }

    switch (s) {
        case MS_COLLECTOR:
            facade_setDirection(interface[SOUTH],DIRECTION_OUT);
            break;
        case MS_CONVEYOR_BELT:
            facade_setDirection(interface[NORTH],DIRECTION_IN);
            facade_setDirection(interface[EAST],DIRECTION_IN);
            facade_setDirection(interface[SOUTH],DIRECTION_OUT);
            facade_setDirection(interface[WEST],DIRECTION_IN);
            break;
        case MS_CROSS:
            facade_setDirection(interface[NORTH],DIRECTION_IN);
            facade_setDirection(interface[EAST],DIRECTION_IN);
            facade_setDirection(interface[SOUTH],DIRECTION_OUT);
            facade_setDirection(interface[WEST],DIRECTION_OUT);
            break;
        case MS_RECYCLING_CENTER:
            facade_setDirection(interface[NORTH],DIRECTION_IN);
            facade_setDirection(interface[EAST],DIRECTION_IN);
            facade_setDirection(interface[SOUTH],DIRECTION_OUT);
            facade_setDirection(interface[WEST],DIRECTION_IN);
            break;
        case MS_JUNKYARD:
            facade_setDirection(interface[NORTH],DIRECTION_IN);
            facade_setDirection(interface[EAST],DIRECTION_IN);
            facade_setDirection(interface[SOUTH],DIRECTION_IN);
            facade_setDirection(interface[WEST],DIRECTION_IN);
            break;
        default:
            return NULL;
    }
    return interface;
}

Machine *machine_create(MachineStuff type) {
    Machine *mach = (Machine *) malloc(sizeof(Machine));
    mach->type = type;
    mach->level = 1;
    mach->interface = facade_defaultFacade(type);

    return mach;
}

ErrorCode machine_destroyMachine(Machine *mach) {
    // free tous les composants de machine, y compris Carton
    for (Cardinal i = 0; i < NUMBER_CARDINAL; ++i) {
        facade_destroy(mach->interface[i]);
    }
    free(mach);
    return NO_ERROR;
}

MachineStuff machine_getType(const Machine *machine) { return machine->type; }

int machine_getLevel(const Machine *machine) { return machine->level; }

void machine_rotateMachine(Machine *machine, int rotation) {
    Box* tmpBox;
    Direction tmpDirection;

    rotation = (rotation % NUMBER_CARDINAL) + NUMBER_CARDINAL;
    for (int rot = 0; rot < (rotation % NUMBER_CARDINAL); rot++) {
        tmpDirection = facade_getDirection(machine->interface[0]);
        tmpBox = facade_getBox(machine->interface[0]);

        for (Cardinal i = 1; i < NUMBER_CARDINAL; ++i) {
            facade_setDirection(machine->interface[i-1], facade_getDirection(machine->interface[i]));
            facade_setBox(machine->interface[i-1], facade_getBox(machine->interface[i]));
        }

        facade_setDirection(machine->interface[NUMBER_CARDINAL-1], tmpDirection);
        facade_setBox(machine->interface[NUMBER_CARDINAL-1], tmpBox);
    }
}

void machine_incrementLevel(Machine *m) { m->level++; }


bool machine_isOrientationTop(const Machine *mach, Direction d) {
    return machine_getDirection(mach, NORTH) == d;
}

bool machine_isOrientationTopRight(const Machine *mach, Direction d) {
    return machine_getDirection(mach, NORTH) == d && machine_getDirection(mach, EAST) == d;
}

bool machine_isOrientationRight(const Machine *mach, Direction d) {
    return machine_getDirection(mach, EAST) == d;
}

bool machine_isOrientationBottomRight(const Machine *mach, Direction d) {
    return machine_getDirection(mach, SOUTH) == d && machine_getDirection(mach, EAST) == d;
}

bool machine_isOrientationBottom(const Machine *mach, Direction d) {
    return machine_getDirection(mach, SOUTH) == d;
}

bool machine_isOrientationBottomLeft(const Machine *mach, Direction d) {
    return machine_getDirection(mach, SOUTH) == d && machine_getDirection(mach, WEST) == d;
}

bool machine_isOrientationLeft(const Machine *mach, Direction d) {
    return machine_getDirection(mach, WEST) == d;
}

bool machine_isOrientationTopLeft(const Machine *mach, Direction d) {
    return machine_getDirection(mach, NORTH) == d && machine_getDirection(mach, WEST) == d;
}

bool machine_isRotationCorrect(int rotation) {
    return rotation >= 0 && rotation < NUMBER_CARDINAL;
}

// Struct Facade
Direction machine_getDirection(const Machine *machine, Cardinal card) {
    return facade_getDirection(machine->interface[card]);
}

Box *machine_getBox(const Machine *machine, Cardinal card) {
    return facade_getBox(machine->interface[card]);
}

void machine_addBox(Machine*machine, Cardinal card, Box* box) {
    facade_setBox(machine->interface[card], box);
}

void machine_destroyBox(Machine*machine, Cardinal card) {
    Box *tmp = facade_getBox(machine->interface[card]);
    if (tmp != NULL) {
        free(tmp);
        facade_setBox(machine->interface[card], NULL);
    }
}