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

/*!
 * \fn int map_utils_getSizeByDifficulty(Difficulty d)
 * @brief a function to get the map size according to the difficulty
 *
 * This function get this size of the map
 * in order to create the map type
 *
 * @param[in] d a valid difficulty chosen by the user
 * @return int : map size
 * @see Difficulty enum
 */
int map_utils_getSizeByDifficulty(Difficulty d);

#endif //PRIM_DIFFICULTY_H
