/*!
 * \file staff.h
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 04/03/2021
 * \see effect.h
 *
 * Contains all information about the character of the staff
 */

#ifndef PRIM_STAFF_H
#define PRIM_STAFF_H

    #include "effect.h" //!< information about effect

    /*!
    * \typedef staff
     * \struct Staff staff.h "headers/data/staff.h"
     * \param Id: int, id of the character
     * \param Name: char *, name of the character
     * \param Cost_E: uint, price in E of the character
     * \param Cost_DD: uint, price in DD of the character 
     * \param Description: char *, description of character effects
     * \param Effect_s: Effect[], contains the target of the effect  
     *
     * Struct which contains the target of the effect
     *
     */
    typedef struct Staff{
        int Id; //!< Id of the character
        char * Name; //!< Name of the character
        uint Cost_E; //!< Price in E of the character
        uint Cost_DD; //!< Price in DD of the character
        char * Description; //!< Description of character effects
        Effect Effect_s[]; //!< array which contains the target of the effect
    } staff;

#endif //PRIM_STAFF_H