"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.CaseType = exports.Case = exports.PRODUCTION_MODE = exports.Map = void 0;
const difficulty_1 = require("./difficulty");
const config_1 = require("../utils/config");
const staffs_1 = require("./staffs");
const code_1 = require("../utils/code");
const events_1 = require("../utils/events");
const machine_1 = require("./machine");
const utilities_1 = require("../utils/utilities");
const logger_1 = require("./logger");
/**
 * \file map
 * \author Antoine MAN, Ramzy ZEBRIR and Valentin DREANO
 * \version 1.0
 * \date 28/03/2021
 * \see Difficulty
 * \see CaseType
 * \see ErrorCode
 *
 * This class contains any functions related to the interactions
 * between the player and the elements on the board game.
 * <ul>
 * <li>create a new map</li>
 * <li>destroy a map</li>
 * <li>hire a FISE</li>
 * <li>hire a FISA</li>
 * <li>switch energy type produced by the FISA </li>
 * <li>finish a turn</li>
 * <li>add a machine in a case</li>
 * <li>upgrade a machine, already created in a case</li>
 * <li>detroy a machine, already created in a case</li>
 * <li>buy staffs in order to have bonus</li>
 * </ul>
 *
 */
class Map {
    /**
     * @brief Create a new map
     *
     * In order to begin a new game, we need a board game.
     * It will contains all the map information concerning machines
     * emplacement, sources, resources, garbage, Staff and gate, presents on the map.
     *
     * Difficulty has been chosen by the player which determine the width and height of the map
     * Creation of the map : a bi dimensional Case table
     * 2 sources cases and 1 transdimensional gate are randomly placed into those cases.
     * The player starts the game with 5 FISE, 5 FISA, 100 E and 100 DD.
     * Initialization of the turn, the score the pollution to 0.
     * By default, the FISA production is E.
     * A table which contain staffs that the user bought is also initialized
     *
     * @param difficulty a valid difficulty chosen by the user
     * @param empty if should create an empty map, for deserialization purposes
     * @return a new map that contains all the map information
     * @see Map type
     * @see Difficulty enum
     */
    constructor(difficulty, empty = false) {
        let logger = logger_1.Logger.Instance;
        logger.info("Creation of a new map with difficulty " + difficulty.level);
        if (empty) { // we load the map from a save, only init basic values then return
            this.width = difficulty.getMapSizeByDifficulty();
            this.height = difficulty.getMapSizeByDifficulty();
            this.difficulty = difficulty;
            logger.warn("Calling Map constructor with illegal arguments!");
            return;
        }
        // Initialisation map
        let source_x;
        let source_y;
        let gate_x;
        let gate_y;
        // Initializing the basic values of the game
        logger.debug("Initializing the basic values of the game !");
        this.turn = 1;
        this.productionFISA = PRODUCTION_MODE.E;
        this.E = config_1.Config.constants.NUMBER_E_START;
        this.DD = config_1.Config.constants.NUMBER_DD_START;
        this.score = 0;
        this.numberFISA = config_1.Config.constants.NUMBER_FISE;
        this.numberFISE = config_1.Config.constants.NUMBER_FISA;
        this.team = staffs_1.StaffUtils.createStaffDictionary();
        // Initialization of the map according to the difficulty
        logger.debug("Initialization of the map according to the difficulty !");
        this.width = difficulty.getMapSizeByDifficulty();
        this.height = difficulty.getMapSizeByDifficulty();
        this.difficulty = difficulty;
        // Create grid
        logger.debug("Grid Creation with width = " + this.width + " and height = " + this.height);
        this.map = new Array();
        for (let i = 0; i < this.width; i++) {
            // Creation of each Case
            this.map[i] = new Array();
            // Initialization of boxes
            for (let j = 0; j < this.height; j++) {
                this.map[i][j] = new Case(i, j);
            }
        }
        gate_x = Map.getRandomInt(0, this.width - 1);
        gate_y = Map.getRandomInt(0, this.height - 1);
        this.map[gate_x][gate_y].setGate();
        logger.debug("Gate coordinates x = " + gate_x + " y = " + gate_y);
        // Random placement of the n sources
        for (let i = 0; i < config_1.Config.constants.NUMBER_OF_SOURCES; i++) {
            do {
                source_x = Map.getRandomInt(0, this.width - 1);
                source_y = Map.getRandomInt(0, this.height - 1);
                logger.debug("Resources coordinates x = " + source_x + " y = " + source_y);
                // try set as source
            } while (!this.map[source_x][source_y].setSource());
        }
    }
    /**
    * \fn int map_getNumberFISE( const Map* m )
    * @brief a function to get the number of FISE
    *
    * This function get the number of FISE recruited by the player.
    *
    * @return the number of FISE available
    */
    get getNumberFISE() { return this.numberFISE; }
    ;
    /**
    * \fn int map_getNumberFISA( const Map* m )
    * @brief a function to get the number of FISA
    *
    * This function get the number of FISA recruited by the player.
    *
    * @return the number of FISA available
    */
    get getNumberFISA() { return this.numberFISA; }
    ;
    /**
    * \fn int map_getNumberE( const Map* m )
    * @brief a function to get the number of E
    *
    * This function get the number of E posseded by the player.
    *
    * @return the number of E available
    */
    get getNumberE() { return this.E; }
    ;
    /**
    * \fn int map_getNumberDD( const Map* m )
    * @brief a function to get the number of DD
    *
    * This function get the number of DD posseded by the player.
    *
    * @return the number of DD available
    */
    get getNumberDD() { return this.DD; }
    ;
    /**
    * \fn int map_getPlayerScore( const Map* m )
    * @brief a function to get the player score
    *
    * This function get the player score.
    * 10 000 points to win the game
    *
    * @return the score
    */
    get getPlayerScore() { return this.score; }
    ;
    // noinspection JSUnusedGlobalSymbols
    /**
    * \fn Difficulty map_getDifficulty( const Map* m )
    * @brief a function to get the difficulty of the map
    *
    * This function get the difficulty of the map.
    * EASY level : 10 x 10
    * MEDIUM level : 20 x 20
    * HARD level : 30 x 30
    *
    * @return the difficulty
    */
    get getDifficulty() { return this.difficulty; }
    ;
    /**
    * \fn int map_getWidth( const Map* m )
    * @brief a function to get map width
    *
    * This function get map width.
    *
    * @return the map width.
    */
    get getWidth() { return this.width; }
    ;
    /**
    * \fn int map_getHeight( const Map* m )
    * @brief a function to get map height
    *
    * This function get map height.
    *
    * @return the map height.
    */
    get getHeight() { return this.height; }
    ;
    /**
    * \fn int map_getNumberTurn( const Map* m )
    * @brief a function to get the number of turn
    *
    * This function get the number of turn
    *
    * @return the number of turn
    */
    get getNumberTurn() { return this.turn; }
    /**
     * a function to get the production of FISA
     * @return the production of FISA
     */
    get getProductionFISA() { return this.productionFISA; }
    ;
    /**
    * \fn int map_getStaffDictionary( const Map* m )
    * @brief a function to get the staff dictionary
    *
    * This function get the staff dictionary
    *
    * @return the staff dictionary
    */
    get staffList() { return this.team; }
    /**
    * \fn Case* map_getCase( int x, int y, const Map* m );
    * @brief a function to get a case of the map
    * @param x case abscissa
    * @param y case ordinate
    *
    * This function get a case of the map
    *
    * @return the case address if exist, if not a null address
    */
    getCase(x, y) {
        let logger = logger_1.Logger.Instance;
        if (!this.isCaseExist(x, y)) {
            logger.warn("Impossible access to a case nonexistent " + x + ";" + y);
            return null;
        }
        // @ts-ignore
        return this.map[x][y];
    }
    /**
    * \fn ErrorCode map_isCaseExist( int x, int y, const Map* m );
    * @brief In order to verify if a case exist
    * @param x case abscissa
    * @param y case ordinate
    * @return an error that specify what is the problem
    */
    isCaseExist(x, y) {
        let logger = logger_1.Logger.Instance;
        // @ts-ignore
        if (x >= 0 && x < this.width) {
            // @ts-ignore
            if (y >= 0 && y < this.height) {
                return true;
            }
        }
        logger.warn("Case nonexistent " + x + ";" + y);
        return false;
    }
    ;
    /**
     * \fn ErrorCode map_hireFISE(Map* m)
     * @brief Hire a FISE
     *
     * We hire a FISE in order to product more resources.
     * Every turn, each FISE student produce 1 E and 1 DD
     * A student (FISE or FISA) costs 50 E and 20 DD.
     *
     * A verification is necessary to know if the player can hire a new FISE.
     * We have to check resources E and DD of the player
     *
     * @return an error that specify what is the problem
     * @see Map type
     */
    map_hireFISE() {
        let logger = logger_1.Logger.Instance;
        if (this.numberFISE === undefined)
            return code_1.ErrorCode.ERROR;
        let e = this.map_hireStudent(events_1.EventType.HIRE_FISE, config_1.Config.constants.COST_FISE_E, config_1.Config.constants.COST_FISE_DD);
        if (e === code_1.ErrorCode.NO_ERROR) {
            this.numberFISE++;
            logger.info("Fise hire");
        }
        else {
            logger.warn("Not enough resources to hire a FISE");
        }
        return e;
    }
    ;
    /**
     * \fn ErrorCode map_hireFISA(Map* m)
     * @brief Hire a FISA
     *
     * We hire a FISA in order to product more resources.
     * Every 2 turns, each FISA student produce either 4 E or 4 DD
     *
     * A student (FISE or FISA) costs 50 E and 20 DD.
     *
     * A verification is necessary to know if the player can hire a new FISA.
     * We have to check resources E and DD of the player
     *
     * @return an error that specify what is the problem
     * @see Map type
     */
    map_hireFISA() {
        let logger = logger_1.Logger.Instance;
        if (this.numberFISA === undefined)
            return code_1.ErrorCode.ERROR;
        let e = this.map_hireStudent(events_1.EventType.HIRE_FISA, config_1.Config.constants.COST_FISA_E, config_1.Config.constants.COST_FISA_DD);
        if (e === code_1.ErrorCode.NO_ERROR) {
            this.numberFISA++;
            logger.info("FISA Hire");
        }
        else {
            logger.warn("Not enough resources to hire a FISA");
        }
        return e;
    }
    ;
    /**
     * Convenience method to hire a student
     */
    map_hireStudent(type, defaultE, defaultDD) {
        if (this.team === undefined)
            return code_1.ErrorCode.ERROR;
        // Take into account the effects of staff
        let hireStudentEvent = this.team.applyEffect(new events_1.GameEvent(type, new events_1.HireStudentEvent(defaultE, defaultDD))).data;
        // Check that the player has the money
        return this.tryBuy(hireStudentEvent.costE, hireStudentEvent.costDD);
    }
    /**
     * This function was created for the purpose of factorization of the code
     * It allows you to check that you can buy at a certain price and if so to debit the sub
     * @param costE The price in E
     * @param costDD The price in DD
     * @return ErrorCode An error code allowing to know if we succeeded or what is missing
     */
    tryBuy(costE, costDD) {
        let logger = logger_1.Logger.Instance;
        if (this.E === undefined || this.DD === undefined)
            return code_1.ErrorCode.ERROR;
        // Check that the player has enough E
        if (this.E >= costE) {
            // Check that the player has enough DD
            if (this.DD >= costDD) {
                // Debits the player
                this.E -= costE;
                this.DD -= costDD;
                // Informs that everything went well
                logger.info("Staff hire");
                return code_1.ErrorCode.NO_ERROR;
            }
            else {
                // Informs that it lacks DD
                logger.warn("Not enough DD resources to hire a staff");
                return code_1.ErrorCode.ERROR_NOT_ENOUGH_DD;
            }
        }
        else {
            // Informs that it lacks E
            logger.warn("Not enough E resources to hire a staff");
            return code_1.ErrorCode.ERROR_NOT_ENOUGH_E;
        }
    }
    /**
     * Parse or convert an object to a Map
     * @param parse an object that is a map but don't have the map type
     */
    static revive(parse) {
        let logger = logger_1.Logger.Instance;
        logger.debug("Parse or convert an object to a Map");
        // @ts-ignore
        let d = difficulty_1.Difficulty.getDifficultyByID(parse.difficulty.level);
        let map = new Map(d, true);
        // @ts-ignore
        map.turn = parse.turn;
        // @ts-ignore
        map.productionFISA = parse.productionFISA === 0 ? PRODUCTION_MODE.E : PRODUCTION_MODE.DD;
        // @ts-ignore
        map.E = parse.E;
        // @ts-ignore
        map.DD = parse.DD;
        // @ts-ignore
        map.score = parse.score;
        // @ts-ignore
        map.numberFISA = parse.numberFISA;
        // @ts-ignore
        map.numberFISE = parse.numberFISE;
        // Create grid
        map.map = new Array();
        // @ts-ignore
        for (let i = 0; i < map.width; i++) {
            // Creation of each Case
            map.map[i] = new Array();
            // @ts-ignore Initialization of boxes
            for (let j = 0; j < map.height; j++) {
                // @ts-ignore
                map.map[i][j] = Case.revive(parse.map[i][j]);
            }
        }
        // @ts-ignore
        map.team = parse.team;
        return map;
    }
    /**
     * @brief Switch the energy type produced by the FISA
     *
     * This function allow us to switch the energy type
     * produced by the FISA between E or DD.
     *
     * @return an error that specify what is the problem
     * @see Map type
     */
    changeProductionFISA() {
        let logger = logger_1.Logger.Instance;
        // Check the previous production
        if (this.productionFISA == PRODUCTION_MODE.E) {
            logger.info("Switch the energy type produced by the FISA to E !");
            this.productionFISA = PRODUCTION_MODE.DD;
        }
        else {
            logger.info("Switch the energy type produced by the FISA to DD !");
            this.productionFISA = PRODUCTION_MODE.E;
        }
        return code_1.ErrorCode.NO_ERROR;
    }
    /**
     * @brief Finish a turn
     *
     * Verifications to do at the end of a turn
     * <ol>
     * <li>Check FISA and FISE production</li>
     * <li>Update E</li>
     * <li>Call all conveyor belt/cross at the same time.</li>
     *
     * <li>
     * <ol>
     * <li>Resources moves</li>
     * <li>Verify each resource destination</li>
     * <li>next case empty then resource is lost</li>
     * <li>next case is an ENTRY machine -> send to machine</li>
     * </ol>
     * </li>
     *
     * <li>Check if we produce resources (sources)</li>
     * <li>Check if we produce wastes (gate)</li>
     * <li>Call all Recycling center</li>
     *
     * <li>
     * <ol>
     * <li>stored garbage don't decrease DD</li>
     * <li>10 garbage produce 1 /per turn</li>
     * </ol>
     * </li>
     *
     * <li>Call all collectors</li>
     *
     * <li>
     * <ol>
     * <li>activated from top to bot, left to right</li>
     * <li>No source then do nothing</li>
     * <li>randomly choose a source among all adjacent ones</li>
     * </ol>
     * </li>
     *
     * <li>Update DD value</li>
     * </ol>
     *
     * \param m game map
     * \return an error that specify what is the problem
    */
    endTurn() {
        let logger = logger_1.Logger.Instance;
        logger.debug("EndTurn function !");
        if (this.DD === undefined || this.turn === undefined || this.score === undefined) {
            logger.error("Calling endTurn with illegal values in the Map class!");
            return code_1.ErrorCode.ERROR;
        }
        // Production of Fise
        this.productionFise();
        // Production of Fisa
        this.productionFisa();
        // Move resources
        this.moveResources();
        // Generation of resources
        this.generateResources();
        // The door produces waste
        this.generateGarbage();
        // Operate waste reception centers
        this.activateRecyclingCenters();
        // The collectors activate
        this.activateCollectors();
        // Destroy the no-collected resources
        this.resetResourcesGarbage();
        this.moveResourcesInMachine();
        // Minus pollution to DD
        logger.debug("Minus pollution to DD!");
        let numberPollution = this.numberPollution;
        if (this.DD < numberPollution) {
            logger.info("Game lost because no more DD available !");
            return code_1.ErrorCode.ERROR_GAME_LOST;
        }
        this.DD -= numberPollution;
        // Checking if the player has won
        logger.debug("Checking if the player has won!");
        if (this.score > config_1.Config.constants.NUMBER_RESOURCE_WIN) {
            logger.info("Player victory!");
            return code_1.ErrorCode.ERROR_GAME_WIN;
        }
        // Turn increment
        this.turn++;
        return code_1.ErrorCode.NO_ERROR;
    }
    ;
    /** Produce DD and E by fise */
    productionFise() {
        let logger = logger_1.Logger.Instance;
        logger.debug("Resource production by FISE");
        this.studentProduction(events_1.EventType.PRODUCTION_FISE, config_1.Config.constants.PRODUCTION_FISE_E, config_1.Config.constants.PRODUCTION_FISE_DD, this.numberFISE);
    }
    ;
    /** Produce DD or E by fisa */
    productionFisa() {
        let logger = logger_1.Logger.Instance;
        // Checking that it is the turn to produce
        if (this.turn === undefined || this.turn % config_1.Config.constants.NB_TURN_FISA != 0) {
            logger.error("Calling productionFisa with illegal values in the Map class!");
            return;
        }
        // produce
        logger.debug("Resource production by FISA");
        this.studentProduction(events_1.EventType.PRODUCTION_FISA, config_1.Config.constants.PRODUCTION_FISA_E, config_1.Config.constants.PRODUCTION_FISA_DD, this.numberFISA, true);
    }
    /**
     * Handle production of FISE/FISA
     * @param type type of event
     * @param defaultE default production value (E)
     * @param defaultDD default production value (DD)
     * @param numberOfStudents number of students that are generating E/DD
     * @param checkProductionMode true if we should check production mode
     * @private
     */
    studentProduction(type, defaultE, defaultDD, numberOfStudents, checkProductionMode = false) {
        let logger = logger_1.Logger.Instance;
        logger.debug("Handle production of FISE/FISA");
        if (this.team === undefined || this.E === undefined || this.DD === undefined
            || numberOfStudents === undefined) {
            logger.warn("Calling studentProduction with illegal values in the Map class!");
            return;
        }
        // Initialization of basic production of Fise
        let productionE = defaultE;
        let productionDD = defaultDD;
        // Recovery of possible modifications on the production of Fise/Fisa
        let productionStudentEvent = this.team.applyEffect(new events_1.GameEvent(type, new events_1.ProductionStudentEvent())).data;
        // Adds the production of fise/fisa to the player
        if (!checkProductionMode || PRODUCTION_MODE.E === this.productionFISA)
            this.E += (productionE + productionStudentEvent.costE) * numberOfStudents;
        if (!checkProductionMode || PRODUCTION_MODE.DD === this.productionFISA)
            this.DD += (productionDD + productionStudentEvent.costDD) * numberOfStudents;
    }
    /**
    * \fn ErrorCode map_setNumberFISE( Map* m, int val)
    * @brief a function to set the number of FISE
    * @param val number of FISE to add/to substract
    *
    * This function set the number of FISE recruited by the player.
    *
    * @return an error that specify what is the problem
    */
    addFISE(val) { return this.addTo(val, 0); }
    /**
    * \fn ErrorCode map_setNumberFISA( Map* m, int val )
    * @brief a function to set the number of FISA
    * @param val number of FISA to add/to substract
    *
    * This function set the number of FISA recruited by the player.
    *
    * @return an error that specify what is the problem
    */
    addFISA(val) { return this.addTo(val, 1); }
    /**
    * \fn ErrorCode map_setNumberE( Map* m, int val )
    * @brief a function to set the number of E
    * @param val E value to add/to substract
    *
    * This function set the number of E posseded by the player.
    *
    * @return an error that specify what is the problem
    */
    addE(val) { return this.addTo(val, 2); }
    // noinspection JSUnusedGlobalSymbols
    /**
    * \fn ErrorCode map_setNumberDD( Map* m, int val )
    * @brief a function to set the number of DD
    * @param val DD value to add/to substract
    *
    * This function set the number of DD posseded by the player.
    *
    * @return an error that specify what is the problem
    */
    addDD(val) { return this.addTo(val, 3); }
    /**
    * \fn ErrorCode map_setNumberScore( Map* m, int val )
    * @brief a function to set the score
    * @param val DD value to add/to substract
    *
    * This function set the score
    *
    * @return an error that specify what is the problem
    */
    addScore(val) { return this.addTo(val, 4); }
    // noinspection JSUnusedGlobalSymbols
    /**
    * \fn ErrorCode map_setNumberTurn( Map* m, int val )
    * @brief a function to set the turn
    * @param val DD value to add/to substract
    *
    * This function set the turn
    *
    * @return an error that specify what is the problem
    */
    addTurn(val) { return this.addTo(val, 5); }
    /**
     * Convenience method to increase the number of FISE/FISA
     * @param val number of FISE/FISA to add/to substract
     * @param type 0 FISE, 1 FISA, 2 E and 3 DD
     * @private
     */
    addTo(val, type) {
        let attr = this.setFromType(type);
        if (attr === undefined)
            return code_1.ErrorCode.ERROR;
        if (attr + val >= 0) {
            this.setFromType(type, val);
            return code_1.ErrorCode.NO_ERROR;
        }
        else {
            return code_1.ErrorCode.ERROR_NEGATIVE_RESULT;
        }
    }
    /**
     * set and return attribute + val
     * @param type 0 numberFISE, 1 numberFISA, 2 E and 3 DD, 4 score
     * @param val a value
     * @private
     */
    setFromType(type, val = 0) {
        switch (type) {
            // @ts-ignore
            case 0: return this.numberFISE += val;
            // @ts-ignore
            case 1: return this.numberFISA += val;
            // @ts-ignore
            case 2: return this.E += val;
            // @ts-ignore
            case 3: return this.DD += val;
            // @ts-ignore
            case 4: return this.score += val;
            // @ts-ignore
            case 5: return this.turn += val;
        }
    }
    /**
    * \fn int map_getNumberPollution(  const Map* m );
    * @brief a function to get the pollution number
    *
    * This function get the pollution number
    * In order to have this information, we have to sum each case garbage
    *
    * @return the pollution number
    */
    get numberPollution() {
        let logger = logger_1.Logger.Instance;
        logger.debug("Calculate pollution Number");
        if (this.map === undefined || this.height === undefined || this.width === undefined)
            return -1;
        let nbGarbage = 0;
        // Process each case of the map
        for (let i = 0; i < this.height; ++i) {
            for (let j = 0; j < this.width; ++j) {
                let c = this.getCase(i, j);
                // Garbage contained in a box on the case
                if (c.hasBox()) {
                    nbGarbage += c.numberGarbage();
                    // Garbage contained in a machine
                    // We have to sum garbage of each facade of the machine
                }
                else if (c.isMachine) {
                    let machine = c.getMachine();
                    let machineType = machine.type;
                    // We don't take garbage from a junkyard into account
                    if (machineType != machine_1.MachineStuff.MS_JUNKYARD) {
                        for (let k = 0; k < machine_1.Machine.NUMBER_CARDINAL; ++k) {
                            if (machine.getBox(k) != null) {
                                nbGarbage += machine.getBox(k).numberGarbage;
                            }
                        }
                    }
                }
            }
        }
        return nbGarbage;
    }
    /**
     * Add a machine on the map
     * @param type a machine
     * @param rotation
     * @param x x > 0
     * @param y y > 0
     * @return error that specify what is the problem
     */
    addMachine(type, rotation, x, y) {
        let logger = logger_1.Logger.Instance;
        let e = this.machineManager(x, y, events_1.EventType.BUY_MACHINE, type);
        if (e == code_1.ErrorCode.NO_ERROR) {
            let c = this.getCase(x, y);
            // Created the machine
            let machine = new machine_1.Machine(type);
            // Turn the machine the right way
            machine.rotate(rotation);
            // @ts-ignore Add machine to box
            c.setMachine(machine);
            logger.info("New machine type " + type + " to the case x = " + x + ", y = " + y);
        }
        else {
            logger.warn("Failed to add a new machine");
        }
        return e;
    }
    /**
     * \fn ErrorCode map_upgradeMachine(const int x,const int y, Map* m)
     * @brief Upgrade a machine
     * @param x x > 0
     * @param y y > 0
     *
     * Upgrade a machine on the map. We know which machine we upgrade thanks
     * to the x and y coordinates
     *
     * @return an error that specify what is the problem
     */
    upgradeMachine(x, y) {
        let logger = logger_1.Logger.Instance;
        let e = this.machineManager(x, y, events_1.EventType.UPGRADE_MACHINE, undefined, true);
        if (e == code_1.ErrorCode.NO_ERROR) {
            let c = this.getCase(x, y);
            // @ts-ignore Improve the machine
            c.getMachine().increaseLevel();
            logger.info("Increase machine level to the case x = " + x + ", y = " + y);
        }
        else {
            logger.warn("Failed to increase machine level");
        }
        return e;
    }
    /**
     * \fn ErrorCode map_destroyMachine( int x, int y, Map* m )
     * @brief Destroy a machine
     * @param x x > 0
     * @param y y > 0
     * Destroy a machine on the map. We know which machine we destroy thanks
     * to the x and y coordinates
     *
     * @return an error that specify what is the problem
     */
    destroyMachine(x, y) {
        let logger = logger_1.Logger.Instance;
        let e = this.machineManager(x, y, events_1.EventType.DESTROY_MACHINE, undefined, true);
        if (e == code_1.ErrorCode.NO_ERROR) {
            let c = this.getCase(x, y);
            if (c == null)
                return code_1.ErrorCode.ERROR;
            // Improve the machine
            let machine = c.getMachine();
            // Send the waste to the door
            let checkBox;
            for (let card = 0; card < machine_1.Machine.NUMBER_CARDINAL; ++card) {
                checkBox = machine.getBox(card);
                if (checkBox != null) {
                    this.sendResourcesToGate(checkBox.numberGarbage);
                }
            }
            // Destroy machine
            logger.info("Machine destroyed to the cas x = " + x + ", y = " + y);
            c.setEmpty();
        }
        else {
            logger.warn("Failed to destroy a machine");
        }
        return e;
    }
    /**
     * Convenience methode to create, upgrade and destroy a machine
     * @param x x > 0
     * @param y y > 0
     * @param type event type so one of our three kind above
     * @param s a machine stuff, only if you got one (so create only)
     * @param invertIsEmpty case should not be empty (true), else case should be empty (false)
     * @private
     */
    machineManager(x, y, type, s, invertIsEmpty = false) {
        let logger = logger_1.Logger.Instance;
        if (this.team === undefined)
            return code_1.ErrorCode.ERROR;
        // Check that the box exists
        if (this.isCaseExist(x, y)) {
            let c = this.getCase(x, y);
            if (c == null)
                return code_1.ErrorCode.ERROR;
            // Check that the box is empty
            let goIn = c.isEmpty;
            if (invertIsEmpty)
                goIn = !goIn;
            if (goIn) {
                //Retrieving Machine Information
                let machineInfo = config_1.Config.getMachineStuff(s === undefined ? c.getMachine()?.type : s);
                // get the default cost according to the type of event
                let { costE, costDD } = function () {
                    switch (type) {
                        case events_1.EventType.UPGRADE_MACHINE:
                            return { costE: machineInfo?.costUpgradeE, costDD: machineInfo?.costUpgradeDD };
                        case events_1.EventType.DESTROY_MACHINE:
                            return { costE: machineInfo?.costDestroyE, costDD: machineInfo?.costDestroyDD };
                    }
                    return machineInfo;
                }();
                // Allows you to find machine info
                let machineEvent = this.team.applyEffect(new events_1.GameEvent(type, new events_1.MachineEvent(costE, costDD, machineInfo?.type))).data;
                // Check that the player has the money
                return this.tryBuy(machineEvent?.costE, machineEvent?.costDD);
            }
            else {
                return invertIsEmpty ? code_1.ErrorCode.ERROR_CASE_EMPTY : code_1.ErrorCode.ERROR_CASE_NOT_EMPTY;
            }
        }
        else {
            logger.error("");
            return code_1.ErrorCode.ERROR_CASE_NOT_FOUND;
        }
    }
    /*
    End turn functions
     */
    /**
     * Allows you to move resources on crosses and mats
     */
    moveResources() {
        let logger = logger_1.Logger.Instance;
        // Retrieving the tray size
        let width = this.width ?? 0;
        let height = this.height ?? 0;
        // Course of the game board
        for (let x = 0; x < width; ++x) {
            for (let y = 0; y < height; ++y) {
                // Case recovery
                let conveyorCase = this.getCase(x, y);
                // If there is a carpet
                if (conveyorCase.isType(machine_1.MachineStuff.MS_CONVEYOR_BELT) ||
                    conveyorCase.isType(machine_1.MachineStuff.MS_CROSS_BELT)) {
                    // Machine recovery
                    let conveyorMachine = conveyorCase.getMachine();
                    // Course of all faces
                    for (let card = 0; card < machine_1.Machine.NUMBER_CARDINAL; ++card) {
                        // Look for my exit face
                        if (conveyorMachine.getDirection(card) == machine_1.Direction.OUT) {
                            // Collect the box
                            let conveyorBox = conveyorMachine.getBox(card);
                            if (conveyorBox != null) {
                                // If there is a box, move it to the next box
                                this.moveBox(conveyorCase, conveyorBox, card);
                                logger.info("Cases resources x = " + x + ", y = " + y + " move to this direction " + card);
                                conveyorMachine.destroyBox(card);
                            }
                        }
                    }
                }
            }
        }
    }
    /**
     * This function allows you to move a box on an adjacent box in a certain direction
     * @param c Starting point
     * @param outputBox Box to move
     * @param card Direction in which to move the box
     * @return An error to warn of a possible error
     */
    moveBox(c, outputBox, card) {
        let logger = logger_1.Logger.Instance;
        // Retrieving the coordinates of the box
        let x = c.x;
        let y = c.y;
        // Calculation of changes in coordinates with respect to the new cardinal
        let modifier = machine_1.Facade.modifyXYWithCardinal(card);
        let outputCase = this.getCase(x + modifier.x, y + modifier.y);
        let inputBox;
        // Verification of the existence of the box
        if (outputCase != null) {
            // Checking the box type
            if (!outputCase.isMachine) {
                // If case is not a machine
                // Checking the presence of a box
                if (outputCase.hasBox()) {
                    // If yes add to the box already present the data of the new box
                    inputBox = outputCase.getBox();
                }
                else {
                    // If not add the box to the machine
                    inputBox = new machine_1.Box(0, 0);
                    outputCase.setBox(inputBox);
                }
                inputBox.addBox(outputBox);
                return code_1.ErrorCode.NO_ERROR;
            }
            else {
                // Otherwise recover the machine
                let outputMachine = outputCase.getMachine();
                // Capacity recovery and calculation
                const machineInfo = config_1.Config.getMachineStuff(outputMachine.type);
                let baseCapacity = machineInfo?.capacity;
                if (machineInfo?.canUpgrade) {
                    // @ts-ignore
                    baseCapacity += machineInfo?.capacityByLevel(outputMachine.level);
                }
                // Calculates the cardinal opposite to the output
                let outputCardinal = (card + (machine_1.Machine.NUMBER_CARDINAL / 2)) % machine_1.Machine.NUMBER_CARDINAL;
                // Checking that you are on the machine's entrance
                if (outputMachine.getDirection(outputCardinal) == machine_1.Direction.IN) {
                    // Verification of the existence of a box
                    let existBox = outputMachine.getBox(outputCardinal);
                    if (existBox == null) {
                        // Otherwise add the box to the box
                        existBox = new machine_1.Box(0, 0);
                        existBox.addBox(outputBox);
                        outputMachine.setBox(outputCardinal, existBox);
                    }
                    else {
                        existBox.addBox(outputBox);
                    }
                    if (outputMachine.type === machine_1.MachineStuff.MS_RECYCLING_CENTER) {
                        logger.debug("Entering by " + machine_1.Cardinal[outputCardinal] + " in");
                        logger.debug(machine_1.MachineStuff[outputMachine.type]);
                        logger.debug(JSON.stringify(outputMachine));
                        logger.debug(JSON.stringify(existBox));
                        logger.debug("value is now");
                        logger.debug(JSON.stringify(outputMachine.getBox(machine_1.Cardinal.NORTH)));
                        logger.debug(JSON.stringify(outputMachine.getBox(machine_1.Cardinal.EAST)));
                        logger.debug(JSON.stringify(outputMachine.getBox(machine_1.Cardinal.WEST)));
                        logger.debug(JSON.stringify(outputMachine.getBox(machine_1.Cardinal.SOUTH)));
                        logger.debug("******************");
                    }
                    // If the capacity is exceeded, send the waste to the door and destroy the resources
                    // @ts-ignore
                    if (outputCase.numberGarbage() > baseCapacity) {
                        // @ts-ignore
                        this.sendResourcesToGate((baseCapacity - outputCase.numberGarbage()) * -1);
                        // @ts-ignore
                        existBox.addGarbage(baseCapacity - outputCase.numberGarbage());
                    }
                    // @ts-ignore
                    if (outputCase.numberResources() > baseCapacity) {
                        // @ts-ignore
                        existBox.addResources(baseCapacity - outputCase.numberResources());
                    }
                    return code_1.ErrorCode.NO_ERROR;
                }
                else {
                    return code_1.ErrorCode.ERROR; // not an entry
                }
            }
        }
        else {
            return code_1.ErrorCode.ERROR_CASE_NOT_FOUND;
        }
    }
    /**
     * Allows you to send resources to the door
     * @param resources Number of resources
     */
    sendResourcesToGate(resources) {
        let logger = logger_1.Logger.Instance;
        logger.info("Call sendResourcesToGate()");
        if (this.width === undefined || this.height === undefined) {
            logger.error("Calling sendResourcesToGate with illegal values in the Map class!");
            return;
        }
        let c;
        // Gate search
        for (let i = 0; i < this.width; ++i) {
            for (let j = 0; j < this.height; ++j) {
                c = this.getCase(i, j);
                if (c == null)
                    continue;
                // Checking the presence of the door
                if (c.isGate) {
                    // Add the number of resources to the door
                    if (c.hasBox()) {
                        c.getBox().addResources(resources);
                    }
                    else {
                        c.setBox(new machine_1.Box(resources, 0));
                    }
                    // Pass resources through the Gate
                    this.generateGarbage();
                }
            }
        }
    }
    /**
     * Allows to generate resources
     */
    generateResources() {
        let logger = logger_1.Logger.Instance;
        logger.info("Call generateResources()");
        if (this.turn === undefined || this.team === undefined || this.width === undefined || this.height === undefined) {
            logger.error("Calling generateResources with illegal values in the Map class!");
            return;
        }
        // Initialization of the number of turn before production
        // and get staff reduction
        let numberTour = this.team.applyEffect(new events_1.GameEvent(events_1.EventType.GENERATE_RESOURCES, new events_1.TurnEvent(config_1.Config.constants.NB_TURN_PRODUCTION_SOURCE))).data.turn;
        // Lap check
        if (this.turn % numberTour == 0) {
            let c;
            let generateResource = config_1.Config.constants.NB_RESOURCE_PRODUCT_BY_SOURCE;
            // Browse the cells to find the sources
            for (let i = 0; i < this.width; ++i) {
                for (let j = 0; j < this.height; ++j) {
                    c = this.getCase(i, j);
                    // Checking for the presence of a source
                    if (c.isSource) {
                        // Add a box with the number of resources generated
                        c.setBox(new machine_1.Box(generateResource, 0));
                    }
                }
            }
        }
    }
    /**
     * Allows you to generate waste at the door
     */
    generateGarbage() {
        let logger = logger_1.Logger.Instance;
        logger.info("Call generateGarbage()");
        if (this.width === undefined || this.height === undefined || this.team === undefined) {
            logger.warn("Calling generateGarbage with illegal values in the Map class!");
            return;
        }
        let c;
        let modifierRes = // by default 1 resource = 1 point of score, but modifierRes can chance that
         this.team.applyEffect(new events_1.GameEvent(events_1.EventType.CALCULATE_SCORE, new events_1.ScoreEvent())).data.modifierScore;
        // Browse the map until you find the door
        for (let i = 0; i < this.width; ++i) {
            for (let j = 0; j < this.height; ++j) {
                c = this.getCase(i, j);
                // Checking the presence of the door
                if (c.isGate && c.hasBox()) {
                    // Recovery of the box
                    let box = c.getBox();
                    // Retrieving the number of resources
                    let numberR = box.numberResources;
                    // Transformation of resources into waste
                    box.addResources(numberR * -1);
                    // Score increase
                    this.addScore(numberR * modifierRes);
                    // can destroy some garbage using staffs
                    numberR = this.team.applyEffect(new events_1.GameEvent(events_1.EventType.GARBAGE_DESTROY, new events_1.GarbageEvent(numberR))).data.garbage;
                    // Creation of waste
                    logger.debug("Creation of waste!");
                    box.addGarbage(numberR);
                }
            }
        }
    }
    /**
     * Allows you to activate recycling centers
     */
    activateRecyclingCenters() {
        let logger = logger_1.Logger.Instance;
        logger.info("Call activateRecyclingCenters()");
        if (this.width === undefined || this.height === undefined) {
            logger.warn("Calling activateRecyclingCenters with illegal values in the Map class!");
            return;
        }
        let machineType = machine_1.MachineStuff.MS_RECYCLING_CENTER;
        let numberWasteToResource = config_1.Config.constants.NUMBER_WASTE_TO_PRODUCT_RESOURCE;
        // Browse the map to find recycling centers
        let c;
        for (let j = 0; j < this.height; ++j) {
            for (let i = 0; i < this.width; ++i) {
                c = this.getCase(i, j);
                // Verification of the presence of recycling centers
                if (c.isType(machineType)) {
                    let machine = c.getMachine();
                    // Finding the exit where the resources are present
                    for (let card = 0; card < machine_1.Machine.NUMBER_CARDINAL; ++card) {
                        // Checking the output
                        if (machine.getDirection(card) == machine_1.Direction.OUT) {
                            let machineBox = machine.getBox(card);
                            // Checking the presence of a box
                            if (machineBox != null) {
                                let numberGarbage = machineBox.numberGarbage;
                                // Verifying that resources are generated
                                if (numberGarbage > numberWasteToResource) {
                                    // Calculates the number of resources generated
                                    let numberResource = 1; //todo: produce one per ten garbage (const)
                                    // Transformation of waste into resources
                                    machineBox.addGarbage(-numberWasteToResource); // removing theses garbage
                                    // adding resource
                                    let outputBox = new machine_1.Box(numberResource, 0);
                                    // Sends resources on the output
                                    this.moveBox(c, outputBox, card);
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    /**
     * Allows you to activate collectors
     */
    activateCollectors() {
        let logger = logger_1.Logger.Instance;
        logger.info("Call activateCollectors()");
        if (this.width === undefined || this.height === undefined) {
            logger.warn("Calling activateCollectors with illegal values in the Map class!");
            return;
        }
        let machineType = machine_1.MachineStuff.MS_COLLECTOR;
        // Retrieving basic information from collectors
        const machineInfo = config_1.Config.getMachineStuff(machineType);
        let BaseCapacity = machineInfo.capacity;
        let modifiers = 0;
        // Browse the boxes to find the collectors
        let collectorCase;
        for (let j = 0; j < this.height; ++j) {
            for (let i = 0; i < this.width; ++i) {
                // Case recovery
                collectorCase = this.getCase(i, j);
                // Checking for the presence of a machine
                if (collectorCase.isType(machineType)) {
                    let collectorMachine = collectorCase.getMachine();
                    // Calculates capacity based on level
                    let capacity = BaseCapacity + machineInfo.capacityByLevel(collectorMachine.level) + modifiers;
                    let x = collectorCase.x;
                    let y = collectorCase.y;
                    let sourceCase;
                    let sourceBox;
                    let dir;
                    let out;
                    // Browse the different facades to find adjacent sources
                    let listSource = new Array();
                    for (let card = 0; card < machine_1.Machine.NUMBER_CARDINAL; ++card) {
                        dir = collectorMachine.getDirection(card);
                        // If the direction is NONE
                        if (dir == machine_1.Direction.NONE) {
                            // Calculates coordinates of the adjacent cell
                            let modifier = machine_1.Facade.modifyXYWithCardinal(card);
                            sourceCase = this.getCase(x + modifier.x, y + modifier.y);
                            // Verification of the existence of the adjacent box
                            if (sourceCase != null) {
                                // Then check if there is an adjacent source with a box
                                if ((sourceCase.isSource
                                    || sourceCase.isGate) && sourceCase.hasBox()) {
                                    sourceBox = sourceCase.getBox();
                                    // Checking the presence of resource in the box
                                    if (sourceBox.numberResources > 0 || sourceBox.numberGarbage > 0) {
                                        // Adding the box to the source list
                                        listSource.push(sourceCase);
                                    }
                                }
                            }
                        }
                        else if (dir == machine_1.Direction.OUT) {
                            // If OUT remember the exit
                            // Assumption that there is always an OUT
                            out = card;
                        }
                    }
                    // Creation of a temporary box to store the number of recovered resources
                    let choiceSource = 0;
                    let cumulative = new machine_1.Box(0, 0);
                    // As long as there is still the possibility of recovering resources
                    // And that there are still resources to recover
                    while (capacity > 0 && listSource.length > 0) {
                        // Choose a source randomly
                        choiceSource = Map.getRandomInt(0, listSource.length - 1);
                        // Retrieve the box from the source
                        sourceBox = listSource[choiceSource].getBox();
                        // Take a resource from the source
                        if (listSource[choiceSource].isSource) {
                            cumulative.addResources(1);
                            sourceBox.addResources(-1);
                        }
                        else {
                            cumulative.addGarbage(1); // add one to moved box
                            sourceBox.addGarbage(-1); // remove one from door
                        }
                        // Remove the source from the list if it is empty
                        if (sourceBox.numberResources <= 0 && sourceBox.numberGarbage <= 0) {
                            listSource.splice(choiceSource, 1);
                        }
                        // Decrease the capacity of the collector
                        capacity--;
                    }
                    // Destroy the source list
                    // xxx
                    logger.debug(`Collector at x=${i} and y=${j} is moving`);
                    logger.debug(JSON.stringify(cumulative));
                    // If there are resources that have been recovered then send the box to
                    // the outlet of the collector
                    if (cumulative.numberResources > 0 || cumulative.numberGarbage > 0) {
                        // @ts-ignore
                        // noinspection JSUnusedAssignment
                        this.moveBox(collectorCase, cumulative, out);
                    }
                }
            }
        }
    }
    /**
     * Allows you to delete all uncollected resources and bring all ground trash to the door
     */
    resetResourcesGarbage() {
        let logger = logger_1.Logger.Instance;
        logger.info("Call resetResourcesGarbage()");
        if (this.width === undefined || this.height === undefined) {
            logger.warn("Calling activateCollectors with illegal values in the Map class!");
            return;
        }
        let c, gate = null;
        let box = new machine_1.Box(0, 0);
        let tmpBox;
        // Browse the map to find the boxes
        for (let i = 0; i < this.width; ++i) {
            for (let j = 0; j < this.height; ++j) {
                c = this.getCase(i, j);
                // Checking the presence of the door
                if (c.isGate) {
                    gate = c;
                }
                else if (c.hasBox()) { // Verification of the presence of a box on an empty box
                    // Recovery of the box
                    tmpBox = c.getBox();
                    let n = tmpBox.numberGarbage;
                    // Adding your waste to the temporary box
                    box.addGarbage(n);
                    logger.debug(`send ${n} garbage on x=${j} y=${i} to door.`);
                    // Destruction of the box with uncollected resources
                    c.deleteBox();
                }
            }
        }
        // Add recovered waste to the door
        if (gate != null) {
            if (gate.hasBox()) {
                gate.getBox().addBox(box);
            }
            else {
                gate.setBox(box);
            }
        }
    }
    /**
     * This function allows you to move all the resources on the facades out of the machines.
     * It is called at the end of the turn and ensures that at the end of each turn and
     * at the start of each turn that all waste and resources are on the facades out
     */
    moveResourcesInMachine() {
        let logger = logger_1.Logger.Instance;
        logger.info("Call moveResourcesInMachine()");
        if (this.width === undefined || this.height === undefined) {
            logger.warn("Calling moveResourcesInMachine with illegal values in the Map class!");
            return;
        }
        let c;
        let direction;
        // Browse the map until you find machines
        for (let j = 0; j < this.height; ++j) {
            for (let i = 0; i < this.width; ++i) {
                // Case recovery
                c = this.getCase(i, j);
                // Checking for the presence of a machine
                if (c.isMachine) {
                    // Machine recovery
                    let machine = c.getMachine();
                    // Checking whether the machine is a cross or not
                    if (machine.type == machine_1.MachineStuff.MS_CROSS_BELT) {
                        // Course from all sides
                        for (let card = 0; card < machine_1.Machine.NUMBER_CARDINAL; ++card) {
                            direction = machine.getDirection(card);
                            // Checking the direction of the facade
                            if (direction == machine_1.Direction.IN) {
                                // Otherwise check for the presence of a box
                                let inBox = machine.getBox(card);
                                if (inBox != null) {
                                    // Calculation of the opposite facade
                                    let out = (card + (machine_1.Machine.NUMBER_CARDINAL / 2)) % machine_1.Machine.NUMBER_CARDINAL;
                                    // Recovery of the box
                                    let outputBox = machine.getBox(out);
                                    if (outputBox == null) {
                                        // Creation of a box if there was none
                                        outputBox = new machine_1.Box(0, 0);
                                        machine.setBox(out, outputBox);
                                    }
                                    // Add resources from the IN box to the OUT box
                                    outputBox.addBox(inBox);
                                    // Destroy IN box
                                    machine.destroyBox(card);
                                }
                            }
                        }
                    }
                    else {
                        // Creation of a temporary box to store all Resources / Garbage
                        let cumulBox = new machine_1.Box(0, 0);
                        let out = machine_1.Cardinal.NORTH;
                        // Course from all sides
                        for (let card = 0; card < machine_1.Machine.NUMBER_CARDINAL; ++card) {
                            // Management check
                            direction = machine.getDirection(card);
                            if (direction == machine_1.Direction.OUT) {
                                // If OUT saves the face
                                out = card;
                            }
                            else if (direction == machine_1.Direction.IN) {
                                // Otherwise check for the presence of a box
                                let tmp = machine.getBox(card);
                                if (tmp != null) {
                                    // If yes add the values to the temporary box
                                    cumulBox.addBox(tmp);
                                    // Delete the box
                                    machine.destroyBox(card);
                                }
                            }
                        }
                        if (machine.type === machine_1.MachineStuff.MS_RECYCLING_CENTER) {
                            if (cumulBox.numberGarbage !== 0 || cumulBox.numberResources !== 0) {
                                logger.debug("on machine " + machine_1.MachineStuff[machine.type]);
                                logger.debug("out is at " + machine_1.Cardinal[out]);
                                logger.debug("and we got ");
                                logger.debug(JSON.stringify(cumulBox));
                                logger.debug("for");
                                logger.debug(JSON.stringify(machine));
                                logger.debug(JSON.stringify(machine.getBox(out)));
                                logger.debug("---------------------");
                            }
                        }
                        // Checking for the presence of resources
                        if (cumulBox.numberGarbage > 0 || cumulBox.numberResources > 0) {
                            // Checking the presence of a Box on the output
                            let tmp = machine.getBox(out);
                            if (tmp != null) {
                                // If yes add the data
                                machine.addBox(out, cumulBox);
                            }
                            else {
                                // Addition of the box to the exit face
                                machine.setBox(out, cumulBox);
                            }
                        }
                        else {
                            // Destruction of the box
                            // xxx
                        }
                    }
                }
            }
        }
    }
    // Random placement
    static getRandomInt(min, max) {
        return utilities_1.randomNumber(min, max);
    }
    /**
     * \fn ErrorCode map_buyStaff( int idStaff, Map* m )
     * @brief Buy a Staff
     * @param idStaff a int
     * Buy a Staff
     *
     * @return ErrorCode an error that specify what is the problem
     */
    buyStaff(idStaff) {
        let logger = logger_1.Logger.Instance;
        if (this.team === undefined || this.E === undefined || this.DD === undefined) {
            logger.error("Calling buyStaff with illegal values in the Map class!");
            return code_1.ErrorCode.ERROR;
        }
        const staff = this.team.getStaff(idStaff);
        // Check the existence of staff
        if (staff != null) {
            // Recovery of the basic price of the staff
            let { costE, costDD } = this.team.applyEffect(new events_1.GameEvent(events_1.EventType.BUY_STAFF, new events_1.StaffBuyEvent(staff.costE, staff.costDD, idStaff))).data;
            // Check that the player has the money
            let e = this.tryBuy(costE, costDD);
            if (e == code_1.ErrorCode.NO_ERROR) {
                // Add staff to player
                this.team.hire(staff.id);
                // If the staff takes immediate action, do so
                this.team.applyEffect(new events_1.GameEvent(events_1.EventType.BOUGHT_STAFF, new events_1.StaffBoughtEvent(idStaff, this)));
                logger.debug(JSON.stringify(this.team));
                // If the action of the staff to fail reimburse the player
                if (e != code_1.ErrorCode.NO_ERROR) {
                    this.E += costE;
                    this.DD += costDD;
                    return e;
                }
                return code_1.ErrorCode.NO_ERROR;
            }
            else {
                return e;
            }
        }
        else {
            return code_1.ErrorCode.ERROR_INVALID_STAFF_NUMBER;
        }
    }
}
exports.Map = Map;
/**
 * FISA Can produce either E or DD
 */
var PRODUCTION_MODE;
(function (PRODUCTION_MODE) {
    PRODUCTION_MODE[PRODUCTION_MODE["E"] = 0] = "E";
    PRODUCTION_MODE[PRODUCTION_MODE["DD"] = 1] = "DD"; //!< DD Constant that measure the planet general health
})(PRODUCTION_MODE = exports.PRODUCTION_MODE || (exports.PRODUCTION_MODE = {}));
/**
 * \file case.h
 * \author Antoine Man
 * \version 0.1
 * \date 11/03/2021
 * \see map
 * \see machine
 * \see box
 *
 * all the information concerning a case.
 * it correspond to a case of the board game
 */
class Case {
    /**
     * A function to create a new case
     * @param x case abscissa
     * @param y case ordinate
     * @return a new case
     */
    constructor(x, y) {
        this.box = false; //!< type of object contained in the case
        this.x = x;
        this.y = y;
        this.type = CaseType.CASE_EMPTY;
        this.in = null;
    }
    /**
     * A function to know if there is something on the case (box, machine)
     * To know if we are allowed to create something on
     * @return true if there is nothing on, if not false
     */
    get isEmpty() { return this.type == CaseType.CASE_EMPTY; }
    /** convenience to check if it's a machine **/
    get isMachine() { return this.type == CaseType.CASE_MACHINE; }
    /** convenience to check if it's a gate **/
    get isGate() { return this.type == CaseType.CASE_GATE; }
    /** convenience to check if it's a source **/
    get isSource() { return this.type == CaseType.CASE_SOURCE; }
    /**
     * A function to remove everything on the case
     * if there is a box or a machine
     */
    setEmpty() {
        this.type = CaseType.CASE_EMPTY;
        this.in = null;
    }
    ;
    /**
     * This function get the type case of the case
     * <ul>
     *   <li> CASE_VIDE = 0, a case that contain nothing
     *   <li> CASE_GATE = 1, a case that contain the transdimensional gate
     *   <li> CASE_SOURCE = 2, a case that contain resources
     *   <li> CASE_MACHINE = 3, a case that contain a machine
     * </ul>
     * @return the type case if case exist, if not -1
     * @private since we can to make the code easier
     */
    get caseType() { return this.type; }
    /**
     * Set case type
     * @param type a type of case
     */
    setType(type) {
        if (this.isEmpty) {
            this.type = type;
            return true;
        }
        return false;
    }
    /**
     * A function to add a gate on an empty case
     */
    setGate() { return this.setType(CaseType.CASE_GATE); }
    /**
     * A function to add a source on an empty case
     */
    setSource() { return this.setType(CaseType.CASE_SOURCE); }
    /**
     * A function to add a machine on an empty case
     * @param mach machine
     */
    setMachine(mach) {
        if (this.isEmpty && this.in == null) {
            this.type = CaseType.CASE_MACHINE;
            this.in = mach;
            return true;
        }
        return false;
    }
    /**
     * A function to add a box on an empty case
     * @param box box
     */
    setBox(box) {
        if (this.type != CaseType.CASE_MACHINE && !this.hasBox()) {
            this.box = true;
            this.in = box;
            return true;
        }
        return false;
    }
    /**
     * A function to know if there is a box on the case
     * In order to know it, we have to analyze the first bit of the type case.
     * If the number is odd, there is a box
     * If the number is even, there is nothing
     * @return true if there is a box, if not false
     */
    hasBox() { return this.box; }
    /**
     * This function get a located machine on the map
     * @return a located machine on the map if exist
     */
    getMachine() { return this.in; }
    /**
     * This function get a located box on the map
     * @return a located box on the map if exist
     */
    getBox() { return this.in; }
    /**
     * This function get number of resources from a case
     * @return resources from a case if exist
     */
    numberResources() {
        return this.numberHelper("numberResources");
    }
    /**
     * This function get number of garbage from a case
     * @return garbage from a case if exist
     */
    numberGarbage() {
        return this.numberHelper("numberGarbage");
    }
    /**
     * Fusion of numberResources/Garbage getters
     * @param of the attribute we want to count such as numberGarbage or numberResources. Theses
     *           are attributes of Box
     */
    numberHelper(of) {
        let nbResources = 0;
        let box;
        let type = this.type;
        // Verify if there is a case on the case
        if (this.hasBox()) {
            box = this.getBox();
            // @ts-ignore
            nbResources = box[of];
            // Verify if there is a machine on the case
        }
        else if (type == CaseType.CASE_MACHINE) {
            let machine = this.getMachine();
            // Sum resources number for each facade of a machine
            for (let card = 0; card < machine_1.Machine.NUMBER_CARDINAL; ++card) {
                box = machine.getBox(card);
                if (box != null) {
                    // @ts-ignore
                    nbResources += box[of];
                }
            }
        }
        return nbResources;
    }
    /**
     * A function to remove the box on a located case
     * @return an error code to know what happen
     */
    deleteBox() {
        // Verify if there is a box on the case
        if (this.hasBox()) {
            this.box = false;
            this.in = null;
        }
        return code_1.ErrorCode.NO_ERROR;
    }
    /**
     * Revive from object
     * @param object serialization as object
     */
    static revive(object) {
        let c = new Case(object.x, object.y);
        c.type = object.type;
        c.in = object.in;
        c.box = object.box;
        return c;
    }
    /**
     * This function allows you to check if a machine of a specific type is present in a space
     * Return true if the contains contains this type of machine
     * @param type of machine
     * @return returns boolean if there is a machine of the right type
     */
    isType(type) {
        // Checking the presence of a machine
        return this.caseType === CaseType.CASE_MACHINE
            // Returns the result of the comparison between the type of the machine and the desired type
            && this.getMachine().type === type;
    }
}
exports.Case = Case;
/**
 * Contains all type that a case can contain.
 * Each case can contain 4 elements types :
 * a part of the production line
 * a resource case
 * an empty case
 * a transdimensional gate
 *
 * 3 resources are produced by a resource case every 10 turns
 *
 * In order to know if a case contain a box (that contain resources and garbage),
 * we use the first bit of an integer.
 * The case contain a box -> odd number
 * The case does not contain a box -> even number
 */
var CaseType;
(function (CaseType) {
    CaseType[CaseType["CASE_EMPTY"] = 0] = "CASE_EMPTY";
    CaseType[CaseType["CASE_GATE"] = 2] = "CASE_GATE";
    CaseType[CaseType["CASE_SOURCE"] = 4] = "CASE_SOURCE";
    CaseType[CaseType["CASE_MACHINE"] = 6] = "CASE_MACHINE";
})(CaseType = exports.CaseType || (exports.CaseType = {}));
