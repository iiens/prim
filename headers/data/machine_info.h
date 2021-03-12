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

    #include "effect.h" //! effects of the staff and of the machine
    #include <stdbool.h> //! return value
    #include <stdlib.h> //! to use uint

    /*!
     * \typedef MachineInfo
     * \struct MachineInfo_S machine_info.h "headers/data/MachineInfo.h"
     *
     * Struct which contains all information about a machine
     *
     */
    typedef struct MachineInfo_S {
        int type; //!< int which represent the type of the machine
        int costE; //!< price in E of the machine
        int CostDD; //!< price in DD of the machine
        int level; //!< level of upgrade of the machine
        int costUpgradeE; //!< price for upgrade the machine in E
        int costUpgradeDD; //!< price for upgrade the machine in DD
        int costDestroyE; //!< price for destroy the machine in E
        int costDestroyDD; //!< price for destroy the machine in DD;
        char* description; //!< description of the machine
        bool canUpgrade; //!< 1 if it's upgradable, else 0
        Effect effect; //!< An effect for the machine if it's upgrade
    } MachineInfo; //!< Information of the machine,Only machines that have canUpgrade=true can upgrade.
    //!< this value must be checked before applying effect or increase level.

#endif //PRIM_MACHINE_INFO_H
