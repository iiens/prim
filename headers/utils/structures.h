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
     * Struct which contains a key which is the index and the value contains in this index
     *
     */
    typedef struct Element_S {
        int key; //!< index of the tab
        int value; //!< value of the tab
    } Element; //!< Struct which contains the target and the of the effect


    /*!
     * \typedef ElementListe
     * \struct ElementListe_S Structures.h "headers/data/Structures.h"
     *
     * Struct which represent a list
     *
     */
    typedef struct ElementList_S
    {
        int number;
        struct ElementList *next;
    }ElementList;

    extern Element structures_tab[]; //!< contains all of the recruited staff and the number of each staff recruited

    /*!
     * \fn Element* createStructuresStaff()
     * @brief Create an Array of structures_tab
     * create an array of structures_tab
     *
     *
     * @return Array of the structures_tab
     */
    Element* createStructuresTab();

    /*!
     * \fn destroyStructuresTab
     * @brief Destroy the array structures_tab
     *
     * At the end of the game we need to clean all of the map
     * this function will destroy the array
     *
     * @param[in] array of structures_tab
     * @return a void
     */
    void destroyStructuresTab(Element * e);


    int getElement(Element* e, int index_Staff);


    int add_Element(Element * e, int number_Staff);





#endif //PRIM_STRUCTURES_H