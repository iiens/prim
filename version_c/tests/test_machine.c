/*!
 * \author Valentin DREANO
 * \version 0.1
 * \date 17/04/2021
 *
 * Contains all the suite for Case.c tests
 * The assumption is made that the setters and getter are functional
 *
 */

#include "test_machine.h"

test_List testMachine_listTests[TESTMACHINE_NUMBERTESTS] = {
        {"Machine_Instantiation\0", testMachine_create},
        {"Machine_Rotation\0", testMachine_rotation},
        {"Machine_Update\0", testMachine_LevelUp},
        {"Machine_Add_Delete_Box\0", testMachine_AddDeleteBox}
};

int testMachine_createSuite(CU_pSuite pSuite) {
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
    // Machine creation
    MachineStuff type = MS_COLLECTOR;
    Machine *machine = machine_create(type);

    // Checking values
    CU_ASSERT_EQUAL(machine_getLevel(machine), MACHINE_DEFAULT_LVL);
    CU_ASSERT_EQUAL(machine_getType(machine), type);
    // Check that the exit is to the South
    CU_ASSERT_EQUAL(machine_getDirection(machine, SOUTH), DIRECTION_OUT);

    // Destroy map
    machine_destroyMachine(machine);
}

void testMachine_rotation() {
    // Assumption that the creation of a machine has been tested beforehand
    // Case creation
    MachineStuff type = MS_COLLECTOR;
    Machine *machine = machine_create(type);

    // Checking values
    CU_ASSERT_EQUAL(machine_getDirection(machine, SOUTH), DIRECTION_OUT);

    // Calls the function to test
    machine_rotateMachine(machine, 1);
    // Checking values
    CU_ASSERT_EQUAL(machine_getDirection(machine, WEST), DIRECTION_OUT);

    // Calls the function to test
    machine_rotateMachine(machine, 1);
    // Checking values
    CU_ASSERT_EQUAL(machine_getDirection(machine, NORTH), DIRECTION_OUT);

    // Calls the function to test
    machine_rotateMachine(machine, 1);
    // Checking values
    CU_ASSERT_EQUAL(machine_getDirection(machine, EAST), DIRECTION_OUT);

    // Calls the function to test
    machine_rotateMachine(machine, 2);
    // Checking values
    CU_ASSERT_EQUAL(machine_getDirection(machine, WEST), DIRECTION_OUT);

    // Calls the function to test
    machine_rotateMachine(machine, 4);
    // Checking values
    CU_ASSERT_EQUAL(machine_getDirection(machine, WEST), DIRECTION_OUT);

    // Destroy map
    machine_destroyMachine(machine);
}

void testMachine_LevelUp() {
    // Assumption that the creation of a machine has been tested beforehand
    // Create machine
    Machine *machine = machine_create(MS_COLLECTOR);

    // Recovery of value before purchase
    int level = machine_getLevel(machine);

    // Calls the function to test
    machine_incrementLevel(machine);

    // Checking values
    CU_ASSERT_EQUAL(machine_getLevel(machine), level + 1);

    // Destroy machine
    machine_destroyMachine(machine);
}

void testMachine_AddDeleteBox() {
    // Assumption that the creation of a machine has been tested beforehand
    // Machine creation
    MachineStuff type = MS_COLLECTOR;
    Machine *machine = machine_create(type);

    // Assumption that the operation of a box has been tested beforehand
    // Box creation
    int numberR = 10;
    int numberG = 10;
    Box *box = box_create(numberR, numberG);

    // Calls the function to test
    machine_addBox(machine, NORTH, box);

    // Checking values
    Box*tmp = machine_getBox(machine, NORTH);
    CU_ASSERT_EQUAL(tmp, box);

    // Calls the function to test
    machine_destroyBox(machine, NORTH);

    // Checking values
    tmp = machine_getBox(machine, NORTH);
    CU_ASSERT_EQUAL(tmp, NULL);

    // Destroy machine
    machine_destroyMachine(machine);
}