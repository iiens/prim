import {Vector2D} from "../src/utils/utilities";
import {CaseType, Map, PRODUCTION_MODE} from "../src/model/map"
import {Difficulty, Level} from "../src/model/difficulty";
import {ErrorCode} from "../src/utils/code";
import {Config} from "../src/utils/config";
import {MachineStuff} from "../src/model/machine";
import {Logger} from "../src/model/logger";

let assert = require('assert');

describe('Map', function() {
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

    before('Prepare', function () {
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

        console.log("test");
    });

    describe('Create map', function () {
        function verificationGateAndSource(numberGate: number, numberSource: number) {
            let searchGate = 0;
            let searchSource = 0;

            // Go through the map in order to count the number of gate and sources
            for (let ligne = 0; ligne < test_map.getWidth; ligne++) {
                for (let colonne = 0; colonne < test_map.getHeight; colonne++) {
                    let currentCase = test_map.getCase(ligne, colonne);
                    if (currentCase != null) {
                        if (currentCase.caseType == CaseType.CASE_SOURCE) {
                            searchSource++;
                        } else if (currentCase.caseType == CaseType.CASE_GATE) {
                            searchGate++;
                        }
                    }
                }
            }
            // Checking values found
            assert.equal(searchGate, numberGate);
            assert.equal(searchSource, numberSource);
        }
        
        it('Création Map Facile', function() {
            // Map creation
            test_map = new Map(Difficulty.getDifficultyByID(Level.EASY));

            // Checking values
            assert.equal(test_map.getWidth, 10);
            assert.equal(test_map.getHeight, 10);
            assert.equal(test_map.getDifficulty.level, Difficulty.getDifficultyByID(Level.EASY).level);
            assert.equal(test_map.getNumberDD, 100);
            assert.equal(test_map.getNumberE, 100);
            assert.equal(test_map.numberPollution, 0);
            assert.equal(test_map.getPlayerScore, 0);
            assert.equal(test_map.getNumberFISE, 5);
            assert.equal(test_map.getNumberFISA, 5);
            assert.equal(test_map.getProductionFISA, PRODUCTION_MODE.E);

            verificationGateAndSource(1, 2);
        });

        it('Création Map Medium', function() {
            // Map creation
            test_map = new Map(Difficulty.getDifficultyByID(Level.MEDIUM));

            // Checking values
            assert.equal(test_map.getWidth, 20);
            assert.equal(test_map.getHeight, 20);
            assert.equal(test_map.getDifficulty.level, Difficulty.getDifficultyByID(Level.MEDIUM).level);
            assert.equal(test_map.getNumberDD, 100);
            assert.equal(test_map.getNumberE, 100);
            assert.equal(test_map.numberPollution, 0);
            assert.equal(test_map.getPlayerScore, 0);
            assert.equal(test_map.getNumberFISE, 5);
            assert.equal(test_map.getNumberFISA, 5);
            assert.equal(test_map.getProductionFISA, PRODUCTION_MODE.E);

            verificationGateAndSource(1, 2);
        });

        it('Création Map difficile', function() {
            // Map creation
            test_map = new Map(Difficulty.getDifficultyByID(Level.HARD));

            // Checking values
            assert.equal(test_map.getWidth, 30);
            assert.equal(test_map.getHeight, 30);
            assert.equal(test_map.getDifficulty.level, Difficulty.getDifficultyByID(Level.HARD).level);
            assert.equal(test_map.getNumberDD, 100);
            assert.equal(test_map.getNumberE, 100);
            assert.equal(test_map.numberPollution, 0);
            assert.equal(test_map.getPlayerScore, 0);
            assert.equal(test_map.getNumberFISE, 5);
            assert.equal(test_map.getNumberFISA, 5);
            assert.equal(test_map.getProductionFISA, PRODUCTION_MODE.E);

            verificationGateAndSource(1, 2);
        });
    });

    describe('Achat Fise', function () {
        it('Assez d\'argent', function () {
            // Recovery of value before purchase
            let numberFise = test_map.getNumberFISE;
            let numberE = test_map.getNumberE;
            let numberDD = test_map.getNumberDD;

            // Calls the function to test
            let error = test_map.map_hireFISE();
            assert.equal(error, ErrorCode.NO_ERROR);

            // Verification that the data has changed
            // An additional Fise
            assert.equal(test_map.getNumberFISE, numberFise + 1);
            // Resources debited
            assert.equal(test_map.getNumberDD, numberDD - Config.constants.COST_FISE_DD);
            assert.equal(test_map.getNumberE, numberE - Config.constants.COST_FISE_E);
        });
    });

    describe('Achat Fisa', function () {
        it('Assez d\'argent', function () {
            // Recovery of value before purchase
            let numberFise = test_map.getNumberFISA;
            let numberE = test_map.getNumberE;
            let numberDD = test_map.getNumberDD;

            // Calls the function to test
            let error = test_map.map_hireFISA();
            assert.equal(error, ErrorCode.NO_ERROR);

            // Verification that the data has changed
            // An additional Fise
            assert.equal(test_map.getNumberFISA, numberFise + 1);
            // Resources debited
            assert.equal(test_map.getNumberDD, numberDD - Config.constants.COST_FISA_DD);
            assert.equal(test_map.getNumberE, numberE - Config.constants.COST_FISA_E);
        });
    });

    describe('Change production Fisa', function () {
        it('Change production Fisa', function () {
            // Recovery of value before purchase
            let productionFisa = test_map.getProductionFISA;

            // Calls the function to test
            let error = test_map.changeProductionFISA();
            assert.equal(error, ErrorCode.NO_ERROR);

            // Verification that the data has changed
            if (productionFisa == PRODUCTION_MODE.E) {
                assert.equal(test_map.getProductionFISA, PRODUCTION_MODE.DD);
            } else {
                assert.equal(test_map.getProductionFISA, PRODUCTION_MODE.E);
            }
        });
    });

    describe('Achat machine ', function () {
        beforeEach('Mise a zero des ressources', function () {
            test_map.addE(-1 * test_map.getNumberE);
            test_map.addDD(-1 * test_map.getNumberDD);
        });

        it('Case mauvaise', function () {
            let e = test_map.addMachine(MachineStuff.MS_RECYCLING_CENTER, 0, -1, 0);

            // Checking values
            assert.equal(e, ErrorCode.ERROR_CASE_NOT_FOUND);
        });

        it('Pas assez de DD', function () {
            let typeM = MachineStuff.MS_RECYCLING_CENTER;
            let machineInfo = Config.getMachineStuff(typeM);
            let costE = machineInfo?.costE;
            assert.notEqual(costE, null);

            if (costE != null) {
                test_map.addE(costE);

                let c = firstCaseEmpty();
                assert.notEqual(c, null);

                if (c != null) {
                    let e = test_map.addMachine(typeM, 0, c.x, c.y);

                    // Checking values
                    assert.equal(e, ErrorCode.ERROR_NOT_ENOUGH_DD);
                }
            }
        });

        it('Pas assez de E', function () {
            let typeM = MachineStuff?.MS_COLLECTOR;
            let machineInfo = Config.getMachineStuff(typeM);
            let costDD = machineInfo?.costDD;
            assert.notEqual(costDD, null);

            if (costDD != null) {
                test_map.addDD(costDD);

                let c = firstCaseEmpty();
                assert.notEqual(c, null);

                if (c != null) {
                    let e = test_map.addMachine(typeM, 0, c.x, c.y);

                    // Checking values
                    assert.equal(e, ErrorCode.ERROR_NOT_ENOUGH_E);
                }
            }
        });

        it('Assez de ressource', function () {
            let typeM = MachineStuff.MS_COLLECTOR;
            let machineInfo = Config.getMachineStuff(typeM);
            let costE = machineInfo?.costE;
            assert.notEqual(costE, null);
            let costDD = machineInfo?.costDD;
            assert.notEqual(costDD, null);

            if (costE != null && costDD != null) {
                test_map.addE(costE);
                test_map.addDD(costDD);

                let c = firstCaseEmpty();
                assert.notEqual(c, null);

                if (c != null) {
                    let e = test_map.addMachine(typeM, 0, c.x, c.y);

                    // Checking values
                    assert.equal(e, ErrorCode.NO_ERROR);
                }
            }
        });
    });

    describe('Upgrade machine', function () {
        let case_machine: Vector2D | null;

        before('Placement d\'une machine', function () {
            let typeM = MachineStuff.MS_COLLECTOR;
            let machineInfo = Config.getMachineStuff(typeM);
            let costE = machineInfo?.costE;
            let costDD = machineInfo?.costDD;

            if (costE != null && costDD != null) {
                test_map.addE(costE);
                test_map.addDD(costDD);

                case_machine = firstCaseEmpty();

                if (case_machine != null) {
                    test_map.addMachine(typeM, 0, case_machine.x, case_machine.y);
                }
            }
        });

        beforeEach('Mise a zero des ressources', function () {
            test_map.addE(-1 * test_map.getNumberE);
            test_map.addDD(-1 * test_map.getNumberDD);
        });

        it('Case mauvaise', function () {
            let e = test_map.upgradeMachine(0, -1);

            // Checking values
            assert.equal(e, ErrorCode.ERROR_CASE_NOT_FOUND);
        });

        it('Case sans machine', function () {
            let c = firstCaseEmpty();
            assert.notEqual(c, null);

            if (c != null) {
                let e = test_map.upgradeMachine(c.x, c.y);

                // Checking values
                assert.equal(e, ErrorCode.ERROR_CASE_EMPTY);
            }
        });

        it('Pas assez de DD', function () {
            let typeM = MachineStuff.MS_RECYCLING_CENTER;
            let machineInfo = Config.getMachineStuff(typeM);
            let costE = machineInfo?.costUpgradeE;
            assert.notEqual(costE, null);

            if (costE != null) {
                test_map.addE(costE);
                Logger.Instance.error('sous en E=' + test_map.getNumberE + " DD="+ test_map.getNumberDD)

                if (case_machine != null) {
                    let e = test_map.upgradeMachine(case_machine.x, case_machine.y);
                    // Checking values
                    assert.equal(e, ErrorCode.ERROR_NOT_ENOUGH_DD);
                }
            }
        });

        it('Pas assez de E', function () {
            let typeM = MachineStuff.MS_COLLECTOR;
            let machineInfo = Config.getMachineStuff(typeM);
            let costDD = machineInfo?.costUpgradeDD;
            assert.notEqual(costDD, null);

            if (costDD != null) {
                test_map.addDD(costDD);

                if (case_machine != null) {
                    let e = test_map.upgradeMachine(case_machine.x, case_machine.y);

                    // Checking values
                    assert.equal(e, ErrorCode.ERROR_NOT_ENOUGH_E);
                }
            }
        });

        it('Assez de ressource', function () {
            let typeM = MachineStuff.MS_COLLECTOR;
            let machineInfo = Config.getMachineStuff(typeM);
            let costE = machineInfo?.costUpgradeE;
            assert.notEqual(costE, null);
            let costDD = machineInfo?.costUpgradeDD;
            assert.notEqual(costDD, null);

            if (costE != null && costDD != null) {
                test_map.addE(costE);
                test_map.addDD(costDD);

                if (case_machine != null) {
                    let e = test_map.upgradeMachine(case_machine.x, case_machine.y);

                    // Checking values
                    assert.equal(e, ErrorCode.NO_ERROR);
                }
            }
        });
    });

    describe('Destroy machine', function () {
        let case_machine: Vector2D | null;

        before('Placement d\'une machine', function () {
            let typeM = MachineStuff.MS_COLLECTOR;
            let machineInfo = Config.getMachineStuff(typeM);
            let costE = machineInfo?.costE;
            let costDD = machineInfo?.costDD;

            if (costE != null && costDD != null) {
                test_map.addE(costE);
                test_map.addDD(costDD);

                case_machine = firstCaseEmpty();

                if (case_machine != null) {
                    test_map.addMachine(typeM, 0, case_machine.x, case_machine.y);
                }
            }
        });

        beforeEach('Mise a zero des ressources', function () {
            test_map.addE(-1 * test_map.getNumberE);
            test_map.addDD(-1 * test_map.getNumberDD);
        });

        it('Case mauvaise', function () {
            let e = test_map.destroyMachine(0, -1);

            // Checking values
            assert.equal(e, ErrorCode.ERROR_CASE_NOT_FOUND);
        });

        it('Case sans machine', function () {
            let c = firstCaseEmpty();
            assert.notEqual(c, null);

            if (c != null) {
                let e = test_map.destroyMachine(c.x, c.y);

                // Checking values
                assert.equal(e, ErrorCode.ERROR_CASE_EMPTY);
            }
        });

        it('Pas assez de DD', function () {
            let typeM = MachineStuff.MS_RECYCLING_CENTER;
            let machineInfo = Config.getMachineStuff(typeM);
            let costE = machineInfo?.costDestroyE;
            assert.notEqual(costE, null);

            if (costE != null) {
                test_map.addE(costE);

                if (case_machine != null) {
                    let e = test_map.destroyMachine(case_machine.x, case_machine.y);

                    // Checking values
                    assert.equal(e, ErrorCode.ERROR_NOT_ENOUGH_DD);
                }
            }
        });

        it('Pas assez de E', function () {
            let typeM = MachineStuff.MS_COLLECTOR;
            let machineInfo = Config.getMachineStuff(typeM);
            let costDD = machineInfo?.costDestroyDD;
            assert.notEqual(costDD, null);

            if (costDD != null) {
                test_map.addDD(costDD);

                if (case_machine != null) {
                    let e = test_map.destroyMachine(case_machine.x, case_machine.y);

                    // Checking values
                    assert.equal(e, ErrorCode.ERROR_NOT_ENOUGH_E);
                }
            }
        });

        it('Assez de ressource', function () {
            let typeM = MachineStuff.MS_COLLECTOR;
            let machineInfo = Config.getMachineStuff(typeM);
            let costE = machineInfo?.costDestroyE;
            assert.notEqual(costE, null);
            let costDD = machineInfo?.costDestroyDD;
            assert.notEqual(costDD, null);

            if (costE != null && costDD != null) {
                test_map.addE(costE);
                test_map.addDD(costDD);

                if (case_machine != null) {
                    let e = test_map.destroyMachine(case_machine.x, case_machine.y);

                    // Checking values
                    assert.equal(e, ErrorCode.NO_ERROR);
                }
            }
        });
    });
});
