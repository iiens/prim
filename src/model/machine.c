#include <stdio.h>
#include <stdlib.h>
#include "../../headers/data/case.h"
#include "../../headers/data/machine_info.h" //! to use bool

struct Facade_S {
    Direction direction;
    Box *content;
}; //!< Facade

struct Orientation_S {
    Facade top; //!< top
    Facade left; //!< left
    Facade bottom; //!< bottom
    Facade right; //!< right
}; //!< Orientation

struct Machine_S {
    MachineStuff type; //!< number associate to the type of the machine
    int level; //!< Represent the level of improvement of the machine
    Orientation *orientation; //!< Represent the orientation of the machine
}; //!< Machine

MachineStuff machine_getType(const Machine *machine) { return machine->type; }

int machine_getLevel(const Machine *machine) { return machine->level; }

Orientation *machine_getOrientation(const Machine *machine) { return machine->orientation; }

Orientation *machine_generateDefaultOrientation(MachineStuff s) {
    Orientation *orient = (Orientation *) malloc(sizeof(Orientation));
    switch (s) {
        case MS_COLLECTOR:
            orient->top.direction = DIRECTION_NONE;
            orient->right.direction = DIRECTION_NONE;
            orient->bottom.direction = DIRECTION_OUT;
            orient->left.direction = DIRECTION_NONE;
            break;
        case MS_CONVEYOR_BELT:
            orient->top.direction = DIRECTION_IN;
            orient->right.direction = DIRECTION_IN;
            orient->left.direction = DIRECTION_IN;
            break;
        case MS_CROSS:
            orient->top.direction = DIRECTION_IN;
            orient->right.direction = DIRECTION_IN;
            orient->bottom.direction = DIRECTION_OUT;
            orient->left.direction = DIRECTION_OUT;
            break;
        case MS_RECYCLING_CENTER:
            orient->top.direction = DIRECTION_IN;
            orient->right.direction = DIRECTION_IN;
            orient->bottom.direction = DIRECTION_OUT;
            orient->left.direction = DIRECTION_IN;
            break;
        case MS_JUNKYARD:
            orient->top.direction = DIRECTION_IN;
            orient->right.direction = DIRECTION_IN;
            orient->bottom.direction = DIRECTION_IN;
            orient->left.direction = DIRECTION_IN;
            break;
        default:
            return NULL;
    }
    return orient;
}

// PASTE QUENTIN
//int machine_getOrientation(Orientation o);

//Todo ANTOINE Number direction COnstante ?
void machine_rotateMachine(Orientation *o, int rotation) {
    Facade tmp;
    rotation = (rotation % 4) + 4;
    for (int i = 0; i < (rotation % 4); i++) {
        tmp = o->top;
        o->top = o->left;
        o->left = o->bottom;
        o->bottom = o->right;
        o->right = tmp;
    }
}

void machine_incrementLevel(Machine *m) { m->level++; }

Machine *machine_Create(MachineStuff type, Orientation *orient) {
    Machine *mach = (Machine *) malloc(sizeof(Machine));
    mach->orientation = orient;
    mach->type = type;
    mach->level = 1;

    return mach;
}

ErrorCode machine_destroyMachine(Machine *mach) {
    // free tous les composants de machine, y compris Carton
    free(mach->orientation);
    free(mach);
    return NO_ERROR;
}

bool machine_isOrientationTop(const Machine *mach, Direction d) {
    Orientation *orient = mach->orientation;
    if (machine_getOrientationTop(orient) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationTopRight(const Machine *mach, Direction d) {
    Orientation *orient = mach->orientation;
    if (machine_getOrientationTop(orient) == d && machine_getOrientationRight(orient) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationRight(const Machine *mach, Direction d) {
    Orientation *orient = mach->orientation;
    if (machine_getOrientationRight(orient) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationBottomRight(const Machine *mach, Direction d) {
    Orientation *orient = mach->orientation;
    if (machine_getOrientationBottom(orient) == d && machine_getOrientationRight(orient) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationBottom(const Machine *mach, Direction d) {
    Orientation *orient = mach->orientation;
    if (machine_getOrientationBottom(orient) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationBottomLeft(const Machine *mach, Direction d) {
    Orientation *orient = mach->orientation;
    if (machine_getOrientationBottom(orient) == d && machine_getOrientationLeft(orient) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationLeft(const Machine *mach, Direction d) {
    Orientation *orient = mach->orientation;
    if (machine_getOrientationLeft(orient) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationTopLeft(const Machine *mach, Direction d) {
    Orientation *orient = mach->orientation;
    if (machine_getOrientationTop(orient) == d && machine_getOrientationLeft(orient) == d) {
        return true;
    } else {
        return false;
    }
}

// Struct Facade
Direction machine_getOrientationTop(const Orientation *orient) { return orient->top.direction; }

Direction machine_getOrientationBottom(const Orientation *orient) { return orient->bottom.direction; }

Direction machine_getOrientationLeft(const Orientation *orient) { return orient->left.direction; }

Direction machine_getOrientationRight(const Orientation *orient) { return orient->right.direction; }

Box *facade_getBoxTop(const Orientation *orient) { return orient->top.content; }

Box *facade_getBottom(const Orientation *orient) { return orient->bottom.content; }

Box *facade_getBoxLeft(const Orientation *orient) { return orient->left.content; }

Box *facade_getBotRight(const Orientation *orient) { return orient->right.content; }
