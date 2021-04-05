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

    /*!
     * \typedef Staff
     * \struct Staff_S staff.h "headers/data/staff.h"
     * \brief Struct which contains the target of the effect
     */
    typedef struct Staff_S {
        int id; //!< id of the character
        char* name; //!< name of the character
        int costE; //!< Price in E of the character
        int costDD; //!< Price in DD of the character
        char* description; //!< description of character effects
        Effect effects; //!< array which contains the target of the effect
    } Staff; //!< information about staff

    #define NUMBER_OF_STAFFS 21 //!< number of staff in staff_list

    extern const Staff staff_list[]; //!< contains all of the staff

    /*!
    * \fn ErrorCode staff_isIDValid(int id)
    * @brief a function in order to verify if a staff id exist
    * @param[in] id an id
    *
    * @return an error that specify what is the problem
    */
    ErrorCode staff_isIDValid(int id);

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
    Effect* staff_getStaffEffectByID(int id);


#endif //PRIM_STAFF_H