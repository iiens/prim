/*!
 * \file staff.h
 * \author Ramzy ZEBRIR and Antoine MAn
 * \version 0.1
 * \date 04/03/2021
 * \see effect.h
 * \see error.h
 *
 * Contains all information about the character of the Staff
 */

#ifndef PRIM_STAFF_H
#define PRIM_STAFF_H

#include "effect.h" // effect.h : information about effect
#include "error.h" // error.h : errors messages
#include "../utils/structures.h" //! to use type List

/*!
 * \typedef Staff
 * \struct Staff_S staff.h "headers/data/staff.h"
 * \brief Struct which contains the target of the effect
 */
typedef struct Staff_S Staff;

#define NUMBER_OF_STAFFS 24 //!< number of staff in staff_list

/**
 * a function in order to verify if a staff id exist
 * @param id
 * @return tab index if exist, -1 if not
 */
int staff_isIDValid(int id);

/**
 * This function get the staff according to the id in order
 * to get all the information about him.
 * @param id
 * @return the staff according to the id
 */
const Staff *staff_getStaffByID(int id);

/**
 * This function get the staff name attribute according to the id
 * @param id
 * @return the staff name according to the id
 */
char *staff_getStaffNameByID(int id);

/**
 * This function get the staff cost E attribute according to the id
 * @param id
 * @return the staff cost E according to the id
 */
int staff_getStaffCostEByID(int id);

/**
 * This function get the staff cost DD attribute according to the id
 * @param id
 * @return the staff cost DD according to the id
 */
int staff_getStaffCostDDByID(int id);

/**
 * This function get the staff description attribute according to the id
 * @param id
 * @return the staff description according to the id
 */
char *staff_getStaffDescriptionByID(int id);

/**
 * This function get the staff effect attribute according to the id
 * @param id
 * @return the staff effect according to the id
 */
const Effect *staff_getStaffEffectByID(int id);

/**
 * This function get the staff id attribute from a staff
 * @param id
 * @return the staff id from a staff
 */
int staff_getStaffID(const Staff *staff);

/**
 * This function get the staff name attribute from a staff
 * @param id
 * @return the staff name from a staff
 */
char *staff_getStaffName(const Staff *staff);

/**
 * This function get the staff cost E attribute from a staff
 * @param id
 * @return the staff cost E from a staff
 */
int staff_getStaffCostE(const Staff *staff);

/**
 * This function get the staff CostDD attribute from a staff
 * @param id
 * @return the staff CostDD from a staff
 */
int staff_getStaffCostDD(const Staff *staff);

/**
 * This function get the staff description attribute from a staff
 * @param id
 * @return the staff description from a staff
 */
char *staff_getStaffDescription(const Staff *staff);

/**
 * This function get the staff effect attribute from a staff
 * @param id
 * @return the staff effect from a staff
 */
const Effect *staff_getStaffEffect(const Staff *staff);

/**
 * This function get the TurnProduction attribute from a effect
 * @param id
 * @return the TurnProduction from a effect
 */
int effect_getTurnProduction(const Effect *effect);

/**
 * This function get the MinTurnProduction attribute from a effect
 * @param id
 * @return the MinTurnProduction from a effect
 */
int effect_getMinTurnProduction(const Effect *effect);

/**
 * A function to get a specific staff according to his Mode and his Target
 * in order to get all the information about a staff
 * @param mode
 * @param type
 * @return a specific staff
 */
const Staff *staffInfo_getByModeAndType(Mode mode, Target type);

/**
 * A function to create a staff dictionnary which for each staff, his id and the number of staff hired
 * @return Dictionary
 */
Dictionary *staff_createStaffDictionary();

/**
 * A function to get the number of staff hired according to the id staff
 * @param dict
 * @param id
 * @return the number of staff hired
 */
int staff_getNumberStaffByID(const Dictionary *dict, int id);

/**
 * A function to incremente the number of a specific staff (hire)
 * @param dict
 * @param id
 */
void staff_hireStaff(Dictionary *dict, int id);

/**
 * A function to free allocated resources in memory in order to
 * stock the staff dictionnary
 * @param dict
 */
void staff_destroyStaffDictionary(Dictionary *dict);

#endif //PRIM_STAFF_H