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
#include "../data/error.h" // error.h : need to exit status
#include "elements.h" // element.h : structures contains Element

/*!
 * \typedef Dictionary : represent a Dictionary
 * \struct Dictionary_S structures.h "headers/utils/structures.h"
 * \brief Struct which contains a dictionary of ElementType
 */

typedef struct Dictionary_S {
    int length; //!< represent the length of a dictionary
    int numberOfElement; //!< represent the number of element in the dictionary
    Couple* entries; //!< represent a couple
} Dictionary; //!< a dictionary composed by it's length it's number of element and a couple

/*!
 * \typedef List
 * \struct List_S structures.h "headers/utils/structures.h"
 * \brief Struct which represent a linked list
 */
typedef struct List_S {
    Element* current; //!< represent the head of the linked list
    struct List_S* next; //!< represent the queue of the linked list
} List; //!< represent a linked list

// create list

/*!
 * \fn List* list_create(Element first)
 * @brief Create a linked list with an element
 * @param[in] first an Element
 * @return A new linked list
 */
List* list_create(Element first);

/*!
 * \fn List* list_createEmpty()
 * @brief Create a linked list without element
 *
 * @return A new linked list
 */
List* list_createEmpty( );

/*!
 * \fn List* list_getByIndex(List* list, int index)
 * @brief get an Element by it's index
 * @param[in] list a linked list
 * @param[in] index the index of the Element in list
 * @return pointer of the element
 */
Element* list_getByIndex(List* list, int index);

/*!
 * \fn int list_getSize(List* list)
 * @brief get the size of the linked list
 * @param[in] list a linked list
 * @return the size of the list
 */
int list_getSize(List* list);

/*!
 * \fn ErrorCode list_addElement(List* l, Element e)
 * @brief add an Element to the list, if the key of the Element e
 * is the same that an other Element in the list we overwrite the Element
 * @param[out] l a linked list
 * @param[in] e the Element to add to the linked list
 * @return ErrorCode
 */
// at the end
ErrorCode list_addElement(List* l, Element e);

/*!
 * \fn ErrorCode list_addCoupleNumberText(List* l, int number, char* text)
 * @brief create an Element by a number and a char*, add this Element to the list,
 * if the key of the Element e is the same that an other Element in the list we overwrite the Element
 *
 * @param[out] l a linked list
 * @param[in] number int that we will add to the list by creating an Element
 * @param[in] text char* that we will add to the list by creating an Element
 * @return ErrorCode
 */
ErrorCode list_addCoupleNumberText(List* l, int number, char* text);

/*!
 * \fn ErrorCode list_addCoupleNumber(List* l, int n1, int n2)
 * @brief create an Element by two number, add this Element to the list,
 * if the key of the Element e is the same that an other Element in the list we overwrite the Element
 *
 * @param[out] l a linked list
 * @param[in] n1 number int that we will add to the list by creating an Element
 * @param[in] n2 number int that we will add to the list by creating an Element
 * @return ErrorCode
 */
ErrorCode list_addCoupleNumber(List* l, int n1, int n2);
// advance list => next and return current

/*!
 * \fn Element list_next(List** current)
 * @brief return the current value and go to the next element of the linked list
 *
 *
 * @param[out] current a pointer of a linked list
 *
 * @return an Element
 */
Element* list_next(List** current);
// get Element

/*!
 * \fn Element* list_getCurrent(List* list)
 * @brief return the current value of the linked list, element should be free
 *
 *
 * @param[in] list a linked list
 *
 * @return an Element
 */
Element* list_getCurrent(List* list);
// remove Element by Index

/*!
 * \fn ErrorCode list_removeByIndex(List** list,int index)
 * @brief remove an Element of the linked list by it's index
 *
 *
 * @param[out] list a pointer of linked list
 * @param[in] index int which represent the index where we will remove the Element
 * @return ErrorCode
 */
ErrorCode list_removeByIndex(List** list,int index);
// destroy all (next included)

/*!
 * \fn ErrorCode list_destroy(List* list)
 * @brief destroy all of the list ( recursive )
 *
 *
 * @param[out] list a linked list
 *
 * @return ErrorCode
 */
ErrorCode list_destroy(List* list);
// destroy only this list

