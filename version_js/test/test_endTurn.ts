// @ts-ignore
import {CaseType, Map, PRODUCTION_MODE} from "../src/model/map"
import {Box, Cardinal, Machine, MachineStuff} from "../src/model/machine";
import {describe, it} from "mocha";
import {Difficulty, Level} from "../src/model/difficulty";
import {Config} from "../src/utils/config";
import {Vector2D} from "../src/utils/utilities";

let assert = require('assert');

describe('End Turn', function() {
    let test_map: Map;
    let test_gate : Vector2D;
    let test_sources : Array<Vector2D>;

    function firstCaseEmpty() {
        for (let i = 0; i < test_map.getWidth; i++) {
            for (let j = 0; j < test_map.getHeight; j++) {
                if (test_map.getCase(i,j)?.isEmpty) {
                    return new Vector2D(i,j);
                }
            }
        }

        return null;
    }

    beforeEach('Prepare', function () {
        test_map = new Map(Difficulty.getDifficultyByID(Level.EASY));

        test_sources = new Array<Vector2D>();
        for (let ligne = 0; ligne < test_map.getWidth; ligne++) {
            for (let colonne = 0; colonne < test_map.getHeight; colonne++) {
                let currentCase = test_map.getCase(ligne, colonne);
                if (currentCase != null) {
                    if (currentCase.caseType == CaseType.CASE_SOURCE) {
                        test_sources.push(new Vector2D(ligne, colonne));
                    } else if (currentCase.caseType == CaseType.CASE_GATE) {
                        test_gate = new Vector2D(ligne, colonne);
                    }
                }
            }
        }
    });

    it('Production Fise', function () {
        // Assumption that the creation of a map has been tested beforehand
        // Create map
        let map = new Map(Difficulty.getDifficultyByID(Level.EASY));

        let numberE = map.getNumberE;
        let numberDD = map.getNumberDD;
        let numberFise = map.getNumberFISE;

        // This function uses functions of another implemented type.
        // Each of the functions has been tested in the previous tests.
        // Calls the function to test
        map.productionFise();

        // Checking values
        assert.equal(map.getNumberE, numberE + (Config.constants.PRODUCTION_FISE_E * numberFise));
        assert.equal(map.getNumberDD, numberDD + (Config.constants.PRODUCTION_FISE_DD * numberFise));
    });

    it('Production Fisa', function () {
        // Assumption that the creation of a map has been tested beforehand
        // Create map
        let map = new Map(Difficulty.getDifficultyByID(Level.EASY));

        let numberE = map.getNumberE;
        let numberDD = map.getNumberDD;
        let numberFisa = map.getNumberFISA;

        // This function uses functions of another implemented type.
        // Each of the functions has been tested in the previous tests.
        // Calls the function to test
        map.productionFisa();

        // Checking values
        assert.equal(map.getNumberE, numberE);
        assert.equal(map.getNumberDD, numberDD);

        map.addTurn(Config.constants.NB_TURN_FISA - 1);
        assert.equal(map.getNumberTurn, Config.constants.NB_TURN_FISA);

        // Calls the function to test
        map.productionFisa();

        // Checking values
        assert.equal(map.getNumberE, numberE + (Config.constants.PRODUCTION_FISA_E * numberFisa));
        assert.equal(map.getNumberDD, numberDD);

        // Recovery of value before purchase
        numberE = map.getNumberE;
        numberDD = map.getNumberDD;

        map.addTurn(Config.constants.NB_TURN_FISA);
        map.changeProductionFISA();

        // Calls the function to test
        map.productionFisa();

        // Checking values
        assert.equal(map.getNumberE, numberE);
        assert.equal(map.getNumberDD, numberDD + (Config.constants.PRODUCTION_FISA_DD * numberFisa));
    });

    it('Move box', function () {
        // Assumption that the operation of a machine, case and box has been tested beforehand
        // Machine creation
        let numberR = 10;

        let beltCase1 = firstCaseEmpty();
        let outCase1 : Vector2D;

        let machine1 = new Machine(MachineStuff.MS_CONVEYOR_BELT);
        let machine2 = new Machine(MachineStuff.MS_CONVEYOR_BELT);

        let cardinalIn : Cardinal;
        let cardinalOut : Cardinal;
        // @ts-ignore
        if (test_map.getCase(beltCase1.x - 1, beltCase1.y)?.isEmpty) {
            machine1.rotate(1);
            machine2.rotate(1);
            cardinalOut = Cardinal.WEST;
            cardinalIn = Cardinal.EAST;
            // @ts-ignore
            outCase1 = new Vector2D(beltCase1.x - 1, beltCase1.y);
        } else { // @ts-ignore
            if (test_map.getCase(beltCase1.x, beltCase1.y - 1)?.isEmpty) {
                machine1.rotate(2);
                machine2.rotate(2);
                cardinalOut = Cardinal.NORTH;
                cardinalIn = Cardinal.SOUTH;
                // @ts-ignore
                outCase1 = new Vector2D(beltCase1.x, beltCase1.y - 1);
            } else { // @ts-ignore
                if (test_map.getCase(beltCase1.x + 1, beltCase1.y)?.isEmpty) {
                    machine1.rotate(3);
                    machine2.rotate(3);
                    cardinalOut = Cardinal.EAST;
                    cardinalIn = Cardinal.WEST;
                    // @ts-ignore
                    outCase1 = new Vector2D(beltCase1.x + 1, beltCase1.y);
                } else {
                    // @ts-ignore
                    outCase1 = new Vector2D(beltCase1.x, beltCase1.y + 1);
                    cardinalOut = Cardinal.SOUTH;
                    cardinalIn = Cardinal.NORTH;
                }
            }
        }

        let box1 = new Box(numberR,0);
        machine1.setBox(cardinalOut, box1);

        // @ts-ignore
        let ca1 = test_map.getCase(beltCase1.x, beltCase1.y);
        ca1?.setMachine(machine1);

        let ca2 = test_map.getCase(outCase1.x, outCase1.y);
        ca2?.setMachine(machine2);

        // This function uses functions of another implemented type.
        // Each of the functions has been tested in the previous tests.
        // Calls the function to test
        test_map.moveResources();

        // Checking values
        assert.equal(machine1.getBox(cardinalOut), null);
        let box1R = machine2.getBox(cardinalIn);
        assert.notEqual(box1R, null);
        assert.equal(box1R?.numberResources, numberR);
        assert.equal(box1R?.numberGarbage, 0);
    });

    it('Generate Ressource', function () {
        let source1 = test_map.getCase(test_sources[0].x, test_sources[0].y);
        assert.equal(source1?.caseType, CaseType.CASE_SOURCE);
        let source2 = test_map.getCase(test_sources[1].x, test_sources[1].y);
        assert.equal(source2?.caseType, CaseType.CASE_SOURCE);

        // This function uses functions of another implemented type.
        // Each of the functions has been tested in the previous tests.
        // Calls the function to test
        test_map.generateResources();

        let boxSource1 = source1?.getBox();
        assert.equal(boxSource1, null);


        let boxSource2 = source2?.getBox();
        assert.equal(boxSource2, null);

        test_map.addTurn(Config.constants.NB_TURN_PRODUCTION_SOURCE-1);

        // Calls the function to test
        test_map.generateResources();

        // Checking values
        boxSource1 = source1?.getBox();
        assert.notEqual(boxSource1, null);
        assert.equal(boxSource1?.numberGarbage, 0);
        assert.equal(boxSource1?.numberResources, Config.constants.NB_RESOURCE_PRODUCT_BY_SOURCE);

        boxSource2 = source2?.getBox();
        assert.notEqual(boxSource2, null);
        assert.equal(boxSource2?.numberGarbage, 0);
        assert.equal(boxSource2?.numberResources, Config.constants.NB_RESOURCE_PRODUCT_BY_SOURCE);
    });

    it('Generate Garbage', function () {
        let numberR = 10;
        // Assumption that the operation of a machine, case and box has been tested beforehand
        // Machine creation
        let gate = test_map.getCase(test_gate.x, test_gate.y);
        let box = new Box(numberR, 0);
        gate?.setBox(box);

        // This function uses functions of another implemented type.
        // Each of the functions has been tested in the previous tests.
        // Calls the function to test
        test_map.generateGarbage();

        // Checking values
        let boxGateR = gate?.getBox();
        assert.notEqual(boxGateR, null);
        assert.equal(boxGateR?.numberGarbage, numberR);
        assert.equal(boxGateR?.numberResources, 0);
    });

    it('Recycling Center', function () {
        // Assumption that the operation of a machine, case and box has been tested beforehand
        // Machine creation
        let cEmpty = firstCaseEmpty();
        // @ts-ignore
        let ca = test_map.getCase(cEmpty?.x, cEmpty?.y);
        let machine = new Machine(MachineStuff.MS_RECYCLING_CENTER);
        let box = new Box(0, Config.constants.NUMBER_WASTE_TO_PRODUCT_RESOURCE);
        machine.setBox(Cardinal.SOUTH, box);
        ca?.setMachine(machine);

        // This function uses functions of another implemented type.
        // Each of the functions has been tested in the previous tests.
        // Calls the function to test
        test_map.activateRecyclingCenters();

        // Checking values
        let boxOut = machine.getBox(Cardinal.SOUTH);
        // @ts-ignore
        assert.equal(boxOut.numberGarbage, 0);
        // @ts-ignore
        assert.equal(boxOut.numberResources, 0);
        // @ts-ignore
        let out = test_map.getCase(cEmpty?.x, cEmpty?.y + 1);
        let boxR = out?.getBox();
        assert.notEqual(boxR, undefined);
        // @ts-ignore
        assert.equal(boxR.numberGarbage, 0);
        // @ts-ignore
        assert.equal(boxR.numberResources, 1);
    });

    it('Activate Collector', function () {
        let numberR = 3;
        // Assumption that the operation of a machine, case and box has been tested beforehand
        // Machine creation
        let ca1 = test_map.getCase(test_sources[0].x, test_sources[0].y);
        let box = new Box(numberR,0);
        ca1?.setBox(box);

        let collectorCase : Vector2D;
        if (test_map.getCase(test_sources[0].x, test_sources[0].y + 1)?.isEmpty) {
            collectorCase = new Vector2D(test_sources[0].x, test_sources[0].y + 1);
        } else if (test_map.getCase(test_sources[0].x, test_sources[0].y - 1)?.isEmpty) {
            collectorCase = new Vector2D(test_sources[0].x, test_sources[0].y - 1);
        } else if (test_map.getCase(test_sources[0].x + 1, test_sources[0].y)?.isEmpty) {
            collectorCase = new Vector2D(test_sources[0].x + 1, test_sources[0].y);
        } else {
            collectorCase = new Vector2D(test_sources[0].x - 1, test_sources[0].y);
        }

        let ca2 = test_map.getCase(collectorCase.x, collectorCase.y);
        let machine = new Machine(MachineStuff.MS_COLLECTOR);
        ca2?.setMachine(machine);

        let outCase : Vector2D;
        if (test_map.getCase(collectorCase.x - 1, collectorCase.y)?.isEmpty) {
            machine.rotate(1);
            outCase = new Vector2D(collectorCase.x - 1, collectorCase.y);
        } else if (test_map.getCase(collectorCase.x, collectorCase.y - 1)?.isEmpty) {
            machine.rotate(2);
            outCase = new Vector2D(collectorCase.x, collectorCase.y - 1);
        } else if (test_map.getCase(collectorCase.x + 1, collectorCase.y)?.isEmpty) {
            machine.rotate(3);
            outCase = new Vector2D(collectorCase.x + 1, collectorCase.y);
        } else {
            outCase = new Vector2D(collectorCase.x, collectorCase.y + 1);
        }

        // This function uses functions of another implemented type.
        // Each of the functions has been tested in the previous tests.
        // Calls the function to test
        test_map.activateCollectors();

        // Checking values
        assert.equal(box.numberGarbage, 0);
        assert.equal(box.numberResources, numberR-1);
        let boxR = test_map.getCase(outCase.x, outCase.y)?.getBox();
        assert.notEqual(boxR, null);
        assert.equal(boxR?.numberGarbage, 0);
        assert.equal(boxR?.numberResources, 1);
    });

    it('Reset Ressource Garbage', function () {
        let type = MachineStuff.MS_CONVEYOR_BELT;

        let numberR = 10;
        let numberG = 10;

        // Assumption that the operation of a machine, case and box has been tested beforehand
        // Machine creation
        let emptyCase1 = firstCaseEmpty();
        // @ts-ignore
        let ca1 = test_map.getCase(emptyCase1.x, emptyCase1.y);
        let machine: Machine | undefined = new Machine(type);
        ca1?.setMachine(machine);
        let boxM1 = new Box(numberR,numberG);
        machine.setBox(Cardinal.NORTH, boxM1);
        let boxM2 = new Box(numberR,numberG);
        machine.setBox(Cardinal.SOUTH, boxM2);
        let boxM3 = new Box(numberR,numberG);
        machine.setBox(Cardinal.EAST, boxM3);
        let boxM4 = new Box(numberR,numberG);
        machine.setBox(Cardinal.WEST, boxM4);

        let emptyCase2 = firstCaseEmpty();
        // @ts-ignore
        let ca2 = test_map.getCase(emptyCase2.x, emptyCase2.y);
        let boxS = new Box(numberR,numberG);
        ca2?.setBox(boxS);

        // This function uses functions of another implemented type.
        // Each of the functions has been tested in the previous tests.
        // Calls the function to test
        test_map.resetResourcesGarbage();

        // Checking values
        machine = ca1?.getMachine();
        assert.equal(machine?.getBox(Cardinal.NORTH), boxM1);
        assert.equal(machine?.getBox(Cardinal.SOUTH), boxM2);
        assert.equal(machine?.getBox(Cardinal.EAST), boxM3);
        assert.equal(machine?.getBox(Cardinal.WEST), boxM4);
        assert.equal(ca2?.getBox(), undefined);

        let gate = test_map.getCase(test_gate.x, test_gate.y);
        assert.notEqual(gate, null);
        let boxGate = gate?.getBox();
        assert.notEqual(boxGate, undefined);
        assert.equal(boxGate?.numberGarbage, numberG);
        assert.equal(boxGate?.numberResources, 0);
    });
});