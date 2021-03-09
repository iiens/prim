/*!
 * \file mapping.h
 * \author Quentin Ra
 * \version 0.1
 * \date 07/03/2021
 *
 * List of actions mappings
 *
 */
#ifndef PRIM_MAPPING_H
#define PRIM_MAPPING_H

    #include "actions.h" //! actions.h : enum of all actions

    /*!
     * \typedef UserActionMapping
     * \struct UserActionMapping_S mapping.h "headers/data/mapping.h"
     *
     * Struct of an action mapping. Each action is mapped with a string.
     *
     */
    typedef struct UserActionMapping_S {
        Action action_id; //!< action_id: int, see actions.h
        char* key; //!< a sentence to input to select this action
    } UserActionMapping; //!< one mapping so (action, input_sequence)

    // @see UserActionMapping, all mappings
    const UserActionMapping user_mapping[] = {
            // actions related to the game in general
            {ACTION_SHOW_MAP,        "s"}, //!< show map with s
            {ACTION_END_TURN,        "n"}, //!< end turn with n
            {ACTION_CANCEL_ACTION,   "b"}, //!< cancel action with b
            {ACTION_EXIT,            "q"}, //!< exit with q

            // hire
            {ACTION_HIRE_FISE,       "he"}, //!< hire FISE with he
            {ACTION_HIRE_FISA,       "ha"}, //!< hire FISA with ha

            // actions related to the units
            {ACTION_BUY_MACHINE,     "bm"}, //!< buy machine with bm
            {ACTION_BUY_STAFF,       "bs"}, //!< hire Staff with bs
            {ACTION_ASK_STAFF_LIST,  "ls"}, //!< list Staff with ls

            // actions related to the machines
            {ACTION_UPGRADE_MACHINE, "upm"}, //!< upgrade machine with upm
            {ACTION_DESTROY_MACHINE, "dm"}, //!< destroy machine with dm
    }; //!< array of all the mappings

#endif //PRIM_MAPPING_H
