/**
 * \file mapping.h
 * \author Quentin Ra
 * \version 0.5
 * \date 10/03/2021
 *
 * List of actions mappings
 */

import {Game} from "../game";
import {ErrorCode} from "./code";
import {Translation} from "./translation";
import {Machine, MachineInfo} from "../model/machine";

/**
 * Map of mappings
 */
class MappingsMap {
    /** our real map of mappings **/
    private readonly mappings: Map<Action, Mapping>;
    /** shortcut for mappings functions **/
    private readonly functions: Object;
    /** shortcut for mappings keys **/
    private readonly keys: Array<string>;

    constructor() {
        this.mappings = new Map<Action, Mapping>();
        this.functions = {};
        this.keys = new Array<string>();
    }

    set(mapping: Mapping) : void {
        this.mappings.set(mapping.action, mapping);
        // save function as "ls": this.listStaff for instance
        // @ts-ignore
        this.functions[mapping.key] = mapping.code;
        // save key
        this.keys.push(mapping.key)
    }

    getFunctions() : object { return this.functions; }
    getKeys() : Array<string> { return this.keys; }

    getValues() : IterableIterator<Mapping> {
        return this.mappings.values();
    }

    get(action:Action) : Mapping | undefined {
        return this.mappings.get(action);
    }
}

/**
 * Handler of our mappings
 */
export class Mappings {
    /** our map of mappings **/
    private static mappings: MappingsMap;
    /** true if init called **/
    private static isInit = false;

    /**
     * Init all our static variables
     * @private
     */
    private static initMappings(){
        if (this.isInit) return; // done

        // init map
        this.mappings = new MappingsMap();
        this.mappings.set(new Mapping(Action.LIST_ACTIONS, "help","Show the list of available actions." , this.listMappings))
        this.mappings.set(new Mapping(Action.CANCEL_ACTION, "b","Used to go back or cancel the current an action." , this.goBack))
        this.mappings.set(new Mapping(Action.LIST_MACHINES, "lm","List all machines." , this.listMachines))
        this.mappings.set(new Mapping(Action.LIST_STAFF, "ls","List all staffs." , this.listStaff))
        this.mappings.set(new Mapping(Action.HIRE_FISE, "he","Hire a FISE." , this.hireFISE))
        this.mappings.set(new Mapping(Action.HIRE_FISA, "ha","Hire a FISA." , this.hireFISA))
        this.mappings.set(new Mapping(Action.CHANGE_FISA_MODE, "c","Change production mode." , this.fisaMode))
        this.mappings.set(new Mapping(Action.BUY_STAFF, "bs","Buy a staff." , this.buyStaff))
        this.mappings.set(new Mapping(Action.BUY_MACHINE, "bm","Buy a machine." , this.buyMachine))
        this.mappings.set(new Mapping(Action.UPGRADE_MACHINE, "um","Upgrade a machine." , this.upgradeMachine))
        this.mappings.set(new Mapping(Action.DESTROY_MACHINE, "dm","Destroy a machine." , this.destroyMachine))
        this.mappings.set(new Mapping(Action.SHOW_MAP, "m","Show map." , this.showMap))
        this.mappings.set(new Mapping(Action.SHOW_CASE_RESOURCE, "r","Show map with resource count instead of machine type." , this.showResource))
        this.mappings.set(new Mapping(Action.SHOW_CASE_GARBAGE, "g","Show map with garbage count instead of machine type." , this.showGarbage))
        this.mappings.set(new Mapping(Action.END_TURN, "n","End turn." , this.endTurn))
        this.mappings.set(new Mapping(Action.EXIT, "q","End game." , this.exit))

        this.isInit = true;
    }

    // handlers

    /** list actions with help **/
    private static listMappings = function () {
        // @ts-ignore since it's terminal method
        this.clear();
        // Request display of actions
        Game.save();
        location.href = 'mappings.html';
    };

    /** list machines with lm  **/
    private static listMachines = function () {
        // @ts-ignore since it's terminal method
        this.clear();
        // Request the display of machines
        Game.save();
        location.href = 'machines.html';
    };

