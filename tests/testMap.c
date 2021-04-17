#include "testMap.h"

test_List testMap_listTests[TESTMAP_NUMBERTESTS] = {
        {"Instantiation_Map_Easy\0",   testMap_createMapEasy},
        {"Instantiation_Map_Medium\0", testMap_createMapMedium},
        {"Instantiation_Map_Hard\0",   testMap_createMapHard},
        {"Buy_Fisa\0",                 testMap_hireFisa},
        {"Buy_Fise\0",                 testMap_hireFise},
        {"Change_Fisa_Production\0",   testMap_changeProductionFISA}
};

int testMap_createSuite(CU_pSuite pSuite) {

    /* add a suite to the registry */
    pSuite = CU_add_suite("Test_Type_Map", testMap_initSuite, testMap_cleanSuite);
    if (NULL == pSuite) {
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

/**
 * Allows you to check the presence of the right number of source and gate on the map
 *
 * @param numberGate Number gate on the map
 * @param numberSource Number source on the map
 * @param map Map with game information
 */
void testMap_factorisation_verificationGateAndSource(int numberGate, int numberSource, Map *map) {
    Case *ca;
    CaseType typeCase;
    int searchGate = 0;
    int searchSource = 0;
    // Go through the map in order to count the number of gate and sources
    for (int i = 0; i < map_getWidth(map); ++i) {
        for (int j = 0; j < map_getWidth(map); ++j) {
            ca = map_getCase(i, j, map);
            typeCase = case_getType(ca);
            if (typeCase == CASE_GATE) {
                searchGate++;
            }
            if (typeCase == CASE_SOURCE) {
                searchSource++;
            }
        }
    }

    // Checking values found
    CU_ASSERT_EQUAL(searchGate, numberGate);
    CU_ASSERT_EQUAL(searchSource, numberSource);
}

void testMap_createMapEasy() {
    // Map creation
    Map *map = map_create(DIFFICULTY_EASY);

    // Checking values
    CU_ASSERT_EQUAL(map_getWidth(map), 10);
    CU_ASSERT_EQUAL(map_getHeight(map), 10);
    CU_ASSERT_EQUAL(map_getDifficulty(map), DIFFICULTY_EASY);
    CU_ASSERT_EQUAL(map_getNumberDD(map), 100);
    CU_ASSERT_EQUAL(map_getNumberE(map), 100);
    CU_ASSERT_EQUAL(map_getNumberPollution(map), 0);
    CU_ASSERT_EQUAL(map_getPlayerScore(map), 0);
    CU_ASSERT_EQUAL(map_getNumberFISE(map), 5);
    CU_ASSERT_EQUAL(map_getNumberFISA(map), 5);

    testMap_factorisation_verificationGateAndSource(1, 2, map);

    // Destroy map
    map_destroy(map);
}

void testMap_createMapMedium() {
    // Map creation
    Map *map = map_create(DIFFICULTY_MEDIUM);

    // Checking values
    CU_ASSERT_EQUAL(map_getWidth(map), 20);
    CU_ASSERT_EQUAL(map_getHeight(map), 20);
    CU_ASSERT_EQUAL(map_getDifficulty(map), DIFFICULTY_MEDIUM);
    CU_ASSERT_EQUAL(map_getNumberDD(map), 100);
    CU_ASSERT_EQUAL(map_getNumberE(map), 100);
    CU_ASSERT_EQUAL(map_getNumberPollution(map), 0);
    CU_ASSERT_EQUAL(map_getPlayerScore(map), 0);
    CU_ASSERT_EQUAL(map_getNumberFISE(map), 5);
    CU_ASSERT_EQUAL(map_getNumberFISA(map), 5);

    testMap_factorisation_verificationGateAndSource(1, 2, map);

    // Destroy map
    map_destroy(map);
}

void testMap_createMapHard() {
    // Map creation
    Map *map = map_create(DIFFICULTY_HARD);

    // Checking values
    CU_ASSERT_EQUAL(map_getWidth(map), 30);
    CU_ASSERT_EQUAL(map_getHeight(map), 30);
    CU_ASSERT_EQUAL(map_getDifficulty(map), DIFFICULTY_HARD);
    CU_ASSERT_EQUAL(map_getNumberDD(map), 100);
    CU_ASSERT_EQUAL(map_getNumberE(map), 100);
    CU_ASSERT_EQUAL(map_getNumberPollution(map), 0);
    CU_ASSERT_EQUAL(map_getPlayerScore(map), 0);
    CU_ASSERT_EQUAL(map_getNumberFISE(map), 5);
    CU_ASSERT_EQUAL(map_getNumberFISA(map), 5);

    testMap_factorisation_verificationGateAndSource(1, 2, map);

    // Destroy map
    map_destroy(map);
}

void testMap_hireFise() {
    // Principle that the creation of a map to work previously
    // Map creation
    Map *map = map_create(DIFFICULTY_EASY);

    // Recovery of value before purchase
    int numberFise = map_getNumberFISE(map);
    int numberE = map_getNumberE(map);
    int numberDD = map_getNumberDD(map);

    // Calls the function to test
    map_hireFISE(map);

    // Verification that the data has changed
    // An additional Fise
    CU_ASSERT_EQUAL(map_getNumberFISE(map), numberFise + 1);
    // Resources debited
    CU_ASSERT_EQUAL(map_getNumberDD(map), numberDD - COST_FISE_DD);
    CU_ASSERT_EQUAL(map_getNumberE(map), numberE - COST_FISE_E);

    // Destroy map
    map_destroy(map);
}

void testMap_hireFisa() {
    // Principle that the creation of a map to work previously
    // Map creation
    Map *map = map_create(DIFFICULTY_EASY);

    // Recovery of value before purchase
    int numberFisa = map_getNumberFISA(map);
    int numberE = map_getNumberE(map);
    int numberDD = map_getNumberDD(map);

    // Calls the function to test
    map_hireFISA(map);

    // Verification that the data has changed
    // An additional Fise
    CU_ASSERT_EQUAL(map_getNumberFISA(map), numberFisa + 1);
    // Resources debited
    CU_ASSERT_EQUAL(map_getNumberDD(map), numberDD - COST_FISA_DD);
    CU_ASSERT_EQUAL(map_getNumberE(map), numberE - COST_FISA_E);

    // Destroy map
    map_destroy(map);
}

void testMap_changeProductionFISA() {
    // Principle that the creation of a map to work previously
    // Map creation
    Map *map = map_create(DIFFICULTY_EASY);

    // Recovery of value before purchase
    int productionFisa = map_getProductionFISA(map);

    // Calls the function to test
    map_changeProductionFISA(map);

    // Verification that the data has changed
    if (productionFisa == E_VALUE) {
        CU_ASSERT_EQUAL(map_getProductionFISA(map), DD_VALUE);
    } else {
        CU_ASSERT_EQUAL(map_getProductionFISA(map), E_VALUE);
    }

    // Destroy map
    map_destroy(map);
}
