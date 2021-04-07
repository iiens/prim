//
// Created by mana on 08/04/2021.
//

#ifndef PRIM_BOX_H
#define PRIM_BOX_H

#include "error.h"

    /*!
         * \typedef Box
         * \struct Box_S map.h "headers/map.h"
         *
         * Struct that contains all the information concerning a box
         * It contain resources and garbage on a case
         *
         */
    typedef struct Box_S Box;

/*!
* \fn int box_getNumberResource(const Box* c)
* @brief a function to get the number of resources
* @param[in] Box* a box
*
* This function get the number of resources of the box.
*
* @return the number of resources available in the box
*/
int box_getNumberResource(const Box* c);

/*!
* \fn int box_getNumberGarbage(const Box* c)
* @brief a function to get the number of garbage
* @param[in] Box* a box
*
* This function get the number of garbage of the box.
*
* @return the number of garbage available in the box
*/
int box_getNumberGarbage(const Box* c);

/*!
    * \fn ErrorCode box_setNumberResource(Box * c, int val )
    * @brief a function to set the number of resources
    * @param[in] Box* a box
    * @param[in] val a resource value to add/to substract
    *
    * This function set the number of resources of the box
    *
    * @return an error that specify what is the problem
    */
ErrorCode box_setNumberResource(Box * c, int val );

/*!
* \fn ErrorCode box_setNumberGarbage(Box * c, int val )
* @brief a function to set the number of garbage
* @param[in] Box* a box
* @param[in] val a resource value to add/to substract
*
* This function set the number of garbage of the box
*
* @return an error that specify what is the problem
*/
ErrorCode box_setNumberGarbage(Box * c, int val );

#endif //PRIM_BOX_H
