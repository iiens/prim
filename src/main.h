#ifndef PRIM_MAIN_H
#define PRIM_MAIN_H

    #include "../headers/interface.h" //!< contains actions
    #include "../headers/data/effect.h"

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

    //todo: mettre les bonnes valeurs pour machine_list
    //todo: make descriptions shorter please
    const MachineInfo machine_list[] = {
            {
                    MS_COLLECTOR,200,20,500,100,60,200,
                    "The collector sends a resource produced by the source to the "
                    "neighboring cell indicated by its orientation. It must be placed "
                    "on a square adjacent to that of the source",
                    1, .effects = {
                    {
                             .mode = UPGRADE,
                             .onOther = true,
                             .what.machine = MS_COLLECTOR,
                             .modifierE = -10,
                             .modifierDD = -1,
                             .min_costE = 10,
                             .min_costDD = 1,
                             .description = "Le coût de construction des collecteurs diminue de 10E et 1DD (minimum 10E\n"
                                            "et 1DD)."
                     },}
            },
            {MS_CONVEYOR_BELT,60,20,-1,-1,60,200,
                    "A carpet has one exit and three entrances, the resource or waste exits"
                    " 1 turn after entering the conveyor belt",
                    0, .effects = {{
                                          .mode = UPGRADE,
                                          .onOther = true,
                                          .what.machine = MS_COLLECTOR,
                                          .modifierE = -10,
                                          .modifierDD = -1,
                                          .min_costE = 10,
                                          .min_costDD = 1,
                                          .description = "Le coût de construction des collecteurs diminue de 10E et 1DD (minimum 10E\n"
                                                         "et 1DD)."
                                  },}
            },
            {MS_CROSS,160,20,-1,-1,60,200,
                    "A cross is a set of two juxtaposed conveyor belts, allowing two "
                    "lines of conveyor belts to cross. The cross has 2 inlets and 2 outlets "
                    "which depend on the orientation of the cross",
                    0, .effects = {}},
            {MS_RECYCLING_CENTER,500,40,1500,100,100,500,
                    "The recycling center is used to store waste. The recycling center"
                    " has 4 entrances and 0 exits. At the start of the game, a recycling "
                    "center can store up to 50 pieces of waste",
                    1, .effects = {}},
            {MS_JUNKYARD,100,100,200,600,100,200,
                    "The recycling center turns waste into a resource. Like the conveyor belt,"
                    " the center has 3 entrances and one exit. The center can store up to 100 "
                    "waste",
                    1, .effects = {}
            },
    }; //!< Array with information about all machine

    //todo: NUMBER_OF_STAFFS in staff.h (increase each time you add a staff)
    const Staff staff_list[] = {
            {1, "Fetia Bannour", 100, 30, "The cost of constructing collectors"
                                          "decreases by 10E and 1DD ", .effects = {
                    {
                            .mode = CONSTRUCTION,
                            .onOther = false,
                            .what.machine = MS_COLLECTOR,
                            .modifierE = -10,
                            .modifierDD = -1,
                            .min_costE = 10,
                            .min_costDD = 1,
                            .description = "The cost of constructing collectors decreases by 10EE and 1DD (min 10E\n"
                                           "and 1DD)."
                    },

            }},
            {2, "Kevin Goilard", 100, 30, "The cost of constructing conveyor belt"
                                          "decreases by 3E and 1DD ", .effects = {
                    {
                            .mode = CONSTRUCTION,
                            .onOther = false,
                            .what.machine = MS_CONVEYOR_BELT,
                            .modifierE = -3,
                            .modifierDD = -1,
                            .min_costE = 3,
                            .min_costDD = 1,
                            .description = "The cost of constructing conveyor belt decreases by 3E and 1DD (min 3EE\n"
                                           "and 1DD)."
                    },

            }},
            {3, "Vincent Jeannas", 100, 30, "The cost of constructing cross"
                                            "decreases by 8E and 1DD ", .effects = {
                    {
                            .mode = CONSTRUCTION,
                            .onOther = false,
                            .what.machine = MS_CROSS,
                            .modifierE = -8,
                            .modifierDD = -1,
                            .min_costE = 8,
                            .min_costDD = 1,
                            .description = "The cost of constructing cross decreases by 8E and 1DD (min 8EE\n"
                                           "and 1DD)."
                    },

            }},
            {4, "Thomas Laurent", 100, 30, "The cost of constructing recycling center"
                                          "decreases by 25E and 2DD ", .effects = {
                    {
                            .mode = CONSTRUCTION,
                            .onOther = false,
                            .what.machine = MS_RECYCLING_CENTER,
                            .modifierE = -25,
                            .modifierDD = -2,
                            .min_costE = 25,
                            .min_costDD = 2,
                            .description = "The cost of constructing conveyor belt decreases by 25E and 2DD (min 25E\n"
                                           "and 2DD)."
                    },

            }},

            {5, "Massinissa Merabet", 100, 30, "The cost of constructing junkyard"
                                           "decreases by 5E and 5DD ", .effects = {
                    {
                            .mode = CONSTRUCTION,
                            .onOther = false,
                            .what.machine = MS_JUNKYARD,
                            .modifierE = -5,
                            .modifierDD = -5,
                            .min_costE = 5,
                            .min_costDD = 5,
                            .description = "The cost of constructing conveyor belt decreases by 5E and 5DD (min 5E\n"
                                           "and 5DD)."
                    },

            }},


            {6, "Stefi Nouleho", 200, 100, "The cost of upgrading collectors"
                                           "decreases by 25E and 5DD ", .effects = {
                    {
                            .mode = UPGRADE,
                            .onOther = false,
                            .what.machine = MS_COLLECTOR,
                            .modifierE = -25,
                            .modifierDD = -5,
                            .min_costE = 25,
                            .min_costDD = 5,
                            .description = "The cost of upgrading collectors decreases by 25E and 5DD (min 25E\n"
                                           "and 5DD)."
                    },

            }},


            {7, "Vitera Y", 200, 100, "The cost of upgrading recycling center"
                                           "decreases by 75E and 5DD ", .effects = {
                    {
                            .mode = UPGRADE,
                            .onOther = false,
                            .what.machine = MS_RECYCLING_CENTER,
                            .modifierE = -75,
                            .modifierDD = -5,
                            .min_costE = 75,
                            .min_costDD = 5,
                            .description = "The cost of upgrading recycling center decreases by 75E and 5DD (min 75E\n"
                                           "and 5DD)."
                    },

            }},

            {8, "Laurence Bourard", 200, 100, "The cost of upgrading junkyard"
                                      "decreases by 10E and 30DD ", .effects = {
                    {
                            .mode = UPGRADE,
                            .onOther = false,
                            .what.machine = MS_JUNKYARD,
                            .modifierE = -10,
                            .modifierDD = -30,
                            .min_costE = 20,
                            .min_costDD = 30,
                            .description = "The cost of upgrading junkyard decreases by 10E and 30DD (min 20E\n"
                                           "and 30DD)."
                    },

            }},

            {9, "Nicolas Brunel", 100, 200, "The cost of destroying collectors"
                                      "decreases by 3E and 10DD ", .effects = {
                    {
                            .mode = DESTROY,
                            .onOther = false,
                            .what.machine = MS_COLLECTOR,
                            .modifierE = -3,
                            .modifierDD = -10,
                            .min_costE = 3,
                            .min_costDD = 10,
                            .description = "The cost of destroying recycling center decreases by 3E and 10DD (min 3E\n"
                                           "and 10DD)."
                    },

            }},

            {10, "Anastase Charantonis", 100, 200, "The cost of destroying conveyor"
                                      "belt decreases by 3E and 10DD ", .effects = {
                    {
                            .mode = DESTROY,
                            .onOther = false,
                            .what.machine = MS_CONVEYOR_BELT,
                            .modifierE = -3,
                            .modifierDD = -10,
                            .min_costE = 3,
                            .min_costDD = 10,
                            .description = "The cost of destroying conveyor belt decreases by 3E and 10DD (min 3E\n"
                                           "and 10DD)."
                    },

            }},

            {7, "Vitera Y", 200, 100, "The cost of upgrading recycling center"
                                      "decreases by 75E and 5DD ", .effects = {
                    {
                            .mode = UPGRADE,
                            .onOther = false,
                            .what.machine = MS_RECYCLING_CENTER,
                            .modifierE = -75,
                            .modifierDD = -5,
                            .min_costE = 75,
                            .min_costDD = 5,
                            .description = "The cost of upgrading recycling center decreases by 75E and 5DD (min 75E\n"
                                           "and 5DD)."
                    },

            }},

            {7, "Vitera Y", 200, 100, "The cost of upgrading recycling center"
                                      "decreases by 75E and 5DD ", .effects = {
                    {
                            .mode = UPGRADE,
                            .onOther = false,
                            .what.machine = MS_RECYCLING_CENTER,
                            .modifierE = -75,
                            .modifierDD = -5,
                            .min_costE = 75,
                            .min_costDD = 5,
                            .description = "The cost of upgrading recycling center decreases by 75E and 5DD (min 75E\n"
                                           "and 5DD)."
                    },

            }},














    };

#endif //PRIM_MAIN_H
