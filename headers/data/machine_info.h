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

#include <stdbool.h> //!< todo

/*!
     * \typedef machine_info
     * \struct Machine_Info machine_info.h "headers/data/machine_info.h"
     * \param Type: int, number associate to the type of the machine
     * \param CosttE: uint, price in E of the machine
     * \param CostDD: uint, price in DD of the machine
     * \param Is_Upgrade: boolean, true if the machine had an Upgrade
     * \param CostUpgradeE: uint, price for upgrade the machine in E
     * \param CostUpgradeDD: uint, price for upgrade the machine in DD
     * \param CostDestroyE: uint, price for destroy the machine in DD
     * \param CostDestroyDD: uint, price for destroy the machine in E
     * \param Description: char *, description of the machine
     *
     * Struct which contains all information about a machine
     *
     */
    typedef struct Machine_Info {
        int Type; //!< int which represent the type of the machine
        uint CostE; //!< price in E of the machine
        uint CostDD; //!< price in DD of the machine
        bool Is_Upgrade; //!< true if the machine had an Upgrade
        uint CostUpgradeE; //!< price for upgrade the machine in E
        uint CostUpgradeDD; //!< price for upgrade the machine in DD
        uint CostDestroyE; //!< price for destroy the machine in E
        uint CostDestroyDD; //!< price for destroy the machine in DD;
        char * Description; //!< description of the machine
    } machine_info; //!< todo 

#endif //PRIM_MACHINE_INFO_H
