/*!
 * \file list_suite.h
 * \author Valentin DREANO
 * \version 0.1
 * \date 17/04/2021
 *
 * Contains the list of all the suites to create
 *
 */

#ifndef PRIM_LIST_SUITE_H
#define PRIM_LIST_SUITE_H

#include "test_box.h"
#include "test_structure.h"
#include "test_machine.h"
#include "test_case.h"
#include "test_map.h"
#include "test_endTurn.h"

/**
 * Number of suites to test
 */
#define NUMBERSUITE 6

/**
 * list of different suites
 * @return
 */
int (*listSuit[NUMBERSUITE])(CU_pSuite) = {
        testStructure_createSuite,
        testBox_createSuite,
        testMachine_createSuite,
        testCase_createSuite,
        testMap_createSuite,
        testEndTurn_createSuite
};

#endif //PRIM_LIST_SUITE_H
