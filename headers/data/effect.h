/*!
 * \file effect.h
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 04/03/2021
 * \see staff.h
 *
 * Contains information about effects
 */
#ifndef PRIM_EFFECT_H
#define PRIM_EFFECT_H

    /*!
     * \typedef Effect
     * \struct Effect_S Staff.h "headers/data/Staff.h"
     *
     * Struct which contains the target of the effect
     *
     */
    typedef struct Effect_S {
        int target; //!< represent the target of the effect
        int update; //!< represent the value of the effect
    } Effect; //!< Struct which contains the target and the of the effect

#endif //PRIM_EFFECT_H
