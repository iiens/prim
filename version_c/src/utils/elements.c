/*!
 * \file elements.h
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 13/04/2021
 * \see structures.h
 *
 * Contains elements
 */

#include "../../headers/utils/structures.h"

int elements_toNumber(Element e )
{
    if ( e.type == NUMBER ) {
        return e.content.number;
    }
    return -1;
}


void* elements_toObject(Element e )
{
    if ( e.type == OBJECT ) {
        return e.content.object;
    }
    return NULL;
}


char* elements_toText(Element e )
{
    if ( e.type == TEXT ) {
        return e.content.text;
    }
    return "";
}


Element elements_fromNumber(int number )
{
    Element e;
    e.type = NUMBER;
    e.content.number = number;
    return e;
}


Element elements_fromText(char* text )
{
    Element e;
    e.type = TEXT;
    e.content.text = text;
    return e;
}


Element elements_fromObject(void* object )
{
    Element e;
    e.type = OBJECT;
    e.content.object = object;
    return e;
}
