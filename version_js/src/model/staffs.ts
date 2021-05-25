/**
 * \author Ramzy ZEBRIR and Antoine MAn
 * \version 0.1
 * \date 04/03/2021
 *
 * Contains all information about the character of the Staff
 */
import {
    EventType,
    GameEvent,
    HireStudentEvent,
    MachineEvent,
    ProductionStudentEvent,
    ScoreEvent,
    StaffBoughtEvent,
    StaffBuyEvent,
    TurnEvent
} from "../utils/events";
import {Box, Cardinal, Machine, MachineInfo, MachineStuff} from "./machine";
import {Case} from "./map";
import {randomNumber} from "../utils/utilities";
import {Game} from "../game";
import {Language} from "../utils/translation";
import {Logger} from "./logger";

/**
 * Contains all information about the character of the Staff
 */
export class Staff {

    public readonly id: number; //!< id of the character
    public readonly name: string; //!< name of the character
    public readonly desc_en: string; //!< Price in E of the character in english
    public readonly desc_fr: string; //!< Price in E of the character in french


    public readonly costE: number; //!< Price in DD of the character
    public readonly costDD: number; //!< description of character effects

    /**
     * This is a function. Taking an event and a number of this staff
     * that we hired. Return back an event.
     *
     * For instance, we can modify the E or DD of a price event according to the number
     * of this staff that we hired then returns the reduced price.
     *
     * See applyEffect or events.
     */
    public effect: (event:GameEvent, count: number) => GameEvent; //!< staff effect

    public readonly levelMax: number; //!< max level

    public readonly icon: string; //!< staff icon

    constructor(id: number, name: string, desc_en : string,desc_fr: string,
                costE: number, costDD: number, effect: (event:GameEvent, count: number) => GameEvent,
                levelMax: number = 100, icon: string) {
        let logger = Logger.Instance;
        logger.debug("New Staff");
        this.id = id;
        this.name = name;
        this.levelMax = levelMax;
        this.desc_en = desc_en;
        this.desc_fr = desc_fr;
        this.costE = costE;
        this.costDD = costDD;
        this.effect = effect;
        this.icon = icon;
    }

    /**
     * From an object (serialisation), create a Staff
     * @param object a Staff serialized
     */
    static revive(object: any) : Staff {
        return new Staff(
            object.id,
            object.name,
            object.desc_en,
            object.desc_fr,
            object.costE,
            object.costDD,
            object.effect,
            object.levelMax,
            object.icon,
        );
    }

    /**
     * return the description with the correct language
     * @return description the description of a staff
     */
    get desc() : string {
        if(Game.getTranslationLanguage()==Language.EN)
            return this.desc_en;
        else if(Game.getTranslationLanguage()==Language.FR)
            return this.desc_fr;
        else
            return "ERROR TRANSLATION";
    }

}

export class StaffDictionary {
    private values : Map<Staff, number>;

    /**
     * A function to create a staff dictionary which for each staff, his id
     * and the number of staff hired
     */
    constructor() {
        this.values = new Map<Staff, number>();
    }

    set(staff: Staff){
        this.values.set(staff, 0)
    }

    /**
     * A function to get the number of staff hired according to the id staff
     * @param id a staff ID
     * @return the number of staff hired
     */
    get(id: number){
        for (const entry of this.values.entries()) {
            if (entry[0].id === id) return entry[1];
        }
        return -1;
    }

    /**
     * A function to incremente the number of a specific staff (hire)
     * @param id a staff ID
     */
    hire(id: number) {
        let staff = null;
        let count = 0;
        for (const entry of this.values.entries()) {
            if (entry[0].id === id) {
                staff = entry[0];
                count = entry[1];
            }
        }
        if (staff != null){
            this.values.set(staff, count+1)
        }
    }

    entries(): IterableIterator<[Staff, number]> {
        return this.values.entries();
    }

    /**
     * From an object (serialisation), create a StaffDictionary
     * @param object a StaffDictionary serialized
     */
    static revive(object: any) : StaffDictionary {
        let team = StaffUtils.createStaffDictionary();
        for (const entry of object.value) {
            // hire again
            for (let i = 0; i < entry[1]; i++) {
                team.hire(entry[0].id);
            }
        }
        return team;
    }

