#include <stdio.h>
#include <stdlib.h>

#include "../../headers/data/facade.h" //! to use bool

struct Facade_S {
    Cardinal cardinal; //!< Cardinal that indicates the wall position in the machine
    Direction direction; //!< Direction that indicates the resources flow direction
    Box *content; //!< Bow that contains number of resources and number of garbage
}; //!< Facade that contains all the map information concerning a wall machine

/*
 * Allocate resources in memory to stock the facade
 */
Facade *facade_create(Cardinal card) {
    // Initialize a basic facade
    Facade *facade = (Facade *) malloc(sizeof(Facade));
    facade->direction = DIRECTION_NONE;
    facade->content = NULL;
    facade->cardinal = card;
    return facade;
}

/*
 * A function to free resources allocated in memory to stock the facade
 */
void facade_destroy(Facade *facade) {
    if (facade->content != NULL) {
        free(facade->content);
    }
    free(facade);
}

/*
 * A function to get the facade direction of the transit
 */
Direction facade_getDirection(Facade *facade) { return facade->direction; }

/*
 * A function to set the facade direction according to the new direction
 */
void facade_setDirection(Facade *facade, Direction direction) { facade->direction = direction; }

/*
 * A function to get the facade cardinal
 */
Cardinal facade_getCardinal(Facade *facade) { return facade->cardinal; }

/*
 * A function to set the facade cardinal
 */
void facade_setCardinal(Facade *facade, Cardinal card) { facade->cardinal = card; }

/*
 * A function to get box contained in the facade
 */
Box *facade_getBox(Facade *facade) { return facade->content; }

/*
 * A function to set a new box to the facade
 */
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