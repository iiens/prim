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
    /**
     * A function to verify if the id given in argument correspond to a machineInfo
     * @param id a machine stuff, or expected to be one
     * @return If id exist, return the tab index, If not -1
     */
    static isMachineStuffValid(id) {
        for (const machine of Config.machines) {
            if (machine.type == id)
                return id;
        }
        return -1;
    }
    /**
     * A function to return all the information about a machineInfo according to the id
     * @param id an id
     * @return machineInfo a machine info
     */
    static getMachineStuff(id) {
        for (const machine of Config.machines) {
            if (machine.type == id)
                return machine;
        }
        return null;
    }
}
exports.Config = Config;
Config.GAME_VERSION = "3.1.2";
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
    NUMBER_DD_START: 500,
    NUMBER_E_START: 500,
    PRODUCTION_FISA_E: 4,
    PRODUCTION_FISA_DD: 4,
    PRODUCTION_FISE_E: 1,
    NUMBER_OF_SOURCES: 2,
    PRODUCTION_FISE_DD: 1,
    NUMBER_FISE: 10,
    NUMBER_FISA: 10,
    COST_FISE_E: 50,
    COST_FISE_DD: 20,
    COST_FISA_E: 50,
    COST_FISA_DD: 20,
    NB_TURN_FISA: 2,
    NB_TURN_PRODUCTION_SOURCE: 10,
    NB_RESOURCE_PRODUCT_BY_SOURCE: 10,
    NUMBER_WASTE_TO_PRODUCT_RESOURCE: 10,
    NUMBER_RESOURCE_WIN: 5000,
    MACHINE_DEFAULT_LVL: 1,
    RECYCLING_RATIO: 1,
    GENERATE_GARBAGE_DOOR: 50 // x percent of generating garbage if not resources sent on the door
};
/**
 * Array with information about all machine
 */
