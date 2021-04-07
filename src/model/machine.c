#include "../../headers/data/machine.h"

#include <stdio.h>
#include <stdlib.h>

MachineStuff machine_getType(Machine* machine){ return machine->type; }

int machine_getLevel(Machine* machine){ return machine->level; }

Orientation  machine_getOrientation(Machine* machine){ return machine->orientation; }

Direction  machine_getOrientationTop(Orientation* orient){ return orient->top; }

Direction  machine_getOrientationBottom(Orientation* orient){ return orient->bottom; }

Direction  machine_getOrientationLeft(Orientation* orient){ return orient->left; }

Direction  machine_getOrientationRight(Orientation* orient){ return orient->right; }

Orientation machine_generateDefaultOrientation(MachineStuff s) {
    Orientation orient;
    switch (s) {
        case MS_COLLECTOR:
            orient.top = DIRECTION_NONE;
            orient.right = DIRECTION_NONE;
            orient.bottom = DIRECTION_OUT;
            orient.left = DIRECTION_NONE;
            break;
        case MS_CONVEYOR_BELT:
            orient.top = DIRECTION_IN;
            orient.right = DIRECTION_IN;
            orient.bottom = DIRECTION_OUT;
            orient.left = DIRECTION_IN;
            break;
        case MS_CROSS:
            orient.top = DIRECTION_IN;
            orient.right = DIRECTION_IN;
            orient.bottom = DIRECTION_OUT;
            orient.left = DIRECTION_OUT;
            break;
        case MS_RECYCLING_CENTER:
            orient.top = DIRECTION_IN;
            orient.right = DIRECTION_IN;
            orient.bottom = DIRECTION_OUT;
            orient.left = DIRECTION_IN;
            break;
        case MS_JUNKYARD:
            orient.top = DIRECTION_IN;
            orient.right = DIRECTION_IN;
            orient.bottom = DIRECTION_IN;
            orient.left = DIRECTION_IN;
            break;
        default:
            orient.top = DIRECTION_NONE;
            orient.right = DIRECTION_NONE;
            orient.bottom = DIRECTION_NONE;
            orient.left = DIRECTION_NONE;
            break;
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

