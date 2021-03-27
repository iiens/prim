/*!
 * \file map.h
 * \author Antoine MAN and Ramzy ZEBRIR
 * \version 0.1
 * \date 28/02/2021
 * \see Difficulty
 * \see CaseType
 * \see ErrorCode
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
 * <li>add a machine in a case</li>
 * <li>upgrade a machine, already created in a case</li>
 * <li>detroy a machine, already created in a case</li>
 * <li>buy staffs in order to have bonus</li>
 * </ul>
 *
 */
#ifndef PRIM_MAP_H
#define PRIM_MAP_H

    #include <stdbool.h> // return value
    #include "data/machine.h" // information about machine
    #include "data/staff.h" // information about Staff
    #include "data/difficulty.h" // difficulty of the game
    #include "data/error.h" // errors messages
    #include "data/case_type.h" // case type (empty, source, gate, machine)

    //\////////////////////////////\//
    //\/ Types declarations
    //\////////////////////////////\//

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
        int nbResource; //!< number of resource on the machine
        int nbGarbage; //!< number of garbage on the machine
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
    Map* map_create( Difficulty dif );

    /*!
     * \fn ErrorCode map_destroy(Map* map)
     * @brief Destroy a map
     *
     * At the end of a game, we need to free all the memory allocated
     * to a map.
     *
     * We have to free :
     * <pre>
     * Staff* team
     *  Case** map
     *  ... (map.h , staff.f, machine.h)
     * </pre>
     *
     * @param[in] map a map
     * @return an error that specify what is the problem
     * @see Map type
     */
    ErrorCode map_destroy( Map* map );

    /*!
     * \fn ErrorCode map_hireFISE(Map* map)
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
     * @return an error that specify what is the problem
     * @see Map type
     */
    ErrorCode map_hireFISE( Map* map );

    /*!
     * \fn ErrorCode map_hireFISA(Map* map)
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
     * @return an error that specify what is the problem
     * @see Map type
     */
    ErrorCode map_hireFISA( Map* map );

    /*!
     * \fn ErrorCode map_changeProductionFISA( Map* map )
     * @brief Switch the energy type produced by the FISA
     *
     * This function allow us to switch the energy type
     * produced by the FISA between E or DD.
     *
     * @param[in] map a map
     * @return an error that specify what is the problem
     * @see Map type
     */
    ErrorCode map_changeProductionFISA( Map* map );

    /*!
     * \fn ErrorCode map_endTurn(Map* map)
     * @brief Finish a turn
     *
     * Verifications to do at the end of a turn
     * <ol>
     * <li>Check FISA and FISE production</li>
     * <li>Update E</li>
     * <li>Call all conveyor belt/cross at the same time.</li>
     *
     * <li>
     * <ol>
     * <li>Resources moves</li>
     * <li>Verify each resource destination</li>
     * <li>next case empty then resource is lost</li>
     * <li>next case is an ENTRY machine -> send to machine</li>
     * </ol>
     * </li>
     *
     * <li>Check if we produce resources (sources)</li>
     * <li>Check if we produce wastes (gate)</li>
     * <li>Call all Recycling center</li>
     *
     * <li>
     * <ol>
     * <li>stored garbage don't decrease DD</li>
     * <li>10 garbage produce 1 /per turn</li>
     * </ol>
     * </li>
     *
     * <li>Call all collectors</li>
     *
     * <li>
     * <ol>
     * <li>activated from top to bot, left to right</li>
     * <li>No source then do nothing</li>
     * <li>randomly choose a source among all adjacent ones</li>
     * </ol>
     * </li>
     *
     * <li>Update DD value</li>
     * </ol>
     *
     * \param map game map
     * \return an error that specify what is the problem
    */
    ErrorCode map_endTurn( Map* map );

    /*!
     * \fn ErrorCode map_addMachine(const Machine machine, const int x, const int y, Map* m)
     * @brief Add a machine
     * @param[in] machine a machine
     * @param[in] x x > 0
     * @param[in] y y > 0
     * @param[in,out] m a map
     * Add a machine on the map
     *
     * @return an error that specify what is the problem
     */
    ErrorCode map_addMachine( Machine machine, int x, int y, Map* m );

    /*!
     * \fn ErrorCode map_upgradeMachine(const int x,const int y, Map* m)
     * @brief Upgrade a machine
     * @param[in] x x > 0
     * @param[in] y y > 0
     * @param[in,out] m a map
     * Upgrade a machine on the map. We know which machine we upgrade thanks
     * to the x and y coordinates
     *
     * @return an error that specify what is the problem
     */
    ErrorCode map_upgradeMachine( int x, int y, Map* m );

    /*!
     * \fn ErrorCode map_destroyMachine(const int x,const int y, Map* m)
     * @brief Destroy a machine
     * @param[in] x x > 0
     * @param[in] y y > 0
     * @param[in,out] m a map
     * Destroy a machine on the map. We know which machine we destroy thanks
     * to the x and y coordinates
     *
     * @return an error that specify what is the problem
     */
    ErrorCode map_destroyMachine( int x, int y, Map* m );

    /*!
     * \fn ErrorCode map_buyStaff(Staff s, Map* m)
     * @brief Buy a Staff
     * @param[in] s a Staff
     * @param[in,out] m a map
     * Buy a Staff
     *
     * @return an error that specify what is the problem
     */
    ErrorCode map_buyStaff( Staff s, Map* m );

    /*!
    * \fn ErrorCode map_isEmpty( int x, int y, Map* m )
    * @brief In order to verify if a case is empty
    * @param[in] x case abscissa
    * @param[in] y case ordinate
    * @param[in] map a map
    * @return an error that specify what is the problem
    */
    ErrorCode map_isEmpty( int x, int y, Map* m );

    /*!
    * \fn ErrorCode map_isCaseExist( int x, int y, Map* m )
    * @brief In order to verify if a case exist
    * @param[in] x case abscissa
    * @param[in] y case ordinate
    * @param[in] map a map
    * @return an error that specify what is the problem
    */
    ErrorCode map_isCaseExist( int x, int y, Map* m );

    //\////////////////////////////\//
    //\/ Functions Getters and Setters
    //\////////////////////////////\//

    /*!
    * \fn int map_getNumberResource( int x, int y, Map* m )
    * @brief a function to get the number of resources
    * @param[in] x case abscissa
    * @param[in] y case ordinate
    * @param[in] map a map
    *
    * This function get the number of resources on a specific case.
    * Return a negative value if the case does not exist
    *
    * @return the number of resources available on the case
    */
    int map_getNumberResource( int x, int y, Map* m );

    /*!
    * \fn int map_getNumberGarbage( int x, int y, Map* m )
    * @brief a function to get the number of garbage
    * @param[in] x case abscissa
    * @param[in] y case ordinate
    * @param[in] map a map
    *
    * This function get the number of garbage on a specific case.
    * Return a negative value if the case does not exist
    *
    * @return the number of garbage available on the case
    */
    int map_getNumberGarbage( int x, int y, Map* m );

    /*!
    * \fn int map_getNumberFISE( Map* m )
    * @brief a function to get the number of FISE
    * @param[in] map a map
    *
    * This function get the number of FISE recruited by the player.
    *
    * @return the number of FISE available
    */
    int map_getNumberFISE( Map* m );

    /*!
    * \fn int map_getNumberFISA( Map* m )
    * @brief a function to get the number of FISA
    * @param[in] map a map
    *
    * This function get the number of FISA recruited by the player.
    *
    * @return the number of FISA available
    */
    int map_getNumberFISA( Map* m );

    /*!
    * \fn int map_getNumberE( Map* m )
    * @brief a function to get the number of E
    * @param[in] map a map
    *
    * This function get the number of E posseded by the player.
    *
    * @return the number of E available
    */
    int map_getNumberE( Map* m );

    /*!
    * \fn int map_getNumberDD( Map* m )
    * @brief a function to get the number of DD
    * @param[in] map a map
    *
    * This function get the number of DD posseded by the player.
    *
    * @return the number of DD available
    */
    int map_getNumberDD( Map* m );

    /*!
    * \fn ErrorCode map_setNumberResource( int x, int y, Map* m, int val )
    * @brief a function to set the number of resources
    * @param[in] x case abscissa
    * @param[in] y case ordinate
    * @param[in] map a map
    * @param[in] val a resource value to add/to substract
    *
    * This function set the number of resources on a specific case.
    *
    * @return an error that specify what is the problem
    */
    ErrorCode map_setNumberResource( int x, int y, Map* m, int val );

    /*!
    * \fn ErrorCode map_setNumberGarbage( int x, int y, Map* m, int val )
    * @brief a function to set the number of garbage
    * @param[in] x case abscissa
    * @param[in] y case ordinate
    * @param[in] map a map
    * @param[in] val a resource value to add/to substract
    *
    * This function set the number of garbage on a specific case.
    *
    * @return an error that specify what is the problem
    */
    ErrorCode map_setNumberGarbage( int x, int y, Map* m, int val );

    /*!
    * \fn ErrorCode map_setNumberFISE( Map* m, int val)
    * @brief a function to set the number of FISE
    * @param[in] map a map
    * @param[in] val number of FISE to add/to substract
    *
    * This function set the number of FISE recruited by the player.
    *
    * @return an error that specify what is the problem
    */
    ErrorCode map_setNumberFISE( Map* m, int val);

    /*!
    * \fn ErrorCode map_setNumberFISA( Map* m, int val )
    * @brief a function to set the number of FISA
    * @param[in] map a map
    * @param[in] val number of FISA to add/to substract
    *
    * This function set the number of FISA recruited by the player.
    *
    * @return an error that specify what is the problem
    */
    ErrorCode map_setNumberFISA( Map* m, int val );

    /*!
    * \fn ErrorCode map_setNumberE( Map* m, int val )
    * @brief a function to set the number of E
    * @param[in] map a map
    * @param[in] val E value to add/to substract
    *
    * This function set the number of E posseded by the player.
    *
    * @return an error that specify what is the problem
    */
    ErrorCode map_setNumberE( Map* m, int val );

    /*!
    * \fn ErrorCode map_setNumberDD( Map* m, int val )
    * @brief a function to set the number of DD
    * @param[in] map a map
    * @param[in] val DD value to add/to substract
    *
    * This function set the number of DD posseded by the player.
    *
    * @return an error that specify what is the problem
    */
    ErrorCode map_setNumberDD( Map* m, int val );

#endif //PRIM_MAP_H
