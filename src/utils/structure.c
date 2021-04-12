/*!
 * \file structures.c
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 06/04/2021
 * \see structures.h
 *
 * Contains structures
 */
#include <string.h>
#include "../../headers/utils/structures.h"

List* list_createEmpty( )
{
    List* l = (List*) malloc(sizeof(List));
    l->current = NULL;
    l->next = NULL;
    return l;
}

List* list_create( Element first )
{
    List* l = (List*) malloc(sizeof(List));
    //todo: Ramzy do better and a it's not a name
    Element* elm = (Element*) malloc(sizeof(Element));
    *elm = first;
    l->current = elm;
    l->next = NULL;
    return l;
}

// at the end

ErrorCode list_addElement( List* l, Element e )
{
    if (l->current == NULL){
        //todo: do better
        Element* a = (Element*) malloc(sizeof(Element));
        *a = e;
        l->current = a;
        return ERROR_LIST_NULL;
    }

    if ( l->next == NULL ) {
        l->next = list_create(e);
    } else {
        List* c = l;
        while ( c->next != NULL ) {
            c = c->next;
        }
        c->next = list_create(e);
    }
    return NO_ERROR;
}

ErrorCode list_addCoupleIntText(List* l, int number, char* text)
{
    Element e;
    Couple c;
    c.keys = dictionary_elementFromNumber(number);
    c.values = dictionary_elementFromText(text);
    e.content.object = &c;
    e.type = OBJECT;
    return list_addElement(l, e);
}

ErrorCode list_addCoupleNumber(List* l, int n1, int n2)
{
    Couple* c = (Couple*) malloc(sizeof(Couple));
    c->keys = dictionary_elementFromNumber(n1);
    c->values = dictionary_elementFromNumber(n2);
    return list_addElement(l, dictionary_elementFromObject(c));
}

// advance list => next and return current
//todo: Ramzy don't forgot to free list
Element list_next( List** current )
{
    Element* e = (*current)->current;
    *current = (*current)->next;
    return *e;
}

// get Element
Element list_get( List* list )
{
    return *list->current;
}

ErrorCode list_removeByIndex(List* list,int index){
    int pos=0;
    if(list->current ==NULL)
        return ERROR_LIST_NULL;

    if(list->next == NULL) {
        free(list->current); //todo: delete
        list->current = NULL;
    }

    while (list->next !=NULL){
        if(pos+1 == index) {
            list->next = list->next->next;
            return NO_ERROR;
        }
        pos++;
    }

    return NO_ERROR;
}


Element* list_getByIndex(List* list, int index){
    int pos = 0;
    if(list->current ==NULL)
        return NULL;

    while (list->current !=NULL){
        if(pos == index)
            return list->current;
        list = list->next;
        pos++;
    }
    return NULL;
}

int list_getSize(List* list){
    int sz = 0;
    if(list->current ==NULL)
        return ERROR_LIST_NULL;

    if(list->current == NULL)
        return 0;
    while (list !=NULL){
        list = list->next;
        sz++;
    }
    return sz;
}

// destroy
//todo: Ramzy each element should be free
ErrorCode list_destroy( List* list )
{
    if ( list != NULL )
        free(list);
    return NO_ERROR;
}

Dictionary* dictionary_create( int length )
{
    Dictionary* dict = (Dictionary*) malloc(sizeof(Dictionary));
    dict->length = length;
    dict->numberOfElement = 0;
    dict->entries = (Couple*) malloc(length * sizeof(Couple));
    return dict;
}

ErrorCode dictionary_destroy( Dictionary* d )
{
    if ( d != NULL ) {
        free(d->entries);
        free(d);
    }
    return NO_ERROR;
}

Element* dictionary_getElement( Dictionary* d, Element key )
{
    for ( int i = 0; i < d->numberOfElement; i++ ) {
        Couple current = d->entries[i]; //!< current value check
        // type is different, we can't compare
        if ( key.type != current.keys.type )
            continue; //next
        if ( current.keys.type == NUMBER && key.type == NUMBER ) {
            if ( current.keys.content.number == key.content.number )
                return &(d->entries[i].values);
        } else if ( current.keys.type == OBJECT && key.type == OBJECT ) {
            if ( current.keys.content.object == key.content.object )
                return &(d->entries[i].values);
        } else if ( current.keys.type == TEXT && key.type == TEXT ) {
            if ( current.keys.content.text == key.content.text )
                return &(d->entries[i].values);
        }
    }
    return NULL;
}

