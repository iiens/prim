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
 * \enum ElementType_S "headers/utils/elements.h"
 * \brief it's a number, a text or a object
 */
typedef enum ElementType_S {
    NUMBER,
    TEXT,
    OBJECT
} ElementType; //!< represent the different type of an Element


/*!
* \typedef Element
* \union Element_S elements.h "headers/utils/elements.h"
* \brief Represent a list
*/

typedef struct Element_S {
    union {
        int number; //!< represent a number
        char* text; //!< represent a text
        void* object; //!< represent a object
    } content; //!< represent the content of the Element
    ElementType type; //!< in witch field we got our value
} Element; //!< represent an Element

/*!
* \typedef Couple
* \union Couple_S elements.h "headers/utils/elements.h"
* \brief Represent a couple composed by it's key and it's value
*/
typedef struct Couple_S{
    Element keys; //!< represent the key of the Couple
    Element values; //!< represent the values of the Couple
} Couple; //!< composed by it's key and it's value

/*!
 * int elements_toNumber(Element e)
 * @brief if the Element is a number return it's value
 *
 *
 * @param[in] e element which contains a value
 *
 *
 * @return int
 */
int elements_toNumber(Element e);

/*!
 * char* elements_toText(Element e)
 * @brief if the Element is a char* return it's value
 *
 *
 * @param[in] e element which contains a value
 *
 *
 * @return char*
 */
char* elements_toText(Element e);

/*!
 * void* elements_toObject(Element e)
 * @brief if the Element is a object return it's value
 *
 *
 * @param[in] e element which contains a value
 *
 *
 * @return void*
 */
void* elements_toObject(Element e);

/*!
 * Element elements_fromNumber(int number)
 * @brief we make a number element with the value given by the function
 *
 *
 * @param[in] number int which represent the value of our Element
 *
 *
 * @return Element
 */
Element elements_fromNumber(int number);

/*!
 * Element elements_fromText(char* text)
 * @brief we make a text element with the value given by the function
 *
 *
 * @param[in] text char* which represent the value of our Element
 *
 *
 * @return Element
 */
Element elements_fromText(char* text);

/*!
 * Element elements_fromObject (void* object)
 * @brief we make a object element with the value given by the function
 *
 *
 * @param[in] object void* which represent the value of our Element
 *
 *
 * @return Element
 */
Element elements_fromObject (void* object);

#endif //PRIM_ELEMENTS_H
