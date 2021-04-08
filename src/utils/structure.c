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
#include <stdio.h>
#include "../../headers/utils/structures.h"

List *list_create(Element first) {
    List *l = (List *) malloc(sizeof(List));
    l->current = first;
    l->next = NULL;
    return l;
}

// at the end
ErrorCode list_addElement(List *l, Element e) {
    List *c = l;
    if (l->next == NULL) {
        l->next = list_create(e);
    } else {
        while (c->next != NULL) {
            c = c->next;
        }
        c->next = list_create(e);
    }
    return NO_ERROR;
}

// advance list => next and return current
Element list_next(List **current) {
    Element e = (*current)->current;
    *current = (*current)->next;
    return e;
}

// get Element
Element list_get(List *list) {
    return list->current;
}

// destroy
ErrorCode list_destroy(List *list) {
    //todo: no a real free (check list->next)
    if (list != NULL)
        free(list);
    return NO_ERROR;
}

Dictionary *dictionary_create(int length) {
    Dictionary* dict = (Dictionary *) malloc(sizeof(Dictionary));
    dict->length = length;
    dict->numberOfElement = 0;
    dict->entries = (Couple*) malloc(dict->length * sizeof(Couple));

    Couple c1;
    c1.keys = (Element) { .type = TEXT, .content.text = "a" };
    c1.values = (Element) { .type = TEXT, .content.text = "aza" };

    Couple c2;
    c2.keys = (Element) { .type = TEXT, .content.text = "b" };
    c2.values = (Element) { .type = TEXT, .content.text = "bza" };

    Couple c3;
    c3.keys = (Element) { .type = TEXT, .content.text = "c" };
    c3.values = (Element) { .type = TEXT, .content.text = "cza" };

    dict->entries[0] = c1;
    dict->entries[1] = c2;
    dict->entries[2] = c3;
    dict->numberOfElement = 3;

    return dict;
}

ErrorCode dictionary_destroy(Dictionary *d) {
    if ( d != NULL ){
        free(d->entries);
        free(d);
    }
    return NO_ERROR;
}

Element *dictionary_getElement(Dictionary *d, Element key) {
    for (int i = 0; i < d->numberOfElement; i++) {
        if (d->entries->keys.type == NUMBER && key.type == NUMBER) {
            if (d->entries->keys.content.number == key.content.number)
                return &d[i].entries->values;
        } else if (d->entries->keys.type == OBJECT && key.type == OBJECT) {
            if (d->entries->keys.content.object == key.content.object)
                return &d[i].entries->values;
        } else if (d->entries->keys.type == TEXT && key.type == TEXT) {
            if (d->entries->keys.content.text == key.content.text)
                return &d[i].entries->values;
        }
    }
    return NULL;
}

ErrorCode dictionary_addElement( Dictionary *d, Element key, Element value ) {
    Couple c; //!<
    int foundPosition = -1; //!< where we will insert our Couple in the Dictionary

    // verify that the key don't exist before insert
    for ( int i = 0; i < d->numberOfElement ; i++ ) {
        Couple current = d->entries[i]; //!< current value check
        // type is different, we can't compare
        if (key.type != current.keys.type) continue; //next
        // check equals
        switch (key.type) {
            case NUMBER:
                if ( current.keys.content.number == key.content.number ) {
                    c = current;
                    foundPosition = i;
                }
                break;
            case TEXT:
                if ( strcmp(current.keys.content.text, key.content.text) == 0 ) {
                    c = current;
                    foundPosition = i;
                }
                break;
            case OBJECT:
                if ( current.keys.content.object == key.content.object ) {
                    c = current;
                    foundPosition = i;
                }
                break;
        }
    }

    if (foundPosition != -1){
        // replace element
        c.values = value;
        d->entries[foundPosition] = c;
        return NO_ERROR;
    }

    // we do not replace a value
    c.keys = key;
    c.values = value;

    // realloc if needed
    if( d->length == d->numberOfElement ){
        d->length += 5;
        d->entries = (Couple*) realloc(d->entries,d->length * sizeof(Couple));
    }

    // add and increase number of elements
    d->entries[d->numberOfElement] = c;
    d->numberOfElement++;

    return NO_ERROR;
}

Couple *dictionary_getCoupleByIndex(Dictionary *d, int index) {
    if ( index <= d->numberOfElement )
        return &(d->entries[index]);
    return NULL;
}

ErrorCode dictionary_addCoupleText(Dictionary *d, char *key, char *value) {
    Element e_key;
    Element e_value;

    e_key.type = TEXT;
    e_key.content.text = key;

    e_value.type = TEXT;
    e_value.content.text = value;
    return dictionary_addElement(d, e_key, e_value);
}

ErrorCode dictionary_addCoupleIntText(Dictionary *d, int key, char *value) {
    Element e_key;// rename name of variable
    Element e_value;

    e_key.type = NUMBER;
    e_key.content.number = key;

    e_value.type = TEXT;
    e_value.content.text = value;
    return dictionary_addElement(d, e_key, e_value);
}

Element* dictionary_getElementText(Dictionary *d, char* key) {
    // create element
    Element e_key;
    e_key.type = TEXT;
    e_key.content.text = key;
    return dictionary_getElement(d, e_key);
}

int main(void){
    Dictionary* d = dictionary_create(10);
    /*dictionary_addCoupleText(d, "t", "joker");
    dictionary_addCoupleText(d, "t", "maria");
    dictionary_addCoupleText(d, "aza", "fzdaa");
    printf("%s\n", dictionary_getElementText(d, "t")->content.text);
    printf("%s\n", dictionary_getElementText(d, "aza")->content.text);
    printf("%s\n", dictionary_getElementText(d, "blah blah")->content.text);*/
    dictionary_destroy(d);
}