    /**
     * list Staff with ls
     *
     * Should take a map and print the list of the staff.
     * Please do take note that this method use a global
     * variable containing all data about the staff.
     *
     * This method should be a catalog of available staffs.
     * You must add right after a staff name the count of this staff
     * that the user have already bought.
     *
     * <pre>
     * --> ({n°}) Name E:{cost} DD:{cost} Desc:"perks"
     * ...
     * </pre>
     *
     * @pre staff list must be set
     * @pre map must contains the list of staff that the player bought
     * @see Map
     */
    private static listStaff = function () {
        // @ts-ignore since it's terminal method
        this.clear();
        // Call the interface function to show the list of staff
        // Player staff list and staff list available
        Game.save();
        location.href = 'staffs.html';
    };

    /** hire FISE with he  **/
    private static hireFISE = function (n = 1) {
        if (n <= 0) n = 1;
        while (n > 0){
            // @ts-ignore since it's terminal method
            this.clear();
            let e = Game.map.map_hireFISE();
            if (e !== ErrorCode.NO_ERROR){
                // @ts-ignore
                this.echo(Translation.error(e))
                break;
            } else Game.interface.renderGameScreen(Game.map);
            n--;
        }
    };

    /** hire FISA with ha **/
    private static hireFISA = function (n = 1) {
        if (n <= 0) n = 1;
        while (n > 0){
            // @ts-ignore since it's terminal method
            this.clear();
            let e = Game.map.map_hireFISA();
            if (e !== ErrorCode.NO_ERROR){
                // @ts-ignore
                this.echo(Translation.error(e))
                break;
            } else Game.interface.renderGameScreen(Game.map);
            n--;
        }
    };

    /** change mode with c **/
    private static fisaMode = function () {
        // @ts-ignore since it's terminal method
        this.clear();
        // Call The map function to change the mode of production of the FISA
        // E or DD
        let e = Game.map.changeProductionFISA();
        if (e !== ErrorCode.NO_ERROR){
            // @ts-ignore Show the error message
            this.echo(Translation.error(e))
        } else Game.interface.renderGameScreen(Game.map);
    };

    /**
     * Call the function to buy the staff
     * buy staff with bs
     * @brief Ask which Staff the user wants to buy.
     *
     * The user input an id (that he could find using list staff action)
     * and we returns the staff in the global staff array that match the given id.
     *
     * If the user wants to go back, then he can using
     * ACTION_CANCEL_ACTION action.
     *
     * @return a valid Staff that the user chosen. Or null if he asked to cancel.
     *
     * @see ACTION_BUY_STAFF
     * @see ACTION_ASK_STAFF_LIST (action enum)
     */
    private static buyStaff = function (id = -1, n = 1) {
        // @ts-ignore since it's terminal method
        this.clear();
        if (id === -1){ //todo:
            // @ts-ignore Show the error message
            this.echo("Usage is: bs Staff_id [or] bs Staff_id count")
            return;
        }
        if (n < 1 || n > 100){
            // @ts-ignore Show the error message
            this.echo("Count must be in [1,100]")
            return;
        }
        while (n > 0){
            // Call The map function to try to buy a staff member
            let e = Game.map.buyStaff(id);
            if (e !== ErrorCode.NO_ERROR){
                // @ts-ignore Show the error message
                this.echo(Translation.error(e))
                break;
            } else Game.interface.reload(); // reload all since staff can change the map
            n--;
        }
    };

