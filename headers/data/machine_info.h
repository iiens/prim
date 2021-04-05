/*!
 * \file machine_info.h
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 01/03/2021
 * \see machine.h
 *
 * Contains all information about machine
 */
#ifndef PRIM_MACHINE_INFO_H
#define PRIM_MACHINE_INFO_H

    #include <stdbool.h> //! return value
    #include <stdlib.h> //! to use uint
    #include "machine.h"
    #include "effect.h"

    /*!
     * \typedef MachineInfo
     * \struct MachineInfo_S machine_info.h "headers/data/MachineInfo.h"
     *
     * Struct which contains all information about a machine
     *
     * Only machines that have canUpgrade=true can upgrade.
     * This value must be checked before applying effect or increase level.
     */
    typedef struct MachineInfo_S {
        MachineStuff type; //!< int which represent the type of the machine
        int costE; //!< price in E of the machine
        int costDD; //!< price in DD of the machine
        int costUpgradeE; //!< price for upgrade the machine in E
        int costUpgradeDD; //!< price for upgrade the machine in DD
        int costDestroyE; //!< price for destroy the machine in E
        int costDestroyDD; //!< price for destroy the machine in DD;
        char* description; //!< description of the machine
        int capacity; //!< -1 it don't have capacity
        bool canUpgrade; //!< 1 if it's upgradable, else 0
        Effect effects[5]; //!< An effect for the machine if it's upgrade
    } MachineInfo; //!< Information of the machine.

    #define NUMBER_OF_MACHINES 5 //!< name of machines

    extern const MachineInfo machine_list[]; //!< contains information about machines

#endif //PRIM_MACHINE_INFO_H