    /**
     * Call of staffs
     * @param event
     */
    applyEffect(event: GameEvent) : GameEvent {
        for (const entry of this.values.entries()) {
            let count = entry[1];
            if (count == 0) continue; // not worth our time
            let staff : Staff = entry[0];
            // tell there is an event
            staff.effect(event, count);
        }
        return event;
    }

    /**
     * Returns a staff by ID or null if not found
     * @param idStaff a staff ID
     * @return  Staff|null a staff or null
     */
    getStaff(idStaff: number) : Staff | null {
        if (idStaff < 0) return null; // optimization
        for (const entry of this.values.entries()) {
            if (entry[0].id === idStaff) {
                return entry[0];
            }
        }
        return null;
    }
}

/**
 *
 */
export class StaffUtils {

    static createStaffDictionary() : StaffDictionary {
        let staffs = new StaffDictionary();
        // create machine
        staffs.set(this.createBannour());
        staffs.set(this.createGoilard());
        staffs.set(this.createJeannas());
        staffs.set(this.createLaurent());
        staffs.set(this.createMerabet());
        // upgrade machine
        staffs.set(this.createNouleho());
        staffs.set(this.createY());
        staffs.set(this.createBourard());
        // destroy machine
        staffs.set(this.createBrunel());
        staffs.set(this.createCharantonis());
        staffs.set(this.createDubois());
        staffs.set(this.createDumbrava());
        staffs.set(this.createFaye());
        // special
        staffs.set(this.createLigozat());
        staffs.set(this.createMouilleron());
        staffs.set(this.createSzafranski());
        staffs.set(this.createThomas());
        staffs.set(this.createLejeune());
        staffs.set(this.createMathias());
        staffs.set(this.createSalhab());
        staffs.set(this.createForest());
        staffs.set(this.createLim());
        staffs.set(this.createWatel());
        staffs.set(this.createPrevel());
        return staffs;
    }

    /*
    Helpers
     */

    /**
     * Apply a machine event
     * @param event event
     * @param count and count
     * @param typeWanted we will only do a reduction on a type of machine, choose witch one MachineStuff
     * @param typeEvent a type a machine of event this function must handle (such as EventType.BUY_MACHINE)
     * @param mE number E reduced per staff
     * @param mDD number DD reduced per staff
     * @param minE number min E of the reduction
     * @param minDD number min DD of the reduction
     * @return event the modified event
     * @private
     */
    private static applyMachinePriceEvent(event: GameEvent, count: number, typeWanted: MachineStuff,
                                          typeEvent: EventType, mE: number, mDD: number, minE: number, minDD: number){
        if (count === 0 || event.type != typeEvent) return event; // nothing
        if (event.data.type !== typeWanted) return event;
        let machineEvent : MachineEvent = event.data;
        // get machine info
        machineEvent.costE = Math.max(machineEvent.costE - count * mE, minE);
        machineEvent.costDD = Math.max(machineEvent.costDD - count * mDD, minDD);
        // some effect applied here
        return event;
    }

    /**
     * Simulate max level
     * @param s machine stuff
     * @param mE price E
     * @param mDD price DD
     * @param minE minE
     * @param minDD min DD
     * @param type 1 for update, 2 for destroy or 0
     * @private
     */
    private static simulateLevelMax(s: MachineStuff, mE : number, mDD : number, minE : number, minDD : number,
                                    type: number){
        let level = 1;
        let stuff : MachineInfo = <MachineInfo>Game.config.getMachineStuff(s);
        let MsE = 0, MsDD = 0;
        // cost default
        if (type == 0){ MsE = stuff.costE; MsDD = stuff.costDD; }
        if (type == 1){ MsE = stuff.costUpgradeE; MsDD = stuff.costUpgradeDD; }
        if (type == 2){ MsE = stuff.costDestroyE; MsDD = stuff.costDestroyDD; }
        // simulate
        while (MsE - mE > minE || MsDD - mDD > minDD) {
            level++;
            MsE -= mE;
            MsDD -= mDD;
        }
        return level;
    }

    private static simulateLevelMaxStudent(mE : number, mDD : number, minE : number,
                                           minDD : number, type: number){
        let level = 1;
        let defaultE: number, defaultDD: number;
        if (type == 0){ // fise
            defaultE = Game.config.constants.COST_FISE_E;
            defaultDD = Game.config.constants.COST_FISE_DD;
        } else {
            defaultE = Game.config.constants.COST_FISA_E;
            defaultDD = Game.config.constants.COST_FISA_DD;
        }
        // simulate
        while (defaultE - mE > minE || defaultDD - mDD > minDD) {
            level++;
            defaultE -= mE;
            defaultDD -= mDD;
        }
        return level;
    }

