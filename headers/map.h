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
 */

#ifndef PRIM_MAP_H
#define PRIM_MAP_H

#include <stdbool.h> // return value
#include "data/machine_info.h" // information about machine
#include "data/staff.h" // information about Staff
#include "data/difficulty.h" // difficulty of the game
#include "data/error.h" // errors messages
#include "data/case.h" // case type (empty, source, gate, machine)

#define E_VALUE 0 //!< E Constant that measure the energy quantity of the player
#define DD_VALUE 1 //!< DD Constant that measure the planet general health

/*!
 * \typedef Map
 * \struct Map_S map.h "headers/map.h"
 *
 * Struct that contains all the map information concerning machines
 * emplacement, sources, resources, garbage, Staff and gate, presents on the map.
 *
 */
typedef struct Map_S Map; //!< documentation above

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
Map *map_create(Difficulty dif);

/*!
 * \fn ErrorCode map_destroy( Map* m )
 * @param[in] m a map
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
 * @return an error that specify what is the problem
 * @see Map type
 */
ErrorCode map_destroy(Map *m);

/*!
 * \fn ErrorCode map_hireFISE(Map* m)
 * @brief Hire a FISE
 *
 * We hire a FISE in order to product more resources.
 * Every turn, each FISE student produce 1 E and 1 DD
 * A student (FISE or FISA) costs 50 E and 20 DD.
 *
 * A verification is necessary to know if the player can hire a new FISE.
 * We have to check resources E and DD of the player
 *
 * @param[in] m a map
 * @return an error that specify what is the problem
 * @see Map type
 */
ErrorCode map_hireFISE(Map *m);

/*!
 * \fn ErrorCode map_hireFISA(Map* m)
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
 * @param[in] m a map
 * @return an error that specify what is the problem
 * @see Map type
 */
ErrorCode map_hireFISA(Map *m);

/*!
 * \fn ErrorCode map_changeProductionFISA( Map* m )
 * @brief Switch the energy type produced by the FISA
 *
 * This function allow us to switch the energy type
 * produced by the FISA between E or DD.
 *
 * @param[in] m a map
 * @return an error that specify what is the problem
 * @see Map type
 */
ErrorCode map_changeProductionFISA(Map *m);

/*!
 * \fn ErrorCode map_endTurn(Map* m)
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
 * \param m game map
 * \return an error that specify what is the problem
*/
ErrorCode map_endTurn(Map *m);

/**
 * Add a machine on the map
 * @param type a machine
 * @param rotation
 * @param x x > 0
 * @param y y > 0
 * @param m a map
 * @return error that specify what is the problem
 */
ErrorCode map_addMachine(MachineStuff type, int rotation, int x, int y, Map *m);

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
ErrorCode map_upgradeMachine(int x, int y, Map *m);

/*!
 * \fn ErrorCode map_destroyMachine( int x, int y, Map* m )
 * @brief Destroy a machine
 * @param[in] x x > 0
 * @param[in] y y > 0
 * @param[in,out] m a map
 * Destroy a machine on the map. We know which machine we destroy thanks
 * to the x and y coordinates
 *
 * @return an error that specify what is the problem
 */
ErrorCode map_destroyMachine(int x, int y, Map *m);

/*!
 * \fn ErrorCode map_buyStaff( int idStaff, Map* m )
 * @brief Buy a Staff
 * @param[in] idStaff a int
 * @param[in,out] m a Map*
 * Buy a Staff
 *
 * @return an error that specify what is the problem
 */
ErrorCode map_buyStaff(int idStaff, Map *m);

/*!
* \fn ErrorCode map_isCaseExist( int x, int y, const Map* m );
* @brief In order to verify if a case exist
* @param[in] x case abscissa
* @param[in] y case ordinate
* @param[in] m a map
* @return an error that specify what is the problem
*/
ErrorCode map_isCaseExist(int x, int y, const Map *m);

/*!
* \fn int map_getNumberFISE( const Map* m )
* @brief a function to get the number of FISE
* @param[in] m a map
*
* This function get the number of FISE recruited by the player.
*
* @return the number of FISE available
*/
int map_getNumberFISE(const Map *m);

/*!
* \fn int map_getNumberFISA( const Map* m )
* @brief a function to get the number of FISA
* @param[in] m a map
*
* This function get the number of FISA recruited by the player.
*
* @return the number of FISA available
*/
int map_getNumberFISA(const Map *m);

/*!
* \fn int map_getNumberE( const Map* m )
* @brief a function to get the number of E
* @param[in] m a map
*
* This function get the number of E posseded by the player.
*
* @return the number of E available
*/
int map_getNumberE(const Map *m);

