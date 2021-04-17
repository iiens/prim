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

#include "testMachine.h"

test_List testMachine_listTests[TESTMACHINE_NUMBERTESTS] = {
        {"Instantiation_Machine\0",   testMachine_create}
};

int testCase_createSuite(CU_pSuite pSuite) {

    /* add a suite to the registry */
    pSuite = CU_add_suite("Test_Type_Machine", testMachine_initSuite, testMachine_cleanSuite);
    if (NULL == pSuite) {
        return EXIT_FAILURE;
    }

    /* add the tests to the suite */
    for (int i = 0; i < TESTMACHINE_NUMBERTESTS; i++) {
        if (NULL == CU_add_test(pSuite, testMachine_listTests[i].description, testMachine_listTests[i].function)) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int testMachine_initSuite() {
    return 0;
}

int testMachine_cleanSuite() {
    return 0;
}

void testMachine_create() {
    // Case creation
    MachineStuff type = MS_COLLECTOR;
    Machine *machine = machine_create(type);

    // Checking values
    CU_ASSERT_EQUAL(machine_getLevel(machine), MACHINE_DEFAULT_LVL);
    CU_ASSERT_EQUAL(machine_getType(machine), type);

    // Destroy map
    machine_destroyMachine(machine);
}