    /*
    * all staffs
    */
    private static createBannour() : Staff {
        let minE = 10;
        let minDD = 1;
        let mE = 10;
        let mDD = 1;
        return new Staff(1, "Fetia Bannour", "The cost of constructing collectors decreases by" +
            " 10EE and 1DD (min 10E and 1DD).","Le coût de construction des collecteurs diminue de "+
            " 10EE et 1DD (min 10E et 1DD).", 100, 30,
            function (event: GameEvent, count: number) : GameEvent {
                    return StaffUtils.applyMachinePriceEvent(
                        event, count, MachineStuff.MS_COLLECTOR, EventType.BUY_MACHINE, mE, mDD, minE, minDD
                     );
                },
            StaffUtils.simulateLevelMax(MachineStuff.MS_COLLECTOR, mE, mDD, minE, mDD, 0),
            "../../assets/img/staffs/bannour.png"
            )
    }

    private static createGoilard() : Staff {
        let minE = 3;
        let minDD = 1;
        let mE = 3;
        let mDD = 1;
        return new Staff(2, "Kevin Goilard", "The cost of constructing conveyor belt decreases by 3E" +
            " and 1DD (min 3EE and 1DD).", "Le coût de construction du tapis roulant diminue de 3E" +
            " et 1DD (min 3EE et 1DD).",100,  30,
            function (event: GameEvent, count: number) : GameEvent {
                return StaffUtils.applyMachinePriceEvent(
                    event, count, MachineStuff.MS_CONVEYOR_BELT, EventType.BUY_MACHINE, mE, mDD, minE, minDD
                );
            },
            StaffUtils.simulateLevelMax(MachineStuff.MS_CONVEYOR_BELT, mE, mDD, minE, mDD, 0),
            "../../assets/img/staffs/goilard.png"
            )
    }

    private static createJeannas() : Staff {
        let minE = 8;
        let minDD = 1;
        let mE = 8;
        let mDD = 1;
        return new Staff(3, "Vincent Jeannas", "The cost of constructing cross decreases by 8E and 1DD (min 8EE " +
            "and 1DD).","Le coût de construction d'une croix diminue de 8E et 1DD (min 8EE" +
            " et 1DD).", 100, 30,
            function (event: GameEvent, count: number) : GameEvent {
                return StaffUtils.applyMachinePriceEvent(
                    event, count, MachineStuff.MS_CROSS_BELT, EventType.BUY_MACHINE, mE, mDD, minE, minDD
                );
            },
            StaffUtils.simulateLevelMax(MachineStuff.MS_CONVEYOR_BELT, mE, mDD, minE, mDD, 0),
            "../../assets/img/staffs/jeannas.png"
            )
    }

    private static createLaurent() : Staff {
        let minE = 25;
        let minDD = 2;
        let mE = 25;
        let mDD = 2;
        return new Staff(4, "Thomas Laurent", "The cost of constructing recycling center decreases by 25E and " +
            "2DD (min 25E and 2DD).","Le coût de construction du centre de recyclage diminue de 25E et" +
            " 2DD (min 25E et 2DD).",100,  30,
            function (event: GameEvent, count: number) : GameEvent {
                return StaffUtils.applyMachinePriceEvent(
                    event, count, MachineStuff.MS_RECYCLING_CENTER, EventType.BUY_MACHINE, mE, mDD, minE, minDD
                )
            },
            StaffUtils.simulateLevelMax(MachineStuff.MS_RECYCLING_CENTER, mE, mDD, minE, mDD, 0),
            "../../assets/img/staffs/laurent.png"
        )
    }

    private static createMerabet() : Staff {
        let minE = 5;
        let minDD = 5;
        let mE = 5;
        let mDD = 5;
        return new Staff(5, "Massinissa Merabet",  "The cost of constructing junkyard decreases by 5E and 5DD" +
            " (min 5E and 5DD).","Le coût de construction de la déchetterie diminue de 5E et 5DD" +
            " (min 5E et 5DD).", 100,  30,
            function (event: GameEvent, count: number) : GameEvent {
                return StaffUtils.applyMachinePriceEvent(
                    event, count, MachineStuff.MS_JUNKYARD, EventType.BUY_MACHINE, mE, mDD, minE, minDD
                );
            },
            StaffUtils.simulateLevelMax(MachineStuff.MS_JUNKYARD, mE, mDD, minE, mDD, 0),
            "../../assets/img/staffs/merabet.png"
        )
    }

