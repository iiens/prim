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
     * \typedef effect
     * \struct Effect staff.h "headers/data/staff.h"
     * \param Target: int, represent the target of the effect
     * \param Update: int, the value of the effect
     *
     * Struct which contains the target of the effect
     *
     */
    typedef struct Effect {
        int Target; //!< represent the target of the effect
        int Update; //!< represent the value of the effect
    } effect; //!< Struct which contains the target and the of the effect

#endif //PRIM_EFFECT_H
