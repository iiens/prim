/*!
 * \file machine.h
 * \author Ramzy ZEBRIR and Antoine MAN
 * \version 0.1
 * \date 01/03/2021
 * \see machine_info.h
 *
 * Contains main information about all of the machine
 */

#ifndef PRIM_MACHINE_H
#define PRIM_MACHINE_H

#include <stdlib.h> //! to use uint
#include "error.h" //! to return error message
#include "stdbool.h" //! to use bool
#include "box.h"
#include "facade.h"
#include "../utils/const.h"

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

/*!
 * \typedef Machine
 * \struct Machine_S machine.h "headers/data/machine.h"
 *
 * Struct which contains the main information about a machine
 *
 */
typedef struct Machine_S Machine;

/**
 * function to get the type of the machine
 * @param machine
 * @return the type of the machine
 */
MachineStuff machine_getType(const Machine *machine);

/**
 * function to get the level of the machine
 * @param machine
 * @return the level of the machine
 */
int machine_getLevel(const Machine *machine);

/*!
 * @brief a function to get a default orientation for a machine
 * @param[in] s a type machine
 *
 * This fonction get D:
 * MS_COLLECTOR = 1, collector machine
 * <pre>
 *      None
 *  None x None
 *      Out
 * </pre>
 *
 * MS_CONVEYOR_BELT = 2, conveyor belt
 * <pre>
 *      In
 *   In x In
 *     Out
 * </pre>
 *
 *
 * MS_CROSS = 3, cross
 * <pre>
 *      In
 *  Out x In
 *     Out
 * </pre>
 *
 * MS_RECYCLING_CENTER = 4, recycling center
 * <pre>
 *      In
 *   In x In
 *     Out
 * </pre>
 *
 * MS_JUNKYARD = 5, junkyard
 * <pre>
 *      In
 *   In x In
 *     In
 * </pre>
 * @return a default orientation for a machine
 */
Facade **facade_defaultFacade(MachineStuff s);

/**
 * Function to create a new machine according to the type machine given
 * @param type MachineStuff
 * @return a new machine
 */
Machine *machine_create(MachineStuff type);

/**
 * A function to free allocated resources in memory in order to stock a machine
 * @param mach
 * @return an error code to know what happened
 */
ErrorCode machine_destroyMachine(Machine *mach);

/**
 * This function rotate the orientation of a machine in clockwise
 * The int rotation can be a negative value.
 * @param machine
 * @param rotation
 */
void machine_rotateMachine(Machine *machine, int rotation);

/**
 * This function upgrade a machine by incrementing his level
 * @param m machine
 */
void machine_incrementLevel(Machine *m);

/**
 * A function to know if the direction given in argument is equals to
 * the north direction of the machine
 * @param mach
 * @param d
 * @return true if equals, if not false
 */
bool machine_isOrientationTop(const Machine *mach, Direction d);

/**
 * A function to know if the direction given in argument is equals to
 * the north direction and the east direction of the machine
 * @param mach
 * @param d
 * @return true if equals, if not false
 */
bool machine_isOrientationTopRight(const Machine *mach, Direction d);

/**
 * A function to know if the direction given in argument is equals to
 * the east direction of the machine
 * @param mach
 * @param d
 * @return true if equals, if not false
 */
bool machine_isOrientationRight(const Machine *mach, Direction d);

/**
 * A function to know if the direction given in argument is equals to
 * the east direction and the south direction of the machine
 * @param mach
 * @param d
 * @return true if equals, if not false
 */
bool machine_isOrientationBottomRight(const Machine *mach, Direction d);

/**
 * A function to know if the direction given in argument is equals to
 * the south direction of the machine
 * @param mach
 * @param d
 * @return true if equals, if not false
 */
bool machine_isOrientationBottom(const Machine *mach, Direction d);

/**
 * A function to know if the direction given in argument is equals to
 * the south direction and the left direction of the machine
 * @param mach
 * @param d
 * @return true if equals, if not false
 */
bool machine_isOrientationBottomLeft(const Machine *mach, Direction d);

/**
 * A function to know if the direction given in argument is equals to
 * the left direction of the machine
 * @param mach
 * @param d
 * @return true if equals, if not false
 */
bool machine_isOrientationLeft(const Machine *mach, Direction d);

/**
 * A function to know if the direction given in argument is equals to
 * the north direction and the left direction of the machine
 * @param mach
 * @param d
 * @return true if equals, if not false
 */
bool machine_isOrientationTopLeft(const Machine *mach, Direction d);

/**
 * A function to know if the number of rotation is correct
 * Between 0 and NUMBER_CARDINAL(4)
 * @param rotation
 * @return true if yes, if not false
 */
bool machine_isRotationCorrect(int rotation);

/**
 * A function to get the direction of a facade machine according to the cardinal
 * @param machine
 * @param card
 * @return Direction of the facade machine (IN, OUT, NONE)
 */
Direction machine_getDirection(const Machine *machine, Cardinal card);

/**
 * A function to get a box of a facade machine according to the cardinal
 * @param machine
 * @param card
 * @return box of the facade machine
 */
Box *machine_getBox(const Machine *machine, Cardinal card);

/**
 * A function to add a box to the facade machine according to the cardinal
 * @param machine
 * @param card
 * @param box
 */
void machine_addBox(Machine *machine, Cardinal card, Box *box);

/**
 * A function to destroy a box of the facade machine according to the cardinal
 * @param machine
 * @param card
 */
void machine_destroyBox(Machine *machine, Cardinal card);

#endif //PRIM_MACHINE_H
