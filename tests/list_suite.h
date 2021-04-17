//
// Created by doe on 28/03/2021.
//

#ifndef PRIM_LIST_SUITE_H
#define PRIM_LIST_SUITE_H

#include "test_structure.h"
#include "test_machine.h"
#include "test_case.h"
#include "test_map.h"

#define NUMBERSUITE 4

int (*listSuit[NUMBERSUITE])(CU_pSuite) = {
        testStructure_createSuite,
        testMachine_createSuite,
        testCase_createSuite,
        testMap_createSuite
};

#endif //PRIM_LIST_SUITE_H