    private static createNouleho() : Staff {
        let minE = 25;
        let minDD = 5;
        let mE = 25;
        let mDD = 5;
        return new Staff(6, "Stefi Nouleho", "The cost of upgrading collectors decreases by" +
            " 25E and 5DD (min 25E and 5DD).", "Le coût d'amélioration des collecteurs diminue de " +
            "25E et 5DD (min 25E et 5DD).", 200,  100,
            function (event: GameEvent, count: number) : GameEvent {
                return StaffUtils.applyMachinePriceEvent(
                    event, count, MachineStuff.MS_COLLECTOR, EventType.UPGRADE_MACHINE, mE, mDD, minE, minDD
                );
            },
            StaffUtils.simulateLevelMax(MachineStuff.MS_COLLECTOR, mE, mDD, minE, mDD, 1),
            "../../assets/img/staffs/nouleho.png"
        )
    }

    private static createY() : Staff {
        let minE = 75;
        let minDD = 5;
        let mE = 75;
        let mDD = 5;
        return new Staff(7, "Vitera Y", "The cost of upgrading recycling center " +
            "decreases by 75E and 5DD (min 75E and 5DD).","Le coût d'amélioration'du centre de recyclage" +
            " diminue de 75E et 5DD (min 75E et 5DD).", 200,  100,
            function (event: GameEvent, count: number) : GameEvent {
                return StaffUtils.applyMachinePriceEvent(
                    event, count, MachineStuff.MS_RECYCLING_CENTER, EventType.UPGRADE_MACHINE, mE, mDD, minE, minDD
                );
            },
            StaffUtils.simulateLevelMax(MachineStuff.MS_RECYCLING_CENTER, mE, mDD, minE, mDD, 1),
            "../../assets/img/staffs/y.png"
        )
    }

    private static createBourard() : Staff {
        let minE = 10;
        let minDD = 30;
        let mE = 10;
        let mDD = 30;
        return new Staff(8, "Laurence Bourard", "The cost of upgrading junkyard decreases " +
            "by 10E and 30DD (min 20E and 30DD).", "Le coût d'améliration de la déchetterie' diminue "+
            " par 10E et 30DD (min 20E et 30DD).",200,  100,
            function (event: GameEvent, count: number) : GameEvent {
                return StaffUtils.applyMachinePriceEvent(
                    event, count, MachineStuff.MS_JUNKYARD, EventType.UPGRADE_MACHINE, mE, mDD, minE, minDD
                );
            },
            StaffUtils.simulateLevelMax(MachineStuff.MS_JUNKYARD, mE, mDD, minE, mDD, 1),
            "../../assets/img/staffs/bourard.png"
        )
    }

    private static createBrunel() : Staff {
        let minE = 3;
        let minDD = 10;
        let mE = 3;
        let mDD = 10;
        return new Staff(9, "Nicolas Brunel", "The cost of destroying collectors " +
            "decreases by 3E and 10DD (min 3E and 10DD).","Le coût de la destruction des collecteurs" +
            " diminue de 3E et 10DD (min 3E et 10DD).", 100,  200,
            function (event: GameEvent, count: number) : GameEvent {
                return StaffUtils.applyMachinePriceEvent(
                    event, count, MachineStuff.MS_COLLECTOR, EventType.DESTROY_MACHINE, mE, mDD, minE, minDD
                );
            },
            StaffUtils.simulateLevelMax(MachineStuff.MS_COLLECTOR, mE, mDD, minE, mDD, 2),
            "../../assets/img/staffs/brunel.png"
        )
    }

    private static createCharantonis() : Staff {
        let minE = 3;
        let minDD = 10;
        let mE = 3;
        let mDD = 10;
        return new Staff(10, "Anastase Charantonis", "The cost of destroying conveyor belt decreases" +
            " by 3E and 10DD (min 3E and 10DD).", "Le coût de destruction du tapis roulant diminue " +
            " par 3E et 10DD (min 3E et 10DD).", 100,  200,
            function (event: GameEvent, count: number) : GameEvent {
                return StaffUtils.applyMachinePriceEvent(
                    event, count, MachineStuff.MS_CONVEYOR_BELT, EventType.DESTROY_MACHINE, mE, mDD, minE, minDD
                );
            },
            StaffUtils.simulateLevelMax(MachineStuff.MS_CONVEYOR_BELT, mE, mDD, minE, mDD, 2),
            "../../assets/img/staffs/charantonis.png"
        )
    }

