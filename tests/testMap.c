#include "testMap.h"

testMap_Description testMap_listTests[TESTMAP_NUMBERTESTS] = {
        {"Instantiation_Map_Easy\0", testMap_createMapEasy},
        {"Instantiation_Map_Medium\0", testMap_createMapMedium},
        {"Instantiation_Map_Hard\0", testMap_createMapHard}
};

int testMap_createSuite(CU_pSuite pSuite) {

    /* add a suite to the registry */
    pSuite = CU_add_suite("Test_Type_Map", testMap_initSuite, testMap_cleanSuite);
    if (NULL == pSuite)
    {
        return EXIT_FAILURE;
    }

    /* add the tests to the suite */
    for (int i = 0; i < TESTMAP_NUMBERTESTS; i++) {
        if (NULL == CU_add_test(pSuite, testMap_listTests[i].description, testMap_listTests[i].function)) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int testMap_initSuite() {
    return 0;
}

int testMap_cleanSuite() {
    return 0;
}

void testMap_createMapEasy() {
    Map * map = map_create(DIFFICULTY_EASY);

    CU_ASSERT_EQUAL(map_getWidth(map), 10);
    CU_ASSERT_EQUAL(map_getHeight(map),10);
    CU_ASSERT_EQUAL(map_getDifficulty(map), DIFFICULTY_EASY);
    CU_ASSERT_EQUAL(map_getNumberDD(map), 100);
    CU_ASSERT_EQUAL(map_getNumberE(map), 100);
    CU_ASSERT_EQUAL(map_getNumberPollution(map), 0);
    CU_ASSERT_EQUAL(map_getPlayerScore(map), 0);
    CU_ASSERT_EQUAL(map_getNumberFISE(map), 5);
    CU_ASSERT_EQUAL(map_getNumberFISA(map), 5);

    map_destroy(map);
}

void testMap_createMapMedium() {
    Map * map = map_create(DIFFICULTY_MEDIUM);

    CU_ASSERT_EQUAL(map_getWidth(map), 20);
    CU_ASSERT_EQUAL(map_getHeight(map),20);
    CU_ASSERT_EQUAL(map_getDifficulty(map), DIFFICULTY_MEDIUM);
    CU_ASSERT_EQUAL(map_getNumberDD(map), 100);
    CU_ASSERT_EQUAL(map_getNumberE(map), 100);
    CU_ASSERT_EQUAL(map_getNumberPollution(map), 0);
    CU_ASSERT_EQUAL(map_getPlayerScore(map), 0);
    CU_ASSERT_EQUAL(map_getNumberFISE(map), 5);
    CU_ASSERT_EQUAL(map_getNumberFISA(map), 5);

    map_destroy(map);
    CU_ASSERT_EQUAL(1, 1);
}

void testMap_createMapHard() {
    Map * map = map_create(DIFFICULTY_HARD);

    CU_ASSERT_EQUAL(map_getWidth(map), 30);
    CU_ASSERT_EQUAL(map_getHeight(map),30);
    CU_ASSERT_EQUAL(map_getDifficulty(map), DIFFICULTY_HARD);
    CU_ASSERT_EQUAL(map_getNumberDD(map), 100);
    CU_ASSERT_EQUAL(map_getNumberE(map), 100);
    CU_ASSERT_EQUAL(map_getNumberPollution(map), 0);
    CU_ASSERT_EQUAL(map_getPlayerScore(map), 0);
    CU_ASSERT_EQUAL(map_getNumberFISE(map), 5);
    CU_ASSERT_EQUAL(map_getNumberFISA(map), 5);

    map_destroy(map);
}