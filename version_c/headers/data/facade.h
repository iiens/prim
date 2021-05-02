/**
 * \file facade.h
 * \author Antoine MAN
 * \version 0.1
 * \date 09/04/2021
 * \see Box
 *
 * This header contains functions related to the interactions with a machine facade.
 * A facade correspond to a machine wall.
 */

#ifndef PRIM_FACADE_H
#define PRIM_FACADE_H

#include "box.h"
#include "../../headers/utils/utils.h"


/**
 * A constant to know the number of direction
 */
#define NUMBER_CARDINAL 4

/*!
* \enum Cardinal_S facade.h "headers/data/facade.h"
* \typedef Cardinal
* \brief the direction
*
* a direction to select each wall of the machine
*
*/
typedef enum Cardinal_S {
    NORTH = 0, //!< up direction
    EAST = 1, //!< right direction
    SOUTH = 2, //!< down direction
    WEST = 3 //!< left direction
} Cardinal;

/*!
* \enum Direction_S facade.h "headers/data/facade.h"
* \typedef Direction
* \brief the direction of the transit
*
* IN it correspond to an entry
* OUT it correspond to an exit
* NONE it's not a enter and not a exit
*
*/
typedef enum Direction_S {
    DIRECTION_IN = 0,
    DIRECTION_OUT = 1,
    DIRECTION_NONE = 2,
} Direction; //!< Direction

/*!
 * \typedef Facade
 * \struct Facade_S facade.h "headers/data/facade.h"
 *
 * Struct that contains all the map information concerning a wall machine
 * Cardinal : to identify the wall of the machine (NORTH, EAST, SOUTH, WEST)
 * Direction : to know if the wall correspond to an entry, to an exit or to nothing
 * Box : it allow to stock resources and garbage
 *
 */
typedef struct Facade_S Facade; //!< documentation above

/**
 * A function to initialize a facade type.
 * @param card
 * @return the facade
 */
Facade *facade_create(Cardinal card);

/**
 * A function to free resources allocated in memory to stock the facade
 * @param facade
 */
void facade_destroy(Facade *facade);

/**
 * A function to get the facade direction of the transit
 * @param facade
 * @return
 */
Direction facade_getDirection(Facade *facade);

/**
 * A function to set the facade direction according to the new direction
 * @param facade
 * @param direction
 */
void facade_setDirection(Facade *facade, Direction direction);

/**
 * A function to get box contained in the facade
 * @param facade
 * @return
 */
Box *facade_getBox(Facade *facade);

/**
 * A function to set a new box to the facade
 * @param facade
 * @param box
 */
void facade_setBox(Facade *facade, Box *box);

/**
 * A function to get the facade cardinal
 * @param facade
 * @return
 */
Cardinal facade_getCardinal(Facade *facade);

/**
 * A function to set the facade cardinal
 * @param facade
 * @param card
 */
void facade_setCardinal(Facade *facade, Cardinal card);

Vector2D cardinal_modifyXYWithCardinal(Cardinal cardinal);

#endif //PRIM_FACADE_H
