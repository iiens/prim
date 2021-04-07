#ifndef PRIM_MAIN_H
#define PRIM_MAIN_H

#include "../headers/interface.h" //!< contains actions
#include "../headers/data/effect.h"

bool back = false; //!< Allow to cancel the current action

/*!
 * This array length is predetermined by {@link USER_MAPPING_SIZE}
 * constant in interface.h.
 *
 * BEWARE ! Theses values cannot be changed easily, for now, since
 * they are used in the translation. Also, since it's hard (for now) to get
 * the key for ACTION_CANCEL_ACTION, there is a constant in some file that
 * need to be changed if this value is changed (but since this value mustn't change
 * for now, it's useless to know witch file).
 */
const UserActionMapping user_mapping[] = {
        // actions related to the game in general
        {ACTION_SHOW_MAP,         "s"}, //!< show map with s
        {ACTION_END_TURN,         "n"}, //!< end turn with n
        {ACTION_CANCEL_ACTION,    "b"}, //!< cancel action with b
        {ACTION_LIST_ACTIONS,     "help"}, //!< list actions with help
        {ACTION_EXIT,             "q"}, //!< exit with q

        // hire
        {ACTION_HIRE_FISE,        "he"}, //!< hire FISE with he
        {ACTION_HIRE_FISA,        "ha"}, //!< hire FISA with ha
        {ACTION_CHANGE_FISA_MODE, "cm"}, //!< change mode with cm

        // actions related to the units
        {ACTION_LIST_MACHINES,    "lm"}, //!< list machines with lm
        {ACTION_BUY_MACHINE,      "bm"}, //!< buy machine with bm
        {ACTION_BUY_STAFF,        "bs"}, //!< hire Staff with bs
        {ACTION_ASK_STAFF_LIST,   "ls"}, //!< list Staff with ls

        // actions related to the machines
        {ACTION_UPGRADE_MACHINE,  "upm"}, //!< upgrade machine with upm
        {ACTION_DESTROY_MACHINE,  "dm"}, //!< destroy machine with dm
}; //!< array of all the mappings

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



