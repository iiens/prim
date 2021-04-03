/*!
 * \file staff.h
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 04/03/2021
 * \see effect.h
 *
 * Contains all information about the character of the Staff
 */
#ifndef PRIM_STAFF_H
#define PRIM_STAFF_H

    #include "effect.h" // effect.h : information about effect

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
        Effect effects[20]; //!< array which contains the target of the effect
    } Staff; //!< information about staff

    #define NUMBER_OF_STAFFS 21 //!< number of staff in staff_list

    extern const Staff staff_list[]; //!< contains all of the staff

#endif //PRIM_STAFF_H