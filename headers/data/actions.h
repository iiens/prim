/***
 * @file actions.h
 * @package headers/data
 *
 * Contains all the actions that the player can choose.
 *
 * @see interface.h
 * @see keys.h
 */
#ifndef PRIM_ACTIONS_H
#define PRIM_ACTIONS_H

    /***
     * @enum
     * Contains all actions and their code (id).
     * Used when asking the user what he wants to do.
     */
    typedef enum Action {
        //!< actions related to the game in general
        ACTION_SHOW_MAP = 143, //!< show map
        ACTION_CANCEL_ACTION = 144, //!< cancel action so go back
        ACTION_EXIT = 145, //!< exit so leave the program
        ACTION_END_TURN = 146, //!< go to next turn

        //!< hire
        ACTION_HIRE_FISE = 221, //!< trigger hire fise
        ACTION_HIRE_FISA = 222, //!< trigger hire fisa

        //!< actions related to the units
        ACTION_BUY_MACHINE = 332, //!< trigger add machine
        ACTION_BUY_STAFF = 333, //!< trigger hire staff
        ACTION_ASK_STAFF_LIST = 334, //!< in hire staff, show staff list

        //!< actions related to the machines
        ACTION_UPGRADE_MACHINE = 514, //!< trigger upgrade machine
        ACTION_DESTROY_MACHINE = 515, //!< trigger destroy machine
    }Action;

#endif //PRIM_ACTIONS_H
