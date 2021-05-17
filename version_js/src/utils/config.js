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
    new machine_1.MachineInfo("Collector", "Collecteur", machine_1.MachineStuff.MS_COLLECTOR, "C", 200, 20, 500, 100, 60, 200, "Sends a resource (resp. a garbage) produced by the source (resp. the gate)" +
        " to the neighboring cell indicated by its orientation. Collector storage increases by 1 per level.", "Envoie une ressource produites par la source sur la case voisine indiquée par son orientation." +
        " La capacité d'un Collecteur augmente de 1 par niveau", "+1 collected / level", "+1 collectée / niveau", 1, "Collector Out is South by default", "La sortie du collecteur est" +
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
    new machine_1.MachineInfo("Recycling center", "Centre de recyclage", machine_1.MachineStuff.MS_RECYCLING_CENTER, "R", 500, 40, 1500, 100, 100, 500, "The recycling center has 3 entrances and one exit. The center can store up to 100 garbage." +
        " 10 garbage produce 1 resource by default. Storage of Recycling center increases by 10 per level.", "Le centre de recyclage a 3 entrées et une sortie. Le centre peut stocker jusqu'à 100 déchets. " +
        "10 déchets produisent 1 ressource par défaut. Le stockage du centre de recyclage augmente de 10 par niveau.", "+10 storage / level", "+10 capacité / niveau", 100, "Recycling Center Out is South by default", "La sortie du centre" +
        " de recyclage est le Sud par défaut", true, function (level) {
        return 10 * (level - 1); // we add ten by level (aside lvl1 since that's the default)
    }, new Map([
        [machine_1.Cardinal.SOUTH, "../../assets/img/machines/Recycling_center/MS_RECYCLING_CENTER_BOT.png"],
        [machine_1.Cardinal.WEST, "../../assets/img/machines/Recycling_center/MS_RECYCLING_CENTER_LEFT.png"],
        [machine_1.Cardinal.NORTH, "../../assets/img/machines/Recycling_center/MS_RECYCLING_CENTER_TOP.png"],
        [machine_1.Cardinal.EAST, "../../assets/img/machines/Recycling_center/MS_RECYCLING_CENTER_RIGHT.png"]
    ])),
    new machine_1.MachineInfo("Junkyard", "Déchetterie", machine_1.MachineStuff.MS_JUNKYARD, "J", 100, 100, 200, 600, 100, 200, "The junkyard  has 4 entrances and no exit. It can store up to 50 garbage." +
        "Storage of Junkyard increases by 20 per level.", "La déchetterie a 4 entrées et aucune sortie. Il peut stocker jusqu'à 50 déchets. " +
        "Le stockage de la déchetterie augmente de 20 par niveau.", "+20 storage / level", "+20 capacité / niveau", 50, "Junkyard doesn't have any Out", "La déchetterie ne possède pas" +
        " de sorties par défaut", true, function (level) {
        return 20 * (level - 1); // when level = 2, return 20 since we add 20 to the 50
    }, new Map([
        [machine_1.Cardinal.SOUTH, "../../assets/img/machines/MS_JUNKYARD.png"],
        [machine_1.Cardinal.WEST, "../../assets/img/machines/MS_JUNKYARD.png"],
        [machine_1.Cardinal.NORTH, "../../assets/img/machines/MS_JUNKYARD.png"],
        [machine_1.Cardinal.WEST, "../../assets/img/machines/MS_JUNKYARD.png"]
    ])),
];
