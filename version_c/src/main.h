#ifndef PRIM_MAIN_H
#define PRIM_MAIN_H

#include "../headers/interface.h" //!< contains actions
#include "../headers/data/effect.h"
#include "../headers/map.h"

bool back = false; //!< Allow to cancel the current action

/**
 * @brief This function is used to initialize a game.
 * It therefore calls the necessary functions to start the interface and to create a map.
 *
 * @return The starting map for a game
 */
Map* main_initGame();

/**
 * @brief This function processes actions
 *
 * @param act : action that was requested by the user
 * @param map : map of the current game
 * @param exit : This parameter allows to specify to the caller if the player to decide to quit
 * @return a boolean to specify the end of turn
 */
bool main_handlingActions(Action act, Map* map, bool* exit);

/**
 * @brief This function is used to process the action ACTION_BUY_MACHINE
 *
 * @param map : map of the current game
 */
void main_buyMachineAction(Map* map);

/**
 * @brief This function is used to process the action ACTION_BUY_STAFF
 *
 * @param map : map of the current game
 */
void main_buyStaffAction(Map* map);

/**
 * @brief This function is used to process the action ACTION_UPGRADE_MACHINE
 *
 * @param map : map of the current game
 */
void main_upgradeMachineAction(Map* map);

/**
 * @brief This function is used to process the action
 *
 * @param map : map of the current game ACTION_DESTROY_MACHINE
 */
void main_destroyMachineAction(Map* map);

#endif //PRIM_MAIN_H



