#ifndef PRIM_MAIN_H
#define PRIM_MAIN_H

    #include "../headers/interface.h" //!< contains actions

    bool back = false; //!< Allow to cancel the current action

    /*!
     * This array length is predetermined by {@link USER_MAPPING_SIZE}
     * constant in interface.h.
     */
    const UserActionMapping user_mapping[] = {
            // actions related to the game in general
            {ACTION_SHOW_MAP,         "s"}, //!< show map with s
            {ACTION_END_TURN,         "n"}, //!< end turn with n
            {ACTION_CANCEL_ACTION,    "b"}, //!< cancel action with b
            {ACTION_LIST_ACTIONS,     "help"}, //!< list actions with la
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

#endif //PRIM_MAIN_H
