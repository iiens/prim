/*!
 * \file caseType.h
 * \author Antoine Man
 * \version 0.1
 * \date 11/03/2021
 * \see map.h
 *
 * Contains all the type that a case can contain.
 *
 */
#ifndef PRIM_CASETYPE_H
#define PRIM_CASETYPE_H

    /*!
     * \typedef CaseType: rename for enum caseType
     * \enum caseType caseType.h "headers/data/caseType.h"
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
    typedef enum caseType {
        CASE_VIDE = 0, //!< a case that contain nothing
        CASE_GATE = 1, //!< a case that contain the transdimensional gate
        CASE_SOURCE = 2, //!< a case that contain resources
        CASE_MACHINE = 3, //!< a case that contain a machine
    } caseType; //!< Case type

#endif //PRIM_CASETYPE_H