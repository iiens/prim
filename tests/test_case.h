/*!
 * \file testCase.h
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

#define TESTCASE_NUMBERTESTS 1

/**
 * This function is used to create the "Test Case" suite
 * with the test set on the Map type and its manipulation functions
 *
 * @param pSuite test suite
 */
int testCase_createSuite(CU_pSuite pSuite);

int testCase_initSuite();
int testCase_cleanSuite();

/**
 * This function allows you to test that a box is created with the correct values
 */
void testCase_create();

#endif //PRIM_TEST_CASE_H