/*!
* \fn int map_getNumberDD( const Map* m )
* @brief a function to get the number of DD
* @param[in] m a map
*
* This function get the number of DD posseded by the player.
*
* @return the number of DD available
*/
int map_getNumberDD(const Map *m);

/*!
* \fn int map_getPlayerScore( const Map* m )
* @brief a function to get the player score
* @param[in] m a map
*
* This function get the player score.
* 10 000 points to win the game
*
* @return the score
*/
int map_getPlayerScore(const Map *m);

/*!
* \fn Difficulty map_getDifficulty( const Map* m )
* @brief a function to get the difficulty of the map
* @param[in] m a map
*
* This function get the difficulty of the map.
* EASY level : 10 x 10
* MEDIUM level : 20 x 20
* HARD level : 30 x 30
*
* @return the difficulty
*/
Difficulty map_getDifficulty(const Map *m);

/*!
* \fn int map_getWidth( const Map* m )
* @brief a function to get map width
* @param[in] m a map
*
* This function get map width.
*
* @return the map width.
*/
int map_getWidth(const Map *m);

/*!
* \fn int map_getHeight( const Map* m )
* @brief a function to get map height
* @param[in] m a map
*
* This function get map height.
*
* @return the map height.
*/
int map_getHeight(const Map *m);

/*!
* \fn int map_getNumberTurn( const Map* m )
* @brief a function to get the number of turn
* @param[in] m a map
*
* This function get the number of turn
*
* @return the number of turn
*/
int map_getNumberTurn(const Map *m);

/**
 * a function to get the production of FISA
 * @param m a map
 * @return the production of FISA
 */
int map_getProductionFISA(const Map *m);

/*!
* \fn int map_getStaffDictionary( const Map* m )
* @brief a function to get the staff dictionary
* @param[in] m a map
*
* This function get the staff dictionary
*
* @return the staff dictionary
*/
Dictionary *map_getStaffDictionary(const Map *m);

/*!
* \fn Case* map_getCase( int x, int y, const Map* m );
* @brief a function to get a case of the map
* @param[in] x case abscissa
* @param[in] y case ordinate
* @param[in] m a map
*
* This function get a case of the map
*
* @return the case address if exist, if not a null address
*/
Case *map_getCase(int x, int y, const Map *m);

/*!
* \fn int map_getNumberPollution(  const Map* m );
* @brief a function to get the pollution number
* @param[in] m a map
*
* This function get the pollution number
* In order to have this information, we have to sum each case garbage
*
* @return the pollution number
*/
int map_getNumberPollution(const Map *m);

/*!
* \fn ErrorCode map_setNumberFISE( Map* m, int val)
* @brief a function to set the number of FISE
* @param[in] m a map
* @param[in] val number of FISE to add/to substract
*
* This function set the number of FISE recruited by the player.
*
* @return an error that specify what is the problem
*/
ErrorCode map_setNumberFISE(Map *m, int val);

/*!
* \fn ErrorCode map_setNumberFISA( Map* m, int val )
* @brief a function to set the number of FISA
* @param[in] m a map
* @param[in] val number of FISA to add/to substract
*
* This function set the number of FISA recruited by the player.
*
* @return an error that specify what is the problem
*/
ErrorCode map_setNumberFISA(Map *m, int val);

/*!
* \fn ErrorCode map_setNumberE( Map* m, int val )
* @brief a function to set the number of E
* @param[in] m a map
* @param[in] val E value to add/to substract
*
* This function set the number of E posseded by the player.
*
* @return an error that specify what is the problem
*/
ErrorCode map_setNumberE(Map *m, int val);

/*!
* \fn ErrorCode map_setNumberDD( Map* m, int val )
* @brief a function to set the number of DD
* @param[in] m a map
* @param[in] val DD value to add/to substract
*
* This function set the number of DD posseded by the player.
*
* @return an error that specify what is the problem
*/
ErrorCode map_setNumberDD(Map *m, int val);

/*!
* \fn ErrorCode map_setNumberScore( Map* m, int val )
* @brief a function to set the score
* @param[in] m a map
* @param[in] val DD value to add/to substract
*
* This function set the score
*
* @return an error that specify what is the problem
*/
ErrorCode map_setNumberScore(Map *m, int val);

/*!
* \fn ErrorCode map_setNumberTurn( Map* m, int val )
* @brief a function to set the turn
* @param[in] m a map
* @param[in] val DD value to add/to substract
*
* This function set the turn
*
* @return an error that specify what is the problem
*/
ErrorCode map_setNumberTurn(Map *m, int val);

#endif //PRIM_MAP_H
