#include "../../headers/data/case.h"

#include "stdlib.h"
#include "stdio.h"

struct Case_S {
    int x; //!< int, abscissa
    int y; //!< int, ordinate
    union {
        Machine* mach;
        void* other;
    } in; //!< union, it correspond to the object contained in the case
    CaseType type; //!< type of object contained in the case
    int nbResource; //!< number of resource on the machine
    int nbGarbage; //!< number of garbage on the machine
}; //!< it correspond to a case of the board game

int case_getX(const Case* c) { return c->x; }

int case_getY(const Case* c) { return c->y; }

int case_getNumberResource(const Case* c) { return c->nbResource; }

int case_getNumberGarbage(const Case* c) { return c->nbGarbage; }

CaseType case_getType(const Case* c) { return c->type; }

Machine* case_getMachine(const Case* c) {
    if (case_getType(c) == CASE_MACHINE) {
        return c->in.mach;
    } else {
        return NULL;
    }
}

ErrorCode case_setNumberResource(Case* c, int val ) {
    if (case_getNumberResource(c) + val >= 0) {
        c->nbResource += val;
        return NO_ERROR;
    } else {
        return ERROR_NEGATIVE_RESULT;
    }
}

ErrorCode case_setNumberGarbage(Case* c, int val ) {
    if (case_getNumberGarbage(c) + val >= 0) {
        c->nbGarbage += val;
        return NO_ERROR;
    } else {
        return ERROR_NEGATIVE_RESULT;
    }
}

void case_addMachine(Case* c, Machine* mach) {
    if(case_isEmpty(c)) {
        c->type = CASE_MACHINE;
        c->in.mach = mach;
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
    c->nbResource = 0;
    c->nbGarbage = 0;
    c->type = CASE_VIDE;
    c->in.other = NULL;
    c->in.mach = NULL;
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

ErrorCode case_destroy(Case* c) {
    if (case_getType(c) == CASE_MACHINE) {
        free(c->in.mach);
    }
    free(c);
    return NO_ERROR;
}