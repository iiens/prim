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

    #include <stdlib.h> //! to use uint

    /*!
     * \enum MachineStuff_S machine.h "headers/data/machine.h"
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
    } MachineStuff; //!< Link between a machine and a int to recognize them

    #include "effect.h" //! contains effects
    #include "machine_info.h" //! all information about machine

    /*!
     * \enum Direction_S machine.h "headers/data/machine.h"
     * \typedef Direction
     * \brief IN if it's the direction of the transit, else out, none if it's not a enter and not a exit
     *
     * Contains id associate to the machine.
     *
     */
    typedef enum Direction_S {
        DIRECTION_IN = 0,
        DIRECTION_OUT = 1,
        DIRECTION_NONE = 2,
    } Direction; //!< Direction

    /*!
     * \typedef Orientation
     * \struct Orientation_S machine.h "headers/data/machine.h"
     *
     * Struct which contains the 4 direction possible for a machine
     *
     */
    typedef struct Orientation_S {
        Direction top; //!< top
        Direction left; //!< left
        Direction bottom; //!< bottom
        Direction right; //!< right
    } Orientation; //!< Orientation

    /*!
     * \typedef Machine
     * \struct Machine_S machine.h "headers/data/machine.h"
     *
     * Struct which contains the main information about a machine
     *
     */
    typedef struct Machine_S {
        MachineStuff type; //!< number associate to the type of the machine
        int level; //!< Represent the level of improvement of the machine
        Orientation orientation; //!< Represent the orientation of the machine
        int capacity; //!< -1 it don't have capacity
    } Machine; //!< Machine

    #define NUMBER_OF_MACHINES 5 //!< todo: Ramzy comment

    extern const MachineInfo machine_list[]; //!< todo: Ramzy comment

#endif //PRIM_MACHINE_H