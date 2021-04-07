#include "../../headers/data/box.h"

struct Box_S {
    int nbResource; //!< number of resource on the machine
    int nbGarbage; //!< number of garbage on the machine
};

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