    /**
     * Call the function to buy the machine
     * buy machine with bm
     *
     * @brief ask user machine specific details
     *
     * @pre this method should be called after (or before) asking
     * the user where the machine should be put
     *
     * If the user wants to go back, then he can using
     * ACTION_CANCEL_ACTION action.
     *
     * We must fill each value inside our machine, for that
     * check {@link Machine} type.
     *
     * @return the machine that the user wanted to add.
     *
     * @see ACTION_BUY_MACHINE
     */
    private static buyMachine = function (machineStuff = -1, x=-1, y=-1, rotation= 0) {
        // @ts-ignore since it's terminal method
        this.clear();

        if (machineStuff == -1 || x == -1 || y == -1 || rotation == -1){
            // @ts-ignore todo:
            this.echo("Usage is : bm machine_id x y rotation (see help)");
        } else {
            // check machine stuff
            if(MachineInfo.isMachineStuffValid(machineStuff) === -1) {
                // @ts-ignore
                this.echo(Translation.error(ErrorCode.ERROR_INVALID_MACHINE_NUMBER));
            } else {
                // check coordinates
                // @ts-ignore
                Mappings.handleMachine(machineStuff, x, y, rotation, Action.BUY_MACHINE, this);
            }
        }
    };

    /**
     * Call the function to upgrade machine
     * upgrade machine with um **/
    private static upgradeMachine = function (x=-1, y = -1) {
        // @ts-ignore since it's terminal method
        this.clear();
        if (x == -1 && y == -1){
            // @ts-ignore todo:
            this.echo("Usage is : um x y (see help)");
        } else {
            // check coordinates
            // @ts-ignore
            Mappings.handleMachine(null, x, y, 0, Action.UPGRADE_MACHINE, this);
        }
    };

    /**
     * Call the function to destroy machine
     * destroy machine with dm **/
    private static destroyMachine = function (x=-1, y = -1) {
        // @ts-ignore since it's terminal method
        this.clear();
        if (x == -1 && y == -1){
            // @ts-ignore todo:
            this.echo("Usage is : dm x y (see help)");
        } else {
            // check coordinates
            // @ts-ignore
            Mappings.handleMachine(null, x, y, 0, Action.DESTROY_MACHINE, this);
        }
    };

    /** show map with m **/
    private static showMap = function () {
        // @ts-ignore since it's terminal method
        this.clear();
        Game.interface.renderMap(Game.map, false, false, true)
    };

    /** show map of resources with r **/
    private static showResource = function () {
        // @ts-ignore since it's terminal method
        this.clear();
        Game.interface.renderMap(Game.map, true, false, true)
    };

    /** show map of resources with g **/
    private static showGarbage = function () {
        // @ts-ignore since it's terminal method
        this.clear();
        Game.interface.renderMap(Game.map, false, true, true)
    };

    /** cancel action with b **/
    private static goBack = function () {
        // @ts-ignore since it's terminal method
        this.clear();
    };

    /** end turn with n **/
    private static endTurn = function (n=1) {
        if (n <= 0) n = 1;
        if (n > 1000){
            // @ts-ignore since it's terminal method
            this.clear();
            // @ts-ignore since it's terminal method todo:
            this.echo("Can only do up to 1000 in one go.")
            return;
        }
        while (n > 0){
            // @ts-ignore since it's terminal method
            this.clear();
            let e = Game.map.endTurn();
            if (e !== ErrorCode.NO_ERROR){
                Game.save();
                // end of the game (lost or win)
                location.href = 'end.html';
                break;
            } else // redraw all
                Game.interface.reload();
            n--;
        }
    };

    /** exit with q **/
    private static exit = function () {
        // @ts-ignore since it's terminal method
        this.clear();
        Game.save();
        // end the game
        location.href = 'end.html'
    };

