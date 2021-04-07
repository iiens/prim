/*!
 * \file structures.c
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 06/04/2021
 * \see structures.h
 *
 * Contains structures
 */
#include "../../headers/utils/structures.h"

    List* list_create(Element first) {
        List* l = (List*) malloc(sizeof(List));
        l->current = first;
        l->next = NULL;
        return l;
    }
    // at the end
    ErrorCode list_addElement(List* l, Element e){
        List* c = l;
        if ( l->next == NULL ){
            l->next = list_create(e);
        } else {
            while ( c->next != NULL ){
                c = c->next;
            }
            c->next = list_create(e);
        }
        return NO_ERROR;
    }
    // advance list => next and return current
    Element list_next(List** current){
        Element e = (*current)->current;
        *current = (*current)->next;
        return e;
    }
    // get Element
    Element list_get(List* list) {
        return list->current;
    }
    // destroy
    ErrorCode list_destroy(List* list) {
        if (list != NULL)
            free(list);
    }