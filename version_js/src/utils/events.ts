/**
 * \author Ramzy ZEBRIR, Antoine Man and Quentin RA
 * \version 1.0
 * \date 25/04/2021
 * \see staff
 *
 * Contains information about events. Was know as effects before.
 */
import {Map} from "../model/map";
import {MachineStuff} from "../model/machine";

export enum EventType {
    HIRE_FISE, //!< date type is HireStudentEvent
    HIRE_FISA, //!< date type is HireStudentEvent
    PRODUCTION_FISE, //!< date type is ProductionStudentEvent
    PRODUCTION_FISA, //!< date type is ProductionStudentEvent

    BUY_MACHINE, //!< data type is MachineEvent
    UPGRADE_MACHINE, //!< data type is MachineEvent
    DESTROY_MACHINE, //!< data type is MachineEvent

    GENERATE_RESOURCES, //!< data type is TurnEvent

    CALCULATE_SCORE, //!< data type is ScoreEvent

    GARBAGE_DESTROY, //!< data type is GarbageEvent

    BUY_STAFF, //!< data type is StaffBuyEvent
    BOUGHT_STAFF, //!< data type is StaffBoughtEvent
}

export class GameEvent {
    public readonly type: EventType;
    public readonly data: any;

    constructor(type: EventType, data: any) {
        this.type = type;
        this.data = data;
    }
}

/*
* Utils
*/

/**
 * Convenience class for price related events
 */
class PriceEvent {
    public costE;
    public costDD;

    constructor(costE: number, costDD: number) {
        this.costE = costE;
        this.costDD = costDD;
    }
}

/**
 * HIRE_FISE/HIRE_FISA date type.
 * Can increase/decrease the price of a FISE/FISA
 */
export class HireStudentEvent extends PriceEvent {
    constructor(costE: number, costDD: number) {
        super(costE, costDD);
    }
}

/**
 * PRODUCTION_FISE/PRODUCTION_FISA date type.
 * The value that is set as E/DD is the number that
 * we will add the the basic value.
 *
 * if costE = 1, and FISE produce 1E per default, then
 * they will now produce 2E !
 */
export class ProductionStudentEvent extends PriceEvent {
    /** no modifier by default **/
    constructor() {
        super(0, 0);
    }
}

/**
 * BUY_MACHINE/UPGRADE_MACHINE/DESTROY_MACHINE date type.
 * Returns the new price of a machine after reduction
 */
export class MachineEvent extends PriceEvent {

    public readonly type: MachineStuff;

    /**
     * Can apply a reduction on a machine
     * @param costE new price in E
     * @param costDD new price in DD
     * @param type machine type
     */
    constructor(costE: number, costDD: number, type: MachineStuff) {
        super(costE, costDD);
        this.type = type;
    }
}

/**
 * GENERATE_RESOURCES data type.
 * Can reduce the number of turns required for
 * a source to produce resources.
 */
export class TurnEvent {

    // number of turns
    public turn: number;

    constructor(turn: number) {
        this.turn = turn;
    }
}

/**
 * CALCULATE_SCORE data type.
 * Can increase (most likely but can reduce) the score.
 * if set to n, then we will multiply the number
 * of resources generating the score by this number
 */
export class ScoreEvent {

    // number of turns
    public modifierScore: number;

    constructor() {
        this.modifierScore = 1;
    }
}

/**
 * GARBAGE_DESTROY data type.
 * Here on can delete some garbage (or add)
 * generated when a resource got send to the door.
 */
export class GarbageEvent {

    // number of garbage created
    public garbage: number;

    constructor(garbage: number) {
        this.garbage = garbage;
    }
}

/**
 * BUY_STAFF data type.
 * Can apply a reduction of the cost of the staff
 */
export class StaffBuyEvent extends PriceEvent {
    // can be modified but not assigned
    public readonly idStaff : number;

    /**
     * Can apply a reduction of the cost of the staff
     * @param costE new price in E
     * @param costDD new price in DD
     * @param idStaff a staff ID if needed
     */
    constructor(costE: number, costDD: number, idStaff: number) {
        super(costE, costDD);
        this.idStaff = idStaff;
    }
}

/**
 * BOUGHT_STAFF data type.
 * After a staff is bought, he can trigger a once in a lifetime
 * event.
 */
export class StaffBoughtEvent {
    // can be modified but not assigned
    public readonly idStaff: number;
    // can be modified but not assigned
    public readonly map: Map;

    /**
     * Can apply a reduction of the cost of the staff
     * @param idStaff a staff ID if needed
     * @param map the map if the staff will do something with it
     */
    constructor(idStaff: number, map: Map) {
        this.idStaff = idStaff;
        this.map = map;
    }
}