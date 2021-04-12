/*!
 * \file error.h
 * \author Antoine Man
 * \version 0.1
 * \date 12/03/2021
 * \see interface.h
 * \see map.h
 *
 * Contains all errors messages returned by our functions
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
     * Contain all error type returned by functions
     * It allow to communicate directly with interface and
     * to inform the user what is the problem, if there is an error
     *
     */
    typedef enum ErrorCode_S {
        NO_ERROR = 0,
        ERROR = 1,

        ERROR_GAME_WIN = 10,
        ERROR_GAME_LOST = 11,

        ERROR_CASE_EMPTY = 2,
        ERROR_CASE_MACHINE = 21,
        ERROR_CASE_SOURCE = 22,
        ERROR_CASE_GATE = 23,
        ERROR_CASE_NOT_FOUND = 24,

        ERROR_NOT_ENOUGH_E = 3,
        ERROR_NOT_ENOUGH_DD = 31,
        ERROR_NEGATIVE_RESULT = 32,

        ERROR_INVALID_ACTION_SEQUENCE = 9,
        ERROR_INVALID_LOCATION_SEQUENCE = 91,
        ERROR_INVALID_STAFF_NUMBER = 92,
        ERROR_INVALID_MACHINE_NUMBER = 93,
        ERROR_INVALID_ORIENTATION_NUMBER = 94,

        ERROR_INIT_INTERFACE = 10,
        ERROR_INIT_NCURSES_INTERFACE = 101,
        ERROR_INIT_NCURSES_INTERFACE_SIZE = 102,
        ERROR_NO_NCURSES_COLORS_INTERFACE = 11,
        ERROR_CLOSE_INTERFACE = 12,

        ERROR_LIST_NULL = 4,
        ERROR_DICTIONARY_NULL = 41,
    } ErrorCode; //!< Error type

    /*!
     * \fn char* error_getMessage(ErrorCode e)
     * @brief Get an error message
     *
     * In order to know in detail an error returned by a function
     * we need a function to describe this error
     *
     * @param[in] e: a error code
     * @return a string that describe the error
     * @see ErrorCode type
     */
    char* error_getMessage( ErrorCode e );

#endif //PRIM_ERROR_H