Config.machines = [
    new machine_1.MachineInfo("Collector", "Collecteur", machine_1.MachineStuff.MS_COLLECTOR, "C", 200, 20, 1500, 300, 60, 200, "Mine a resource or a garbage and send it to a belt adjacent to the white" +
        "bar side.", "Recolte une ressource et l'envoi sur un tapis selon son orientation" +
        "indiquée par la ligne blanche.", "+1 mined / level", "+1 recoltée / niveau", 1, "Collector Out is South by default", "La sortie du collecteur est" +
        " Sud par défaut", true, (level) => {
        return level - 1; // that number mean capacity = 1 + <result> on level n
    }, new Map([
        [machine_1.Cardinal.SOUTH, "../../assets/img/machines/Collecteur/MS_COLLECTOR_BOT.png"],
        [machine_1.Cardinal.WEST, "../../assets/img/machines/Collecteur/MS_COLLECTOR_LEFT.png"],
        [machine_1.Cardinal.NORTH, "../../assets/img/machines/Collecteur/MS_COLLECTOR_TOP.png"],
        [machine_1.Cardinal.EAST, "../../assets/img/machines/Collecteur/MS_COLLECTOR_RIGHT.png"]
    ])),
    new machine_1.MachineInfo("Conveyor belt", "Tapis roulant", machine_1.MachineStuff.MS_CONVEYOR_BELT, "B", 60, 20, -1, -1, 60, 200, "A conveyor belt has one exit and three entrances.", "Un tapis roulant a une sortie et trois entrées.", "Do nothing", "Ne fait rien", Number.MAX_VALUE, "Conveyor Belt Out is South by default", " La sortie" +
        " du tapis roulant est Sud par défaut", false, null, new Map([
        [machine_1.Cardinal.SOUTH, "../../assets/img/machines/Conveyor_belt/MS_CONVEYOR_BELT_BOT.png"],
        [machine_1.Cardinal.WEST, "../../assets/img/machines/Conveyor_belt/MS_CONVEYOR_BELT_LEFT.png"],
        [machine_1.Cardinal.NORTH, "../../assets/img/machines/Conveyor_belt/MS_CONVEYOR_BELT_TOP.png"],
        [machine_1.Cardinal.EAST, "../../assets/img/machines/Conveyor_belt/MS_CONVEYOR_BELT_RIGHT.png"]
    ])),
    new machine_1.MachineInfo("Cross", "Croix", machine_1.MachineStuff.MS_CROSS_BELT, "X", 160, 20, -1, -1, 60, 200, "The cross has two entries and two exits, each resources/garbage is sent to the opposite exit.", "La croix a deux entrées et deux sorties, chaque ressource / poubelle est envoyée à la sortie opposée.", "", "", Number.MAX_VALUE, "Cross Out is South and West by default", " Les sorties de la " +
        " croix sont Sud et Ouest par défaut", false, null, new Map([
        [machine_1.Cardinal.SOUTH, "../../assets/img/machines/Cross/MS_CROSS_BELT_BOT_LEFT.png"],
        [machine_1.Cardinal.WEST, "../../assets/img/machines/Cross/MS_CROSS_BELT_TOP_LEFT.png"],
        [machine_1.Cardinal.NORTH, "../../assets/img/machines/Cross/MS_CROSS_BELT_TOP_RIGHT.png"],
        [machine_1.Cardinal.EAST, "../../assets/img/machines/Cross/MS_CROSS_BELT_BOT_RIGHT.png"]
    ])),
    new machine_1.MachineInfo("Recycling center", "Centre de recyclage", machine_1.MachineStuff.MS_RECYCLING_CENTER, "R", 500, 40, 1500, 100, 100, 500, "The recycling center has 3 entrances and one exit. It can store up to 100 garbage." +
        " 10 garbage produce 1 resource.", "Le centre de recyclage a 3 entrées et une sortie. Le centre peut stocker jusqu'à 100 déchets. " +
        "10 déchets produisent 1 ressource.", "+10 storage / level", "+10 capacité / niveau", 100, "Recycling Center Out is South by default", "La sortie du centre" +
        " de recyclage est le Sud par défaut", true, function (level) {
        return 10 * (level - 1); // we add ten by level (aside lvl1 since that's the default)
    }, new Map([
        [machine_1.Cardinal.SOUTH, "../../assets/img/machines/Recycling_center/MS_RECYCLING_CENTER_BOT.png"],
        [machine_1.Cardinal.WEST, "../../assets/img/machines/Recycling_center/MS_RECYCLING_CENTER_LEFT.png"],
        [machine_1.Cardinal.NORTH, "../../assets/img/machines/Recycling_center/MS_RECYCLING_CENTER_TOP.png"],
        [machine_1.Cardinal.EAST, "../../assets/img/machines/Recycling_center/MS_RECYCLING_CENTER_RIGHT.png"]
    ])),
    new machine_1.MachineInfo("Junkyard", "Déchetterie", machine_1.MachineStuff.MS_JUNKYARD, "J", 100, 100, 200, 600, 100, 200, "The junkyard  has 4 entrances and no exit. It can store up to 50 garbage.", "La déchetterie a 4 entrées et aucune sortie. Elle peut stocker jusqu'à 50 déchets. ", "+20 storage / level", "+20 capacité / niveau", 50, "Junkyard doesn't have any Out", "La déchetterie ne possède pas" +
        " de sorties par défaut", true, function (level) {
        return 20 * (level - 1); // when level = 2, return 20 since we add 20 to the 50
    }, new Map([
        [machine_1.Cardinal.SOUTH, "../../assets/img/machines/MS_JUNKYARD.png"],
        [machine_1.Cardinal.WEST, "../../assets/img/machines/MS_JUNKYARD.png"],
        [machine_1.Cardinal.NORTH, "../../assets/img/machines/MS_JUNKYARD.png"],
        [machine_1.Cardinal.WEST, "../../assets/img/machines/MS_JUNKYARD.png"]
    ])),
];
