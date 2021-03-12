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

    #include "machine_stuff.h" //! a enum of all machine associate with a int
    #include "machine_info.h" //! all information about machine

    /*!
     * \typedef Machine
     * \struct Machine_S machine.h "headers/data/machine.h"
     *
     * Struct which contains the main information about a machine
     *
     */
     //todo: missing attributes
    typedef struct Machine_S {
        int type; //!< number associate to the type of the machine
        uint level; //!< Represent the level of improvement of the machine
    } Machine; //!< Machine

    //todo: Ramzy add a constant with machine_list size ? (since we are in C)

    const MachineInfo machine_list[] = {
        {MS_COLLECTOR,200,20,1,500,200,60,200,
         "The collector sends a resource produced by the source to the "
         "neighboring cell indicated by its orientation. It must be placed "
         "on a square adjacent to that of the source",
         1
         },
        {MS_CONVEYOR_BELT,60,20,1,-1,-1,60,200,
         "A carpet has one exit and three entrances, the resource or waste exits"
         " 1 turn after entering the conveyor belt",
         0
         },
        {MS_CROSS,160,20,1,-1,-1,60,200,
         "A cross is a set of two juxtaposed conveyor belts, allowing two "
         "lines of conveyor belts to cross. The cross has 2 inlets and 2 outlets "
         "which depend on the orientation of the cross",
         0
         },
        {MS_RECYCLING_CENTER,500,40,1,1500,100,100,500,
         "The recycling center is used to store waste. The recycling center"
         " has 4 entrances and 0 exits. At the start of the game, a recycling "
         "center can store up to 50 pieces of waste",
         1
         },
        {MS_JUNKYARD,100,100,1,200,600,100,200,
         "The recycling center turns waste into a resource. Like the conveyor belt,"
         " the center has 3 entrances and one exit. The center can store up to 100 "
         "waste",
         1
         },
    }; //!< Array with information about all machine

#endif //PRIM_MACHINE_H