//
// Created by doe on 28/03/2021.
//

#ifndef PRIM_LISTSUITE_H
#define PRIM_LISTSUITE_H

#include "testMap.h"

#define NUMBERSUITE 1

int (*listSuit[NUMBERSUITE])(CU_pSuite) = {
    testMap_createSuite
};

#endif //PRIM_LISTSUITE_H
