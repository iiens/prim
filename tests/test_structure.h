/*!
 * \file test_structure.h
 * \author Valentin DREANO
 * \version 0.1
 * \date 17/04/2021
 *
 * Contains all the suite for structure.c tests
 * The assumption is made that the setters and getter are functional
 *
 */

#ifndef TEST_STRUCTURE_H
#define TEST_STRUCTURE_H

#include "CUnit/Basic.h"
#include "structure_list_test.h"
#include "../headers/utils/structures.h"

/**
 * Number of tests in the suite
 */
#define TESTDICTIONARY_NUMBERTESTS 3

/**
 * Number of tests in the suite
 */
#define TESTLIST_NUMBERTESTS 3

/**
 * This function is used to create the "Test Structure" suite
 * with the test set on the Map type and its manipulation functions
 *
 * @param pSuite test suite
 * @return 0 if it was successful and 1 otherwise
 */
int testStructure_createSuite(CU_pSuite pSuite);

/**
 * This function is used to initialize the sequence
 * @return 0 if it was successful and 1 otherwise
 */
int testStructure_initSuite();

/**
 * This function is used to close the suite
 * @return 0 if it was successful and 1 otherwise
 */
int testStructure_cleanSuite();

/**
 *
 */
void testDictionary_create();
void testDictionary_addElement();
void testDictionary_removeElement();
void testDictionary_indexElement();

/**
 * This function allows you to test that a list is created
 */
void testList_create();

/**
 * This function allows you to test that an empty list is created.
 */
void testList_createEmpty();
void testList_addElement();
void testList_indexElement();
void testList_index();
void testList_removeIndex();

#endif //TEST_STRUCTURE_H
