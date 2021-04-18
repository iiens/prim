/*!
 * \file test_box.h
 * \author Valentin DREANO
 * \version 0.1
 * \date 17/04/2021
 *
 * Contains all the suite for Box.c tests
 * The assumption is made that the setters and getter are functional
 *
 */

#ifndef PRIM_TEST_BOX_H
#define PRIM_TEST_BOX_H

#include "CUnit/Basic.h"
#include "structure_list_test.h"
#include "../headers/data/box.h"

/**
 * Number of tests in the suite
 */
#define TESTBOX_NUMBERTESTS 2

/**
 * This function is used to create the "Test Box" suite
 * with the test set on the Map type and its manipulation functions
 *
 * @param pSuite test suite
 * @return 0 if it was successful and 1 otherwise
 */
int testBox_createSuite(CU_pSuite pSuite);

/**
 * This function is used to initialize the sequence
 * @return 0 if it was successful and 1 otherwise
 */
int testBox_initSuite();

/**
 * This function is used to close the suite
 * @return 0 if it was successful and 1 otherwise
 */
int testBox_cleanSuite();

/**
 * This function allows you to test that a box is created with the correct values.
 */
void testBox_create();

/**
 * This function allows you to test the addition of two boxes
 */
void testBox_addition();

#endif //PRIM_TEST_BOX_H
