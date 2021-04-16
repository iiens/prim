/*!
 * \file machine_info.c
 * \author Ramzy ZEBRIR and Antoine man
 * \version 0.1
 * \date 01/03/2021
 * \see machine.h
 *
 * Contains all information about machine
 */

#include "../../headers/data/machine_info.h"
#include <stdio.h>
#include "limits.h"

// todo: please use .type, .costE and not simply
//  inserting a value
const MachineInfo machine_list[] = {
        {
                MS_COLLECTOR,        200, 20,  500,  100, 60,  200,
                "Sends a resource produced by the source to the "
                "neighboring cell indicated by its orientation.",
                                                                                    1, " Collector Out is South by default",     1, .effects  =
                {
                        .mode = PRODUCTION,
                        .onOther = 0,
                        .what.machine = MS_COLLECTOR,
                        .modifierCapacity = +1,
                        .description = "Collector storage increases by 1 "
                }
        },
        {       MS_CONVEYOR_BELT,    60,  20,  -1,   -1,  60,  200,
                "A carpet has one exit and three entrances, the resource or waste exits",
                                                                INT_MAX,               " Conveyor Belt Out is South by default", 0, .effects = {}},
        {       MS_CROSS,            160, 20,  -1,   -1,  60,  200,
                "The cross has 2 inlets and 2 outlets "
                "which depend on the orientation of the cross", INT_MAX,
                                                                                       " Cross Out is South and West by default",
                                                                                                                                 0, .effects = {}},
        {       MS_RECYCLING_CENTER, 500, 40,  1500, 100, 100, 500,
                "The recycling center has 3 entrances and one exit. The center can store up to 100 "
                "waste",                                                            100,
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
        {       MS_JUNKYARD,         100, 100, 200,  600, 100, 200,
                "The junkyard"
                " has 4 entrances and 0 exits. Can store up to 50 pieces of waste", 50,
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

/*
 * A function to return all the information about a specific type of machine
 */
const MachineInfo *machineInfo_getMachineInfoByType(MachineStuff type) {
    int indexM = 0;
    while (indexM < NUMBER_OF_MACHINES && machine_list[indexM].type != type) { indexM++; }

    if (indexM == NUMBER_OF_MACHINES) {
        return NULL;
    } else {
        return &(machine_list[indexM]);
    }
}

/*
 * A function to get the machine type attribute from a MachineInfo
 */
MachineStuff machineInfo_getType(const MachineInfo *machine) { return machine->type; }

/*
 * A function to get the CostE attribute from a MachineInfo
 */
int machineInfo_getCostE(const MachineInfo *machine) { return machine->costE; }

/*
 * A function to get the CostDD attribute from a MachineInfo
 */
int machineInfo_getCostDD(const MachineInfo *machine) { return machine->costDD; }

/*
 * A function to get the CostUpgradeE attribute from a MachineInfo
 */
int machineInfo_getCostUpgradeE(const MachineInfo *machine) { return machine->costUpgradeE; }

/*
 * A function to get the CostUpgradeDD attribute from a MachineInfo
 */
int machineInfo_getCostUpgradeDD(const MachineInfo *machine) { return machine->costUpgradeDD; }

/*
 * A function to get the CostDestroyE attribute from a MachineInfo
 */
int machineInfo_getCostDestroyE(const MachineInfo *machine) { return machine->costDestroyE; }

/*
 * A function to get the CostDestroyDD attribute from a MachineInfo
 */
int machineInfo_getCostDestroyDD(const MachineInfo *machine) { return machine->costDestroyDD; }

/*
 * A function to get the Description attribute from a MachineInfo
 */
char *machineInfo_getDescription(const MachineInfo *machine) { return machine->description; }

/*
 * A function to get the Capacity attribute from a MachineInfo
 */
int machineInfo_getCapacity(const MachineInfo *machine) { return machine->capacity; }

/*
 * A function to get the CanUpgrade attribute from a MachineInfo
 * in order to know if a specific machine can be upgraded
 */
bool machineInfo_getCanUpgrade(const MachineInfo *machine) { return machine->canUpgrade; }

/*
 * A function to get the Effects type attribute from a MachineInfo
 */
const Effect *machineInfo_getEffects(const MachineInfo *machine) { return &(machine->effects); }

/*
 * A function to get the DefaultOrientationMessage attribute from a machineInfo.
 * It explain to the user on the interface, the default orientation of the machine
 * in order to help him during the machine purchase
 */
char *machineInfo_getDefaultOrientationMessage(const MachineInfo *m) { return m->defaultOrientation; }

/*
 * A function to verify if the id given in argument correspond to a machineInfo
 * If id exist, return the tab index
 * If not -1
 */
int machineInfo_isMachineStuffValid(int id) {
    for (int i = 0; i < NUMBER_OF_MACHINES; ++i) {
        if (id == (int) machine_list[i].type) {
            return i;
        }
    }
    return -1;
}

/*
 * A function to return all the information about a machineInfo according to the id
 */
const MachineInfo *machineInfo_getMachineStuff(int id) {
    int index = machineInfo_isMachineStuffValid(id);
    if (machineInfo_isMachineStuffValid(id) >= 0) {
        return &(machine_list[index]);
    } else {
        return NULL;
    }
}