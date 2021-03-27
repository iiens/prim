/*!
 * \file map_utils.h
 * \author Antoine Man
 * \version 0.1
 * \date 26/03/2021
 *
 * Contains all utilities functions about map type
 *
 */
#ifndef PRIM_MAP_UTILS_H
#define PRIM_MAP_UTILS_H

    #include "../data/difficulty.h" // contains difficulty type

    /*!
     * \fn int map_utils_getSizeByDifficulty(Difficulty dif)
     * @brief a function to get the map size according to the difficulty
     *
     * This function get this size of the map
     * in order to create the map type
     *
     * @param[in] dif a valid difficulty chosen by the user
     * @return int : map size
     * @see Difficulty enum
     */
    int map_utils_getSizeByDifficulty(Difficulty d){
        switch (d) {
            case DIFFICULTY_EASY:
                return 10;
            case DIFFICULTY_MEDIUM:
                return 20;
            case DIFFICULTY_HARD:
                return 30;
        }
        return -1;
    }

#endif //PRIM_MAP_UTILS_H
