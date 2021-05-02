/*!
 * \file test_machine.h
 * \author Valentin DREANO
 * \version 0.1
 * \date 17/04/2021
 *
 * Contains all the suite for machine.c tests
 * The assumption is made that the setters and getter are functional
 *
 */

#ifndef TEST_MACHINE_H
#define TEST_MACHINE_H

#include "CUnit/Basic.h"
#include "structure_list_test.h"
#include "../headers/data/machine.h"

/**
 * Number of tests in the suite
 */
#define TESTMACHINE_NUMBERTESTS 4

/**
 * This function is used to create the "Test Machine" suite
 * with the test set on the Map type and its manipulation functions
 *
 * @param pSuite test suite
 * @return 0 if it was successful and 1 otherwise
 */
int testMachine_createSuite(CU_pSuite pSuite);

/**
 * This function is used to initialize the sequence
 * @return 0 if it was successful and 1 otherwise
 */
int testMachine_initSuite();

/**
 * This function is used to close the suite
 * @return 0 if it was successful and 1 otherwise
 */
int testMachine_cleanSuite();

/**
 * This function allows you to test that a machine is created with the correct values
 */
void testMachine_create();

/**
 * This function allows you to test that the rotation of a machine is done well.
 */
void testMachine_rotation();

/**
 * This function makes it possible to test that the incrementation of the level is done well
 */
void testMachine_LevelUp();

/**
 * This function is used to test the addition and deletion of a box in a machine
 */
void testMachine_AddDeleteBox();

#endif //TEST_MACHINE_H
