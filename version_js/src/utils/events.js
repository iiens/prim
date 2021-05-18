"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.StaffBoughtEvent = exports.StaffBuyEvent = exports.GarbageEvent = exports.ScoreEvent = exports.TurnEvent = exports.MachineEvent = exports.ProductionStudentEvent = exports.HireStudentEvent = exports.GameEvent = exports.EventType = void 0;
var EventType;
(function (EventType) {
    EventType[EventType["HIRE_FISE"] = 0] = "HIRE_FISE";
    EventType[EventType["HIRE_FISA"] = 1] = "HIRE_FISA";
    EventType[EventType["PRODUCTION_FISE"] = 2] = "PRODUCTION_FISE";
    EventType[EventType["PRODUCTION_FISA"] = 3] = "PRODUCTION_FISA";
    EventType[EventType["BUY_MACHINE"] = 4] = "BUY_MACHINE";
    EventType[EventType["UPGRADE_MACHINE"] = 5] = "UPGRADE_MACHINE";
    EventType[EventType["DESTROY_MACHINE"] = 6] = "DESTROY_MACHINE";
    EventType[EventType["GENERATE_RESOURCES"] = 7] = "GENERATE_RESOURCES";
    EventType[EventType["CALCULATE_SCORE"] = 8] = "CALCULATE_SCORE";
    EventType[EventType["GARBAGE_DESTROY"] = 9] = "GARBAGE_DESTROY";
    EventType[EventType["BUY_STAFF"] = 10] = "BUY_STAFF";
    EventType[EventType["BOUGHT_STAFF"] = 11] = "BOUGHT_STAFF";
})(EventType = exports.EventType || (exports.EventType = {}));
class GameEvent {
    constructor(type, data) {
        this.type = type;
        this.data = data;
    }
}
exports.GameEvent = GameEvent;
/*
* Utils
*/
/**
 * Convenience class for price related events
 */
class PriceEvent {
    constructor(costE, costDD) {
        this.costE = costE;
        this.costDD = costDD;
    }
}
/**
 * HIRE_FISE/HIRE_FISA date type.
 * Can increase/decrease the price of a FISE/FISA
 */
class HireStudentEvent extends PriceEvent {
    constructor(costE, costDD) {
        super(costE, costDD);
    }
}
exports.HireStudentEvent = HireStudentEvent;
/**
 * PRODUCTION_FISE/PRODUCTION_FISA date type.
 * The value that is set as E/DD is the number that
 * we will add the the basic value.
 *
 * if costE = 1, and FISE produce 1E per default, then
 * they will now produce 2E !
 */
class ProductionStudentEvent extends PriceEvent {
    /** no modifier by default **/
    constructor() {
        super(0, 0);
    }
}
exports.ProductionStudentEvent = ProductionStudentEvent;
/**
 * BUY_MACHINE/UPGRADE_MACHINE/DESTROY_MACHINE date type.
 * Returns the new price of a machine after reduction
 */
class MachineEvent extends PriceEvent {
    /**
     * Can apply a reduction on a machine
     * @param costE new price in E
     * @param costDD new price in DD
     * @param type machine type
     */
    constructor(costE, costDD, type) {
        super(costE, costDD);
        this.type = type;
    }
}
exports.MachineEvent = MachineEvent;
/**
 * GENERATE_RESOURCES data type.
 * Can reduce the number of turns required for
 * a source to produce resources.
 */
class TurnEvent {
    constructor(turn) {
        this.turn = turn;
    }
}
exports.TurnEvent = TurnEvent;
/**
 * CALCULATE_SCORE data type.
 * Can increase (most likely but can reduce) the score.
 * if set to n, then we will multiply the number
 * of resources generating the score by this number
 */
class ScoreEvent {
    constructor() {
        this.modifierScore = 1;
    }
}
exports.ScoreEvent = ScoreEvent;
/**
 * GARBAGE_DESTROY data type.
 * Here on can delete some garbage (or add)
 * generated when a resource got send to the door.
 */
class GarbageEvent {
    constructor(garbage) {
        this.garbage = garbage;
    }
}
exports.GarbageEvent = GarbageEvent;
/**
 * BUY_STAFF data type.
 * Can apply a reduction of the cost of the staff
 */
class StaffBuyEvent extends PriceEvent {
    /**
     * Can apply a reduction of the cost of the staff
     * @param costE new price in E
     * @param costDD new price in DD
     * @param idStaff a staff ID if needed
     */
    constructor(costE, costDD, idStaff) {
        super(costE, costDD);
        this.idStaff = idStaff;
    }
}
exports.StaffBuyEvent = StaffBuyEvent;
/**
 * BOUGHT_STAFF data type.
 * After a staff is bought, he can trigger a once in a lifetime
 * event.
 */
class StaffBoughtEvent {
    /**
     * Can apply a reduction of the cost of the staff
     * @param idStaff a staff ID if needed
     * @param map the map if the staff will do something with it
     */
    constructor(idStaff, map) {
        this.idStaff = idStaff;
        this.map = map;
    }
}
exports.StaffBoughtEvent = StaffBoughtEvent;
