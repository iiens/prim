#include "../../headers/data/machine_info.h"

#include <stdio.h>
#include <stdlib.h>

const MachineInfo *map_getMachineInfoByType(MachineStuff type) {
    int indexM = 0;
    while (indexM < NUMBER_OF_MACHINES && machine_list[indexM].type != type) { indexM++; }

    if (indexM == NUMBER_OF_MACHINES) {
        return NULL;
    } else {
        return &(machine_list[indexM]);
    }
}

MachineStuff machineInfo_getType(MachineInfo *machine){ return machine->type; }

int machineInfo_getCostE(MachineInfo *machine){ return machine->costE; }

int machineInfo_getCostDD(MachineInfo *machine){ return machine->costDD; }

int machineInfo_getCostUpgradeE(MachineInfo *machine){ return machine->costUpgradeE; }

int machineInfo_getCostUpgradeDD(MachineInfo *machine){ return machine->costUpgradeDD; }

int machineInfo_getCostDestroyE(MachineInfo *machine){ return machine->costDestroyE; }

int machineInfo_getCostDestroyDD(MachineInfo *machine){ return machine->costDestroyDD; }

char* machineInfo_getDescription(MachineInfo *machine){ return machine->description; }

int machineInfo_getCapacity(MachineInfo *machine){ return machine->capacity;}

bool machineInfo_getCanUpgrade(MachineInfo *machine){ return machine->canUpgrade; }

const Effect *machineInfo_getEffects(MachineInfo *machine){ return &(machine->effects); }
