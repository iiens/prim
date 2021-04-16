/*!
 * \file box.h
 * \author Antoine Man
 * \version 0.6
 * \date 07/04/2021
 *
 * Resources and garbage are stocked in a box in order
 * to facilitate resources moves
 * \see error.h
 *
 */
#ifndef PRIM_BOX_H
#define PRIM_BOX_H

#include "error.h"

/**
 * \typedef Box
 * \struct Box_S box.h "headers/data/box.h"
 *
 * Struct that contains all the information concerning a box
 * It contain resources and garbage on a case
 */
typedef struct Box_S Box;

/**
 * This function get the number of resources of the box.
 * @param c, a box
 * @return the number of resources available in the box
 */
int box_getNumberResource(const Box *c);

/**
 * This function set the number of resources of the box
 * The value can be a negative value
 * @param c, a box
 * @param val, an int
 * @return
 */
ErrorCode box_setNumberResource(Box *c, int val);

/**
 * This function get the number of garbage of the box.
 * @param c, a box
 * @return the number of garbage available in the box
 */
int box_getNumberGarbage(const Box *c);

/**
 * This function set the number of garbage of the box.
 * The value can be a negative value
 * @param c, a box
 * @param val, an int
 * @return an error that specify what is the problem
 */
ErrorCode box_setNumberGarbage(Box *c, int val);

/**
 * This function create a new box in a case or in a facade machine
 * The number of resources and garbage are given in argument
 * @param numberR, resources number
 * @param numberG, garbage number
 * @return a new box
 */
Box *box_create(int numberR, int numberG);

/**
 * This function add resources and garbage of the first box in the second
 * @param b1, first box
 * @param b2, second box
 */
void box_addB2toB1(Box *b1, Box *b2);

/**
 * This function free resources allocated in memory used to stock the box
 * @param b, a box
 */
void box_destroy(Box *b);

#endif //PRIM_BOX_H
