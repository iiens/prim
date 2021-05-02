/*!
 * \file test_case.h
 * \author Valentin DREANO
 * \version 0.1
 * \date 17/04/2021
 *
 * Contains all the suite for Case.c tests
 * The assumption is made that the setters and getter are functional
 *
 */

#ifndef PRIM_TEST_CASE_H
#define PRIM_TEST_CASE_H

#include "CUnit/Basic.h"
#include "structure_list_test.h"
#include "../headers/data/case.h"

/**
 * Number of tests in the suite
 */
#define TESTCASE_NUMBERTESTS 6

/**
 * This function is used to create the "Test Case" suite
 * with the test set on the Map type and its manipulation functions
 *
 * @param pSuite test suite
 * @return 0 if it was successful and 1 otherwise
 */
int testCase_createSuite(CU_pSuite pSuite);

/**
 * This function is used to initialize the sequence
 * @return 0 if it was successful and 1 otherwise
 */
int testCase_initSuite();

/**
 * This function is used to close the suite
 * @return 0 if it was successful and 1 otherwise
 */
int testCase_cleanSuite();

/**
 * This function allows you to test that a box is created with the correct values
 */
void testCase_create();

/**
 * This function allows you to test the addition and deletion of a box.
 */
void testCase_AddDeleteBox();

/**
 * This function is used to test the addition of a source
 */
void testCase_AddSource();

/**
 * This function is used to test the addition of a gate
 */
void testCase_AddGate();

/**
 * This function is used to test the addition of a machine
 */
void testCase_AddMachine();

/**
 * This function is used to test the reset of an empty cell.
 */
void testCase_Empty();

#endif //PRIM_TEST_CASE_H
