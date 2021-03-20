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
 * Contain all error type returned by functions
 * It allow to communicate directly with interface and
 * to inform the user what is the problem, if there is an error
 *
 */
typedef enum ErrorCode_S {
    NO_ERROR = 0,
} ErrorCode; //!< Error type

/*!
     * \fn char* get_Error_Msg(ErrorCode e)
     * @brief Get an error message
     *
     * In order to know in detail an error returned by a function
     * we need a function to describe this error
     *
     * @param[in] ErrorCode, a error code
     * @return a string that describe the error
     * @see ErrorCode type
     */
char* get_Error_Msg(ErrorCode e);

#endif //PRIM_ERROR_H
