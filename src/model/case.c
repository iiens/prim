#include "../../headers/data/case.h"

#include "stdlib.h"
#include "stdio.h"

struct Case_S {
    int x; //!< int, abscissa
    int y; //!< int, ordinate
    void* in; //!< union, it correspond to the object contained in the case
    CaseType type; //!< type of object contained in the case
}; //!< it correspond to a case of the board game

int case_getX(const Case* c) { return c->x; }

int case_getY(const Case* c) { return c->y; }

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

void case_addBox(Case* c) {
    if (c->type != CASE_MACHINE && !(case_hasBox(c))) {
        if(c->type == CASE_GATE) {
            c->type = CASE_BOX_GATE;
        } else if (c->type == CASE_SOURCE) {
            c->type = CASE_BOX_SOURCE;
        } else {
            c->type = CASE_BOX;
        }
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
        return false;
    } else {
        return true;
    }
}

ErrorCode case_destroy(Case* c) {
    if (case_getType(c) == CASE_MACHINE || case_getType(c) == CASE_BOX ) {
        free(c->in);
    }
    free(c);
    return NO_ERROR;
}