    /**
     * @brief Ask for machine location then performs a add/upgrade/delete
     *
     * Ask for machine location, this function should
     * be used when the user triggered upgrade/delete machine action
     *
     * The programmer won't have to check whether this location is a valid
     * machine location, that would have to be done by the one calling it.
     *
     * @see ACTION_BUY_MACHINE
     * @see ACTION_UPGRADE_MACHINE
     * @see ACTION_DESTROY_MACHINE
     *
     * @param machineStuff a machine stuff if buy
     * @param x x > 0
     * @param y y > 0
     * @param rotation a rotation if buy
     * @param type a type of event (buy, upgrade, destroy)
     * @param terminal our terminal
     */
    private static handleMachine(machineStuff: number|null, x: number, y: number, rotation: number = 0, type: Action,
                                 terminal: any) {
        // check the position of the machine
        if (Game.map.isCaseExist(Number(x), Number(y))) {
            // check if rotation is correction
            if (Machine.isRotationCorrect(rotation)){
                let e;
                if (type === Action.DESTROY_MACHINE) {
                    // Call The map function to destroy the machine
                    e = Game.map.destroyMachine(x, y)
                } else if (type === Action.UPGRADE_MACHINE) {
                    // Call The map function to improve the machine
                    e = Game.map.upgradeMachine(x, y)
                } else {
                    // Call the map function to add machine
                    e = Game.map.addMachine(<number>machineStuff, rotation, x, y);
                }
                // Check the return of the function
                if (e === ErrorCode.NO_ERROR) {
                    Game.interface.reload();
                } else {
                    // Show the error message
                    terminal.echo(Translation.error(e))
                }
            } else {
                terminal.echo(Translation.error(ErrorCode.ERROR_INVALID_ORIENTATION_NUMBER));
            }
        } else {
            terminal.echo(Translation.error(ErrorCode.ERROR_CASE_NOT_FOUND));
        }
    }

    // basic functions

    /**
     * Shortcut to get all functions
     * indexed by command (object where
     * fiels are command and their values are functions)
     */
    public static getMappingsFunctions() : Object {
        this.initMappings();
        return this.mappings.getFunctions();
    }

    /**
     * Shortcut to get all mappings keys.
     */
    static getKeys() : Array<string> {
        this.initMappings();
        return this.mappings.getKeys();
    }

    /**
     * Shortcut to get all mappings
     */
    static getMappings() : IterableIterator<Mapping> {
        this.initMappings();
        return this.mappings.getValues();
    }

    // utils

    /**
     * Returns the mapping associated with the back
     * Action. This is a convenient method since
     * this mapping is used in a lot a places.
     */
    static getBackKey() : string {
        this.initMappings();
        // @ts-ignore
        return this.mappings.get(Action.CANCEL_ACTION).key;
    }

    /**
     * Returns exit/quit key
     */
    static getExitKey() : string {
        this.initMappings();
        // @ts-ignore
        return this.mappings.get(Action.EXIT).key;
    }

    static getHelpKey() {
        this.initMappings();
        // @ts-ignore
        return this.mappings.get(Action.LIST_ACTIONS).key;
    }
}

/**
 * Each action is mapped with a string.
 */
export class Mapping {
    /** keyboard keys **/
    public key: string;
    /** Mapping description **/
    public desc: string;
    /** action in the program */
    public action: Action;
    /** function executed on called **/
    public code: any;

    constructor( action: Action, key: string, desc: string, code: any) {
        this.action = action;
        this.key = key;
        this.desc = desc;
        this.code = code;
    }
}

/**
 * Contains all actions and their code (id).
 * Used when asking the user what he wants to do.
 */
export enum Action {
    // actions related to the game in general
    SHOW_MAP = 143, //!< show map
    SHOW_CASE_RESOURCE = 1430, //!< show resources instead of case content
    SHOW_CASE_GARBAGE = 1431, //!< show garbage instead of case content
    CANCEL_ACTION = 144, //!< cancel action so go back
    EXIT = 145, //!< exit so leave the program
    LIST_ACTIONS = 146, //!< list all actions
    END_TURN = 147, //!< go to next turn

    // hire
    HIRE_FISE = 221, //!< trigger hire fise
    HIRE_FISA = 222, //!< trigger hire fisa
    CHANGE_FISA_MODE = 223, //!< change fisa production mode

    // actions related to the units
    LIST_MACHINES = 331, //!< show list of machines
    BUY_MACHINE = 332, //!< trigger add machine
    BUY_STAFF = 333, //!< trigger hire Staff
    LIST_STAFF = 334, //!< in hire Staff, show Staff list

    // actions related to the machines
    UPGRADE_MACHINE = 514, //!< trigger upgrade machine
    DESTROY_MACHINE = 515, //!< trigger destroy machine
} //!< Action type