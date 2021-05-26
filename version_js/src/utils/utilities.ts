/**
 * \file utils.h
 * \author Quentin Ra
 * \version 1.0
 * \date 27/02/2021
 *
 * Contains all utilities functions
 *
 */

/**
 * @brief name of struct Vector2D to Vector2D
 *
 * Convenience type for (x,y)
 * with `x = x axis` and `y = y axis`.
 * In a map (matrix ij), it means
 * that `y = i = row` and `x = j = column`
 *
 */
export class Vector2D {
    public readonly x: number;  //!< x axis
    public readonly y: number; //!< y axis

    constructor(x: number, y: number) {
        this.x = x;
        this.y = y;
    }
}

export function randomNumber(min: number, max: number) : number {
    return Number(Math.floor(Math.random() * (max - min + 1) + min));
}

export function getRandomInt(max: number) {
    return Number(Math.floor(Math.random() * max));
}