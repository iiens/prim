#ifndef TESTS_MAP
#define TESTS_MAP

#include "CUnit/Basic.h"
#include "StructureListTest.h"
#include "../headers/map.h"

#define TESTMAP_NUMBERTESTS 6

/**
 * This function is used to create the "Test Map" suite
 * with the test set on the Map type and its manipulation functions
 *
 * @param pSuite test suite
 */
int testMap_createSuite(CU_pSuite pSuite);

int testMap_initSuite();
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
void testMap_machineUpgrade();
void testMap_machineDestroy();

void testMap_staffBuy();

void testEndTurn_productionFise();
void testEndTurn_productionFisa();
void testEndTurn_productionResources();

void testEndTurn_destroyResourcesAndMoveGarbage();
void tesEndTurn_resourcesToGate();

void testMap_movingResources();

#endif //TESTS_MAP
