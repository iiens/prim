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
#include "../data/error.h" // todo: ...

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
    * \typedef Element
    * \union Element_S effect.h "headers/data/structures.h"
    * \brief Represent a list
    */
    //todo: documentation
    typedef union Element_S {
        int number;
        char* text;
        void* object;
        ElementType type; //!< in witch field we got our value
    } Element;

    typedef struct Couple_S{
        Element keys;
        Element values;
    } Couple;

    /*!
     * \typedef Dictionary
     * \struct Dictionary_S structures.h "headers/data/structures.h"
     * \brief Struct which contains a dictionary of ElementType
     */
    //todo: documentation
    typedef struct Dictionary_S {
        int length;
        Couple* entries;
    } Dictionary;

    typedef struct List_S {
        Element current;
        struct List_S* next;
    } List;

    // create list
    List* list_create(Element first);

    // at the end
    ErrorCode list_addElement(List* l, Element e);
    // advance list => next and return current
    Element list_next(List** current);
    // get Element
    Element list_get(List* list);
    // destroy
    ErrorCode list_destroy(List* list);
    /*!
     * \fn Dictionary* createDictionary()
     * @brief Create a Dictionary of ElementType and Element
     * create an array of structures_tab
     *
     *
     * @return Array of the structures_tab
     */
    // todo : do the documentation
    Dictionary* dictionary_create(int length);
    ErrorCode dictionary_destroy(Dictionary* d);
    Element dictionary_getElement(Dictionary* d, Element key);
    ErrorCode dictionary_addElement(Dictionary* d, Element key, Element value);

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