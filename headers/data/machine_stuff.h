/*!
 * \file machine_stuff.h
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 08/03/2021
 *
 * \see machine.h
 *
 * Link between a machine and a int to recognize them
 *
 */


#ifndef PRIM_MACHINE_STUFF_H
#define PRIM_MACHINE_STUFF_H

    /*!
    * \enum MachineStuff_S machine_stuff.h "headers/data/machine_stuff.h"
    * \typedef MachineStuff
    * \brief Id associate to the machine to identify them
    *
    * Contains id associate to the machine.
    *
    */
    typedef enum MachineStuff_S {
        COLLECTOR_MACHINE = 1, //!< collector machine
        CONVEYOR_BELT = 2, //!< conveyor belt
        CROSS = 3, //!< cross
        JUNKYARD = 4, //!< junkyard
        RECYCLING_CENTER = 5, //!< recycling center

    } MachineStuff; //!< MachineStuff


#endif //PRIM_MACHINE_STUFF_H
