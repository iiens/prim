// @ts-ignore
import {Cardinal, Direction, Machine, MachineStuff} from "../src/model/machine";

let assert = require('assert');

describe('Machine', function() {
    describe('Create machine', function() {
        it('Création Collector', function() {
            // Machine creation
            let typeM = MachineStuff.MS_COLLECTOR;
            let machine = new Machine(typeM);

            // Checking values
            assert.equal(machine.level, 1);
            assert.equal(machine.type, typeM);
            // Check that the exit is to the South
            assert.equal(machine.getDirection(Cardinal.SOUTH), Direction.OUT);
        });
        it('Création Conveyor belt', function() {
            // Machine creation
            let typeM = MachineStuff.MS_CROSS_BELT;
            let machine = new Machine(typeM);

            // Checking values
            assert.equal(machine.level, 1);
            assert.equal(machine.type, typeM);
            // Check that the exit is to the South
            assert.equal(machine.getDirection(Cardinal.SOUTH), Direction.OUT);
        });
        it('Création Cross Belt', function() {
            // Machine creation
            let typeM = MachineStuff.MS_CROSS_BELT;
            let machine = new Machine(typeM);

            // Checking values
            assert.equal(machine.level, 1);
            assert.equal(machine.type, typeM);
            // Check that the exit is to the South
            assert.equal(machine.getDirection(Cardinal.SOUTH), Direction.OUT);
            assert.equal(machine.getDirection(Cardinal.WEST), Direction.OUT);
        });
        it('Création Recycling Center', function() {
            // Machine creation
            let typeM = MachineStuff.MS_RECYCLING_CENTER;
            let machine = new Machine(typeM);

            // Checking values
            assert.equal(machine.level, 1);
            assert.equal(machine.type, typeM);
            // Check that the exit is to the South
            assert.equal(machine.getDirection(Cardinal.SOUTH), Direction.OUT);
        });
        it('Création Junkyard', function() {
            // Machine creation
            let typeM = MachineStuff.MS_JUNKYARD;
            let machine = new Machine(typeM);

            // Checking values
            assert.equal(machine.level, 1);
            assert.equal(machine.type, typeM);
            // Check that the exit is to the South
            assert.equal(machine.getDirection(Cardinal.SOUTH), Direction.IN);
            assert.equal(machine.getDirection(Cardinal.WEST), Direction.IN);
            assert.equal(machine.getDirection(Cardinal.NORTH), Direction.IN);
            assert.equal(machine.getDirection(Cardinal.EAST), Direction.IN);
        });
    });

    describe('')
});