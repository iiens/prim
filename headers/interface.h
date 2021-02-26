/***
 * @file interface.h
 * @package headers
 *
 * This header contains any functions related to the interactions
 * between the player and the game.
 *  - print map
 *  - ask for level ({@link Difficulty}
 *  - ask for an action
 *  - ask for machine information for creation (@link Machine}
 *  - ask for machine information for update/delete
 *  - ask for staff information
 *
 *  @see Machine
 *  @see Difficulty
 *  @see Map
 *  @see data/actions.h
 */

#ifndef PRIM_INTERFACE_H
#define PRIM_INTERFACE_H

    #include "data/actions.h" //!< contains all actions
    #include "utils/utils.h" //!< utilities functions
    // #include "data/map.h" //!< contains map type
    // #include "data/difficulty.h" //!< contains difficulty type

    //\////////////////////////////\//
    //\/ Types declarations
    //\////////////////////////////\//

    /***
     * @struct
     * Struct of an action mapping,
     * each action (see actions.h, and id)
     * is mapped with a string
     */
    typedef struct user_action_mapping_s {
        int action_id;
        char* key;
    } user_action_mapping;

    /***
     * array of all the mappings
     */
    const user_action_mapping user_mapping[] = {
            //!< actions related to the game in general
            {ACTION_SHOW_MAP, "s"},
            {ACTION_END_TURN, "n"},
            {ACTION_CANCEL_ACTION, "b"},
            {ACTION_EXIT, "q"},

            //!< hire
            {ACTION_HIRE_FISE, "he"},
            {ACTION_HIRE_FISA, "ha"},

            //!< actions related to the units
            {ACTION_BUY_MACHINE, "bm"},
            {ACTION_BUY_STAFF, "bs"},
            {ACTION_ASK_STAFF_LIST, "ls"},

            //!< actions related to the machines
            {ACTION_UPGRADE_MACHINE, "upm"},
            {ACTION_DESTROY_MACHINE, "dm"},
    };

    //\////////////////////////////\//
    //\/ Functions declarations
    //\////////////////////////////\//

    /***
     * @brief Ask for the user difficulty
     *
     * Ask for the user difficulty, to process the size of the map.
     * Should be a valid difficulty, if not ask again.
     *
     * @return a valid difficulty chosen by the user.
     * @see Difficulty enum
     */
    Difficulty interface_chooseDifficulty();

    /***
     * @brief Show the map
     *
     * We are waiting for a grid, like
     *      0     1
     *   +----++----+
     * 0 | M  |     |
     *   +----++----+
     * Where 0,1 are the column indexes and 0 is the row index. M is the first
     * letter for machine, but well no need to write a lot, just enough so that the
     * player can guess whether he would want to check this case or not.
     *
     * At the end, we want to find basic information such as
     * - E value
     * - DD value
     * - which turn is it
     * - number of FISE
     * - number of FISA
     * - the production mode
     *
     * @param map a map
     * @see Map type
     */
    void interface_showMap(const Map* map);

    /***
     * @brief Ask for the user action
     *
     * Ask for the user action
     * Should be a valid action, if not ask again.
     *
     * @return a valid action chosen by the user.
     * @see Action enum
     */
    Action interface_chooseAction();

    /***
     * @brief ask user machine specific details
     *
     * @pre this method should be called after (or before) asking
     * the user where the machine should be put
     *
     * If the user wants to go back, then he can using
     * ACTION_CANCEL_ACTION action.
     *
     * @return the machine that the user wanted to add.
     *
     * @see ACTION_BUY_MACHINE
     */
    Machine* interface_askAddMachine();

    /**
     * @brief Ask for machine location
     *
     * Ask for machine location, this function should
     * be used when the user triggered upgrade/delete machine action
     *
     * The programmer won't have to check whether this location is a valid
     * machine location, that would have to be done by the one calling it.
     *
     * If the user wants to go back, then he can using
     * ACTION_CANCEL_ACTION action.
     *
     * @return a two dimensions vector that should contains a positive
     * x and a positive y.
     *
     * @see ACTION_UPGRADE_MACHINE
     * @see ACTION_DESTROY_MACHINE
     */
    Vector2D interface_askMachineLocation();

    /**
     * @brief Ask which staff the user wants to buy.
     *
     * The user can ask for a list, with the ACTION_ASK_STAFF_LIST that print basic
     * info for each staff (1 per line)
     * --> (<n°>) Name E:<cost> DD:<cost> Desc:<perks>
     * ...
     *
     * Then the user choice a Staff (by inputting the n°) and
     * it must be a valid id.
     *
     * If the user wants to go back, then he can using
     * ACTION_CANCEL_ACTION action.
     *
     * @return a valid staff that the user chosen. Or null if he asked to cancel.
     *
     * @see ACTION_BUY_STAFF
     * @see ACTION_ASK_STAFF_LIST (action enum)
     */
    Staff* interface_askBuyStaff();

#endif //PRIM_INTERFACE_H
