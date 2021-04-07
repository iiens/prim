#include "../../headers/data/machine.h"

#include <stdio.h>
#include <stdlib.h>

struct Orientation_S {
    Direction top; //!< top
    Direction left; //!< left
    Direction bottom; //!< bottom
    Direction right; //!< right
}; //!< Orientation

struct Machine_S {
    MachineStuff type; //!< number associate to the type of the machine
    int level; //!< Represent the level of improvement of the machine
    Orientation* orientation; //!< Represent the orientation of the machine
}; //!< Machine

MachineStuff machine_getType(const Machine* machine){ return machine->type; }

int machine_getLevel(const Machine* machine){ return machine->level; }

Orientation* machine_getOrientation(const Machine* machine){ return machine->orientation; }

Direction  machine_getOrientationTop(const Orientation* orient){ return orient->top; }

Direction  machine_getOrientationBottom(const Orientation* orient){ return orient->bottom; }

Direction  machine_getOrientationLeft(const Orientation* orient){ return orient->left; }

Direction  machine_getOrientationRight(const Orientation* orient){ return orient->right; }

Orientation* machine_generateDefaultOrientation(MachineStuff s) {
    Orientation* orient =  (Orientation*) malloc (sizeof(Orientation));
    switch (s) {
        case MS_COLLECTOR:
            orient->top = DIRECTION_NONE;
            orient->right = DIRECTION_NONE;
            orient->bottom = DIRECTION_OUT;
            orient->left = DIRECTION_NONE;
            break;
        case MS_CONVEYOR_BELT:
            orient->top = DIRECTION_IN;
            orient->right = DIRECTION_IN;
            orient->bottom = DIRECTION_OUT;
            orient->left = DIRECTION_IN;
            break;
        case MS_CROSS:
            orient->top = DIRECTION_IN;
            orient->right = DIRECTION_IN;
            orient->bottom = DIRECTION_OUT;
            orient->left = DIRECTION_OUT;
            break;
        case MS_RECYCLING_CENTER:
            orient->top = DIRECTION_IN;
            orient->right = DIRECTION_IN;
            orient->bottom = DIRECTION_OUT;
            orient->left = DIRECTION_IN;
            break;
        case MS_JUNKYARD:
            orient->top = DIRECTION_IN;
            orient->right = DIRECTION_IN;
            orient->bottom = DIRECTION_IN;
            orient->left = DIRECTION_IN;
            break;
        default:
            return NULL;
    }
        return orient;
}

// PASTE QUENTIN
//int machine_getOrientation(Orientation o);

//Todo ANTOINE Number direction COnstante ?
void machine_rotateMachine(Orientation* o, int rotation) {
    Direction tmp;
    rotation = (rotation % 4) + 4;
    for(int i=0; i<(rotation % 4); i++) {
        tmp = o->top;
        o->top = o->left;
        o->left = o->bottom;
        o->bottom = o->right;
        o->right = tmp;
    }
}

void machine_incrementLevel(Machine* m) { m->level++; }

Machine* machine_Create(MachineStuff type, Orientation* orient) {
    Machine* mach = (Machine*) malloc(sizeof(Machine));
    mach->orientation = orient;
    mach->type = type;
    mach->level = 1;

    return mach;
}

ErrorCode machine_destroyMachine(Machine* mach) {
    // free tous les composants de machine, y compris Carton
    free(mach->orientation);
    free(mach);
    return NO_ERROR;
}

bool machine_isOrientationTop(const Machine* mach, Direction d) {
    Orientation* orient = mach->orientation;
    if(machine_getOrientationTop(orient) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationTopRight(const Machine* mach, Direction d) {
    Orientation* orient = mach->orientation;
    if(machine_getOrientationTop(orient) == d && machine_getOrientationRight(orient) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationRight(const Machine* mach, Direction d) {
    Orientation* orient = mach->orientation;
    if(machine_getOrientationRight(orient) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationBottomRight(const Machine* mach, Direction d) {
    Orientation* orient = mach->orientation;
    if(machine_getOrientationBottom(orient) == d && machine_getOrientationRight(orient) == d) {
        return true;
    } else {
        return false;
    }
}
bool machine_isOrientationBottom(const Machine* mach, Direction d) {
    Orientation* orient = mach->orientation;
    if(machine_getOrientationBottom(orient) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationBottomLeft(const Machine* mach, Direction d) {
    Orientation* orient = mach->orientation;
    if(machine_getOrientationBottom(orient) == d && machine_getOrientationLeft(orient) == d) {
        return true;
    } else {
        return false;
    }
}
bool machine_isOrientationLeft(const Machine* mach, Direction d) {
    Orientation* orient = mach->orientation;
    if(machine_getOrientationLeft(orient) == d) {
        return true;
    } else {
        return false;
    }
}

bool machine_isOrientationTopLeft(const Machine* mach, Direction d) {
    Orientation* orient = mach->orientation;
    if(machine_getOrientationTop(orient) == d && machine_getOrientationLeft(orient) == d) {
        return true;
    } else {
        return false;
    }
}