ErrorCode dictionary_addElement( Dictionary* d, Element key, Element value )
{
    if ( d == NULL )
        return ERROR_DICTIONARY_NULL;

    // verify that the key don't exist before insert
    for ( int i = 0; i < d->numberOfElement; i++ ) {
        Couple current = d->entries[i]; //!< current value check
        // type is different, we can't compare
        if ( key.type != current.keys.type )
            continue; //next
        // check equals
        switch ( key.type ) {
            case NUMBER:
                if ( current.keys.content.number == key.content.number ) {
                    // set value and go back
                    d->entries[i].values = value;
                    return NO_ERROR;
                }
                break;
            case TEXT:
                if ( strcmp(current.keys.content.text, key.content.text) == 0 ) {
                    // set value and go back
                    d->entries[i].values = value;
                    return NO_ERROR;
                }
                break;
            case OBJECT:
                if ( current.keys.content.object == key.content.object ) {
                    // set value and go back
                    d->entries[i].values = value;
                    return NO_ERROR;
                }
                break;
        }
    }

    // else
    // realloc if needed
    if ( d->length == d->numberOfElement ) {
        d->length += 5;
        d->entries = (Couple*) realloc(d->entries, d->length * sizeof(Couple*));
    }

    // set
    d->entries[d->numberOfElement].keys = key;
    d->entries[d->numberOfElement].values = value;
    d->numberOfElement++; //increase

    return NO_ERROR;
}

Couple* dictionary_getCoupleByIndex( Dictionary* d, int index )
{
    if ( index <= d->numberOfElement )
        return &(d->entries[index]);
    return NULL;
}

// convenience methods

ErrorCode dictionary_addCoupleText( Dictionary* d, char* key, char* value )
{
    Element e_key;
    Element e_value;

    e_key.type = TEXT;
    e_key.content.text = key;

    e_value.type = TEXT;
    e_value.content.text = value;
    return dictionary_addElement(d, e_key, e_value);
}

ErrorCode dictionary_addCoupleNumber( Dictionary* d, int key, int value )
{
    Element e_key;// rename name of variable
    Element e_value;

    e_key.type = NUMBER;
    e_key.content.number = key;

    e_value.type = NUMBER;
    e_value.content.number = value;
    return dictionary_addElement(d, e_key, e_value);
}

ErrorCode dictionary_addCoupleNumberText( Dictionary* d, int key, char* value )
{
    Element e_key;// rename name of variable
    Element e_value;

    e_key.type = NUMBER;
    e_key.content.number = key;

    e_value.type = TEXT;
    e_value.content.text = value;
    return dictionary_addElement(d, e_key, e_value);
}

Element* dictionary_getElementText( Dictionary* d, char* key )
{
    // create element
    Element e_key;
    e_key.type = TEXT;
    e_key.content.text = key;
    return dictionary_getElement(d, e_key);
}

Element* dictionary_getElementNumber( Dictionary* d, int key )
{
    // create element
    return dictionary_getElement(d, dictionary_elementFromNumber(key));
}

//todo: Ramzy rename and element.h

int dictionary_elementToNumber(Element e )
{
    if ( e.type == NUMBER ) {
        return e.content.number;
    }
    return -1;
}

//todo: Ramzy rename and element.h
void* dictionary_elementToObject( Element e )
{
    if ( e.type == OBJECT ) {
        return e.content.object;
    }
    return NULL;
}

//todo: Ramzy rename and element.h
char* dictionary_elementToText( Element e )
{
    if ( e.type == TEXT ) {
        return e.content.text;
    }
    return "";
}

//todo: Ramzy rename and element.h
Element dictionary_elementFromNumber( int number )
{
    Element e;
    e.type = NUMBER;
    e.content.number = number;
    return e;
}

//todo: Ramzy rename and element.h
Element dictionary_elementFromText( char* text )
{
    Element e;
    e.type = TEXT;
    e.content.text = text;
    return e;
}

//todo: Ramzy rename and element.h
Element dictionary_elementFromObject( void* object )
{
    Element e;
    e.type = OBJECT;
    e.content.object = object;
    return e;
}

