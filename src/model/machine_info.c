#include "../../headers/data/machine_info.h"

#include <stdio.h>

// todo: please use .type, .costE and not simply
//  inserting a value
const MachineInfo machine_list[] = {
        {
                MS_COLLECTOR,200,20,500,100,60,200,
                "Sends a resource produced by the source to the "
                "neighboring cell indicated by its orientation.",
                1," Collector Out is South by default",1, .effects  =
                {
                        .mode = PRODUCTION,
                        .onOther = 0,
                        .what.machine = MS_COLLECTOR,
                        .modifierCapacity = +1 ,
                        .description = "Collector storage increases by 1 "
                }
        },
        {MS_CONVEYOR_BELT,60,20,-1,-1,60,200,
                "A carpet has one exit and three entrances, the resource or waste exits",
                0," Conveyor Belt Out is South by default"
                  ,0, .effects = {}},
        {MS_CROSS,160,20,-1,-1,60,200,
                "The cross has 2 inlets and 2 outlets "
                "which depend on the orientation of the cross",0,
                " Cross Out is South and West by default",
                0, .effects = {}},
        {MS_RECYCLING_CENTER,500,40,1500,100,100,500,
                "The recycling center has 3 entrances and one exit. The center can store up to 100 "
                "waste",100,
                "Recycling Center Out is South by default",
                                                                                     1, .effects =
                {
                        .mode = PRODUCTION,
                        .onOther = 0,
                        .what.machine = MS_RECYCLING_CENTER,
                        .modifierCapacity= +10,
                        .description = "Storage of Recycling center increases by 10"
                }
        },
        {MS_JUNKYARD,100,100,200,600,100,200,
                "The junkyard"
                " has 4 entrances and 0 exits. Can store up to 50 pieces of waste",50,
                "Junkyard hasn't any Out",
                                                                                     1, .effects = {
                .mode = PRODUCTION,
                .onOther = 0,
                .what.machine = MS_JUNKYARD,
                .modifierCapacity= +20,
                .description = "Storage of Junkyard increases by 20"
                               "et 1DD)."}
        }
}; //!< Array with information about all machine

const MachineInfo *machineInfo_getMachineInfoByType(MachineStuff type) {
    int indexM = 0;
    while (indexM < NUMBER_OF_MACHINES && machine_list[indexM].type != type) { indexM++; }

    if (indexM == NUMBER_OF_MACHINES) {
        return NULL;
    } else {
        return &(machine_list[indexM]);
    }
}
//todo: too much methods lined without a comment
// please use a method block comment
// such as
// /*
// * these methods are used for ...
// */
// then some methods again and again. To split since it's unreadable :-(

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

int machineInfo_isMachineStuffValid(int id) {
    for (int i = 0; i < NUMBER_OF_MACHINES; ++i) {
        if (id == (int) machine_list[i].type) {
            return i;
        }
    }
    return -1;
}

const MachineInfo* machineInfo_getMachineStuff(int id) {
    int index = machineInfo_isMachineStuffValid(id);
    if (machineInfo_isMachineStuffValid(id) >= 0) {
        return &(machine_list[index]);
    } else {
        return NULL;
    }
}

char* machineInfo_getDefaultOrientationMessage(const MachineInfo* m) { return m->defaultOrientation; }
