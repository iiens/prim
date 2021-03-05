/*!
 * \file map.h
 * \author Antoine MAN
 * \version 0.1
 * \date 28/02/2021
 * \see Difficulty
 *
 * This header contains any functions related to the interactions
 * between the player and the elements on the board game.
 * <ul>
 * <li>create a new map</li>
 * <li>detroy a map</li>
 * <li>hire a FISE</li>
 * <li>hire a FISA</li>
 * <li>switch energy type produced by the FISA </li>
 * <li>finish a turn</li>
 * </ul>
 *
 */

#ifndef PRIM_MAP_H
#define PRIM_MAP_H

    #include "machine.h" //!< information about machine
    #include "staff.h" //!< information about staff
    #include "difficulty.h" //!< difficulty of the game

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
    #define CASE_VIDE 0 //!< todo
    #define CASE_GATE 1 //!< todo
    #define CASE_SOURCE 2 //!< todo
    #define CASE_MACHINE 3 //!< todo
    #define E 0 //!< todo
    #define DD 1 //!< todo

    /*!
     * \typedef Case
     * \struct case_s map.h "headers/data/map.h"
     * \param x: abscissa
     * \param y: ordinate
     * \param in: it correspond to the object contained in the case
     * \param type: type of object contained in the case
     *
     * Struct that contains all the information concerning a case
     *
     */
    typedef struct case_s {
        int x; //!< int, abscissa
        int y; //!< int, ordinate
        union {
            machine mach;
            // à compléter ///////////////////////////////////////////////
        } in; //!< int, it correspond to the object contained in the case
        int type; //!< int, type of object contained in the case
    } Case; //!< todo

    /*!
     * \typedef Map
     * \struct Map_s map.h "headers/data/map.h"
     * \param width: int, map width
     * \param height: int, map height
     * \param map: a bi dimensional table to refer to 
     * the board of game where each emplacement is a case (struct)
     * \param turn: int, an indicator to correspond to the actual turn of the game
     * \param numberFISE: as the name suggest, its corresponding to the number of FISE
     * \param numberFISA: as the name suggest, its corresponding to the number of FISA
     * \param E: a value that measure the energy quantity of the player
     * \param DD: a value that measure the planet general health
     * \param productionFISA: int, it correspond to the energy type produced by the FISA
     *
     * Struct that contains all the map information concerning machines 
     * emplacement, sources, resources, garbage, staff and gate, presents on the map.
     *
     */
    typedef struct Map_s {
        int width; //!< int, map width
        int height; //!< int, map height
        Case** map; //!< a bi dimensional tableto refer to the board of game
        uint turn; //!< int, an indicator to correspond to the actual turn of the game
        uint numberFISE; //!< as the name suggest, its corresponding to the number of FISE
        uint numberFISA; //!< as the name suggest, its corresponding to the number of FISA
        uint E; //!< a value that measure the energy quantity of the player
        uint DD; //!< a value that measure the planet general health
        int productionFISA; //!< int, it correspond to the energy type produced by the FISA
    } Map; //!< todo

    
    //\////////////////////////////\//
    //\/ Functions declarations
    //\////////////////////////////\//

    /*!
     * \fn const Map* map_create(Difficulty dif)
     * @brief Create a new map
     *
     * In order to begin a new game, we need a board game.
     * It will contains all the map information concerning machines 
     * emplacement, sources, resources, garbage, staff and gate, presents on the map.
     *
     * @param[in] dif a valid difficulty chosen by the user
     * @return a new map that contains all the map information
     * @see Map type
     * @see Difficulty enum
     */
    const Map* map_create(Difficulty dif);

    /*!
     * \fn int map_destroy(const Map* map)
     * @brief Destroy a map
     *
     * At the end of a game, we need to free all the memory allocated
     * to a map.
     *
     * @param[in] map a map
     * @return an int in order to know if everythings worked well
     * @see Map type
     */
    int map_destroy(const Map* map);
    
    /*!
     * \fn int map_hireFISE(const Map* map)
     * @brief Hire a FISE
     *
     * We hire a FISE in order to product more resources.
     * Every turn, each FISE student produce 1 E and 1 DD
     *
     * @param[in] map a map
     * @return an int in order to know if everythings worked well
     * @see Map type
     */
    int map_hireFISE(const Map* map);
    
    /*!
     * \fn int map_hireFISA(const Map* map)
     * @brief Hire a FISA
     *
     * We hire a FISA in order to product more resources.
     * Every 2 turns, each FISA student produce either 4 E or 4 DD
     *
     * @param[in] map a map
     * @return an int in order to know if everythings worked well
     * @see Map type
     */
    int map_hireFISA(const Map* map);
    
    /*!
     * \fn int map_changeProductionFISA()
     * @brief Switch the energy type produced by the FISA
     *
     * This function allow us to switch the energy type 
     * produced by the FISA between E or DD.
     *
     * @return an int in order to know if everythings worked well
     */
    int map_changeProductionFISA();
    
     /*!
     * \fn int map_endTurn()
     * @brief Finish a turn
     *
     * Finish a turn
     *
     * @return an int in order to know if everythings worked well
     */
    int map_endTurn();

    /*!
     * \fn int map_addMachine(const Machine machine, const int x, const int y, Map* m)
     * @brief Add a machine 
     * @param[in] machine a machine
     * @param[in] x x > 0 
     * @param[in] y y > 0 
     * @param[in,out] m a map 
     * Add a machine on the map
     *
     * @return 1 if true else 0 
     */
    int map_addMachine(const Machine machine, const int x, const int y, Map* m); 

    /*!
     * \fn int map_upgradeMachine(const int x,const int y, Map* m)
     * @brief Upgrade a machine 
     * @param[in] x x > 0 
     * @param[in] y y > 0 
     * @param[in,out] m a map 
     * Upgrade a machine on the map. We know which machine we upgrade thanks 
     * to the x and y coordinates
     *
     * @return 1 if true else 0 
     */
    int map_upgradeMachine(const int x,const int y, Map* m); 

    /*!
     * \fn int map_destroyMachine(const int x,const int y, Map* m)
     * @brief Destroy a machine 
     * @param[in] x x > 0 
     * @param[in] y y > 0 
     * @param[in,out] m a map 
     * Destroy a machine on the map. We know which machine we destroy thanks 
     * to the x and y coordinates
     *
     * @return 1 if true else 0 
     */
    int map_destroyMachine(const int x,const int y, Map* m);

    /*!
     * \fn int map_buyStaff(Staff s, Map* m)
     * @brief Buy a staff 
     * @param[in] s a Staff 
     * @param[in,out] m a map 
     * Buy a staff 
     * 
     * @return 1 if true else 0 
     */
    int map_buyStaff(Staff s, Map* m);
    
#endif //PRIM_MAP_H
