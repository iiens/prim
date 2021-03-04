/*!
 * \author Antoine MAN
 * \version 0.1
 * \date 28/02/2021
 * \see Difficulty
 * \see Map
 * @file map.h
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
    #define CASE_VIDE 0
    #define CASE_GATE 1
    #define CASE_SOURCE 2
    #define CASE_MACHINE 3
    #define E 0
    #define DD 1

    /*!
     * \struct case map.h "headers/data/map.h"
     * \typedef case
     * \param x: abscissa
     * \param y: ordinate
     * \param in: it correspond to the object contained in the case
     * \param type: type of object contained in the case
     *
     * Struct that contains all the information concerning a case
     *
     */
    typedef struct case {
        int x; //!< int, abscissa
        int y; //!< int, ordinate
        union {
            machine mach;
            // à compléter ///////////////////////////////////////////////
        } in; //!< int, it correspond to the object contained in the case
        int type; //!< int, type of object contained in the case
    } case;

    /*!
     * \struct map map.h "headers/data/map.h"
     * \typedef map
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
    typedef struct Map {
        int width; //!< int, map width
        int height; //!< int, map height
        case** map; //!< a bi dimensional tableto refer to the board of game
        uint turn; //!< int, an indicator to correspond to the actual turn of the game
        uint numberFISE; //!< as the name suggest, its corresponding to the number of FISE
        uint numberFISA; //!< as the name suggest, its corresponding to the number of FISA
        uint E; //!< a value that measure the energy quantity of the player
        uint DD; //!< a value that measure the planet general health
        int productionFISA; //!< int, it correspond to the energy type produced by the FISA
    } Map;

    
    //\////////////////////////////\//
    //\/ Functions declarations
    //\////////////////////////////\//

    /*!
     * \fn const Map* map_create
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
     * \fn int map_destroy
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
     * \fn int map_hireFISE
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
     * \fn int map_hireFISA
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
     * \fn int map_changeProductionFISA
     * @brief Switch the energy type produced by the FISA
     *
     * This function allow us to switch the energy type 
     * produced by the FISA between E or DD.
     *
     * @return an int in order to know if everythings worked well
     */
    int map_changeProductionFISA();
    
     /*!
     * \fn int map_endTurn
     * @brief Finish a turn
     *
     * Finish a turn
     *
     * @return an int in order to know if everythings worked well
     */
    int map_endTurn();
    
#endif //PRIM_MAP_H
