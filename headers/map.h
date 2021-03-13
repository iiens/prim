/*!
 * \file map.h
 * \author Antoine MAN and Ramzy ZEBRIR
 * \version 0.1
 * \date 28/02/2021
 * \see Difficulty
 *
 * This header contains any functions related to the interactions
 * between the player and the elements on the board game.
 * <ul>
 * <li>create a new map</li>
 * <li>destroy a map</li>
 * <li>hire a FISE</li>
 * <li>hire a FISA</li>
 * <li>switch energy type produced by the FISA </li>
 * <li>finish a turn</li>
 * </ul>
 *
 */
#ifndef PRIM_MAP_H
#define PRIM_MAP_H

    #include <stdbool.h> //!< return value
    #include "data/machine.h" //!< information about machine
    #include "data/staff.h" //!< information about Staff
    #include "data/difficulty.h" //!< difficulty of the game
    #include "data/error.h" //!< errors messages
    #include "data/case_type.h" //!< todo: Antoine

//\////////////////////////////\//
    //\/ Types declarations
    //\////////////////////////////\//

    /*!
     *
     * Type of object contained in a case
     *
     * CASE_VIDE: nothing on a case
     * CASE_VIDE: a case where there is the gate that we want to close
     * CASE_VIDE: a case where resources popup
     * CASE_VIDE: a case where there is a machine
     * E : value that measure the energy quantity of the player
     * DD : value that measure the planet general health
     *
     */

    #define E_VALUE 0 //!< E Constant that measure the energy quantity of the player
    #define DD_VALUE 1 //!< DD Constant that measure the planet general health

    /*!
     * \typedef Case
     * \struct Case_S map.h "headers/map.h"
     *
     * Struct that contains all the information concerning a case
     *
     */
    typedef struct Case_S {
        int x; //!< int, abscissa
        int y; //!< int, ordinate
        union {
            Machine* mach;
            void* other;
        } in; //!< union, it correspond to the object contained in the case
        CaseType type; //!< type of object contained in the case
    } Case; //!< it correspond to a case of the board game

    /*!
     * \typedef Map
     * \struct Map_S map.h "headers/map.h"
     *
     * Struct that contains all the map information concerning machines
     * emplacement, sources, resources, garbage, Staff and gate, presents on the map.
     *
     */
    typedef struct Map_S {
        Difficulty difficulty; //!< game difficulty
        int width; //!< int, map width
        int height; //!< int, map height
        Case** map; //!< a bi dimensional table to refer to the board of game
        int turn; //!< int, an indicator to correspond to the actual turn of the game
        int numberFISE; //!< as the name suggest, its corresponding to the number of FISE
        int numberFISA; //!< as the name suggest, its corresponding to the number of FISA
        int E; //!< a value that measure the energy quantity of the player
        int DD; //!< a value that measure the planet general health
        int productionFISA; //!< int, it correspond to the energy type produced by the FISA, see E_VALUE/DD_VALUE
        Staff* team; //!< a list of staffs that the user bought
        int score; //!< a score which indicate number of resources put in the gate
        int pollution; //!< a score which indicate number of garbage that are still present in the gate
    } Map; //!< Board game that contain all of the information about each case


    //\////////////////////////////\//
    //\/ Functions declarations
    //\////////////////////////////\//

    /*!
     * \fn const Map* map_create(Difficulty dif)
     * @brief Create a new map
     *
     * In order to begin a new game, we need a board game.
     * It will contains all the map information concerning machines
     * emplacement, sources, resources, garbage, Staff and gate, presents on the map.
     *
     * Difficulty has been chosen by the player which determine the width and height of the map
     * Creation of the map : a bi dimensional Case table
     * 2 sources cases and 1 transdimensional gate are randomly placed into those cases.
     * The player starts the game with 5 FISE, 5 FISA, 100 E and 100 DD.
     * Initialization of the turn, the score the pollution to 0.
     * By default, the FISA production is E.
     * A table which contain staffs that the user bought is also initialized
     *
     * @param[in] dif a valid difficulty chosen by the user
     * @return a new map that contains all the map information
     * @see Map type
     * @see Difficulty enum
     */
    Map* map_create(Difficulty dif);

    /*!
     * \fn ErrorCode map_destroy(Map* map)
     * @brief Destroy a map
     *
     * At the end of a game, we need to free all the memory allocated
     * to a map.
     *
     * We have to free :
     * Staff* team
     *  Case** map
     *  ... //todo: Antoine, complete
     *
     * @param[in] map a map
     * @return a bool in order to know if everything worked well
     * @see Map type
     */
    ErrorCode map_destroy(Map* map);

    /*!
     * \fn ErrorCode map_hireFISE(const Map* map)
     * @brief Hire a FISE
     *
     * We hire a FISE in order to product more resources.
     * Every turn, each FISE student produce 1 E and 1 DD
     * A student (FISE or FISA) costs 50 E and 20 DD.
     *
     * A verification is necessary to know if the player can hire a new FISE.
     * We have to check resources E and DD of the player
     *
     * @param[in] map a map
     * @return a bool in order to know if everything worked well
     * @see Map type
     */
    ErrorCode map_hireFISE(const Map* map);

    /*!
     * \fn ErrorCode map_hireFISA(const Map* map)
     * @brief Hire a FISA
     *
     * We hire a FISA in order to product more resources.
     * Every 2 turns, each FISA student produce either 4 E or 4 DD
     *
     * A student (FISE or FISA) costs 50 E and 20 DD.
     *
     * A verification is necessary to know if the player can hire a new FISA.
     * We have to check resources E and DD of the player
     *
     * @param[in] map a map
     * @return a bool in order to know if everything worked well
     * @see Map type
     */
    ErrorCode map_hireFISA(const Map* map);

    /*!
     * \fn ErrorCode map_changeProductionFISA()
     * @brief Switch the energy type produced by the FISA
     *
     * This function allow us to switch the energy type
     * produced by the FISA between E or DD.
     *
     * @return a bool in order to know if everything worked well
     */
    ErrorCode map_changeProductionFISA();

    /*!
    * \fn ErrorCode map_endTurn(Map* map)
    * @brief Finish a turn
    *
    * Verifications to do at the end of a turn
    * Check FISA and FISE production
    * Update E value
    * Call all conveyor belt/cross at the same time.
    *   -> Resources moves
    *   -> Verify each resource destination
    *       -> next case empty -> resource is lost
    *       -> next case is an ENTRY machine -> send to machine
    * Check if we produce resources (sources)
    * Check if we produce wastes (gate)
    * Call all Recycling center
    *   -> stored garbage don't decrease DD
    *   -> 10 garbage produce 1 /per turn
    * Call all collectors
    *   -> activated from top to bot, left to right
    *   -> No source -> do nothing
    *   -> randomly choose a source among all adjacent ones
    * Update DD value
    *
    * @param map game map
    * @return a bool in order to know if everything worked well
    */
    ErrorCode map_endTurn(Map* map);

    /*!
     * \fn ErrorCode map_isEmpty(int x, int y, Map* map)
     * @brief In order to verify if a case is empty
     * @param[in] x case abscissa
     * @param[in] y case ordinate
     * @param[in] map a map
     * @return true/false if a case is empty
     */
    ErrorCode map_isEmpty(int x, int y, Map* map);

    /*!
     * \fn bool map_addMachine(const Machine machine, const int x, const int y, Map* m)
     * @brief Add a machine
     * @param[in] machine a machine
     * @param[in] x x > 0
     * @param[in] y y > 0
     * @param[in,out] m a map
     * Add a machine on the map
     *
     * @return 1 if true else 0
     */
    bool map_addMachine(Machine machine, int x, int y, Map* m);

    /*!
     * \fn bool map_upgradeMachine(const int x,const int y, Map* m)
     * @brief Upgrade a machine
     * @param[in] x x > 0
     * @param[in] y y > 0
     * @param[in,out] m a map
     * Upgrade a machine on the map. We know which machine we upgrade thanks
     * to the x and y coordinates
     *
     * @return 1 if true else 0
     */
    bool map_upgradeMachine(int x, int y, Map* m);

    /*!
     * \fn bool map_destroyMachine(const int x,const int y, Map* m)
     * @brief Destroy a machine
     * @param[in] x x > 0
     * @param[in] y y > 0
     * @param[in,out] m a map
     * Destroy a machine on the map. We know which machine we destroy thanks
     * to the x and y coordinates
     *
     * @return 1 if true else 0
     */
    bool map_destroyMachine(int x, int y, Map* m);

    /*!
     * \fn bool map_buyStaff(Staff s, Map* m)
     * @brief Buy a Staff
     * @param[in] s a Staff
     * @param[in,out] m a map
     * Buy a Staff
     *
     * @return 1 if true else 0
     */
    bool map_buyStaff(Staff s, Map* m);

#endif //PRIM_MAP_H
