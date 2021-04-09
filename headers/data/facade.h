//
// Created by mana on 09/04/2021.
//

#ifndef PRIM_FACADE_H
#define PRIM_FACADE_H

    #include "box.h"

// TODO DOC ANTOINE

#define NUMBER_CARDINAL 4
typedef enum Cardinal_S {
    NORTH = 0, //!<
    EAST = 1, //!<
    SOUTH = 2, //!<
    WEST = 3 //!<
} Cardinal; //!<

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

//todo: Antoine documentation
typedef struct Facade_S Facade;

Facade *facade_create();

void facade_destroy(Facade* facade);

Direction  facade_getDirection(Facade* facade);
Box* facade_getBox(Facade* facade);
Cardinal facade_getCardinal(Facade* facade);

void facade_setDirection(Facade*facade, Direction direction);

void facade_setBox(Facade*facade, Box *box);

void facade_setCardinal(Facade*facade, Cardinal card);

#endif //PRIM_FACADE_H
