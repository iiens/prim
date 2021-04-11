#include "../../headers/data/box.h"

#include "stdio.h"
#include "stdlib.h"

struct Box_S {
    int nbResource; //!< number of resource on the machine
    int nbGarbage; //!< number of garbage on the machine
}; //!< todo: comment here

int box_getNumberResource(const Box * b) { return b->nbResource; }

int box_getNumberGarbage(const  Box * b) { return b->nbGarbage; }

ErrorCode box_setNumberResource(Box * b, int val ) {
    if (box_getNumberResource(b) + val >= 0) {
        b->nbResource += val;
        return NO_ERROR;
    } else {
        return ERROR_NEGATIVE_RESULT;
    }
}

ErrorCode box_setNumberGarbage(Box* b, int val ) {
    if (box_getNumberGarbage(b) + val >= 0) {
        b->nbGarbage += val;
        return NO_ERROR;
    } else {
        return ERROR_NEGATIVE_RESULT;
    }
}

Box* box_create(int numberR, int numberG) {
    Box *box = (Box*)malloc(sizeof (Box));
    box->nbResource = numberR;
    box->nbGarbage = numberG;
    return box;
}

//todo: you may use Box instead of B
void box_addB2toB1(Box *b1, Box *b2) {
    if (b1 != NULL && b2 != NULL) {
        box_setNumberResource(b1, box_getNumberResource(b2));
        box_setNumberGarbage(b1, box_getNumberGarbage(b2));
    }
}