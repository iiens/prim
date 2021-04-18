/*!
 * \file test_map.h
 * \author Valentin DREANO
 * \version 0.1
 * \date 17/04/2021
 *
 * Contains all the suite for Map.c tests
 * The assumption is made that the setters and getter are functional
 *
 */

#ifndef TESTS_MAP
#define TESTS_MAP

#include "CUnit/Basic.h"
#include "structure_list_test.h"
#include "../headers/map.h"

/**
 * Number of tests in the suite
 */
#define TESTMAP_NUMBERTESTS 10

/**
 * This function is used to create the "Test Map" suite
 * with the test set on the Map type and its manipulation functions
 *
 * @param pSuite test suite
 * @return 0 if it was successful and 1 otherwise
 */
int testMap_createSuite(CU_pSuite pSuite);

/**
 * This function is used to initialize the sequence
 * @return 0 if it was successful and 1 otherwise
 */
int testMap_initSuite();

/**
 * This function is used to close the suite
 * @return 0 if it was successful and 1 otherwise
 */
int testMap_cleanSuite();

/**
 * This function allows you to test that an easy map is created with the right values
 */
void testMap_createMapEasy();

/**
 * This function allows you to test that an average map is created with the right values
 */
void testMap_createMapMedium();

/**
 * This function allows you to test that a difficult map is created with the right value.
 */
void testMap_createMapHard();

/**
 * This function allows you to test the purchase of a fise
 */
void testMap_hireFise();

/**
 * This function allows you to test the purchase of a fisa
 */
void testMap_hireFisa();

/**
 * This function makes it possible to test the correct change of production of Fisa
 */
void testMap_changeProductionFISA();

/**
 * This function makes it possible to test the purchase order of any type of machine with the correct positioning.
 */
void testMap_machineBuy();

/**
 * This function allows you to test the update command of any type of machine
 */
void testMap_machineUpgrade();

/**
 * This function is used to test the destruction command of any type of machine.
 */
void testMap_machineDestroy();

/**
 * This function allows to test the purchase order of all the different staff
 */
void testMap_staffBuy();

#endif //TESTS_MAP
