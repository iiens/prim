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
        int target; //!< represent the target of the effect todo: such as ? (maybe use an enum, ..., see later)
        int update; //!< represent the value of the effect todo: such as ? maybe you should say modifier/value
        char * description; //!< describe the effect
    } Effect; //!< Struct which contains the target and the of the effect

#endif //PRIM_EFFECT_H
