/*!
 * \file testCase.c
 * \author Valentin DREANO
 * \version 0.1
 * \date 17/04/2021
 *
 * Contains all the suite for Case.c tests
 * The assumption is made that the setters and getter are functional
 *
 */

#include "testCase.h"

test_List testCase_listTests[TESTCASE_NUMBERTESTS] = {
        {"Instantiation_Case\0",   testCase_create}
};

int testCase_createSuite(CU_pSuite pSuite) {

    /* add a suite to the registry */
    pSuite = CU_add_suite("Test_Type_Case", testCase_initSuite, testCase_cleanSuite);
    if (NULL == pSuite) {
        return EXIT_FAILURE;
    }

    /* add the tests to the suite */
    for (int i = 0; i < TESTCASE_NUMBERTESTS; i++) {
        if (NULL == CU_add_test(pSuite, testCase_listTests[i].description, testCase_listTests[i].function)) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int testCase_initSuite() {
    return 0;
}

int testCase_cleanSuite() {
    return 0;
}

void testCase_create() {
    // Case creation
    int x = 0;
    int y = 0;
    Case *ca = case_create(x,y);

    // Checking values
    CU_ASSERT_EQUAL(case_getX(ca), x);
    CU_ASSERT_EQUAL(case_getY(ca), y);
    CU_ASSERT_EQUAL(case_getType(ca), CASE_VIDE);
    CU_ASSERT_EQUAL(case_getBox(ca), NULL);
    CU_ASSERT_EQUAL(case_getMachine(ca), NULL);

    // Destroy map
    case_destroy(ca);
}