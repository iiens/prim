/*!
 * \file error.h
 * \author Antoine Man
 * \version 0.1
 * \date 12/03/2021
 * \see interface.h
 * \see map.h
 *
 * Contains all errors messages returned by the functions
 *
 */
#ifndef PRIM_ERROR_H
#define PRIM_ERROR_H

/*!
 * \typedef ErrorCode: rename for enum ErrorCode
 * \enum ErrorCode_S error.h "headers/data/error.h"
 * \brief all return errors messages
 *
 *
 * // TODO Antoine commentaires
 *
 */
typedef enum ErrorCode_S {
    NO_ERROR = 0,
    ERROR_CASE_EMPTY = 1,
    ERROR_CASE_MACHINE = 2,
    ERROR_CASE_SOURCE = 3,
    ERROR_CASE_GATE = 4,
    ERROR_NOT_ENOUGH_E = 5,
    ERROR_NOT_ENOUGH_DD = 6,
    ERROR_CASE_NOT_FOUND = 7,
    ERROR = 8,
    ERROR_INVALID_ACTION_SEQUENCE = 9,
    // TODO Antoine ADD ERROR endturn()
} ErrorCode; //!< Error type

#endif //PRIM_ERROR_H
