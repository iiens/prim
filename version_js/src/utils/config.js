"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Config = void 0;
// import mappings
const mappings_1 = require("./mappings");
const machine_1 = require("../model/machine");
/**
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 04/04/2021
 *
 * Contains the game configuration
 *
 */
class Config {
}
exports.Config = Config;
Config.GAME_VERSION = "2.3.0";
/**
 * Keys shortcut that are use everywhere
 */
Config.keys = {
    help: mappings_1.Mappings.getHelpKey(),
    back: mappings_1.Mappings.getBackKey(),
    exit: mappings_1.Mappings.getExitKey(),
};
/**
 * Game specific values
 */
Config.constants = {
    NUMBER_DD_START: 100,
    NUMBER_E_START: 100,
    PRODUCTION_FISA_E: 4,
    PRODUCTION_FISA_DD: 4,
    PRODUCTION_FISE_E: 1,
    NUMBER_OF_SOURCES: 2,
    PRODUCTION_FISE_DD: 1,
    NUMBER_FISE: 5,
    NUMBER_FISA: 5,
    COST_FISE_E: 50,
    COST_FISE_DD: 20,
    COST_FISA_E: 50,
    COST_FISA_DD: 20,
    NB_TURN_FISA: 2,
    NB_TURN_PRODUCTION_SOURCE: 10,
    NB_RESOURCE_PRODUCT_BY_SOURCE: 3,
    NUMBER_WASTE_TO_PRODUCT_RESOURCE: 10,
    NUMBER_RESOURCE_WIN: 10000,
    MACHINE_DEFAULT_LVL: 1 //!< level of the machine by default
};
/**
 * Array with information about all machine
 */
Config.machines = [
    new machine_1.MachineInfo("Collector", machine_1.MachineStuff.MS_COLLECTOR, "C", 200, 20, 500, 100, 60, 200, "Sends a resource (resp. a garbage) produced by the source (resp. the gate)" +
        " to the neighboring cell indicated by its orientation. Collector storage increases by 1 per level.", 1, "Collector Out is South by default", true, (level) => {
        return level - 1; // that number mean capacity = 1 + <result> on level n
    }),
    new machine_1.MachineInfo("Conveyor belt", machine_1.MachineStuff.MS_CONVEYOR_BELT, "B", 60, 20, -1, -1, 60, 200, "A conveyor belt has one exit and three entrances.", Number.MAX_VALUE, "Conveyor Belt Out is South by default", false, null),
    new machine_1.MachineInfo("Cross", machine_1.MachineStuff.MS_CROSS_BELT, "X", 160, 20, -1, -1, 60, 200, "The cross has two entries and two exits, each resources/garbage is sent to the opposite exit.", Number.MAX_VALUE, "Cross Out is South and West by default", false, null),
    new machine_1.MachineInfo("Recycling center", machine_1.MachineStuff.MS_RECYCLING_CENTER, "R", 500, 40, 1500, 100, 100, 500, "The recycling center has 3 entrances and one exit. The center can store up to 100 garbage." +
        " 10 garbage produce 1 resource by default. Storage of Recycling center increases by 10 per level.", 100, "Recycling Center Out is South by default", true, function (level) {
        return 10 * (level - 1); // we add ten by level (aside lvl1 since that's the default)
    }),
    new machine_1.MachineInfo("Junkyard", machine_1.MachineStuff.MS_JUNKYARD, "J", 100, 100, 200, 600, 100, 200, "The junkyard  has 4 entrances and no exit. It can store up to 50 garbage." +
        "Storage of Junkyard increases by 20 per level.", 50, "Junkyard doesn't have any Out", true, function (level) {
        return 20 * (level - 1); // when level = 2, return 20 since we are 20 to the 50
    }),
];
