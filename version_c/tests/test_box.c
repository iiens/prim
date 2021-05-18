/*!
 * \file test_box.c
 * \author Valentin DREANO
 * \version 0.1
 * \date 17/04/2021
 *
 * Contains all the suite for Box.c tests
 * The assumption is made that the setters and getter are functional
 *
 */

#include <stdlib.h>
#include "test_box.h"

/**
 * List of tests in the suite
 */
test_List testBox_listTests[TESTBOX_NUMBERTESTS] = {
        {"Box_Instantiation\0", testBox_create},
        {"Box_Addition\0",      testBox_addition}
};

int testBox_createSuite(CU_pSuite pSuite) {

    /* add a suite to the registry */
    pSuite = CU_add_suite("Test_Type_Box", testBox_initSuite, testBox_cleanSuite);
    if (NULL == pSuite) {
        return EXIT_FAILURE;
    }

    /* add the tests to the suite */
    for (int i = 0; i < TESTBOX_NUMBERTESTS; i++) {
        if (NULL == CU_add_test(pSuite, testBox_listTests[i].description, testBox_listTests[i].function)) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int testBox_initSuite() {
    return 0;
}

int testBox_cleanSuite() {
    return 0;
}

void testBox_create() {
    // Box creation
    int numberR = 10;
    int numberG = 10;

    // Calls the function to test
    Box *box = box_create(numberR, numberG);

    // Checking values
    CU_ASSERT_EQUAL(box_getNumberResource(box), numberR);
    CU_ASSERT_EQUAL(box_getNumberGarbage(box), numberG);

    // Destroy box
    box_destroy(box);
}

void testBox_addition() {
    // Assumption that the creation of a box has been tested beforehand
    // Box creation
    int numberR = 10;
    int numberG = 10;
    Box *box1 = box_create(numberR, numberG);
    Box *box2 = box_create(numberR, numberG);

    // Calls the function to test
    box_addB2toB1(box1, box2);

    // Checking values
    CU_ASSERT_EQUAL(box_getNumberResource(box1), numberR + numberR);
    CU_ASSERT_EQUAL(box_getNumberGarbage(box1), numberG + numberG);
    CU_ASSERT_EQUAL(box_getNumberResource(box2), numberR);
    CU_ASSERT_EQUAL(box_getNumberGarbage(box2), numberG);

    // Destroy box
    box_destroy(box1);
    box_destroy(box2);
}