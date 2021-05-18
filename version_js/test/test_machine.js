"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
// @ts-ignore
const machine_1 = require("../src/model/machine");
let assert = require('assert');
describe('Machine', function () {
    describe('Create machine', function () {
        it('Création Collector', function () {
            // Machine creation
            let typeM = machine_1.MachineStuff.MS_COLLECTOR;
            let machine = new machine_1.Machine(typeM);
            // Checking values
            assert.equal(machine.level, 1);
            assert.equal(machine.type, typeM);
            // Check that the exit is to the South
            assert.equal(machine.getDirection(machine_1.Cardinal.SOUTH), machine_1.Direction.OUT);
        });
        it('Création Conveyor belt', function () {
            // Machine creation
            let typeM = machine_1.MachineStuff.MS_CROSS_BELT;
            let machine = new machine_1.Machine(typeM);
            // Checking values
            assert.equal(machine.level, 1);
            assert.equal(machine.type, typeM);
            // Check that the exit is to the South
            assert.equal(machine.getDirection(machine_1.Cardinal.SOUTH), machine_1.Direction.OUT);
        });
        it('Création Cross Belt', function () {
            // Machine creation
            let typeM = machine_1.MachineStuff.MS_CROSS_BELT;
            let machine = new machine_1.Machine(typeM);
            // Checking values
            assert.equal(machine.level, 1);
            assert.equal(machine.type, typeM);
            // Check that the exit is to the South
            assert.equal(machine.getDirection(machine_1.Cardinal.SOUTH), machine_1.Direction.OUT);
            assert.equal(machine.getDirection(machine_1.Cardinal.WEST), machine_1.Direction.OUT);
        });
        it('Création Recycling Center', function () {
            // Machine creation
            let typeM = machine_1.MachineStuff.MS_RECYCLING_CENTER;
            let machine = new machine_1.Machine(typeM);
            // Checking values
            assert.equal(machine.level, 1);
            assert.equal(machine.type, typeM);
            // Check that the exit is to the South
            assert.equal(machine.getDirection(machine_1.Cardinal.SOUTH), machine_1.Direction.OUT);
        });
        it('Création Junkyard', function () {
            // Machine creation
            let typeM = machine_1.MachineStuff.MS_JUNKYARD;
            let machine = new machine_1.Machine(typeM);
            // Checking values
            assert.equal(machine.level, 1);
            assert.equal(machine.type, typeM);
            // Check that the exit is to the South
            assert.equal(machine.getDirection(machine_1.Cardinal.SOUTH), machine_1.Direction.IN);
            assert.equal(machine.getDirection(machine_1.Cardinal.WEST), machine_1.Direction.IN);
            assert.equal(machine.getDirection(machine_1.Cardinal.NORTH), machine_1.Direction.IN);
            assert.equal(machine.getDirection(machine_1.Cardinal.EAST), machine_1.Direction.IN);
        });
    });
    it('Machine Rotation', function () {
        // Assumption that the creation of a machine has been tested beforehand
        // Case creation
        let typeM = machine_1.MachineStuff.MS_COLLECTOR;
        let machine = new machine_1.Machine(typeM);
        // Checking values
        assert.equal(machine.getDirection(machine_1.Cardinal.SOUTH), machine_1.Direction.OUT);
        // Calls the function to test
        machine.rotate(1);
        // Checking values
        assert.equal(machine.getDirection(machine_1.Cardinal.WEST), machine_1.Direction.OUT);
        // Calls the function to test
        machine.rotate(1);
        // Checking values
        assert.equal(machine.getDirection(machine_1.Cardinal.NORTH), machine_1.Direction.OUT);
        // Calls the function to test
        machine.rotate(1);
        // Checking values
        assert.equal(machine.getDirection(machine_1.Cardinal.EAST), machine_1.Direction.OUT);
        // Calls the function to test
        machine.rotate(2);
        // Checking values
        assert.equal(machine.getDirection(machine_1.Cardinal.WEST), machine_1.Direction.OUT);
        // Calls the function to test
        machine.rotate(4);
        // Checking values
        assert.equal(machine.getDirection(machine_1.Cardinal.WEST), machine_1.Direction.OUT);
    });
    it('Machine Level Up', function () {
        // Assumption that the creation of a machine has been tested beforehand
        // Create machine
        let machine = new machine_1.Machine(machine_1.MachineStuff.MS_COLLECTOR);
        // Recovery of value before purchase
        let level = machine.level;
        // Calls the function to test
        machine.increaseLevel();
        // Checking values
        assert.equal(machine.level, level + 1);
    });
    it('Machine Add Delete', function () {
        // Assumption that the creation of a machine has been tested beforehand
        // Machine creation
        let typeM = machine_1.MachineStuff.MS_COLLECTOR;
        let machine = new machine_1.Machine(typeM);
        // Assumption that the operation of a box has been tested beforehand
        // Box creation
        let numberR = 10;
        let numberG = 10;
        let box = new machine_1.Box(numberR, numberG);
        // Calls the function to test
        machine.setBox(machine_1.Cardinal.NORTH, box);
        // Checking values
        let tmp = machine.getBox(machine_1.Cardinal.NORTH);
        assert.equal(tmp, box);
        // Calls the function to test
        machine.destroyBox(machine_1.Cardinal.NORTH);
        // Checking values
        tmp = machine.getBox(machine_1.Cardinal.NORTH);
        assert.equal(tmp, null);
    });
});
