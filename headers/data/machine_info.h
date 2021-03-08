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

    /*!
     * \typedef MachineInfo
     * \struct MachineInfo_S machine_info.h "headers/data/MachineInfo.h"
     * \param type: int, number associate to the type of the machine
     * \param costE: uint, price in E of the machine
     * \param costDD: uint, price in DD of the machine
     * \param level: level of upgrade of the machine
     * \param costUpgradeE: uint, price for upgrade the machine in E
     * \param costUpgradeDD: uint, price for upgrade the machine in DD
     * \param costDestroyE: uint, price for destroy the machine in DD
     * \param costDestroyDD: uint, price for destroy the machine in E
     * \param description: char *, description of the machine
     *
     * Struct which contains all information about a machine
     *
     */
    typedef struct MachineInfo_S {
        int type; //!< int which represent the type of the machine
        uint costE; //!< price in E of the machine
        uint CostDD; //!< price in DD of the machine
        int Level; //!< level of upgrade of the machine
        uint costUpgradeE; //!< price for upgrade the machine in E
        uint costUpgradeDD; //!< price for upgrade the machine in DD
        uint costDestroyE; //!< price for destroy the machine in E
        uint costDestroyDD; //!< price for destroy the machine in DD;
        char* description; //!< description of the machine
    } MachineInfo; //!< Information of the machine

#endif //PRIM_MACHINE_INFO_H
