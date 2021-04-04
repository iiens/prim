/*!
 * \file actions.h
 * \author Quentin Ra
 * \version 0.6
 * \date 10/03/2021
 * \see interface.h
 * \see mapping.h
 *
 * Contains all the actions that the player can choose.
 *
 */
#ifndef PRIM_ACTIONS_H
#define PRIM_ACTIONS_H

    /*!
     * \enum Action_S actions.h "headers/data/action.h"
     * \typedef Action: rename for enum Action
     * \brief action that the user can do
     *
     * Contains all actions and their code (id).
     * Used when asking the user what he wants to do.
     */
    typedef enum Action_S {
        //todo:
        // action to view case content
        // action to rotate a machine ?
        // action to view the list of orientations

        // actions related to the game in general
        ACTION_SHOW_MAP = 143, //!< show map
        ACTION_CANCEL_ACTION = 144, //!< cancel action so go back
        ACTION_EXIT = 145, //!< exit so leave the program
        ACTION_LIST_ACTIONS = 146, //!< list all actions
        ACTION_END_TURN = 147, //!< go to next turn

        // hire
        ACTION_HIRE_FISE = 221, //!< trigger hire fise
        ACTION_HIRE_FISA = 222, //!< trigger hire fisa
        ACTION_CHANGE_FISA_MODE = 223, //!< change fisa production mode

        // actions related to the units
        ACTION_LIST_MACHINES = 331, //!< show list of machines
        ACTION_BUY_MACHINE = 332, //!< trigger add machine
        ACTION_BUY_STAFF = 333, //!< trigger hire Staff
        ACTION_ASK_STAFF_LIST = 334, //!< in hire Staff, show Staff list

        // actions related to the machines
        ACTION_UPGRADE_MACHINE = 514, //!< trigger upgrade machine
        ACTION_DESTROY_MACHINE = 515, //!< trigger destroy machine
    } Action; //!< Action type

#endif //PRIM_ACTIONS_H
