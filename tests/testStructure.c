//
// Created by doe on 09/04/2021.
//

#include "testStructure.h"

test_List testDictionary_listTests[TESTDICTIONARY_NUMBERTESTS] = {

};

test_List testList_listTests[TESTLIST_NUMBERTESTS] = {

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

}