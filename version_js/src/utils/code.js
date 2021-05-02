"use strict";
/**
 * \file error
 * \author Antoine Man
 * \version 0.1
 * \date 12/03/2021
 * \see interface.h
 * \see map.h
 *
 * Contains all errors messages returned by our functions
 *
 */
Object.defineProperty(exports, "__esModule", { value: true });
exports.ErrorCode = void 0;
/**
* Contain all error type returned by functions
* It allow to communicate directly with interface and
* to inform the user what is the problem, if there is an error
*/
var ErrorCode;
(function (ErrorCode) {
    ErrorCode[ErrorCode["NO_ERROR"] = 0] = "NO_ERROR";
    ErrorCode[ErrorCode["ERROR"] = 1] = "ERROR";
    ErrorCode[ErrorCode["ERROR_GAME_WIN"] = 10] = "ERROR_GAME_WIN";
    ErrorCode[ErrorCode["ERROR_GAME_LOST"] = 11] = "ERROR_GAME_LOST";
    ErrorCode[ErrorCode["ERROR_CASE_EMPTY"] = 2] = "ERROR_CASE_EMPTY";
    ErrorCode[ErrorCode["ERROR_CASE_MACHINE"] = 21] = "ERROR_CASE_MACHINE";
    ErrorCode[ErrorCode["ERROR_CASE_SOURCE"] = 22] = "ERROR_CASE_SOURCE";
    ErrorCode[ErrorCode["ERROR_CASE_GATE"] = 23] = "ERROR_CASE_GATE";
    ErrorCode[ErrorCode["ERROR_CASE_NOT_FOUND"] = 24] = "ERROR_CASE_NOT_FOUND";
    ErrorCode[ErrorCode["ERROR_CASE_NOT_EMPTY"] = 25] = "ERROR_CASE_NOT_EMPTY";
    ErrorCode[ErrorCode["ERROR_CASE_CANT_BE_DESTROYED"] = 26] = "ERROR_CASE_CANT_BE_DESTROYED";
    ErrorCode[ErrorCode["ERROR_CASE_CANT_BE_UPGRADED"] = 27] = "ERROR_CASE_CANT_BE_UPGRADED";
    ErrorCode[ErrorCode["ERROR_NOT_ENOUGH_E"] = 3] = "ERROR_NOT_ENOUGH_E";
    ErrorCode[ErrorCode["ERROR_NOT_ENOUGH_DD"] = 31] = "ERROR_NOT_ENOUGH_DD";
    ErrorCode[ErrorCode["ERROR_NEGATIVE_RESULT"] = 32] = "ERROR_NEGATIVE_RESULT";
    ErrorCode[ErrorCode["ERROR_INVALID_ACTION_SEQUENCE"] = 9] = "ERROR_INVALID_ACTION_SEQUENCE";
    ErrorCode[ErrorCode["ERROR_INVALID_LOCATION_SEQUENCE"] = 91] = "ERROR_INVALID_LOCATION_SEQUENCE";
    ErrorCode[ErrorCode["ERROR_INVALID_STAFF_NUMBER"] = 92] = "ERROR_INVALID_STAFF_NUMBER";
    ErrorCode[ErrorCode["ERROR_INVALID_MACHINE_NUMBER"] = 93] = "ERROR_INVALID_MACHINE_NUMBER";
    ErrorCode[ErrorCode["ERROR_INVALID_ORIENTATION_NUMBER"] = 94] = "ERROR_INVALID_ORIENTATION_NUMBER";
    ErrorCode[ErrorCode["ERROR_CLOSE_INTERFACE"] = 12] = "ERROR_CLOSE_INTERFACE";
})(ErrorCode = exports.ErrorCode || (exports.ErrorCode = {}));