    private static createDubois() : Staff {
        let minE = 3;
        let minDD = 10;
        let mE = 3;
        let mDD = 10;
        return new Staff(11, "Catherine Dubois", "The cost of destroying cross decreases" +
            " by 3E and 10DD (min 3E and 10DD).", "Le coût de destruction des croix diminue " +
            " par 3E et 10DD (min 3E et 10DD).", 100,  200,
            function (event: GameEvent, count: number) : GameEvent {
                return StaffUtils.applyMachinePriceEvent(
                    event, count, MachineStuff.MS_CROSS_BELT, EventType.DESTROY_MACHINE, mE, mDD, minE, minDD
                );
            },
            StaffUtils.simulateLevelMax(MachineStuff.MS_CROSS_BELT, mE, mDD, minE, mDD, 2),
            "../../assets/img/staffs/dubois.png"
        )
    }

    private static createDumbrava() : Staff {
        let minE = 5;
        let minDD = 25;
        let mE = 5;
        let mDD = 25;
        return new Staff(12, "Stefania Dumbrava", "The cost of destroying recycling center decreases" +
            " by 5E and 25DD (min 5E and 25DD).","Le coût de destruction du centre de recyclage diminue " +
            " par 5E et 25DD (min 5E et 25DD).", 100,  200,
            function (event: GameEvent, count: number) : GameEvent {
                return StaffUtils.applyMachinePriceEvent(
                    event, count, MachineStuff.MS_RECYCLING_CENTER, EventType.DESTROY_MACHINE, mE, mDD, minE, minDD
                );
            },
            StaffUtils.simulateLevelMax(MachineStuff.MS_RECYCLING_CENTER, mE, mDD, minE, mDD, 2),
            "../../assets/img/staffs/dumbrava.png"
        )
    }

    private static createFaye() : Staff {
        let minE = 5;
        let minDD = 10;
        let mE = 5;
        let mDD = 10;
        return new Staff(13, "Alain Faye", "The cost of destroying junkyard decreases by 5E" +
            " and 10DD (min 5E and 10DD).","Le coût de destruction des déchetteries diminue de 5E et" +
            " 10DD (min 5E et 10DD).", 100,  200,
            function (event: GameEvent, count: number) : GameEvent {
                return StaffUtils.applyMachinePriceEvent(
                    event, count, MachineStuff.MS_JUNKYARD, EventType.DESTROY_MACHINE, mE, mDD, minE, minDD
                );
            },
            StaffUtils.simulateLevelMax(MachineStuff.MS_JUNKYARD, mE, mDD, minE, mDD, 2),
            "../../assets/img/staffs/faye.png"
        )
    }

    private static createLigozat() : Staff {
        return new Staff(14, "Anne-Laure Ligozat", "Half garbage of each case are remove",
            "La moitié des déchets de chaque case disparaissent",
            1000, 10,
            function (event: GameEvent, count: number) : GameEvent {
                    if (count !== 0 && event.type === EventType.BOUGHT_STAFF){
                        let staffBuyEvent : StaffBoughtEvent = event.data;
                        if( staffBuyEvent.idStaff === 14 ) { // buy Ligozat
                            let map = staffBuyEvent.map;
                            let coefficient = 50; // 50%

                            // Browse the map to remove half of the garbage
                            let c : Case;
                            let numberG, div;
                            for (let i = 0; i < map.getWidth; ++i) {
                                for (let j = 0; j < map.getHeight; ++j) {
                                    // Case recovery
                                    let box : Box | null;
                                    c = <Case>map.getCase(i, j);

                                    // Checking the presence of a box
                                    if (c.hasBox()) {
                                        // Recovery of the box
                                        box = c.getBox();
                                        numberG = box.numberGarbage;

                                        // Application of the coefficient
                                        div = Math.round((numberG * coefficient) / 100);

                                        box.addGarbage(div * -1);
                                    } else if (c.isMachine) { // Checking for the presence of a machine
                                        // Machine recovery
                                        let machine : Machine = c.getMachine();

                                        // Checking for the presence of boxes on the Cardinals
                                        for (let card : Cardinal = 0; card < Machine.NUMBER_CARDINAL; ++card) {
                                            box = machine.getBox(card);
                                            if (box != null) {
                                                // Recovery of the box
                                                numberG = box.numberGarbage;

                                                // Application of the coefficient
                                                div = Math.round((numberG * coefficient) / 100);

                                                box.addGarbage(div * -1);
                                            }
                                        }
                                    }
                                }
                            }


                        }
                    }
                    return event;
            }, 1,
            "../../assets/img/staffs/ligozat.png"
        )
    }

