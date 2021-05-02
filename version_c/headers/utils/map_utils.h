/*!
 * \file map_utils.h
 * \author Valentin DREANO
 * \version 0.1
 * \date 26/03/2021
 *
 * Contains all utilities functions about map type
 *
 */
#ifndef PRIM_MAP_UTILS_H
#define PRIM_MAP_UTILS_H

#include "../map.h"
#include "../data/facade.h"
#include "../data/difficulty.h" // contains difficulty type
#include "translation.h"
#include "structures.h"

/**
 * This function was created for the purpose of factorization of the code
 * It allows you to check that you can buy at a certain price and if so to debit the sub
 *
 * @param m La Map with current game information
 * @param costE The price in E
 * @param costDD The price in DD
 * @return An error code allowing to know if we succeeded or what is missing
 */
ErrorCode map_utils_tryBuy(Map *m, int costE, int costDD);

/**
 * This function is used to generalize and factorize code
 * It is used to apply the modifications of a staff on a price or a quantity
 *
 * @param mode Allows you to know what the staff acts on
 * @param target Allows you to know what the staff acts on
 * @param m Map with current game information
 * @param numberE Price
 * @param numberDD Price
 */
void map_utils_checkModificationStaff(Mode mode, Target target, Map* m, int* numberE, int* numberDD);

/**
 * Allows you to send resources to the door
 *
 * @param m Map with current game information
 * @param resources Number of resources
 */
void map_utils_sendResourcesToGate(Map *m, int resources);

/**
 * Produce DD and E by fise
 *
 * @param m Map with current game information
 */
void map_utils_productionFise(Map *m);

/**
 * Produce DD or E by fisa
 *
 * @param m Map with current game information
 */
void map_utils_productionFisa(Map *m);

/**
 * Allows you to move resources on crosses and mats
 *
 * @param m Map with current game information
 */
void map_utils_moveResources(Map * m);

/**
 * Allows to generate resources
 *
 * @param m Map with current game information
 */
void map_utils_generateResources(Map * m);

/**
 * Allows you to generate waste at the door
 *
 * @param m Map with current game information
 */
void map_utils_generateGarbage(Map *m);

/**
 * Allows you to activate recycling centers
 *
 * @param m Map with current game information
 */
void map_utils_activateRecyclingCenters(Map* m);

/**
 * Allows you to activate collectors
 *
 * @param m Map with current game information
 */
void map_utils_activateCollectors(Map* m);

/**
 * Allows you to delete all uncollected resources and bring all ground trash to the door
 *
 * @param m Map with current game information
 */
void map_utils_resetResourcesGarbage(Map * m);

/**
 * This function allows you to move all the resources on the facades out of the machines.
 * It is called at the end of the turn and ensures that at the end of each turn and
 * at the start of each turn that all waste and resources are on the facades out
 *
 * @param m Map with current game information
 */
void map_utils_moveResourcesInMachine(Map *m);

/**
 * His function allows the staff to take action Anne Laure Ligozat
 *
 * @param m Map with current game information
 * @param idStaff Staff Id
 * @return A ErrorCode to know if everything went well or not
 */
ErrorCode staff_actionAnneLaureLigozat(Map* m, int idStaff);

/**
 * His function allows the staff to take action Christophe Mouilleron
 *
 * @param m Map with current game information
 * @param idStaff Staff Id
 * @return A ErrorCode to know if everything went well or not
 */
ErrorCode staff_actionChristopheMouilleron(Map* m, int idStaff);

/**
 * His function allows the staff to take action Laurent Prevel
 *
 * @param m Map with current game information
 * @param idStaff Staff Id
 * @return A ErrorCode to know if everything went well or not
 */
ErrorCode staff_actionLaurentPrevel(Map* m, int idStaff);

#endif //PRIM_MAP_UTILS_H
