#include <stdio.h>
#include <stdlib.h>

#include "../../headers/data/facade.h" //! to use bool

struct Facade_S {
    Cardinal cardinal;
    Direction direction;
    Box *content;
}; //!< Facade

Facade *facade_create(Cardinal card) {
    Facade *facade = (Facade *) malloc(sizeof(Facade));
    facade->direction = DIRECTION_NONE;
    facade->content = NULL;
    facade->cardinal = card;
    return facade;
}

void facade_destroy(Facade *facade) {
    if (facade->content != NULL) {
        free(facade->content);
    }
    free(facade);
}

//TODO ANTOINE DOC
Direction facade_getDirection(Facade *facade) { return facade->direction; }

Cardinal facade_getCardinal(Facade *facade) { return facade->cardinal; }

Box *facade_getBox(Facade *facade) { return facade->content; }

void facade_setDirection(Facade *facade, Direction direction) {
    facade->direction = direction;
}

void facade_setBox(Facade *facade, Box *box) { facade->content = box; }

void facade_setCardinal(Facade*facade, Cardinal card) { facade->cardinal = card; }