#include "test_map.h"

Vector2D testMap_gate;
Vector2D testMap_source1;
Vector2D testMap_source2;

test_List testMap_listTests[TESTMAP_NUMBERTESTS] = {
        {"Map_Instantiation_Easy\0",     testMap_createMapEasy},
        {"Map_Instantiation_Medium\0",   testMap_createMapMedium},
        {"Map_Instantiation_Hard\0",     testMap_createMapHard},
        {"Map_Buy_Fisa\0",               testMap_hireFisa},
        {"Map_Buy_Fise\0",               testMap_hireFise},
        {"Map_Change_Fisa_Production\0", testMap_changeProductionFISA},
        {"Map_Buy_Machine\0",            testMap_machineBuy},
        {"Map_Update_Machine\0",         testMap_machineUpgrade},
        {"Map_Destroy_Machine\0",        testMap_machineDestroy},
        {"Map_Buy_Staff\0", testMap_staffBuy}
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
    srand(1); // NOLINT(cert-msc51-cpp)
    testMap_gate.x = 3;
    testMap_gate.y = 6;
    testMap_source1.x = 3;
    testMap_source1.y = 5;
    testMap_source2.x = 7;
    testMap_source2.y = 5;
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
    // Assumption that the creation of a map has been tested beforehand
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
    // Assumption that the creation of a map has been tested beforehand
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
    // Assumption that the creation of a map has been tested beforehand
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

void testMap_machineBuy() {
    ErrorCode e;

    // Assumption that the creation of a map has been tested beforehand
    // Create map
    Map *map = map_create(DIFFICULTY_EASY);

    MachineStuff type = MS_RECYCLING_CENTER;
    const MachineInfo *machineInfo = machineInfo_getMachineInfoByType(type);
    int costE = machineInfo_getCostE(machineInfo);
    int costDD = machineInfo_getCostDD(machineInfo);

    int numberE = map_getNumberE(map);
    int numberDD = map_getNumberDD(map);

    // This function uses functions of another implemented type.
    // Each of the functions has been tested in the previous tests.
    // Calls the function to test
    e = map_addMachine(type, 0, -1, 0, map);
    // Checking values
    CU_ASSERT_EQUAL(e, ERROR_CASE_NOT_FOUND);

    map_setNumberE(map, -numberE);
    map_setNumberDD(map, -numberDD);
    // Calls the function to test
    e = map_addMachine(type, 0, 0, 0, map);
    // Checking values
    CU_ASSERT_EQUAL(e, ERROR_NOT_ENOUGH_E);

    map_setNumberE(map, costE);
    // Calls the function to test
    e = map_addMachine(type, 0, 0, 0, map);
    // Checking values
    CU_ASSERT_EQUAL(e, ERROR_NOT_ENOUGH_DD);

    map_setNumberDD(map, costDD);
    // Calls the function to test
    e = map_addMachine(type, 0, 0, 0, map);

    // Checking values
    Case *ca = map_getCase(0, 0, map);
    Machine *machine = case_getMachine(ca);

    CU_ASSERT_EQUAL(e, NO_ERROR);
    CU_ASSERT_NOT_EQUAL(machine, NULL);
    CU_ASSERT_EQUAL(machine_getType(machine), type);

    // Destroy map
    map_destroy(map);
}

void testMap_machineUpgrade() {
    ErrorCode e;

    // Assumption that the creation of a map has been tested beforehand
    // Create map
    Map *map = map_create(DIFFICULTY_EASY);

    MachineStuff type = MS_RECYCLING_CENTER;
    const MachineInfo *machineInfo = machineInfo_getMachineInfoByType(type);
    int costE = machineInfo_getCostUpgradeE(machineInfo);
    int costDD = machineInfo_getCostUpgradeDD(machineInfo);

    int numberE = map_getNumberE(map);
    int numberDD = map_getNumberDD(map);

    // This function uses functions of another implemented type.
    // Each of the functions has been tested in the previous tests.
    // Calls the function to test
    e = map_upgradeMachine(-1, 0, map);
    // Checking values
    CU_ASSERT_EQUAL(e, ERROR_CASE_NOT_FOUND);

    // Calls the function to test
    e = map_upgradeMachine(0, 0, map);
    // Checking values
    CU_ASSERT_EQUAL(e, ERROR_CASE_CANT_BE_UPGRADED);

    // Assumption that the operation of a machine and case has been tested beforehand
    // Machine creation
    Case *ca = map_getCase(0, 0, map);
    Machine *machine = machine_create(type);
    case_addMachine(ca, machine);
    int level = machine_getLevel(machine);

    map_setNumberE(map, -numberE);
    map_setNumberDD(map, -numberDD);
    // Calls the function to test
    e = map_upgradeMachine(0, 0, map);
    // Checking values
    CU_ASSERT_EQUAL(e, ERROR_NOT_ENOUGH_E);

    map_setNumberE(map, costE);
    // Calls the function to test
    e = map_upgradeMachine(0, 0, map);
    // Checking values
    CU_ASSERT_EQUAL(e, ERROR_NOT_ENOUGH_DD);

    map_setNumberDD(map, costDD);
    // Calls the function to test
    e = map_upgradeMachine(0, 0, map);

    // Checking values
    CU_ASSERT_EQUAL(e, NO_ERROR);
    CU_ASSERT_EQUAL(machine_getLevel(machine), level + 1);

    // Destroy map
    map_destroy(map);
}

void testMap_machineDestroy() {
    ErrorCode e;

    // Assumption that the creation of a map has been tested beforehand
    // Create map
    Map *map = map_create(DIFFICULTY_EASY);

    MachineStuff type = MS_RECYCLING_CENTER;
    const MachineInfo *machineInfo = machineInfo_getMachineInfoByType(type);
    int costE = machineInfo_getCostDestroyE(machineInfo);
    int costDD = machineInfo_getCostDestroyDD(machineInfo);

    int numberE = map_getNumberE(map);
    int numberDD = map_getNumberDD(map);

    // This function uses functions of another implemented type.
    // Each of the functions has been tested in the previous tests.
    // Calls the function to test
    e = map_destroyMachine(-1, 0, map);
    // Checking values
    CU_ASSERT_EQUAL(e, ERROR_CASE_NOT_FOUND);

    // Calls the function to test
    e = map_destroyMachine(0, 0, map);
    // Checking values
    CU_ASSERT_EQUAL(e, ERROR_CASE_CANT_BE_DESTROYED);

    // Assumption that the operation of a machine and case has been tested beforehand
    // Machine creation
    Case *ca = map_getCase(0, 0, map);
    Machine *machine = machine_create(type);
    case_addMachine(ca, machine);
    int level = machine_getLevel(machine);

    map_setNumberE(map, -numberE);
    map_setNumberDD(map, -numberDD);
    // Calls the function to test
    e = map_destroyMachine(0, 0, map);
    // Checking values
    CU_ASSERT_EQUAL(e, ERROR_NOT_ENOUGH_E);

    map_setNumberE(map, costE);
    // Calls the function to test
    e = map_destroyMachine(0, 0, map);
    // Checking values
    CU_ASSERT_EQUAL(e, ERROR_NOT_ENOUGH_DD);

    map_setNumberDD(map, costDD);
    // Calls the function to test
    e = map_destroyMachine(0, 0, map);

    // Checking values
    CU_ASSERT_EQUAL(e, NO_ERROR);
    CU_ASSERT_EQUAL(case_getMachine(ca), NULL);

    // Destroy map
    map_destroy(map);
}

void testMap_staffBuy() {
    ErrorCode e;

    // Assumption that the creation of a map has been tested beforehand
    // Create map
    Map *map = map_create(DIFFICULTY_EASY);

    int idStaff = 1;
    const Staff *staff = staff_getStaffByID(idStaff);
    int costE = staff_getStaffCostE(staff);
    int costDD = staff_getStaffCostDD(staff);

    Dictionary *dictionary = map_getStaffDictionary(map);
    int numberStaff = staff_getNumberStaffByID(dictionary, idStaff);

    int numberE = map_getNumberE(map);
    int numberDD = map_getNumberDD(map);

    // This function uses functions of another implemented type.
    // Each of the functions has been tested in the previous tests.
    // Calls the function to test
    e = map_buyStaff(-1, map);
    // Checking values
    CU_ASSERT_EQUAL(e, ERROR_INVALID_STAFF_NUMBER);

    map_setNumberE(map, -numberE);
    map_setNumberDD(map, -numberDD);
    // Calls the function to test
    e = map_buyStaff(idStaff, map);
    // Checking values
    CU_ASSERT_EQUAL(e, ERROR_NOT_ENOUGH_E);

    map_setNumberE(map, costE);
    // Calls the function to test
    e = map_buyStaff(idStaff, map);
    // Checking values
    CU_ASSERT_EQUAL(e, ERROR_NOT_ENOUGH_DD);

    map_setNumberDD(map, costDD);
    // Calls the function to test
    e = map_buyStaff(idStaff, map);

    // Checking values
    CU_ASSERT_EQUAL(e, NO_ERROR);
    CU_ASSERT_EQUAL(staff_getNumberStaffByID(dictionary, idStaff), numberStaff + 1);

    // Destroy map
    map_destroy(map);
}