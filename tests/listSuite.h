//
// Created by doe on 28/03/2021.
//

#ifndef PRIM_LISTSUITE_H
#define PRIM_LISTSUITE_H

#include "testStructure.h"
#include "testMachine.h"
#include "testCase.h"
#include "testMap.h"

#define NUMBERSUITE 4

int (*listSuit[NUMBERSUITE])(CU_pSuite) = {
        testStructure_createSuite,
        testMachine_createSuite,
        testCase_createSuite,
        testMap_createSuite
};

#endif //PRIM_LISTSUITE_H
