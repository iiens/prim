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
     * \union Element_S effect.h "headers/data/structures.h"
     * \brief Represent a list
     */
     //todo: documentation
    typedef union Element_S {
        int number;
        char* text;
        void* object;
    } Element;

    /*!
     * \typedef ElementType
     * \enum ElementType_S
     * \brief todo : do a comment
     */
    typedef enum ElementType_S {
        NUMBER,
        TEXT,
        OBJECT
    } ElementType;

    /*!
     * \typedef Dictionary
     * \struct Dictionary_S structures.h "headers/data/structures.h"
     * \brief Struct which contains a dictionary of ElementType
     */
    //todo: documentation
    typedef struct List_S {
        ElementType typeKey;
        ElementType typeValue;
        Element* keys;
        Element* values;
        struct List* next;
    } List;

    /*!
     * \fn Dictionary* createDictionary()
     * @brief Create a Dictionary of ElementType and Element
     * create an array of structures_tab
     *
     *
     * @return Array of the structures_tab
     */
     // todo : do the documentation
     List* createDictionary(ElementType keyType, ElementType valueType);
     void destroyDictionary(List* d);
     Element getElement(List* d, Element key);
     bool addElement(List* d, Element key, Element value);

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

#endif //PRIM_STRUCTURES_H