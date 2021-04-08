#include <stdio.h>
#include <stdlib.h>

#include "../../headers/data/machine_info.h" //! to use bool

struct Facade_S {
    Cardinal cardinal;
    Direction direction;
    Box *content;
}; //!< Facade

struct Machine_S {
    MachineStuff type; //!< number associate to the type of the machine
    int level; //!< Represent the level of improvement of the machineFacade
    int numberFacade; //!< Represent the number of facade
    Facade *interface; //!< Represent the orientation of the machine
}; //!< Machine

Facade *facade_defaultFacade(MachineStuff s) {
    Facade *interface = (Facade *) malloc(4*sizeof(Facade)); // TODO : RAMZY #define NUMBER FACADE 4

    for (int i = 0; i < 4; ++i) {
        interface[i].content = NULL;
    }

    interface[0].cardinal = NORTH;
    interface[1].cardinal = EAST;
    interface[2].cardinal = SOUTH;
    interface[3].cardinal = WEST;

    switch (s) {
        case MS_COLLECTOR:
            interface[NORTH].direction = DIRECTION_NONE;
            interface[EAST].direction = DIRECTION_NONE;
            interface[SOUTH].direction = DIRECTION_OUT;
            interface[WEST].direction = DIRECTION_NONE;
            break;
        case MS_CONVEYOR_BELT:
            interface[NORTH].direction = DIRECTION_IN;
            interface[EAST].direction = DIRECTION_IN;
            interface[SOUTH].direction = DIRECTION_OUT;
            interface[WEST].direction = DIRECTION_IN;
            break;
        case MS_CROSS:
            interface[NORTH].direction = DIRECTION_IN;
            interface[EAST].direction = DIRECTION_IN;
            interface[SOUTH].direction = DIRECTION_OUT;
            interface[WEST].direction = DIRECTION_OUT;
            break;
        case MS_RECYCLING_CENTER:
            interface[NORTH].direction = DIRECTION_IN;
            interface[EAST].direction = DIRECTION_IN;
            interface[SOUTH].direction = DIRECTION_OUT;
            interface[WEST].direction = DIRECTION_IN;
            break;
        case MS_JUNKYARD:
            interface[NORTH].direction = DIRECTION_IN;
            interface[EAST].direction = DIRECTION_IN;
            interface[SOUTH].direction = DIRECTION_IN;
            interface[WEST].direction = DIRECTION_IN;
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
    mach->numberFacade = 4; // TODO : Demander #define NUMBER FACADE RAMZY
    mach->interface = facade_defaultFacade(type);

    return mach;
}

ErrorCode machine_destroyMachine(Machine *mach) {
    // free tous les composants de machine, y compris Carton
    free(mach->interface);
    free(mach);
    return NO_ERROR;
}

MachineStuff machine_getType(const Machine *machine) { return machine->type; }

int machine_getLevel(const Machine *machine) { return machine->level; }

//Todo ANTOINE Number direction COnstante ?
void machine_rotateMachine(Machine *machine, int rotation) {
    Box* tmpBox;
    Direction tmpDirection;

    rotation = (rotation % machine->numberFacade) + machine->numberFacade;
    for (int i = 0; i < (rotation % machine->numberFacade); i++) {
        tmpDirection = machine->interface[NORTH].direction;
        tmpBox = machine->interface[NORTH].content;

        machine->interface[NORTH].direction = machine->interface[WEST].direction;
        machine->interface[NORTH].content = machine->interface[WEST].content;

        machine->interface[WEST].direction = machine->interface[SOUTH].direction;
        machine->interface[WEST].content = machine->interface[SOUTH].content;

        machine->interface[SOUTH].direction = machine->interface[EAST].direction;
        machine->interface[SOUTH].content = machine->interface[EAST].content;

        machine->interface[EAST].direction = tmpDirection;
        machine->interface[EAST].content = tmpBox;
    }
}

void machine_incrementLevel(Machine *m) { m->level++; }


bool machine_isOrientationTop(const Machine *mach, Direction d) {
    if (facade_getDirection(mach, NORTH) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationTopRight(const Machine *mach, Direction d) {
    if (facade_getDirection(mach, NORTH) == d && facade_getDirection(mach, EAST) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationRight(const Machine *mach, Direction d) {
    if (facade_getDirection(mach, EAST) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationBottomRight(const Machine *mach, Direction d) {
    if (facade_getDirection(mach, SOUTH) == d && facade_getDirection(mach, EAST) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationBottom(const Machine *mach, Direction d) {
    if (facade_getDirection(mach, SOUTH) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationBottomLeft(const Machine *mach, Direction d) {
    if (facade_getDirection(mach, SOUTH) == d && facade_getDirection(mach, WEST) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationLeft(const Machine *mach, Direction d) {
    if (facade_getDirection(mach, WEST) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationTopLeft(const Machine *mach, Direction d) {
    if (facade_getDirection(mach, NORTH) == d && facade_getDirection(mach, WEST) == d) {
        return true;
    } else {
        return false;
    }
}

// Struct Facade
Direction facade_getDirection(const Machine *machine, Cardinal card) {
    for (int i = 0; i < machine->numberFacade; ++i) {
        if (machine->interface[i].cardinal == card) {
            return machine->interface[card].direction;
        }
    }

    return DIRECTION_NONE;
}

Box *facade_getBox(const Machine *machine, Cardinal card) {
    for (int i = 0; i < machine->numberFacade; ++i) {
        if (machine->interface[i].cardinal == card) {
            return machine->interface[card].content;
        }
    }

    return NULL;
}
