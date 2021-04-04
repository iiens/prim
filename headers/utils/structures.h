/*!
 * \file structures.h
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 26/03/2021
 * \see effect.h
 *
 * Contains structures
 */
#ifndef PRIM_STRUCTURES_H
#define PRIM_STRUCTURES_H

#include "../data/effect.h" // effect.h : information about effect

    /*!
     * \typedef Element
     * \struct Element_S Structures.h "headers/data/Structures.h"
     *
     * Struct which contains a staff and the number of this staff
     *
     */
    typedef struct Element_S {
        int index_Staff; //!< index of the staff of staff_list
        int number_Staff; //!< number of this staff recruited
    } Element; //!< Struct which contains the target and the of the effect

    extern Element structures_staff[]; //!< contains all of the recruited staff and the number of each staff recruited

    /*!
     * \fn structures_staff* createStructuresStaff()
     * @brief Create an Array of staff
     * create an array of staff which will be composed of the staff that we recruited
     *
     *
     * @return Array of the staff
     */
    structures_staff* createStructuresStaff();

    /*!
     * \fn destroyStructuresStaff
     * @brief Destroy the staff that we recruited
     *
     * At the end of the game we need to clean all of the map
     * this function will destroy the array of staff of the player
     *
     * @param[in] array of staff that the player has
     * @return a void
     */
    void destroyStructuresStaff(structures_staff* s);


    int getElement(structures_staff* s, int index_Staff);


    int add_Element(structures_staff * s, int number_Staff);





#endif //PRIM_STRUCTURES_H