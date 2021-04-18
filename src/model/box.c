/*!
 * \file box.c
 * \author Antoine Man
 * \version 0.6
 * \date 07/04/2021
 *
 * Resources and garbage are stocked in a box in order
 * to facilitate resources moves
 * \see error.h
 *
 */

#include "../../headers/data/box.h"
#include "stdio.h"
#include "stdlib.h"

struct Box_S {
    int nbResource; //!< nbResource : number of resource on the machine
    int nbGarbage; //!< nbGarbage : number of garbage on the machine
}; //!< It contain resources and garbage on a case

/*
 * This function get the number of resources of the box.
 */
int box_getNumberResource(const Box *b) { return b->nbResource; }

/*
 * This function set the number of resources of the box
 */
ErrorCode box_setNumberResource(Box *b, int val) {

    // Verify if the result of the addition/substract is not negative
    if (box_getNumberResource(b) + val >= 0) {

        // Set number resources of the box
        b->nbResource += val;
        return NO_ERROR;
    } else {
        return ERROR_NEGATIVE_RESULT;
    }
}

/*
 * This function get the number of garbage of the box.
 */
int box_getNumberGarbage(const Box *b) { return b->nbGarbage; }

/*
 * This function set the number of garbage of the box.
 */
ErrorCode box_setNumberGarbage(Box *b, int val) {

    // Verify if the result of the addition/substract is not negative
    if (box_getNumberGarbage(b) + val >= 0) {

        // Set number garbage of the box
        b->nbGarbage += val;
        return NO_ERROR;
    } else {
        return ERROR_NEGATIVE_RESULT;
    }
}

/*
 * This function create a new box in a case or in a facade machine
 */
Box *box_create(unsigned int numberR, unsigned int numberG) {

    // Allocate resources in memory to create a new box
    Box *box = (Box *) malloc(sizeof(Box));
    box->nbResource = numberR;
    box->nbGarbage = numberG;
    return box;
}

/*
 * This function add resources and garbage of the first box in the second
 */
void box_addB2toB1(Box *box1, Box *box2) {
    if (box1 != NULL && box2 != NULL) {

        // We move box2 resources and garbage in the first box
        box_setNumberResource(box1, box_getNumberResource(box2));
        box_setNumberGarbage(box1, box_getNumberGarbage(box2));
    }
}

/*
 * This function free resources allocated in memory used to stock the box
 */
void box_destroy(Box *b) { free(b); }