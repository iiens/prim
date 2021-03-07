/*!
 * \file machine.h
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 01/03/2021
 * \see machine_info.h
 *
 * Contains main information about all of the machine
 */
#ifndef PRIM_MACHINE_H
#define PRIM_MACHINE_H

    //todo: translate
    #define MACHINE_COLLECTEUR 1 //!< todo
    #define TAPIS_ROULANT 2 //!< todo
    #define CROIX 3 //!< todo
    #define DECHETTERIE 4 //!< todo
    #define CENTRE_RECYCLAGE 5 //!< todo 

    #include "machine_info.h" //!< all information about machine
    /*!
     * \typedef machine
     * \struct Machine machine.h "headers/data/machine.h"
     * \param Type: int, number associate to the type of the machine
     * \param Level: uint, Level of improvement of the machine
     *
     * Struct which contains the main information about a machine
     *
     */
    typedef struct Machine {
        int Type; //!< number associate to the type of the machine
        uint Level; //!< Represent the level of improvement of the machine
    } machine; //!< todo

    /*!
     * array with information of all machines
     */
    //todo: create and comment
    const machine_info machine_list [];

#endif //PRIM_MACHINE_H