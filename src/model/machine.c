#include "../../headers/data/machine.h"

#include <stdio.h>
#include <stdlib.h>

MachineStuff machine_getType(Machine* machine){ return machine->type; }

int machine_getLevel(Machine* machine){ return machine->level; }

Orientation  machine_getOrientation(Machine* machine){ return machine->orientation; }

Direction  machine_getOrientationTop(Machine* machine){ return machine->orientation.top; }

Direction  machine_getOrientationBottom(Machine* machine){ return machine->orientation.bottom; }

Direction  machine_getOrientationLeft(Machine* machine){ return machine->orientation.left; }

Direction  machine_getOrientationRight(Machine* machine){ return machine->orientation.right; }