/*!
 * \fn ErrorCode list_destroyFirst(List* list)
 * @brief destroy a list
 *
 *
 * @param[out] list a linked list
 *
 * @return ErrorCode
 */
ErrorCode list_destroyFirst(List* list);


/*!
 * \fn Dictionary* dictionary_create(int length)
 * @brief Create a Dictionary with a predefined size
 *
 *
 * @param[in] length int which represent the size of the dictionary
 * @return a Dictionary
 */
Dictionary* dictionary_create(int length);

/*!
 * \fn ErrorCode dictionary_destroy(Dictionary* d)
 * @brief free the dictionary
 *
 *
 * @param[out] d Dictionary which represent the dictionary
 * @return ErrorCode
 */
ErrorCode dictionary_destroy(Dictionary* d);

/*!
 * Element* dictionary_getElement(Dictionary* d, Element key)
 * @brief get an Element by it's key
 *
 *
 * @param[in] d Dictionary which represent the dictionary
 * @param[in] key Element that we search in the linked list
 * @return pointer of the Element
 */
Element* dictionary_getElement(Dictionary* d, Element key);

/*!
 * ErrorCode dictionary_addElement(Dictionary* d, Element key, Element value)
 * @brief add Elements by creating a Couple composed by the key and the value
 *
 *
 * @param[out] d Dictionary which represent the dictionary
 * @param[in] key Element represent the key of the Couple that we will add
 * @param[in] value Element represent the value of the Couple that we will add
 * @return ErrorCode
 */
ErrorCode dictionary_addElement(Dictionary* d, Element key, Element value);

/*!
 * Couple* dictionary_getCoupleByIndex( Dictionary *d, int index)
 * @brief get a Couple in the dictionary by an index
 *
 *
 * @param[in] d Dictionary which represent the dictionary
 * @param[in] index int which represent the index of the Couple in the dictionary
 *
 * @return a pointer of Couple
 */
Couple* dictionary_getCoupleByIndex( Dictionary *d, int index);

/*!
 * ErrorCode dictionary_addCoupleText(Dictionary *d,char* key, char* value)
 * @brief add a Couple composed of two char *
 *
 *
 * @param[out] d Dictionary which represent the dictionary
 * @param[in] key char* which represent the key of the Couple
 * @param[in] value char* which represent the value of the Couple
 *
 * @return ErrorCode
 */
ErrorCode dictionary_addCoupleText(Dictionary *d,char* key, char* value);

/*!
 * ErrorCode dictionary_addCoupleNumberText(Dictionary* d,int key, char* value)
 * @brief add a Couple composed of int key and char * value
 *
 *
 * @param[out] d Dictionary which represent the dictionary
 * @param[in] key int which represent the key of the Couple
 * @param[in] value char* which represent the value of the Couple
 *
 * @return ErrorCode
 */
ErrorCode dictionary_addCoupleNumberText(Dictionary* d,int key, char* value);

/*!
 * Element* dictionary_getElementText(Dictionary *d, char* key)
 * @brief get Element in a Dictionary by it's char* key
 *
 *
 * @param[in] d Dictionary which represent the dictionary
 * @param[in] key char* which represent the key of the Couple
 *
 *
 * @return a pointer of Element
 */
Element* dictionary_getElementText(Dictionary *d, char* key);

/*!
 * ErrorCode dictionary_addCoupleNumber( Dictionary* d, int key, int value )
 * @brief add a Couple composed of two int
 *
 *
 * @param[out] d Dictionary which represent the dictionary
 * @param[in] key int which represent the key of the Couple
 * @param[in] value int which represent the value of the Couple
 *
 * @return ErrorCode
 */
ErrorCode dictionary_addCoupleNumber( Dictionary* d, int key, int value );

/*!
 * Element* dictionary_getElementNumber(Dictionary *d, int key)
 * @brief get Element in a Dictionary by it's number key
 *
 *
 * @param[in] d Dictionary which represent the dictionary
 * @param[in] key int which represent the key of the Couple
 *
 *
 * @return a pointer of Element
 */
Element* dictionary_getElementNumber(Dictionary *d, int key);


#endif //PRIM_STRUCTURES_H