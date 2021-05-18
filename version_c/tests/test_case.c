/*!
 * \file test_case.c
 * \author Valentin DREANO
 * \version 0.1
 * \date 17/04/2021
 *
 * Contains all the suite for Case.c tests
 * The assumption is made that the setters and getter are functional
 *
 */

#include "test_case.h"

/**
 * List of tests in the suite
 */
test_List testCase_listTests[TESTCASE_NUMBERTESTS] = {
        {"Case_Instantiation\0",   testCase_create},
        {"Case_Add_Delete_Box\0", testCase_AddDeleteBox},
        {"Case_Add_Source\0", testCase_AddSource},
        {"Case_Add_Gate\0", testCase_AddGate},
        {"Case_Add_Machine\0", testCase_AddMachine},
        {"Case_Set_Empty\0", testCase_Empty}
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

    // Calls the function to test
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

void testCase_AddDeleteBox() {
    // Assumption that the creation of a case has been tested beforehand
    // Case creation
    int x = 0;
    int y = 0;
    Case *ca = case_create(x,y);

    // Assumption that the operation of a box has been tested beforehand
    // Box creation
    int numberR = 10;
    int numberG = 10;
    Box*box = box_create(numberR, numberG);

    // Calls the function to test
    case_addBox(ca, box);

    // Checking values
    CU_ASSERT_EQUAL(case_hasBox(ca), true);
    Box* box2 = case_getBox(ca);
    CU_ASSERT_EQUAL(box_getNumberGarbage(box2), numberG);
    CU_ASSERT_EQUAL(box_getNumberResource(box2), numberR);

    // Calls the function to test
    case_deleteBox(ca);

    // Checking values
    CU_ASSERT_EQUAL(case_hasBox(ca), false);
    CU_ASSERT_EQUAL(case_getBox(ca), NULL);

    case_destroy(ca);
}

void testCase_AddSource() {
    // Assumption that the creation of a case has been tested beforehand
    // Case creation
    int x = 0;
    int y = 0;
    Case *ca = case_create(x,y);

    // Calls the function to test
    case_addSource(ca);

    // Checking values
    CU_ASSERT_EQUAL(case_getType(ca), CASE_SOURCE);

    // Case destroy
    case_destroy(ca);
}

void testCase_AddGate() {
    // Assumption that the creation of a case has been tested beforehand
    // Case creation
    int x = 0;
    int y = 0;
    Case *ca = case_create(x,y);

    // Calls the function to test
    case_addGate(ca);

    // Checking values
    CU_ASSERT_EQUAL(case_getType(ca), CASE_GATE);

    // Case destroy
    case_destroy(ca);
}

void testCase_AddMachine() {
    // Assumption that the creation of a case has been tested beforehand
    // Case creation
    int x = 0;
    int y = 0;
    Case *ca = case_create(x,y);

    // Assumption that the operation of a machine has been tested beforehand
    // Machine creation
    MachineStuff type = MS_COLLECTOR;
    Machine *machine = machine_create(type);

    // Calls the function to test
    case_addMachine(ca, machine);

    // Checking values
    CU_ASSERT_EQUAL(case_getType(ca), CASE_MACHINE);
    CU_ASSERT_EQUAL(case_getMachine(ca), machine);

    // Case destroy
    case_destroy(ca);
}

void testCase_Empty() {
    // Assumption that the creation of a case has been tested beforehand
    // Case creation
    int x = 0;
    int y = 0;
    Case *ca = case_create(x,y);

    // Assumption that the operation of a box has been tested beforehand
    // Box creation
    int numberR = 10;
    int numberG = 10;
    Box*box = box_create(numberR, numberG);

    case_addSource(ca);
    case_addBox(ca, box);

    // Checking values
    CU_ASSERT_EQUAL(case_getType(ca), CASE_SOURCE);
    CU_ASSERT_EQUAL(case_isEmpty(ca), false);

    // Calls the function to test
    case_setEmpty(ca);

    // Checking values
    CU_ASSERT_EQUAL(case_isEmpty(ca), true);
    CU_ASSERT_EQUAL(case_getBox(ca), NULL);
    CU_ASSERT_EQUAL(case_getMachine(ca), NULL);

    // Assumption that the operation of a machine has been tested beforehand
    // Machine creation
    MachineStuff type = MS_COLLECTOR;
    Machine *machine = machine_create(type);
    case_addMachine(ca, machine);

    // Checking values
    CU_ASSERT_EQUAL(case_getType(ca), CASE_MACHINE);
    CU_ASSERT_EQUAL(case_isEmpty(ca), false);

    // Calls the function to test
    case_setEmpty(ca);

    // Checking values
    CU_ASSERT_EQUAL(case_isEmpty(ca), true);
    CU_ASSERT_EQUAL(case_getBox(ca), NULL);
    CU_ASSERT_EQUAL(case_getMachine(ca), NULL);

    // Case destroy
    case_destroy(ca);
}