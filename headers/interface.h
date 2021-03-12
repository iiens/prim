/*!
 * \file interface.h
 * \author Quentin Ra
 * \version 0.6
 * \date 10/03/2021
 * \see Machine
 * \see Difficulty
 * \see Map
 * \see data/actions.h
 * \see data/mapping.h
 *
 * This header contains any functions related to the interactions
 * between the player and the game.
 * <ul>
 * <li>print map</li>
 * <li>ask for level (see Difficulty) </li>
 * <li>ask for an action</li>
 * <li>ask for machine information for creation (see Machine)</li>
 * <li>ask for machine information for update/delete</li>
 * <li>ask for Staff information</li>
 * </ul>
 *
 */
#ifndef PRIM_INTERFACE_H
#define PRIM_INTERFACE_H

    #include "data/actions.h" //! contains all actions
    #include "data/difficulty.h" //! contains difficulty type
    #include "data/mapping.h" //! contains mappings type
    #include "map.h" //! contains map type
    #include "utils/utils.h" //! utilities functions

    //\////////////////////////////\//
    //\/ interface declarations
    //\////////////////////////////\//

    /*!
     * Supposed to init interface.
     *
     * Can be used to show a message with the name of the
     * game, the version, ... and/or display difficulties.
     *
     * @return  true ok, false ko
     */
    bool interface_init();

    /**
     * Reload interface. We should use this
     * to update the map, the E,DD,... values
     * that are shown.
     *
     * @param map game map
     * @return true ok, false ko
     */
    bool interface_reload(const Map* map);

    /**
     * Dispose of interface and clean everything.
     * @return true ok, false ko
     */
    bool interface_close();

    //\////////////////////////////\//
    //\/ game interface declarations
    //\////////////////////////////\//

    /*!
     * \fn Difficulty interface_chooseDifficulty
     * @brief Ask for the user difficulty
     *
     * To process the size of the map.
     * Should be a valid difficulty, if not ask again.
     *
     * @return a valid difficulty chosen by the user.
     * @see Difficulty enum
     */
    Difficulty interface_chooseDifficulty();

    /*!
     * @brief Show the map
     *
     * We are waiting for a grid, like
     * <pre>
     *      0     1
     *   +----++----+
     * 0 | M  |     |
     *   +----++----+
     * </pre>
     * Where 0,1 are the column indexes and 0 is the row index. M is the first
     * letter for machine, but well no need to write a lot, just enough so that the
     * player can guess whether he would want to check this case or not.
     *
     * At the end, we want to find basic information such as
     * <ul>
     * <li>E value</li>
     * <li>DD value</li>
     * <li>which turn is it</li>
     * <li>number of FISE</li>
     * <li>number of FISA</li>
     * <li>the production mode</li>
     * <li>the number of hired staffs (or their names followed by the count if different of one)</li>
     * </ul>
     *
     * @param[in] map a map
     * @see Map type
     */
    void interface_showMap(const Map* map);

    /**
     * Should take a map and print the list of the staff.
     * Please do take note that this method use a global
     * variable containing all data about the staff.
     *
     * This method should be a catalog of available staffs.
     * You must add right after a staff name the count of this staff
     * that the user have already bought.
     *
     * <pre>
     * --> ({n°}) Name E:{cost} DD:{cost} Desc:"perks"
     * ...
     * </pre>
     *
     * @pre staff list must be set
     * @pre map must contains the list of staff that the player bought
     * @param map used to fetch staff bought
     * @see Map
     */
    void interface_showStaffList(const Map* map);

    /**
     * Show machine list.
     * Should use global variable {@link machine_list} in {@link machine.h}.
     */
    void interface_showMachinesList();

    /**
     * Show actions list.
     * Should use global variable {@link user_mapping} in {@link mapping.h}.
     * And {@link USER_MAPPING_SIZE}
     */
    void interface_list_actions();

    /*!
     * @brief Ask for the user action
     *
     * Ask for the user action
     * Should be a valid action, if not ask again.
     *
     * Actions returned should be implemented by
     *
     * <ul>
     * <li>{@link ACTION_SHOW_MAP}: {@link interface_showMap}</li>
     * <li>{@link ACTION_CANCEL_ACTION}: no function, can't be used here ! (only when an action got chosen)</li>
     * <li>{@link ACTION_EXIT} : caller should ends the program</li>
     * <li>{@link ACTION_LIST_ACTIONS} : call {@link interface_list_actions}</li>
     * <li>{@link ACTION_END_TURN} : next turn, call of {@link map_endTurn}</li>
     *
     * <li>{@link ACTION_HIRE_FISE} : hire fise, call of {@link map_hireFISE}</li>
     * <li>{@link ACTION_HIRE_FISA} : hire fisa, call of {@link map_hireFISA}</li>
     * <li>{@link ACTION_CHANGE_FISA_MODE} : change fisa production mode, call of {@link map_changeProductionFISA}</li>
     *
     * <li>{@link ACTION_LIST_MACHINES} : should call {@link interface_showMachinesList}</li>
     * <li>{@link ACTION_BUY_MACHINE} : should ask {@link interface_askAddMachine} and {@link interface_askMachineLocation}</li>
     * then call {@link map_addMachine}
     * <li>{@link ACTION_BUY_STAFF} : should ask {@link interface_askBuyStaff} then {@link map_buyStaff}</li>
     * <li>{@link ACTION_ASK_STAFF_LIST} : should call {@link interface_showStaffList}</li>
     *
     * <li>{@link ACTION_UPGRADE_MACHINE} : {@link interface_askMachineLocation} then {@link map_upgradeMachine}</li>
     * <li>{@link ACTION_DESTROY_MACHINE} : {@link interface_askMachineLocation} then {@link map_destroyMachine}</li>
     * </ul>
     *
     * @return a valid action chosen by the user.
     * @see Action enum
     */
    Action interface_chooseAction();

    /*!
     * @brief ask user machine specific details
     *
     * @pre this method should be called after (or before) asking
     * the user where the machine should be put
     *
     * If the user wants to go back, then he can using
     * ACTION_CANCEL_ACTION action.
     *
     * We must fill each value inside our machine, for that
     * check {@link Machine} type.
     *
     * @return the machine that the user wanted to add.
     *
     * @see ACTION_BUY_MACHINE
     */
    Machine* interface_askAddMachine();

    /*!
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

    /*!
     * @brief Ask which Staff the user wants to buy.
     *
     * The user input an id (that he could find using list staff action)
     * and we returns the staff in the global staff array that match the given id.
     *
     * If the user wants to go back, then he can using
     * ACTION_CANCEL_ACTION action.
     *
     * @return a valid Staff that the user chosen. Or null if he asked to cancel.
     *
     * @see ACTION_BUY_STAFF
     * @see ACTION_ASK_STAFF_LIST (action enum)
     */
    Staff interface_askBuyStaff();

    /**
     * Show an error
     * @param e an error code
     * @param show true show this error, false hide any previous error
     * @see ErrorCode
     */
    void interface_showError(ErrorCode e, bool show);

#endif //PRIM_INTERFACE_H
