//
// Created by doe on 09/04/2021.
//

#include "test_structure.h"

test_List testDictionary_listTests[TESTDICTIONARY_NUMBERTESTS] = {
        {"Dictionary_Initialisation\0", testDictionary_create},
        {"Dictionary_Add_Element\0", testDictionary_addElement},
        {"Dictionary_Index_Element\0", testDictionary_indexElement}
};

test_List testList_listTests[TESTLIST_NUMBERTESTS] = {
        {"List_Initialisation\0", testList_create},
        {"List_Initialisation_Empty\0", testList_createEmpty},
        {"List_Add_Element\0", testList_addElement}
};

int testStructure_createSuite(CU_pSuite pSuite) {

    /* add a suite to the registry */
    pSuite = CU_add_suite("Test_Dictionary", testStructure_initSuite, testStructure_cleanSuite);
    if (NULL == pSuite)
    {
        return EXIT_FAILURE;
    }

    /* add the tests to the suite */
    for (int i = 0; i < TESTDICTIONARY_NUMBERTESTS; i++) {
        if (NULL == CU_add_test(pSuite, testDictionary_listTests[i].description, testDictionary_listTests[i].function)) {
            return EXIT_FAILURE;
        }
    }

    pSuite = CU_add_suite("Test_List", testStructure_initSuite, testStructure_cleanSuite);
    if (NULL == pSuite)
    {
        return EXIT_FAILURE;
    }

    /* add the tests to the suite */
    for (int i = 0; i < TESTLIST_NUMBERTESTS; i++) {
        if (NULL == CU_add_test(pSuite, testList_listTests[i].description, testList_listTests[i].function)) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int testStructure_initSuite() {
    return 0;
}

int testStructure_cleanSuite() {
    return 0;
}

void testList_create() {
    // Create List
    Element elt1 = elements_fromNumber(5);
    List *list = list_create(elt1);

    // Checking values
    Element* elt2 = list_getCurrent(list);
    CU_ASSERT_EQUAL(elt2->type, elt1.type);
    CU_ASSERT_EQUAL(elements_toNumber(*elt2), elements_toNumber(elt1));

    // Destroy list
    list_destroy(list);
}

void testList_createEmpty() {
    List *list = list_createEmpty();
    CU_ASSERT_EQUAL(list_getCurrent(list), NULL);
    // Destroy list
    list_destroy(list);
}

void testList_addElement() {
    List *list = list_createEmpty();
    list_addElement(list, elements_fromNumber(15));
    list_addElement(list, elements_fromText("texte"));
    list_addElement(list, elements_fromNumber(27));
    list_addElement(list, elements_fromObject(NULL));
    CU_ASSERT_EQUAL(elements_toNumber(*list_next(&list)), 15);
    CU_ASSERT_STRING_EQUAL(elements_toText(*list_next(&list)), "texte");
    CU_ASSERT_EQUAL(elements_toNumber(*list_next(&list)), 27);
    CU_ASSERT_PTR_EQUAL(elements_toObject(*list_next(&list)), NULL);
    CU_ASSERT_PTR_EQUAL(list_next(&list), NULL);
    // Destroy list
    list_destroy(list);
}

void testDictionary_create() {
    // Create dictionary
    int length = 10;
    Dictionary *dico = dictionary_create(length);

    // Checked value
    CU_ASSERT_EQUAL(dico->length, length);

    // Destroy dictionary
    dictionary_destroy(dico);
}

void testDictionary_addElement() {
    Dictionary* d = dictionary_create(2);

    Element key1 = elements_fromText("trois");
    Element value1 = elements_fromNumber(3);

    Element key2 = elements_fromNumber(15);
    Element value2 = elements_fromText("quinze");

    Element value3 = elements_fromNumber(15);

    dictionary_addElement(d, key1, value1);
    dictionary_addElement(d, key2, value2);

    CU_ASSERT_EQUAL(d->numberOfElement, 2);

    dictionary_addElement(d, key1, value3);

    // should not increase
    CU_ASSERT_EQUAL(d->numberOfElement, 2);

    dictionary_destroy(d);
}

void testDictionary_indexElement() {
    Dictionary* d = dictionary_create(2);

    Element key1 = elements_fromText("trois");
    Element value1 = elements_fromNumber(3);

    Element key2 = elements_fromNumber(15);
    Element value2 = elements_fromText("quinze");

    Element value3 = elements_fromNumber(27);

    dictionary_addElement(d, key1, value1);
    dictionary_addElement(d, key2, value2);

    Couple* c = dictionary_getCoupleByIndex(d, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(c);
    CU_ASSERT_EQUAL_FATAL(c->keys.type, key1.type);
    CU_ASSERT_STRING_EQUAL( elements_toText(c->keys), "trois");
    CU_ASSERT_EQUAL_FATAL(c->values.type, value1.type);
    CU_ASSERT_EQUAL( elements_toNumber(c->values), 3);

    c = dictionary_getCoupleByIndex(d, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(c);
    CU_ASSERT_EQUAL_FATAL(c->keys.type, key2.type);
    CU_ASSERT_EQUAL( elements_toNumber(c->keys), 15);
    CU_ASSERT_EQUAL_FATAL(c->values.type, value2.type);
    CU_ASSERT_STRING_EQUAL( elements_toText(c->values), "quinze");

    dictionary_addElement(d, key1, value3);

    // changed value
    c = dictionary_getCoupleByIndex(d, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(c);
    CU_ASSERT_EQUAL_FATAL(c->keys.type, key1.type);
    CU_ASSERT_STRING_EQUAL( elements_toText(c->keys), "trois");
    CU_ASSERT_EQUAL_FATAL(c->values.type, value1.type);
    CU_ASSERT_EQUAL( elements_toNumber(c->values), 27);

    dictionary_destroy(d);
}