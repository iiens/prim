/*!
 * \file case_type.h
 * \author Antoine Man
 * \version 0.1
 * \date 11/03/2021
 * \see map.h
 *
 * Contains all the types that a case can contain.
 *
 */
#ifndef PRIM_CASE_TYPE_H
#define PRIM_CASE_TYPE_H

    /*!
     * \typedef CaseType
     * \enum CaseType_S case_type.h "headers/data/case_type.h"
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
     */
    typedef enum CaseType_S {
        CASE_VIDE = 0, //!< a case that contain nothing
        CASE_GATE = 1, //!< a case that contain the transdimensional gate
        CASE_SOURCE = 2, //!< a case that contain resources
        CASE_MACHINE = 3, //!< a case that contain a machine
    } CaseType; //!< Case type

#endif //PRIM_CASE_TYPE_H