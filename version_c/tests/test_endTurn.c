/*!
 * \author Valentin DREANO
 * \version 0.1
 * \date 17/04/2021
 *
 * Contains all the suite for endTurn function tests
 * The assumption is made that the setters and getter are functional
 *
 */

#include "test_endTurn.h"

Vector2D testEndTurn_gate;
Vector2D testEndTurn_source1;
Vector2D testEndTurn_source2;

test_List testEndTurn_listTests[TESTENDTURN_NUMBERTESTS] = {
        {"EndTurn_Production_Fise\0", testEndTurn_productionFise},
        {"EndTurn_Production_Fisa\0", testEndTurn_productionFisa},
        {"EndTurn_Move_Resource\0", testEndTurn_moveResource},
        {"EndTurn_Generate_Resource\0", testEndTurn_generateResource},
        {"EndTurn_Generate_Garbage\0", testEndTurn_generateGarbage},
        {"EndTurn_RecyclingCenters\0", testEndTurn_RecyclingCenters},
        {"EndTurn_Collector\0", testEndTurn_Collector},
        {"EndTurn_Production_resetResourceGarbage\0", testEndTurn_resetResourceGarbage}
};

int testEndTurn_createSuite(CU_pSuite pSuite) {

    /* add a suite to the registry */
    pSuite = CU_add_suite("Test_Function_EndTurn", testEndTurn_initSuite, testEndTurn_cleanSuite);
    if (NULL == pSuite) {
        return EXIT_FAILURE;
    }

    /* add the tests to the suite */
    for (int i = 0; i < TESTENDTURN_NUMBERTESTS; i++) {
        if (NULL == CU_add_test(pSuite, testEndTurn_listTests[i].description, testEndTurn_listTests[i].function)) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int testEndTurn_initSuite() {
    testEndTurn_gate.x = 3;
    testEndTurn_gate.y = 6;
    testEndTurn_source1.x = 3;
    testEndTurn_source1.y = 5;
    testEndTurn_source2.x = 7;
    testEndTurn_source2.y = 5;
    return 0;
}

int testEndTurn_cleanSuite() {
    return 0;
}

void testEndTurn_productionFise() {
    // Assumption that the creation of a map has been tested beforehand
    // Create map
    Map *map = map_create(DIFFICULTY_EASY);

    int numberE = map_getNumberE(map);
    int numberDD = map_getNumberDD(map);
    int numberFise = map_getNumberFISE(map);

    // This function uses functions of another implemented type.
    // Each of the functions has been tested in the previous tests.
    // Calls the function to test
    map_utils_productionFise(map);

    // Checking values
    CU_ASSERT_EQUAL(map_getNumberE(map), numberE + (PRODUCTION_FISE_E * numberFise));
    CU_ASSERT_EQUAL(map_getNumberDD(map), numberDD + (PRODUCTION_FISE_DD * numberFise));

    // Destroy map
    map_destroy(map);
}

void testEndTurn_productionFisa() {
    // Assumption that the creation of a map has been tested beforehand
    // Create map
    Map *map = map_create(DIFFICULTY_EASY);

    // Recovery of value before purchase
    int numberE = map_getNumberE(map);
    int numberDD = map_getNumberDD(map);
    int numberFisa = map_getNumberFISA(map);

    // This function uses functions of another implemented type.
    // Each of the functions has been tested in the previous tests.
    // Calls the function to test
    map_utils_productionFisa(map);

    // Checking values
    CU_ASSERT_EQUAL(map_getNumberE(map), numberE);
    CU_ASSERT_EQUAL(map_getNumberDD(map), numberDD);

    map_setNumberTurn(map, NB_TURN_FISA - 1);

    // Calls the function to test
    map_utils_productionFisa(map);

    // Checking values
    CU_ASSERT_EQUAL(map_getNumberE(map), numberE + (PRODUCTION_FISA_E * numberFisa));
    CU_ASSERT_EQUAL(map_getNumberDD(map), numberDD);


    // Recovery of value before purchase
    numberE = map_getNumberE(map);
    numberDD = map_getNumberDD(map);

    map_setNumberTurn(map, NB_TURN_FISA);
    map_changeProductionFISA(map);

    // Calls the function to test
    map_utils_productionFisa(map);

    // Checking values
    CU_ASSERT_EQUAL(map_getNumberE(map), numberE);
    CU_ASSERT_EQUAL(map_getNumberDD(map), numberDD + (PRODUCTION_FISA_DD * numberFisa));

    // Destroy map
    map_destroy(map);
}

void testEndTurn_moveResource() {
    // Assumption that the creation of a map has been tested beforehand
    // Create map
    Map *map = map_create(DIFFICULTY_EASY);

    // Assumption that the operation of a machine, case and box has been tested beforehand
    // Machine creation
    int numberR = 10;
    int numberG = 10;
    Case *ca1 = map_getCase(0, 0, map);
    Machine *machine1 = machine_create(MS_CONVEYOR_BELT);
    Box *box1 = box_create(numberR,0);
    machine_addBox(machine1, SOUTH, box1);
    case_addMachine(ca1, machine1);

    Case *ca2 = map_getCase(0, 1, map);
    Machine *machine2 = machine_create(MS_CONVEYOR_BELT);
    case_addMachine(ca2, machine2);

    Case *ca3 = map_getCase(1, 0, map);
    Machine *machine3 = machine_create(MS_CONVEYOR_BELT);
    Box *box2 = box_create(0,numberG);
    machine_addBox(machine3, SOUTH, box2);
    case_addMachine(ca3, machine3);

    Case *ca4 = map_getCase(1, 1, map);
    Machine *machine4 = machine_create(MS_JUNKYARD);
    case_addMachine(ca4, machine4);

    // This function uses functions of another implemented type.
    // Each of the functions has been tested in the previous tests.
    // Calls the function to test
    map_utils_moveResources(map);
    // Checking values
    CU_ASSERT_EQUAL(machine_getBox(machine1,SOUTH), NULL);
    CU_ASSERT_EQUAL(machine_getBox(machine3,SOUTH), NULL);
    Box* box1R = machine_getBox(machine2,NORTH);
    CU_ASSERT_EQUAL(box_getNumberResource(box1R), numberR);
    CU_ASSERT_EQUAL(box_getNumberGarbage(box1R), 0);;
    Box* box2R = machine_getBox(machine4,NORTH);
    CU_ASSERT_EQUAL(box_getNumberResource(box2R), 0);
    CU_ASSERT_EQUAL(box_getNumberGarbage(box2R), numberG);

    // Destroy map
    map_destroy(map);
}

void testEndTurn_generateResource() {
    // Assumption that the creation of a map has been tested beforehand
    // Create map
    srand(1); // NOLINT(cert-msc51-cpp)
    Map *map = map_create(DIFFICULTY_EASY);

    Case *source1 = map_getCase(testEndTurn_source1.x, testEndTurn_source1.y, map);
    CU_ASSERT_EQUAL_FATAL(case_getType(source1), CASE_SOURCE);
    Case *source2 = map_getCase(testEndTurn_source2.x, testEndTurn_source2.y, map);
    CU_ASSERT_EQUAL_FATAL(case_getType(source2), CASE_SOURCE);

    // This function uses functions of another implemented type.
    // Each of the functions has been tested in the previous tests.
    // Calls the function to test
    map_utils_generateResources(map);

    Box *boxSource1 = case_getBox(source1);
    CU_ASSERT_EQUAL_FATAL(boxSource1, NULL);

    Box *boxSource2 = case_getBox(source2);
    CU_ASSERT_EQUAL_FATAL(boxSource2, NULL);

    map_setNumberTurn(map, 9);

    // Calls the function to test
    map_utils_generateResources(map);

    // Checking values
    boxSource1 = case_getBox(source1);
    CU_ASSERT_NOT_EQUAL_FATAL(boxSource1, NULL);
    CU_ASSERT_EQUAL(box_getNumberGarbage(boxSource1), 0);
    CU_ASSERT_EQUAL(box_getNumberResource(boxSource1), NB_RESOURCE_PRODUCT_BY_SOURCE);

    boxSource2 = case_getBox(source2);
    CU_ASSERT_NOT_EQUAL_FATAL(boxSource2, NULL);
    CU_ASSERT_EQUAL(box_getNumberGarbage(boxSource2), 0);
    CU_ASSERT_EQUAL(box_getNumberResource(boxSource2), NB_RESOURCE_PRODUCT_BY_SOURCE);

    // Destroy map
    map_destroy(map);
}

void testEndTurn_generateGarbage() {
    // Assumption that the creation of a map has been tested beforehand
    // Create map
    srand(1); // NOLINT(cert-msc51-cpp)
    Map *map = map_create(DIFFICULTY_EASY);

    int numberR = 10;
    // Assumption that the operation of a machine, case and box has been tested beforehand
    // Machine creation
    Case *gate = map_getCase(testEndTurn_gate.x, testEndTurn_gate.y, map);
    Box *box = box_create(numberR, 0);
    case_addBox(gate, box);

    // This function uses functions of another implemented type.
    // Each of the functions has been tested in the previous tests.
    // Calls the function to test
    map_utils_generateGarbage(map);

    // Checking values
    Box *boxGateR = case_getBox(gate);
    CU_ASSERT_NOT_EQUAL_FATAL(boxGateR, NULL);
    CU_ASSERT_EQUAL(box_getNumberGarbage(boxGateR), numberR);
    CU_ASSERT_EQUAL(box_getNumberResource(boxGateR), 0);

    // Destroy map
    map_destroy(map);
}

void testEndTurn_RecyclingCenters() {
    // Assumption that the creation of a map has been tested beforehand
    // Create map
    Map *map = map_create(DIFFICULTY_EASY);

    // Assumption that the operation of a machine, case and box has been tested beforehand
    // Machine creation
    Case *ca = map_getCase(0, 0, map);
    Machine *machine = machine_create(MS_RECYCLING_CENTER);
    Box *box = box_create(0, NUMBER_WASTE_TO_PRODUCT_RESOURCE);
    machine_addBox(machine, SOUTH, box);
    case_addMachine(ca, machine);

    // This function uses functions of another implemented type.
    // Each of the functions has been tested in the previous tests.
    // Calls the function to test
    map_utils_activateRecyclingCenters(map);

    // Checking values
    CU_ASSERT_EQUAL(box_getNumberGarbage(box), 0);
    CU_ASSERT_EQUAL(box_getNumberResource(box), 0);
    Box *boxR = case_getBox(map_getCase(0,1,map));
    CU_ASSERT_NOT_EQUAL_FATAL(boxR, NULL);
    CU_ASSERT_EQUAL(box_getNumberGarbage(boxR), 0);
    CU_ASSERT_EQUAL(box_getNumberResource(boxR), 1);

    // Destroy map
    map_destroy(map);
}

void testEndTurn_Collector() {
    // Assumption that the creation of a map has been tested beforehand
    // Create map
    srand(1); // NOLINT(cert-msc51-cpp)
    Map *map = map_create(DIFFICULTY_EASY);

    int numberR = 3;
    // Assumption that the operation of a machine, case and box has been tested beforehand
    // Machine creation
    Case *ca1 = map_getCase(3, 5, map);
    Box*box = box_create(numberR,0);
    case_addBox(ca1, box);

    Case *ca2 = map_getCase(4, 5, map);
    Machine *machine = machine_create(MS_COLLECTOR);
    case_addMachine(ca2, machine);

    // This function uses functions of another implemented type.
    // Each of the functions has been tested in the previous tests.
    // Calls the function to test
    map_utils_activateCollectors(map);

    // Checking values
    CU_ASSERT_EQUAL(box_getNumberGarbage(box), 0);
    CU_ASSERT_EQUAL(box_getNumberResource(box), numberR-1);
    Box *boxR = case_getBox(map_getCase(4,6,map));
    CU_ASSERT_NOT_EQUAL_FATAL(boxR, NULL);
    CU_ASSERT_EQUAL(box_getNumberGarbage(boxR), 0);
    CU_ASSERT_EQUAL(box_getNumberResource(boxR), 1);

    // Destroy map
    map_destroy(map);
}

void testEndTurn_resetResourceGarbage() {
    // Assumption that the creation of a map has been tested beforehand
    // Create map
    srand(1); // NOLINT(cert-msc51-cpp)
    Map *map = map_create(DIFFICULTY_EASY);

    MachineStuff type = MS_CONVEYOR_BELT;

    int numberR = 10;
    int numberG = 10;

    // Assumption that the operation of a machine, case and box has been tested beforehand
    // Machine creation
    Case *ca1 = map_getCase(0, 0, map);
    Machine *machine = machine_create(type);
    Box *boxM1 = box_create(numberR,numberG);
    machine_addBox(machine, NORTH, boxM1);
    Box *boxM2 = box_create(numberR,numberG);
    machine_addBox(machine, SOUTH, boxM2);
    Box *boxM3 = box_create(numberR,numberG);
    machine_addBox(machine, EAST, boxM3);
    Box *boxM4 = box_create(numberR,numberG);
    machine_addBox(machine, WEST, boxM4);
    case_addMachine(ca1, machine);

    Case *ca2 = map_getCase(0, 1, map);
    Box *boxS = box_create(numberR,numberG);
    case_addBox(ca2, boxS);

    // This function uses functions of another implemented type.
    // Each of the functions has been tested in the previous tests.
    // Calls the function to test
    map_utils_resetResourcesGarbage(map);

    // Checking values
    CU_ASSERT_EQUAL(machine_getBox(machine, NORTH), boxM1);
    CU_ASSERT_EQUAL(machine_getBox(machine, SOUTH), boxM2);
    CU_ASSERT_EQUAL(machine_getBox(machine, EAST), boxM3);
    CU_ASSERT_EQUAL(machine_getBox(machine, WEST), boxM4);
    CU_ASSERT_EQUAL(case_getBox(ca2), NULL);

    Case *gate = map_getCase(testEndTurn_gate.x, testEndTurn_gate.y, map);
    CU_ASSERT_NOT_EQUAL_FATAL(gate, NULL);
    Box *boxGate = case_getBox(gate);
    CU_ASSERT_NOT_EQUAL_FATAL(boxGate, NULL);
    CU_ASSERT_EQUAL(box_getNumberGarbage(boxGate), numberG);
    CU_ASSERT_EQUAL(box_getNumberResource(boxGate), 0);

    // Destroy map
    map_destroy(map);
}