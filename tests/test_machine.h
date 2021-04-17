#ifndef TEST_MACHINE_H
#define TEST_MACHINE_H

#include "CUnit/Basic.h"
#include "structure_list_test.h"
#include "../headers/data/machine.h"

#define TESTMACHINE_NUMBERTESTS 1

/**
 * This function is used to create the "Test Machine" suite
 * with the test set on the Map type and its manipulation functions
 *
 * @param pSuite test suite
 */
int testMachine_createSuite(CU_pSuite pSuite);

int testMachine_initSuite();
int testMachine_cleanSuite();

/**
 * This function allows you to test that a machine is created with the correct values
 */
void testMachine_create();

/**
 * This function allows you to test that the rotation of a machine is done well.
 */
void testMachine_rotation();

#endif //TEST_MACHINE_H
