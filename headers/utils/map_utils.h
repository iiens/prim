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
#include "structures.h"
#include "../data/facade.h"

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
ErrorCode map_utils_tryBuy(Map *m, int costE, int costDD);

/**
 *
 * @param mode
 * @param target
 * @param m
 * @param numberE
 * @param numberDD
 */
void map_utils_checkModifyCost(Mode mode, Target target, Map* m, int* numberE, int* numberDD);

/**
 *
 * @param m
 * @param resources
 */
void map_utils_sendResourcesToGate(Map *m, int resources);

/**
 *
 * @param m
 */
void map_utils_productionFise(Map *m);

/**
 *
 * @param m
 */
void map_utils_productionFisa(Map *m);

/**
 * Permet de géné des ressources grâce aux sources
 *
 * @param listResources
 */
void map_utils_generateResources(Map * m);

/**
 * Permet de faire fonctionner les Tapis
 * Attention à ne déplacer les ressources que d'une case
 *
 * @param listResources
 */
void map_utils_moveResources(Map * m);

/**
 *
 * @param m
 */
void map_utils_activateRecyclingCenters(Map* m);

/**
 *
 * @param m
 */
void map_utils_activateCollectors(Map* m);

/**
 * Détruit toutes les ressources non collecté à la fin d'un tour
 *  check :
 *      - sources
 *      - décheterie
 *
 * @param listSources
 */
void map_utils_resetResourcesGarbage(Map * m);

/**
 * Permet de transformer tous les ressources emmené à la porte en déchets
 *
 * @param m
 * @param resources
 * @return
 */
ErrorCode map_utils_generateGarbage(Map *m);

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
