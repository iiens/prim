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

    const MachineInfo machine_list[] = {
            {
                    MS_COLLECTOR,200,20,500,100,60,200,
                    "Sends a resource produced by the source to the "
                    "neighboring cell indicated by its orientation.",
                    1,1, .effects  = {
                    {
                             .mode = PRODUCTION,
                             .onOther = 0,
                             .what.machine = MS_COLLECTOR,
                             .modifierCapacity = +1 ,
                             .description = "Collector storage increases by 1 "
                                            },}
            },
            {MS_CONVEYOR_BELT,60,20,-1,-1,60,200,
                    "A carpet has one exit and three entrances, the resource or waste exits",
                    0,0, .effects = {}},
            {MS_CROSS,160,20,-1,-1,60,200,
                    "The cross has 2 inlets and 2 outlets "
                    "which depend on the orientation of the cross",0,
                    0, .effects = {}},
            {MS_RECYCLING_CENTER,500,40,1500,100,100,500,
                    "The recycling center has 3 entrances and one exit. The center can store up to 100 "
                    "waste",100,
                    1, .effects = {
                    {
                                           .mode = PRODUCTION,
                                           .onOther = 0,
                                           .what.machine = MS_RECYCLING_CENTER,
                                           .modifierCapacity= +10,
                                           .description = "Storage of Recycling center increases by 10"
                                                         },}
            },
            {MS_JUNKYARD,100,100,200,600,100,200,
                    "The junkyard"
                    " has 4 entrances and 0 exits. Can store up to 50 pieces of waste",50,
                    1, .effects = {{
                                           .mode = PRODUCTION,
                                           .onOther = 0,
                                           .what.machine = MS_JUNKYARD,
                                           .modifierCapacity= +20,
                                           .description = "Storage of Junkyard increases by 20"
                                                          "et 1DD)."},}
            },
    }; //!< Array with information about all machine

    const Staff staff_list[] = {
            {1, "Fetia Bannour", 100, 30, "The cost of constructing collectors"
                                          " decreases by 10E and 1DD ", .effects = {
                    {
                            .mode = CONSTRUCTION,
                            .onOther = 0,
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
                                          " decreases by 3E and 1DD ", .effects = {
                    {
                            .mode = CONSTRUCTION,
                            .onOther = 0,
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
                                            " decreases by 8E and 1DD ", .effects = {
                    {
                            .mode = CONSTRUCTION,
                            .onOther = 0,
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
                                          " decreases by 25E and 2DD ", .effects = {
                    {
                            .mode = CONSTRUCTION,
                            .onOther = 0,
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
                                           " decreases by 5E and 5DD ", .effects = {
                    {
                            .mode = CONSTRUCTION,
                            .onOther = 0,
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
                                           " decreases by 25E and 5DD ", .effects = {
                    {
                            .mode = UPGRADE,
                            .onOther = 0,
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
                                           " decreases by 75E and 5DD ", .effects = {
                    {
                            .mode = UPGRADE,
                            .onOther = 0,
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
                                      " decreases by 10E and 30DD ", .effects = {
                    {
                            .mode = UPGRADE,
                            .onOther = 0,
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
                                      " decreases by 3E and 10DD ", .effects = {
                    {
                            .mode = DESTROY,
                            .onOther = 0,
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
                                      " belt decreases by 3E and 10DD ", .effects = {
                    {
                            .mode = DESTROY,
                            .onOther = 0,
                            .what.machine = MS_CONVEYOR_BELT,
                            .modifierE = -3,
                            .modifierDD = -10,
                            .min_costE = 3,
                            .min_costDD = 10,
                            .description = "The cost of destroying conveyor belt decreases by 3E and 10DD (min 3E\n"
                                           "and 10DD)."
                    },

            }},

            {11, "Catherine Dubois", 100, 200, "The cost of destroying cross"
                                      " decreases by 3E and 10DD ", .effects = {
                    {
                            .mode = DESTROY,
                            .onOther = 0,
                            .what.machine = MS_CROSS,
                            .modifierE = -3,
                            .modifierDD = -10,
                            .min_costE = 3,
                            .min_costDD = 10,
                            .description = "The cost of destroying conveyor belt decreases by 3E and 10DD (min 3E\n"
                                           "and 10DD)."
                    },

            }},

            {12, "Stefiana Dumbrava", 100, 200, "The cost of destroying recycling center"
                                      " decreases by 5E and 25DD ", .effects = {
                    {
                            .mode = DESTROY,
                            .onOther = 0,
                            .what.machine = MS_RECYCLING_CENTER,
                            .modifierE = -5,
                            .modifierDD = -25,
                            .min_costE = 5,
                            .min_costDD = 25,
                            .description = "The cost of destroying recycling center decreases by 5E and 25DD (min 5E\n"
                                           "and 25DD)."
                    },

            }},

            {13, "Alain Faye", 100, 200, "The cost of destroying junkyard"
                                                " decreases by 5E and 10DD ", .effects = {
                    {
                            .mode = DESTROY,
                            .onOther = 0,
                            .what.machine = MS_JUNKYARD,
                            .modifierE = -5,
                            .modifierDD = -10,
                            .min_costE = 5,
                            .min_costDD = 10,
                            .description = "The cost of destroying junkyard decreases by 5E and 10DD (min 5E\n"
                                           "and 10DD)."
                    },

            }},

            {14, "Anne-Laure Ligozat", 1000, 10, "Half garbage of each case are remove"
                                                , .effects = {
                    {
                            .mode = DESTROY,
                            .onOther = 0,
                            .what.other = DESTROY_GARBAGE,
                            .modifierRes = 1/2, // multiply for each case this number of garbage by this number
                            .description = "Half garbage of each case are remove"
                    },

            }},

            {15, "Christophe Mouilleron", 1000, 400, "School hire 20 FISE and 10 FISA"
                                                , .effects = {
                    {
                            .mode = HIRE,
                            .onOther = 1,
                            .what.other = SUB_HIRE,
                            .modifierFISE = +20,
                            .modifierFISA = +10,
                            .description = "School hire 20 FISE and 10 FISA"

                    },

            }},

            {16, "Marie Szafranski", 1000, 400, "When a resource is send at the gate"
                                                " it count for 2 but number of garbage is 1 ", .effects = {
                    {
                            .mode = SEND_DOOR,
                            .onOther = 1,
                            .what.other = NONE,
                            .modifierRes = 2,
                            .description = "When a resource is send at the gate it count for 2 but number of garbage "
                                           " is 1"
                    },

            }},

            {17, "Gael Thomas", 1000, 400, "When a garbage leave the door it has a one"
                                                " in 10 chance of disappearing ", .effects = {
                    {
                            .mode = DOOR_OUT,//<!todo : not implement yet make a variable with a randomize if = 1 remove
                            //garbage
                            .onOther = 0,
                            .what.machine = MS_RECYCLING_CENTER,
                            .description = "When a garbage leave the door it has a one"
                                           "in 10 chance of disappearing"
                    },

            }},

            {18, "Eric Lejeune", 1000, 200, "The cost of FISE decreases by 5E and 2DD"
                                            " (min 5E and 2DD)", .effects = {
                    {
                            .mode = ON_BUY,
                            .onOther = 1,
                            .what.other = SUB_FISE,
                            .modifierE = -5,
                            .modifierDD = -2,
                            .min_costE = 5,
                            .min_costDD = 2,
                            .description = "The cost of FISE decreases by 5E and 2DD min 5E and 2DD"
                    },

            }},

            {19, "Christine Mathias", 1000, 200, "The cost of FISA decreases by 5E and 2DD"
                                                 " (min 5E and 2DD)", .effects = {
                    {
                            .mode = ON_BUY,
                            .onOther = 1,
                            .what.other = SUB_FISA,
                            .modifierE = -5,
                            .modifierDD = -2,
                            .min_costE = 5,
                            .min_costDD = 2,
                            .description = "The cost of FISA decreases by 5E and 2DD min 5E and 2DD"
                    },

            }},

            {20, "Stefiana Dumbrava", 100, 200, "The cost of destroying recycling center"
                                                " decreases by 5E and 25DD ", .effects = {
                    {
                            .mode = DESTROY,
                            .onOther = 0,
                            .what.machine = MS_RECYCLING_CENTER,
                            .modifierE = -5,
                            .modifierDD = -25,
                            .min_costE = 5,
                            .min_costDD = 25,
                            .description = "The cost of destroying recycling center decreases by 5E and 25DD (min 5E\n"
                                           "and 25DD)."
                    },

            }},

            {12, "Stefiana Dumbrava", 100, 200, "The cost of destroying recycling center"
                                                " decreases by 5E and 25DD ", .effects = {
                    {
                            .mode = DESTROY,
                            .onOther = 0,
                            .what.machine = MS_RECYCLING_CENTER,
                            .modifierE = -5,
                            .modifierDD = -25,
                            .min_costE = 5,
                            .min_costDD = 25,
                            .description = "The cost of destroying recycling center decreases by 5E and 25DD (min 5E\n"
                                           "and 25DD)."
                    },

            }},














    };

#endif //PRIM_MAIN_H
