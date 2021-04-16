/*!
 * \file elements.h
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 13/04/2021
 * \see structures.h
 *
 * Contains elements
 */

#ifndef PRIM_ELEMENTS_H
#define PRIM_ELEMENTS_H

/*!
 * \typedef ElementType
 * \enum ElementType_S
 * \brief it's a number, a text or a object
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
//todo: Ramzy documentation and move to element.h
typedef struct Element_S {
    union {
        int number;
        char* text;
        void* object;
    } content;
    ElementType type; //!< in witch field we got our value
} Element;

typedef struct Couple_S{
    Element keys;
    Element values;
} Couple;


int dictionary_elementToNumber(Element e);
char* dictionary_elementToText( Element e);
void* dictionary_elementToObject( Element e);
Element dictionary_elementFromNumber(int number);
Element dictionary_elementFromText( char* text);
Element dictionary_elementFromObject (void* object);

#endif //PRIM_ELEMENTS_H
