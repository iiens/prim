/*!
 * \file case.h
 * \author Antoine Man
 * \version 0.1
 * \date 11/03/2021
 * \see map.h
 * \see machine.h
 * \see error.h
 * \see box.h
 *
 * Contains all the types that a case can contain and all
 * interactions possible with it
 *
 */

#ifndef PRIM_CASE_H
#define PRIM_CASE_H

#include "machine.h"
#include "error.h"
#include "box.h"

/*!
 * \typedef CaseType
 * \enum CaseType_S
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
 * In order to know if a case contain a box (that contain resources and garbage),
 * we use the first bit of an integer.
 * The case contain a box -> odd number
 * The case does not contain a box -> even number
 *
 */
typedef enum CaseType_S {
    CASE_VIDE = 0, //!< a case that contain nothing
    CASE_GATE = 2, //!< a case that contain the transdimensional gate
    CASE_SOURCE = 4, //!< a case that contain resources
    CASE_MACHINE = 6, //!< a case that contain a machine
} CaseType; //!< Case type

/*!
 * \typedef Case
 * \struct Case_S case.h "headers/data/case.h"
 *
 * Struct that contains all the information concerning a case
 *
 */
typedef struct Case_S Case; //!< documentation above

/**
 * A function to get the case abscissa
 * @param c case
 * @return the case abscissa
 */
int case_getX(const Case *c);

/**
 * A function to get the case ordinate
 * @param c case
 * @return the case ordinate
 */
int case_getY(const Case *c);

/**
 * This function get the type case of the case
 * <ul>
 *   <li> CASE_VIDE = 0, a case that contain nothing
 *   <li> CASE_GATE = 1, a case that contain the transdimensional gate
 *   <li> CASE_SOURCE = 2, a case that contain resources
 *   <li> CASE_MACHINE = 3, a case that contain a machine
 * </ul>
 * @param c a case
 * @return the type case if case exist, if not -1
 */
CaseType case_getType(const Case *c);

/**
 * This function get a located machine on the map
 * @param c case
 * @return a located machine on the map if exist
 */
Machine *case_getMachine(const Case *c);

/**
 * This function get a located box on the map
 * @param c case
 * @return a located box on the map if exist
 */
Box *case_getBox(const Case *c);

/**
 * This function get number of resources from a case
 * @param c case
 * @return resources from a case if exist
 */
int case_getNumberResourcesByCase(const Case *c);

/**
 * This function get number of garbage from a case
 * @param c case
 * @return garbage from a case if exist
 */
int case_getNumberGarbageByCase(const Case *c);

/**
 * A function to create a new case
 * @param x case abscissa
 * @param y case ordinate
 * @return a new case
 */
Case *case_create(int x, int y);

/**
 * A function to add a machine on an empty case
 * @param c case
 * @param mach machine
 */
void case_addMachine(Case *c, Machine *mach);

/**
 * A function to add a gate on an empty case
 * @param c case
 */
void case_addGate(Case *c);

/**
 * A function to add a source on an empty case
 * @param c case
 */
void case_addSource(Case *c);

/**
 * A function to add a box on an empty case
 * @param c case
 * @param box box
 */
void case_addBox(Case *c, Box *box);

/**
 * A function to remove the box on a located case
 * @param c case
 * @return an error code to know what happen
 */
ErrorCode case_deleteBox(Case *c);

/**
 * A function to remove everything on the case
 * if there is a box or a machine
 * @param c case
 */
void case_setEmpty(Case *c);

/**
 * A function to know if there is something on the case (box, machine)
 * To know if we are allowed to create something on
 * @param c case
 * @return true if there is nothing on, if not false
 */
bool case_isEmpty(const Case *c);

/**
 * A function to know if there is a box on the case
 * In order to know it, we have to analyze the first bit of the type case.
 * If the number is odd, there is a box
 * If the number is even, there is nothing
 * @param c case
 * @return true if there is a box, if not false
 */
bool case_hasBox(const Case *c);

/**
 * A function to free allocated resources in memory in order to
 * stock the case.
 * A case can contain a box or a machine.
 * @param c case
 */
void case_destroy(Case *c);

#endif //PRIM_CASE_H