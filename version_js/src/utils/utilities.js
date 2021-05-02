"use strict";
/**
 * \file utils.h
 * \author Quentin Ra
 * \version 1.0
 * \date 27/02/2021
 *
 * Contains all utilities functions
 *
 */
Object.defineProperty(exports, "__esModule", { value: true });
exports.randomNumber = exports.Vector2D = void 0;
/**
 * @brief name of struct Vector2D to Vector2D
 *
 * Convenience type for (x,y)
 * with `x = x axis` and `y = y axis`.
 * In a map (matrix ij), it means
 * that `y = i = row` and `x = j = column`
 *
 */
class Vector2D {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
}
exports.Vector2D = Vector2D;
function randomNumber(min, max) {
    return Number(Math.floor(Math.random() * (max - min + 1) + min));
}
exports.randomNumber = randomNumber;
