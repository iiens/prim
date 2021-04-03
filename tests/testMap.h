#ifndef TESTS_MAP
#define TESTS_MAP

#include "CUnit/Basic.h"
#include "../headers/map.h"

struct testMap_Description_S {
    char* description;
    void (*function)(void);
};
typedef struct testMap_Description_S testMap_Description;

/**
 * This function is used to create the "Test Map" suite
 * with the test set on the Map type and its manipulation functions
 *
 * @param pSuite test suite
 */
int testMap_createSuite(CU_pSuite pSuite);

int testMap_initSuite();
int testMap_cleanSuite();

void testMap_createMapEasy();
void testMap_createMapMedium();
void testMap_createMapHard();

void testMap_hireFise();
void testMap_hireFisa();
void testMap_changeProductionFISA();

void testMap_machine();

void testMap_collectionResource();
void testMap_collectionWaste();

void testMap_movingOnCarpet();
void testMap_movingOnCroix();

#define TESTMAP_NUMBERTESTS 3

#endif //TESTS_MAP
