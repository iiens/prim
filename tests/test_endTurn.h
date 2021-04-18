/*!
 * \file test_endTurn.h
 * \author Valentin DREANO
 * \version 0.1
 * \date 17/04/2021
 *
 * Contains all the suite for endTurn function tests
 * The assumption is made that the setters and getter are functional
 *
 */

#ifndef TEST_ENDTURN_H
#define TEST_ENDTURN_H

#include "CUnit/Basic.h"
#include "structure_list_test.h"
#include "../headers/utils/map_utils.h"

/**
 * Number of tests in the suite
 */
#define TESTENDTURN_NUMBERTESTS 8

/**
 * This function is used to create the "Test EndTurn" suite
 * with the test set on the Map type and its manipulation functions
 *
 * @param pSuite test suite
 * @return 0 if it was successful and 1 otherwise
 */
int testEndTurn_createSuite(CU_pSuite pSuite);

/**
 * This function is used to initialize the sequence
 * @return 0 if it was successful and 1 otherwise
 */
int testEndTurn_initSuite();

/**
 * This function is used to close the suite
 * @return 0 if it was successful and 1 otherwise
 */
int testEndTurn_cleanSuite();

/**
 * This function makes it possible to test the production of Fise at each turn.
 */
void testEndTurn_productionFise();

/**
 * This function makes it possible to test the production of Fisa at each turn.
 */
void testEndTurn_productionFisa();

/**
 * This function is used to test the movement of boxes between machines
 */
void testEndTurn_moveResource();

/**
 * This function is used to test the generation of resources at the sources.
 */
void testEndTurn_generateResource();

/**
 * This function is used to test the modification of the resources at the door in garbage
 */
void testEndTurn_generateGarbage();

/**
 * This function makes it possible to test the correct functioning of the recycling centers.
 */
void testEndTurn_RecyclingCenters();

/**
 * This function is used to test the correct functioning of the collectors.
 */
void testEndTurn_Collector();

/**
 * This function makes it possible to test the destruction of resources
 * and send waste to the door for the boxes on the ground
 */
void testEndTurn_resetResourceGarbage();

#endif //TEST_ENDTURN_H