    private static createMouilleron() : Staff {
        return new Staff(15, "Christophe Mouilleron", "School hire 20 FISE and 10 FISA",
            "L’école recrute 20 FISE et 10 FISA.",
            1000, 400,function (event: GameEvent, count: number) : GameEvent {
                if (count !== 0 && event.type === EventType.BOUGHT_STAFF){
                    let staffBuyEvent : StaffBoughtEvent = event.data;
                    if( staffBuyEvent.idStaff === 15 ) { // buy Mouilleron
                        staffBuyEvent.map.addFISE(20)
                        staffBuyEvent.map.addFISA(10)
                    }
                }
                return event;
            }, 1,
            "../../assets/img/staffs/mouilleron.png"
        )
    }

    private static createSzafranski() : Staff {
        return new Staff(16, "Marie Szafranski", "When a resource is send at the gate it count is doubled" +
            " but the number of garbage is the same.",
            "A chaque fois qu’une ressource est envoyée à la porte, elle compte double. Le " +
            "nombre de déchet produit est toujours le même.",
            1000, 400,function (event: GameEvent, count: number) : GameEvent {
                if (count !== 0 && event.type === EventType.CALCULATE_SCORE){
                    let scoreEvent : ScoreEvent = event.data;
                    scoreEvent.modifierScore = 2; // multiplier is now two
                }
                return event;
            }, 1,
            "../../assets/img/staffs/szafranski.png"
        )
    }

    private static createThomas() : Staff {
        return new Staff(17, "Gael Thomas", "When a garbage leave the door it has a one "+
        "in 10 chance of disappearing. Effect is not cumulable, but for each staff bough we roll the dice " +
            "one more time.","Quand un déchet quitte la porte, il a une chance sur 10 de disparaître.",
            1000, 400,function (event: GameEvent, numberThomas: number) : GameEvent {
                if (numberThomas !== 0 && event.type === EventType.GARBAGE_DESTROY){
                    let modifierThomas = 10;
                    // Taking into account Gaël Thomas
                    for (let k = 0; k < event.data.garbage; ++k) {
                        for (let l = 0; l < numberThomas; ++l) {
                            // Roll the dice
                            let deVal = randomNumber(0, modifierThomas-1);

                            // Checking the die value
                            if (deVal == 0) {
                                event.data.garbage--;
                                break;
                            }
                        }
                    }
                }
                return event;
            }, 10,
            "../../assets/img/staffs/thomas.png"
        )
    }

    private static createLejeune() : Staff {
        return new Staff(18, "Eric Lejeune", "The cost of FISE decreases by 5E and 2DD"+
        " (min 5E and 2DD)","Le coût des FISE diminue de 5E et 2DD (minimum 5E et 2DD).",
            1000, 200,function (event: GameEvent, count: number) : GameEvent {
                if (count !== 0 && event.type === EventType.HIRE_FISE){
                    let studentCost : HireStudentEvent = event.data;
                    studentCost.costE = Math.max(studentCost.costE - count * 5, 5)
                    studentCost.costDD = Math.max(studentCost.costDD - count * 2, 2)
                }
                return event;
            }, StaffUtils.simulateLevelMaxStudent(5,2,5,2, 0),
            "../../assets/img/staffs/lejeune.png"
        )
    }

    private static createMathias() : Staff {
        return new Staff(19, "Christine Mathias", "The cost of FISA decreases by 5E and 2DD"+
        " (min 5E and 2DD)","Le coût des FISA diminue de 5E et 2DD (minimum 5E et 2DD).",
            1000, 200,function (event: GameEvent, count: number) : GameEvent {
                if (count !== 0 && event.type === EventType.HIRE_FISA){
                    let studentCost : HireStudentEvent = event.data;
                    studentCost.costE = Math.max(studentCost.costE - count * 5, 5)
                    studentCost.costDD = Math.max(studentCost.costDD - count * 2, 2)
                }
                return event;
            } , StaffUtils.simulateLevelMaxStudent(5,2,5,2, 1),
            "../../assets/img/staffs/mathias.png"
        )
    }

