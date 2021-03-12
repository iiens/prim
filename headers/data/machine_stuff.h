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

    //todo: Ramzy, maybe you should move this to machine.h (or not if you don't want to)

    /*!
    * \enum MachineStuff_S machine_stuff.h "headers/data/machine_stuff.h"
    * \typedef MachineStuff
    * \brief id associate to the machine to identify them
    *
    * Contains id associate to the machine.
    *
    */

    typedef enum MachineStuff_S {
        MS_COLLECTOR = 1, //!< collector machine
        MS_CONVEYOR_BELT = 2, //!< conveyor belt
        MS_CROSS = 3, //!< cross
        MS_RECYCLING_CENTER = 4, //!< recycling center
        MS_JUNKYARD = 5, //!< junkyard
    } MachineStuff; //!< MachineStuff

#endif //PRIM_MACHINE_STUFF_H
