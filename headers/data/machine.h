/*!
 * \file machine.h
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 01/03/2021
 * \see MachineInfo.h
 *
 * Contains main information about all of the machine
 */
#ifndef PRIM_MACHINE_H
#define PRIM_MACHINE_H

    #include "machine_stuff.h" //!< a enum of all machine associate with a int
    #include "machine_info.h" //!< all information about machine

    /*!
     * \typedef Machine
     * \struct Machine_S machine.h "headers/data/machine.h"
     * \param type: int, number associate to the type of the machine
     * \param level: uint, Level of improvement of the machine
     *
     * Struct which contains the main information about a machine
     *
     */
    typedef struct Machine_S {
        int type; //!< number associate to the type of the machine
        uint level; //!< Represent the level of improvement of the machine
    } Machine; //!< Machine

    /*!
     * array with information of all machines
     */
    //todo: create and comment
    const MachineInfo machine_list[];

#endif //PRIM_MACHINE_H