    private static createSalhab() : Staff {
        return new Staff(20, "Katrin Salhab", "The cost of staff"+
        " decreases by 50E and 20DD (min 10E and 10DD) ",
            "Les membres du personnel coûtent 50E et 20DD de moins (minimum 10E et " +
            "10DD).",
            1500, 300,function (event: GameEvent, count: number) : GameEvent {
                if (count !== 0 && event.type === EventType.BUY_STAFF){
                    let studentCost : StaffBuyEvent = event.data;
                    studentCost.costE = Math.max(studentCost.costE - count * 5, 5)
                    studentCost.costDD = Math.max(studentCost.costDD - count * 2, 2)
                }
                return event;
            }, 100,
            "../../assets/img/staffs/salhab.png"
        )
    }

    private static createForest() : Staff {
        return new Staff(21, "Julien Forest", "FISE produce 1E and 1DD more per turn",
            "Les FISE produisent 1E et 1DD de plus chaque tours.",
            2000, 500,function (event: GameEvent, count: number) : GameEvent {
                if (count !== 0 && event.type === EventType.PRODUCTION_FISE){
                    let productionEvent : ProductionStudentEvent = event.data;
                    productionEvent.costE += count;
                    productionEvent.costDD += count;
                }
                return event;
            }, 1,
            "../../assets/img/staffs/forest.png"
        )
    }

    private static createLim() : Staff {
        return new Staff(22, "Thomas Lim", "Turn before source production decreases by 1 (min 1 turn)",
            "Les sources mettent un tour de moins à produire (minimum 1).",
            1000, 400,function (event: GameEvent, count: number) : GameEvent {
                if (count !== 0 && event.type === EventType.GENERATE_RESOURCES){
                    let turnEvent : TurnEvent = event.data;
                    // reduce up to one
                    turnEvent.turn = Math.max(1, turnEvent.turn - count);
                }
                return event;
            } , Game.config.constants.NB_TURN_PRODUCTION_SOURCE - 1,
            "../../assets/img/staffs/lim.png"
        )
    }

    private static createWatel() : Staff {
        return new Staff(23, "Dimitri Watel", "FISA product 4E or 4DD more each 2 turns",
            "Les FISA produisent 4E ou 4DD de plus tous les deux tours.",
            2000, 500,function (event: GameEvent, count: number) : GameEvent {
                if (count !== 0 && event.type === EventType.PRODUCTION_FISA){
                    let productionEvent : ProductionStudentEvent = event.data;
                    productionEvent.costE += count * 4;
                    productionEvent.costDD += count * 4;
                }
                return event;
            }, 1,
            "../../assets/img/staffs/watel.png"
        )
    }

    private static createPrevel() : Staff {
        return new Staff(24, "Laurent Prével", "10 percent of FISA and FISE leave the school but they send a" +
            " resource to the gate.",
            "Un dixième des FISE et des FISA de l’école sont diplômés. Ils quittent l’école " +
            "mais chaque élève diplômé envoie une ressource à la porte.",
            3000, 1000,function (event: GameEvent, count: number) : GameEvent {
                if (count !== 0 && event.type === EventType.BOUGHT_STAFF){
                    let staffBuyEvent : StaffBoughtEvent = event.data;
                    if( staffBuyEvent.idStaff === 24 ) { // buy Prével
                        let map = staffBuyEvent.map;
                        let coefficient = 0.1; // 10%
                        // Retrieving the number of Fise and Fisa
                        let numberFise = map.getNumberFISE;
                        let numberFisa = map.getNumberFISA;

                        // Calculate the number of graduates
                        let fiseGraduate = Math.round(numberFise * coefficient);
                        let fisaGraduate = Math.round(numberFisa * coefficient);

                        // Check that there are enough graduates
                        if (numberFise >= fiseGraduate) {
                            if (numberFisa >= fisaGraduate) {
                                // New number of Fise and Fisa
                                map.addFISE(-fiseGraduate);
                                map.addFISA(-fisaGraduate);

                                // Send resources to the gate
                                map.sendResourcesToGate(fiseGraduate + fisaGraduate);
                            }
                        }
                    }
                }
                return event;
            }, 1,
            "../../assets/img/staffs/prevel.png"
        )
    }

}