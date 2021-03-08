/*!
 * \file Staff.h
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 04/03/2021
 * \see effect.h
 *
 * Contains all information about the character of the Staff
 */
#ifndef PRIM_STAFF_H
#define PRIM_STAFF_H

    #include "effect.h" //!< information about effect

    /*!
    * \typedef Staff
     * \struct Staff_S Staff.h "headers/data/Staff.h"
     * \param id: int, id of the character
     * \param name: char *, name of the character
     * \param cost_E: uint, price in E of the character
     * \param cost_DD: uint, price in DD of the character
     * \param description: char *, description of character effects
     * \param Effect_S: Effect_S[], contains the target of the effect
     *
     * Struct which contains the target of the effect
     *
     */
    typedef struct Staff_S {
        int Id; //!< Id of the character
        char* Name; //!< Name of the character
        uint Cost_E; //!< Price in E of the character
        uint Cost_DD; //!< Price in DD of the character
        char* Description; //!< Description of character effects
        Effect Effect_S[]; //!< array which contains the target of the effect
    } Staff; //!< information about staff

#endif //PRIM_STAFF_H