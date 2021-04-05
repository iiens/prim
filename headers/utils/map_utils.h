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
#include "translation.h"
#include "../map.h"

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

// TODO Valentin ; faire documentation
/**
 *
 * @param m
 * @param costE
 * @param costDD
 * @return
 */
ErrorCode map_tryBuy(Map *m, int costE, int costDD);

/**
 *
 * @param m
 */
void productionFise(Map *m);

/**
 *
 * @param m
 */
void productionFisa(Map *m);

/**
 *
 * @param m
 * @return
 */
ErrorCode staff_actionAnneLaureLigozat(Map* m, int idStaff);

/**
 *
 * @param m
 * @return
 */
ErrorCode staff_actionChristopheMouilleron(Map* m, int idStaff);

/**
 *
 * @param m
 * @return
 */
ErrorCode staff_actionLaurentPrevel(Map* m, int idStaff);

#endif //PRIM_MAP_UTILS_H
