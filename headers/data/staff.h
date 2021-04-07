/*!
 * \file staff.h
 * \author Ramzy ZEBRIR
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

    #define NUMBER_OF_STAFFS 21 //!< number of staff in staff_list

    /*!
    * \fn int staff_isIDValid(int id)
    * @brief a function in order to verify if a staff id exist
    * @param[in] id an id
    *
    * @return index if exist, -1 if not
    */
    int staff_isIDValid(int id);

    /*!
    * \fn Staff* staff_getStaffByID(int id)
    * @brief a function to get the staff according to the id
    * @param[in] id an id
    *
    * This function get the staff according to the id in order
    * to get all the information about him.
    *
    * @return the staff according to the id
    */
    const Staff* staff_getStaffByID(int id);

    /*!
    * \fn char* staff_getStaffNameByID(int id)
    * @brief a function to get the staff name according to the id
    * @param[in] id an id
    *
    * This function get the staff name according to the id
    *
    * @return the staff name according to the id
    */
    char* staff_getStaffNameByID(int id);

    /*!
    * \fn int staff_getStaffCostEByID(int id)
    * @brief a function to get the staff cost E according to the id
    * @param[in] id an id
    *
    * This function get the staff cost E according to the id
    *
    * @return the staff cost E according to the id
    */
    int staff_getStaffCostEByID(int id);

    /*!
    * \fn int staff_getStaffCostDDByID(int id)
    * @brief a function to get the staff cost DD according to the id
    * @param[in] id an id
    *
    * This function get the staff cost DD according to the id
    *
    * @return the staff cost DD according to the id
    */
    int staff_getStaffCostDDByID(int id);

    /*!
    * \fn char* staff_getStaffDescriptionByID(int id)
    * @brief a function to get the staff description according to the id
    * @param[in] id an id
    *
    * This function get the staff description according to the id
    *
    * @return the staff description according to the id
    */
    char* staff_getStaffDescriptionByID(int id);

    /*!
    * \fn Effect staff_getStaffEffectByID(int id)
    * @brief a function to get the staff effect according to the id
    * @param[in] id an id
    *
    * This function get the staff effect according to the id
    *
    * @return the staff effect according to the id
    */
    const Effect* staff_getStaffEffectByID(int id);

    /*!
    * \fn char* staff_getStaffNameByID(const Staff *staff)
    * @brief a function to get the staff id of the staff member
    * @param[in] const Staff *staff
    *
    * This function get the staff id of the staff member
    *
    * @return the staff id of the staff member
    */
    int staff_getStaffID(const Staff *staff);

    /*!
    * \fn char* staff_getStaffNameByID(const Staff *staff)
    * @brief a function to get the staff name of the staff member
    * @param[in] const Staff *staff
    *
    * This function get the staff name of the staff member
    *
    * @return the staff name of the staff member
    */
    char* staff_getStaffName(const Staff *staff);

    /*!
    * \fn int staff_getStaffCostEByID(const Staff *staff)
    * @brief a function to get the staff cost E of the staff member
    * @param[in] const Staff *staff
    *
    * This function get the staff cost E of the staff member
    *
    * @return the staff cost E of the staff member
    */
    int staff_getStaffCostE(const Staff *staff);

    /*!
    * \fn int staff_getStaffCostDDByID(const Staff *staff)
    * @brief a function to get the staff cost DD of the staff member
    * @param[in] const Staff *staff
    *
    * This function get the staff cost DD of the staff member
    *
    * @return the staff cost DD of the staff member
    */
    int staff_getStaffCostDD(const Staff *staff);

    /*!
    * \fn char* staff_getStaffDescriptionByID(const Staff *staff)
    * @brief a function to get the staff description of the staff member
    * @param[in] const Staff *staff
    *
    * This function get the staff description of the staff member
    *
    * @return the staff description of the staff member
    */
    char* staff_getStaffDescription(const Staff *staff);

    /*!
    * \fn Effect staff_getStaffEffectByID(const Staff *staff)
    * @brief a function to get the staff effect of the staff member
    * @param[in] const Staff *staff
    *
    * This function get the staff effect of the staff member
    *
    * @return the staff effect of the staff member
    */
    const Effect* staff_getStaffEffect(const Staff *staff);

    //TODO ANTOINE FAIRE LA DOC
    const Staff *staffInfo_getByModeAndType(Mode mode, Target type);

    // creer la liste de staff
    Dictionary* staff_createStaffDictionary();

    // get le nombre d'un staff particulier
    int staff_getNumberStaffByID(const Dictionary* dict, int id);

    // incremente le nombre d'un staff particulier
    void staff_hireStaff(Dictionary* dict, int id);

    ErrorCode staff_destroyStaffDictionary(Dictionary* dict);



#endif //PRIM_STAFF_H