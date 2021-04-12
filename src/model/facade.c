#include <stdio.h>
#include <stdlib.h>

#include "../../headers/data/facade.h" //! to use bool

//todo: laking comment
struct Facade_S {
    Cardinal cardinal;
    Direction direction;
    Box *content;
}; //!< Facade todo: write a little more

Facade *facade_create(Cardinal card) {
    // Allocate resources in memory to stock the facade
    // Initialize a basic facade
    Facade *facade = (Facade *) malloc(sizeof(Facade));
    facade->direction = DIRECTION_NONE;
    facade->content = NULL;
    facade->cardinal = card;
    return facade;
}

void facade_destroy(Facade *facade) {
    // Free resources allocated in memory
    if (facade->content != NULL) {
        free(facade->content);
    }
    free(facade);
}

//todo: too much methods without a "comment"
// please use a method block comment
// such as
// /*
// * these methods are used for ...
// */
// then some methods again and again. To split since it's unreadable :-(

Direction facade_getDirection(Facade *facade) { return facade->direction; }

void facade_setDirection(Facade *facade, Direction direction) { facade->direction = direction; }

Cardinal facade_getCardinal(Facade *facade) { return facade->cardinal; }

void facade_setCardinal(Facade *facade, Cardinal card) { facade->cardinal = card; }

Box *facade_getBox(Facade *facade) { return facade->content; }

void facade_setBox(Facade *facade, Box *box) { facade->content = box; }

/**
 * Allows in relation to a cardinal to return the modifications to be made on the coordinates
 *
 * @param cardinal
 * @return Vector2D
 */
Vector2D cardinal_modifyXYWithCardinal(Cardinal cardinal) {
    switch (cardinal) {
        case NORTH:
            return (Vector2D) {.x = 0, .y = -1};
        case EAST:
            return (Vector2D) {.x = 1, .y = 0};
        case SOUTH:
            return (Vector2D) {.x = 0, .y = +1};
        case WEST:
            return (Vector2D) {.x = -1, .y = 0};
        default:
            return (Vector2D) {.x = 0, .y = 0};
    }
}