#include "../../headers/data/machine_info.h"

#include <stdio.h>
#include <stdlib.h>

const MachineInfo *machineInfo_getMachineInfoByType(MachineStuff type) {
    int indexM = 0;
    while (indexM < NUMBER_OF_MACHINES && machine_list[indexM].type != type) { indexM++; }

    if (indexM == NUMBER_OF_MACHINES) {
        return NULL;
    } else {
        return &(machine_list[indexM]);
    }
}

MachineStuff machineInfo_getType(const MachineInfo *machine){ return machine->type; }

int machineInfo_getCostE(const MachineInfo *machine){ return machine->costE; }

int machineInfo_getCostDD(const MachineInfo *machine){ return machine->costDD; }

int machineInfo_getCostUpgradeE(const MachineInfo *machine){ return machine->costUpgradeE; }

int machineInfo_getCostUpgradeDD(const MachineInfo *machine){ return machine->costUpgradeDD; }

int machineInfo_getCostDestroyE(const MachineInfo *machine){ return machine->costDestroyE; }

int machineInfo_getCostDestroyDD(const MachineInfo *machine){ return machine->costDestroyDD; }

char* machineInfo_getDescription(const MachineInfo *machine){ return machine->description; }

int machineInfo_getCapacity(const MachineInfo *machine){ return machine->capacity;}

bool machineInfo_getCanUpgrade(const MachineInfo *machine){ return machine->canUpgrade; }

const Effect *machineInfo_getEffects(const MachineInfo *machine){ return &(machine->effects); }
