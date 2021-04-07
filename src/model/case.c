#include "../../headers/data/case.h"

#include "stdlib.h"
#include "stdio.h"

struct Box_S {
    int nbResource; //!< number of resource on the machine
    int nbGarbage; //!< number of garbage on the machine
};

struct Case_S {
    int x; //!< int, abscissa
    int y; //!< int, ordinate
    void* in; //!< union, it correspond to the object contained in the case
    CaseType type; //!< type of object contained in the case
}; //!< it correspond to a case of the board game

int case_getX(const Case* c) { return c->x; }

int case_getY(const Case* c) { return c->y; }

int box_getNumberResource(const Box * b) { return b->nbResource; }

int box_getNumberGarbage(const  Box * b) { return b->nbGarbage; }

CaseType case_getType(const Case* c) { return c->type; }

Machine* case_getMachine(const Case* c) {
    if (case_getType(c) == CASE_MACHINE) {
        return (Machine*) c->in;
    } else {
        return NULL;
    }
}

Box* case_getBox(const Case* c) {
    if (case_getType(c) == CASE_BOX) {
        return (Box*) c->in;
    } else {
        return NULL;
    }
}

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

void case_addMachine(Case* c, Machine* mach) {
    if(case_isEmpty(c)) {
        c->type = CASE_MACHINE;
        c->in = mach;
    }
}

void case_addGate(Case* c) {
    if(case_isEmpty(c)) {
        c->type = CASE_GATE;
    }
}
void case_addSource(Case* c) {
    if(case_isEmpty(c)) {
        c->type = CASE_SOURCE;
    }
}

Case* case_create(int x, int y) {
    Case* c = (Case*) malloc(sizeof(Case));
    c->type = CASE_VIDE;
    c->in = NULL;
    c->x = x;
    c->y = y;
    return c;
}

bool case_isEmpty(const Case* c) {
    if (c->type == CASE_VIDE) {
        return true;
    } else {
        return false;
    }
}

bool case_hasBox(const Case* c){
    if (c->in != NULL) {
        return true;
    } else {
        return false;
    }
}

ErrorCode case_destroy(Case* c) {
    if (case_getType(c) == CASE_MACHINE || case_getType(c) == CASE_BOX ) {
        free(c->in);
    }
    free(c);
    return NO_ERROR;
}