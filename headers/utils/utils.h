/*!
 * \file utils.h
 * \author Quentin Ra
 * \version 0.1
 * \date 27/02/2021
 *
 * Contains all utilities functions
 *
 */
#ifndef PRIM_UTILS_H
#define PRIM_UTILS_H

/*!
 * @typedef Vector2D: name of struct Vector2D to Vector2D
 * @struct Vector2D_S utils.h "headers/utils/utils.h"
 *
 * Convenience type for (x,y)
 * with `x = x axis` and `y = y axis`.
 * In a map (matrix ij), it means
 * that `y = i = row` and `x = j = column`
 *
 */
typedef struct Vector2D_S {
    int x; //!< x axis
    int y; //!< y axis
} Vector2D; //!< Vector2D type

#define max( a, b ) \
    ({ __typeof__ (a) _a = (a); \
     __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; }) //!< return the max between two numbers

#define min( a, b ) \
    ({ __typeof__ (a) _a = (a); \
     __typeof__ (b) _b = (b); \
    _a > _b ? _b : _a; }) //!< return the min between two numbers

#endif //PRIM_UTILS_H
