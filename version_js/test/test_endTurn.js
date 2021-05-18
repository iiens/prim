"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
// @ts-ignore
const map_1 = require("../src/model/map");
const machine_1 = require("../src/model/machine");
const mocha_1 = require("mocha");
const difficulty_1 = require("../src/model/difficulty");
const config_1 = require("../src/utils/config");
const utilities_1 = require("../src/utils/utilities");
let assert = require('assert');
mocha_1.describe('End Turn', function () {
    let test_map;
    let test_gate;
    let test_sources;
    function firstCaseEmpty() {
        for (let i = 0; i < test_map.getWidth; i++) {
            for (let j = 0; j < test_map.getHeight; j++) {
                if (test_map.getCase(i, j)?.isEmpty) {
                    return new utilities_1.Vector2D(i, j);
                }
            }
        }
        return null;
    }
    beforeEach('Prepare', function () {
        test_map = new map_1.Map(difficulty_1.Difficulty.getDifficultyByID(difficulty_1.Level.EASY));
        test_sources = new Array();
        for (let ligne = 0; ligne < test_map.getWidth; ligne++) {
            for (let colonne = 0; colonne < test_map.getHeight; colonne++) {
                let currentCase = test_map.getCase(ligne, colonne);
                if (currentCase != null) {
                    if (currentCase.caseType == map_1.CaseType.CASE_SOURCE) {
                        test_sources.push(new utilities_1.Vector2D(ligne, colonne));
                    }
                    else if (currentCase.caseType == map_1.CaseType.CASE_GATE) {
                        test_gate = new utilities_1.Vector2D(ligne, colonne);
                    }
                }
            }
        }
    });
    mocha_1.it('Production Fise', function () {
        // Assumption that the creation of a map has been tested beforehand
        // Create map
        let map = new map_1.Map(difficulty_1.Difficulty.getDifficultyByID(difficulty_1.Level.EASY));
        let numberE = map.getNumberE;
        let numberDD = map.getNumberDD;
        let numberFise = map.getNumberFISE;
        // This function uses functions of another implemented type.
        // Each of the functions has been tested in the previous tests.
        // Calls the function to test
        map.productionFise();
        // Checking values
        assert.equal(map.getNumberE, numberE + (config_1.Config.constants.PRODUCTION_FISE_E * numberFise));
        assert.equal(map.getNumberDD, numberDD + (config_1.Config.constants.PRODUCTION_FISE_DD * numberFise));
    });
    mocha_1.it('Production Fisa', function () {
        // Assumption that the creation of a map has been tested beforehand
        // Create map
        let map = new map_1.Map(difficulty_1.Difficulty.getDifficultyByID(difficulty_1.Level.EASY));
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
        map.addTurn(config_1.Config.constants.NB_TURN_FISA - 1);
        assert.equal(map.getNumberTurn, config_1.Config.constants.NB_TURN_FISA);
        // Calls the function to test
        map.productionFisa();
        // Checking values
        assert.equal(map.getNumberE, numberE + (config_1.Config.constants.PRODUCTION_FISA_E * numberFisa));
        assert.equal(map.getNumberDD, numberDD);
        // Recovery of value before purchase
        numberE = map.getNumberE;
        numberDD = map.getNumberDD;
        map.addTurn(config_1.Config.constants.NB_TURN_FISA);
        map.changeProductionFISA();
        // Calls the function to test
        map.productionFisa();
        // Checking values
        assert.equal(map.getNumberE, numberE);
        assert.equal(map.getNumberDD, numberDD + (config_1.Config.constants.PRODUCTION_FISA_DD * numberFisa));
    });
    mocha_1.it('Move box', function () {
        // Assumption that the operation of a machine, case and box has been tested beforehand
        // Machine creation
        let numberR = 10;
        let beltCase1 = firstCaseEmpty();
        let outCase1;
        let machine1 = new machine_1.Machine(machine_1.MachineStuff.MS_CONVEYOR_BELT);
        let machine2 = new machine_1.Machine(machine_1.MachineStuff.MS_CONVEYOR_BELT);
        let cardinalIn;
        let cardinalOut;
        // @ts-ignore
        if (test_map.getCase(beltCase1.x - 1, beltCase1.y)?.isEmpty) {
            machine1.rotate(1);
            machine2.rotate(1);
            cardinalOut = machine_1.Cardinal.WEST;
            cardinalIn = machine_1.Cardinal.EAST;
            // @ts-ignore
            outCase1 = new utilities_1.Vector2D(beltCase1.x - 1, beltCase1.y);
        }
        else { // @ts-ignore
            if (test_map.getCase(beltCase1.x, beltCase1.y - 1)?.isEmpty) {
                machine1.rotate(2);
                machine2.rotate(2);
                cardinalOut = machine_1.Cardinal.NORTH;
                cardinalIn = machine_1.Cardinal.SOUTH;
                // @ts-ignore
                outCase1 = new utilities_1.Vector2D(beltCase1.x, beltCase1.y - 1);
            }
            else { // @ts-ignore
                if (test_map.getCase(beltCase1.x + 1, beltCase1.y)?.isEmpty) {
                    machine1.rotate(3);
                    machine2.rotate(3);
                    cardinalOut = machine_1.Cardinal.EAST;
                    cardinalIn = machine_1.Cardinal.WEST;
                    // @ts-ignore
                    outCase1 = new utilities_1.Vector2D(beltCase1.x + 1, beltCase1.y);
                }
                else {
                    // @ts-ignore
                    outCase1 = new utilities_1.Vector2D(beltCase1.x, beltCase1.y + 1);
                    cardinalOut = machine_1.Cardinal.SOUTH;
                    cardinalIn = machine_1.Cardinal.NORTH;
                }
            }
        }
        let box1 = new machine_1.Box(numberR, 0);
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
    mocha_1.it('Generate Ressource', function () {
        let source1 = test_map.getCase(test_sources[0].x, test_sources[0].y);
        assert.equal(source1?.caseType, map_1.CaseType.CASE_SOURCE);
        let source2 = test_map.getCase(test_sources[1].x, test_sources[1].y);
        assert.equal(source2?.caseType, map_1.CaseType.CASE_SOURCE);
        // This function uses functions of another implemented type.
        // Each of the functions has been tested in the previous tests.
        // Calls the function to test
        test_map.generateResources();
        let boxSource1 = source1?.getBox();
        assert.equal(boxSource1, null);
        let boxSource2 = source2?.getBox();
        assert.equal(boxSource2, null);
        test_map.addTurn(config_1.Config.constants.NB_TURN_PRODUCTION_SOURCE - 1);
        // Calls the function to test
        test_map.generateResources();
        // Checking values
        boxSource1 = source1?.getBox();
        assert.notEqual(boxSource1, null);
        assert.equal(boxSource1?.numberGarbage, 0);
        assert.equal(boxSource1?.numberResources, config_1.Config.constants.NB_RESOURCE_PRODUCT_BY_SOURCE);
        boxSource2 = source2?.getBox();
        assert.notEqual(boxSource2, null);
        assert.equal(boxSource2?.numberGarbage, 0);
        assert.equal(boxSource2?.numberResources, config_1.Config.constants.NB_RESOURCE_PRODUCT_BY_SOURCE);
    });
    mocha_1.it('Generate Garbage', function () {
        let numberR = 10;
        // Assumption that the operation of a machine, case and box has been tested beforehand
        // Machine creation
        let gate = test_map.getCase(test_gate.x, test_gate.y);
        let box = new machine_1.Box(numberR, 0);
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
    mocha_1.it('Recycling Center', function () {
        // Assumption that the operation of a machine, case and box has been tested beforehand
        // Machine creation
        let cEmpty = firstCaseEmpty();
        // @ts-ignore
        let ca = test_map.getCase(cEmpty?.x, cEmpty?.y);
        let machine = new machine_1.Machine(machine_1.MachineStuff.MS_RECYCLING_CENTER);
        let box = new machine_1.Box(0, config_1.Config.constants.NUMBER_WASTE_TO_PRODUCT_RESOURCE);
        machine.setBox(machine_1.Cardinal.SOUTH, box);
        ca?.setMachine(machine);
        // This function uses functions of another implemented type.
        // Each of the functions has been tested in the previous tests.
        // Calls the function to test
        test_map.activateRecyclingCenters();
        // Checking values
        let boxOut = machine.getBox(machine_1.Cardinal.SOUTH);
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
    mocha_1.it('Activate Collector', function () {
        let numberR = 3;
        // Assumption that the operation of a machine, case and box has been tested beforehand
        // Machine creation
        let ca1 = test_map.getCase(test_sources[0].x, test_sources[0].y);
        let box = new machine_1.Box(numberR, 0);
        ca1?.setBox(box);
        let collectorCase;
        if (test_map.getCase(test_sources[0].x, test_sources[0].y + 1)?.isEmpty) {
            collectorCase = new utilities_1.Vector2D(test_sources[0].x, test_sources[0].y + 1);
        }
        else if (test_map.getCase(test_sources[0].x, test_sources[0].y - 1)?.isEmpty) {
            collectorCase = new utilities_1.Vector2D(test_sources[0].x, test_sources[0].y - 1);
        }
        else if (test_map.getCase(test_sources[0].x + 1, test_sources[0].y)?.isEmpty) {
            collectorCase = new utilities_1.Vector2D(test_sources[0].x + 1, test_sources[0].y);
        }
        else {
            collectorCase = new utilities_1.Vector2D(test_sources[0].x - 1, test_sources[0].y);
        }
        let ca2 = test_map.getCase(collectorCase.x, collectorCase.y);
        let machine = new machine_1.Machine(machine_1.MachineStuff.MS_COLLECTOR);
        ca2?.setMachine(machine);
        let outCase;
        if (test_map.getCase(collectorCase.x - 1, collectorCase.y)?.isEmpty) {
            machine.rotate(1);
            outCase = new utilities_1.Vector2D(collectorCase.x - 1, collectorCase.y);
        }
        else if (test_map.getCase(collectorCase.x, collectorCase.y - 1)?.isEmpty) {
            machine.rotate(2);
            outCase = new utilities_1.Vector2D(collectorCase.x, collectorCase.y - 1);
        }
        else if (test_map.getCase(collectorCase.x + 1, collectorCase.y)?.isEmpty) {
            machine.rotate(3);
            outCase = new utilities_1.Vector2D(collectorCase.x + 1, collectorCase.y);
        }
        else {
            outCase = new utilities_1.Vector2D(collectorCase.x, collectorCase.y + 1);
        }
        // This function uses functions of another implemented type.
        // Each of the functions has been tested in the previous tests.
        // Calls the function to test
        test_map.activateCollectors();
        // Checking values
        assert.equal(box.numberGarbage, 0);
        assert.equal(box.numberResources, numberR - 1);
        let boxR = test_map.getCase(outCase.x, outCase.y)?.getBox();
        assert.notEqual(boxR, null);
        assert.equal(boxR?.numberGarbage, 0);
        assert.equal(boxR?.numberResources, 1);
    });
    mocha_1.it('Reset Ressource Garbage', function () {
        let type = machine_1.MachineStuff.MS_CONVEYOR_BELT;
        let numberR = 10;
        let numberG = 10;
        // Assumption that the operation of a machine, case and box has been tested beforehand
        // Machine creation
        let emptyCase1 = firstCaseEmpty();
        // @ts-ignore
        let ca1 = test_map.getCase(emptyCase1.x, emptyCase1.y);
        let machine = new machine_1.Machine(type);
        ca1?.setMachine(machine);
        let boxM1 = new machine_1.Box(numberR, numberG);
        machine.setBox(machine_1.Cardinal.NORTH, boxM1);
        let boxM2 = new machine_1.Box(numberR, numberG);
        machine.setBox(machine_1.Cardinal.SOUTH, boxM2);
        let boxM3 = new machine_1.Box(numberR, numberG);
        machine.setBox(machine_1.Cardinal.EAST, boxM3);
        let boxM4 = new machine_1.Box(numberR, numberG);
        machine.setBox(machine_1.Cardinal.WEST, boxM4);
        let emptyCase2 = firstCaseEmpty();
        // @ts-ignore
        let ca2 = test_map.getCase(emptyCase2.x, emptyCase2.y);
        let boxS = new machine_1.Box(numberR, numberG);
        ca2?.setBox(boxS);
        // This function uses functions of another implemented type.
        // Each of the functions has been tested in the previous tests.
        // Calls the function to test
        test_map.resetResourcesGarbage();
        // Checking values
        machine = ca1?.getMachine();
        assert.equal(machine?.getBox(machine_1.Cardinal.NORTH), boxM1);
        assert.equal(machine?.getBox(machine_1.Cardinal.SOUTH), boxM2);
        assert.equal(machine?.getBox(machine_1.Cardinal.EAST), boxM3);
        assert.equal(machine?.getBox(machine_1.Cardinal.WEST), boxM4);
        assert.equal(ca2?.getBox(), undefined);
        let gate = test_map.getCase(test_gate.x, test_gate.y);
        assert.notEqual(gate, null);
        let boxGate = gate?.getBox();
        assert.notEqual(boxGate, undefined);
        assert.equal(boxGate?.numberGarbage, numberG);
        assert.equal(boxGate?.numberResources, 0);
    });
});
