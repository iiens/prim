/*!
 * \file case_type.h
 * \author Antoine Man
 * \version 0.1
 * \date 11/03/2021
 * \see map.h
 *
 * Contains all the types that a case can contain.
 *
 */
#ifndef PRIM_CASE_H
#define PRIM_CASE_H

    #include "machine.h"
    #include "error.h"

    /*!
     * \typedef CaseType
     * \enum CaseType_S case_type.h "headers/data/case_type.h"
     * \brief all case type
     *
     * Contains all type that a case can contain.
     * Each case can contain 4 elements types :
     * a part of the production line
     * a resource case
     * an empty case
     * a transdimensional gate
     *
     * 3 resources is produced from a resource case every 10 turns
     *
     */
    typedef enum CaseType_S {
        CASE_VIDE = 0, //!< a case that contain nothing
        CASE_GATE = 1, //!< a case that contain the transdimensional gate
        CASE_SOURCE = 2, //!< a case that contain resources
        CASE_MACHINE = 3, //!< a case that contain a machine
        CASE_BOX = 4, //!< a case that contain a box
    } CaseType; //!< Case type

    /*!
     * \typedef Box
     * \struct Box_S map.h "headers/map.h"
     *
     * Struct that contains all the information concerning a box
     * It contain resources and garbage on a case
     *
     */
    typedef struct Box_S Box;

    //todo: Antoine documentation
    typedef struct Facade_S Facade;

    /*!
     * \typedef Case
     * \struct Case_S map.h "headers/map.h"
     *
     * Struct that contains all the information concerning a case
     *
     */
    typedef struct Case_S Case;

    /*!
    * \fn int case_getX(const Case* c)
    * @brief a function to get the case abscissa
    * @param[in] Case* a case
    *
    * @return the case abscissa
    */
    int case_getX(const Case* c);

    /*!
    * \fn int case_getY(const Case* c)
    * @brief a function to get the case ordinate
    * @param[in] Case* a case
    *
    * @return the case ordinate
    */
    int case_getY(const Case* c);

    /*!
    * \fn int box_getNumberResource(const Box* c)
    * @brief a function to get the number of resources
    * @param[in] Box* a box
    *
    * This function get the number of resources of the box.
    *
    * @return the number of resources available in the box
    */
    int box_getNumberResource(const Box* c);

    /*!
    * \fn int box_getNumberGarbage(const Box* c)
    * @brief a function to get the number of garbage
    * @param[in] Box* a box
    *
    * This function get the number of garbage of the box.
    *
    * @return the number of garbage available in the box
    */
    int box_getNumberGarbage(const Box* c);

    /*!
    * \fn CaseType case_getType(const Case* c)
    * @brief a function to get the type case of the case
    * @param[in] Case* a case
    *
    * This function get the type case of the case
    * <ul>
    *   <li> CASE_VIDE = 0, a case that contain nothing
    *   <li> CASE_GATE = 1, a case that contain the transdimensional gate
    *   <li> CASE_SOURCE = 2, a case that contain resources
    *   <li> CASE_MACHINE = 3, a case that contain a machine
    * </ul>
    *
    * @return the type case if case exist, if not -1
    */
    CaseType case_getType(const Case* c);

    /*!
    * \fn Machine* case_getMachine(const Case* c)
    * @brief a function to get a located machine on the map
    * @param[in] Case* a case
    *
    * This function get a located machine on the map
    *
    * @return a located machine on the map if exist
    */
    Machine* case_getMachine(const Case* c);

    /*!
    * \fn Box* case_getBox(const Case* c)
    * @brief a function to get a located box on the map
    * @param[in] Case* a case
    *
    * This function get a located box on the map
    *
    * @return a located box on the map if exist
    */
    Box* case_getBox(const Case* c);

    /*!
    * \fn ErrorCode box_setNumberResource(Box * c, int val )
    * @brief a function to set the number of resources
    * @param[in] Box* a box
    * @param[in] val a resource value to add/to substract
    *
    * This function set the number of resources of the box
    *
    * @return an error that specify what is the problem
    */
    ErrorCode box_setNumberResource(Box * c, int val );

    /*!
    * \fn ErrorCode box_setNumberGarbage(Box * c, int val )
    * @brief a function to set the number of garbage
    * @param[in] Box* a box
    * @param[in] val a resource value to add/to substract
    *
    * This function set the number of garbage of the box
    *
    * @return an error that specify what is the problem
    */
    ErrorCode box_setNumberGarbage(Box * c, int val );

    /*!
    * \fn Case* case_create(nt x, int y)
    * @brief a function to create a new case
    * @param[in] int x
    * @param[in] int y
    *
    * @return a new case
    */
    Case* case_create(int x, int y);

    /*!
    * \fn void case_addMachine(Case* c, Machine* mach)
    * @brief a function to add a machine on an empty case
    * @param[in] Case* c
    * @param[in] Machine* mach
    *
    */
    void case_addMachine(Case* c, Machine* mach);

    /*!
    * \fn void case_addGate(Case* c)
    * @brief a function to add a gate on an empty case
    * @param[in] Case* c
    *
    */
    void case_addGate(Case* c);

    /*!
    * \fn void case_addSource(Case* c)
    * @brief a function to add a source on an empty case
    * @param[in] Case* c
    *
    */
    void case_addSource(Case* c);
    bool case_isEmpty(const Case* c);
    bool case_hasBox(const Case* c);
//TODO ANTOINE DOC
    ErrorCode case_destroy(Case* c);

#endif //PRIM_CASE_H