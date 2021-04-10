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

//TODO DOC
CaseType case_getType(const Case* c) {
    return c->type & 0xFFFFFFFE;
}

Machine* case_getMachine(const Case* c) {
    if (case_getType(c) == CASE_MACHINE) {
        return (Machine*) c->in;
    } else {
        return NULL;
    }
}

Box* case_getBox(const Case* c) {
    if (case_hasBox(c)) {
        return (Box*) c->in;
    } else {
        return NULL;
    }
}

void case_addMachine(Case* c, Machine* mach) {
    if(case_isEmpty(c) && c->in == NULL) {
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

//TODO DOC
void case_addBox(Case* c, Box* box) {
    if (c->type != CASE_MACHINE && !(case_hasBox(c))) {
        fprintf(stderr, "Case Box add x:%d y:%d\n", c->x, c->y);
        fprintf(stderr, " => Resources %d / Garbage : %d\n", box_getNumberResource(box),
                box_getNumberGarbage(box));
        c->type = c->type | 0x01;
        c->in = box;
    }
}

//TODO DOC
ErrorCode case_deleteBox(Case* c) {
    if (case_hasBox(c)) {
        fprintf(stderr, "Case Box delete x:%d y:%d\n", c->x, c->y);
        free(c->in);
        c->type = c->type & 0xFFFFFFFE;
        c->in = NULL;
    }
    return NO_ERROR;
}

void case_setEmpty(Case* c) {
    if (case_hasBox(c)) {
        free(c->in);
    } else if (case_getType(c) == CASE_MACHINE) {
        machine_destroyMachine((Machine*) c->in);
    }
    c->type = CASE_VIDE;
    c->in = NULL;
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
    return c->type == CASE_VIDE;
}

// TODO DOC
bool case_hasBox(const Case* c){
    return (c->type & 0x01) == 0x01;
}

ErrorCode case_destroy(Case* c) {
    case_setEmpty(c);
    free(c);
    return NO_ERROR;
}