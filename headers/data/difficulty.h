/*!
 * \file difficulty.h
 * \author Antoine Man
 * \version 0.1
 * \date 04/03/2021
 * \see interface.h
 * \see map.h
 *
 * Contains all the difficulty that the player can play.
 *
 */
#ifndef PRIM_DIFFICULTY_H
#define PRIM_DIFFICULTY_H

// A constant to know the number of direction
#define NUMBER_DIFFICULTY 3

/*!
 * \typedef Difficulty: rename for enum Difficulty
 * \enum Difficulty difficulty.h "headers/data/difficulty.h"
 * \brief all difficulties
 *
 * Contains all difficulties that the play can play.
 * Difficulties change width and height of the map.
 *
 * EASY level : 10 x 10
 * MEDIUM level : 20 x 20
 * HARD level : 30 x 30
 *
 */
typedef enum Difficulty {
    DIFFICULTY_EASY = 1, //!< EASY level : 10 x 10
    DIFFICULTY_MEDIUM = 2, //!< MEDIUM level : 20 x 20
    DIFFICULTY_HARD = 3, //!< HARD level : 30 x 30
} Difficulty; //!< Difficulty type

Difficulty difficulty_getLVL(int id);

int difficulty_getNumberOfDifficulties();

#endif //PRIM_DIFFICULTY_H
