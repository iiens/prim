#ifndef TEST_STRUCTURE_H
#define TEST_STRUCTURE_H

#include "CUnit/Basic.h"
#include "StructureListTest.h"
#include "../headers/utils/structures.h"

#define TESTDICTIONARY_NUMBERTESTS 3
#define TESTLIST_NUMBERTESTS 3

/**
 * This function is used to create the "Test Structure" suite
 * with the test set on the Map type and its manipulation functions
 *
 * @param pSuite test suite
 */
int testStructure_createSuite(CU_pSuite pSuite);

int testStructure_initSuite();
int testStructure_cleanSuite();

void testDictionary_create();
void testDictionary_destroy();
void testDictionary_search();

void testList_create();
void testList_createEmpty();
void testList_destroy();
void testList_index();
void testList_removeIndex();

#endif //TEST_STRUCTURE_H
