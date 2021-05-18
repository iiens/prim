// import mappings
import {Mappings} from "./mappings";
import {Cardinal, MachineInfo, MachineStuff} from "../model/machine";

/**
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 04/04/2021
 *
 * Contains the game configuration
 *
 */
export class Config {

    static GAME_VERSION = "2.3.0";

    /**
     * Keys shortcut that are use everywhere
     */
    static keys = {
        help: Mappings.getHelpKey(),
        back: Mappings.getBackKey(),
        exit: Mappings.getExitKey(),
    };

    /**
     * Game specific values
     */
    static constants = {
        NUMBER_DD_START: 100, //!< number of DD at the start of the game
        NUMBER_E_START: 100, //!< number of E at the start of the game
        PRODUCTION_FISA_E: 4, //!< number of E produced by FISA
        PRODUCTION_FISA_DD: 4, //!< number of DD produced by FISA
        PRODUCTION_FISE_E: 1, //!< number of E produced by FISE
        NUMBER_OF_SOURCES: 2, //!< number of sources
        PRODUCTION_FISE_DD: 1, //!< number of DD produced by FISE
        NUMBER_FISE: 5,//!< number of FISE at the start of the game
        NUMBER_FISA: 5 ,//!< number of FISA at the start of the game
        COST_FISE_E: 50, //!< cost in E of FISE
        COST_FISE_DD: 20, //!< cost in DD of FISE
        COST_FISA_E: 50, //!< cost in E of FISA
        COST_FISA_DD: 20, //!< cost in DD of FISA
        NB_TURN_FISA: 2, //!< number of turns before FISA Production
        NB_TURN_PRODUCTION_SOURCE: 10, //!< number of turns before Source Production
        NB_RESOURCE_PRODUCT_BY_SOURCE: 3,  //!< number of resource produced by Source
        NUMBER_WASTE_TO_PRODUCT_RESOURCE: 10, //!< number of waste to product a resource in a recycling center
        NUMBER_RESOURCE_WIN: 10000, //!< number of resource to win
        MACHINE_DEFAULT_LVL: 1 //!< level of the machine by default
    }

    /**
     * Array with information about all machine
     */
    static machines = [
        new MachineInfo("Collector","Collecteur", MachineStuff.MS_COLLECTOR, "C",
            200, 20, 500,100,60,200,
            "Sends a resource (resp. a garbage) produced by the source (resp. the gate)" +
            " to the neighboring cell indicated by its orientation. Collector storage increases by 1 per level.",
            "Envoie une ressource produites par la source sur la case voisine indiquée par son orientation." +
            " La capacité d'un Collecteur augmente de 1 par niveau","+1 collected / level",
            "+1 collectée / niveau",
            1, "Collector Out is South by default","La sortie du collecteur est" +
            " Sud par défaut",
            true,
            (level: number) => { // return 0 when level = 1, 1 when 2 etc.
                return level - 1; // that number mean capacity = 1 + <result> on level n
            }, new Map ([
                [Cardinal.SOUTH, "../../assets/img/machines/Collecteur/MS_COLLECTOR_BOT.png"],
                [Cardinal.WEST, "../../assets/img/machines/Collecteur/MS_COLLECTOR_LEFT.png"],
                [Cardinal.NORTH, "../../assets/img/machines/Collecteur/MS_COLLECTOR_TOP.png"],
                [Cardinal.EAST, "../../assets/img/machines/Collecteur/MS_COLLECTOR_RIGHT.png"]
                ])
        ),
        new MachineInfo("Conveyor belt","Tapis roulant", MachineStuff.MS_CONVEYOR_BELT, "B",
            60,  20,  -1,   -1,  60,  200,
            "A conveyor belt has one exit and three entrances.",
            "Un tapis roulant a une sortie et trois entrées.","Do nothing", "Ne fait rien",
            Number.MAX_VALUE, "Conveyor Belt Out is South by default"," La sortie" +
            " du tapis roulant est Sud par défaut",
            false, null,
            new Map ([
                [Cardinal.SOUTH, "../../assets/img/machines/Conveyor_belt/MS_CONVEYOR_BELT_BOT.png"],
                [Cardinal.WEST, "../../assets/img/machines/Conveyor_belt/MS_CONVEYOR_BELT_LEFT.png"],
                [Cardinal.NORTH, "../../assets/img/machines/Conveyor_belt/MS_CONVEYOR_BELT_TOP.png"],
                [Cardinal.EAST, "../../assets/img/machines/Conveyor_belt/MS_CONVEYOR_BELT_RIGHT.png"]
            ])
        ),
        new MachineInfo("Cross","Croix", MachineStuff.MS_CROSS_BELT, "X",
            160, 20,  -1,   -1,  60,  200,
            "The cross has two entries and two exits, each resources/garbage is sent to the opposite exit.",
            "La croix a deux entrées et deux sorties, chaque ressource / poubelle est envoyée à la sortie opposée.",
            "","",
            Number.MAX_VALUE, "Cross Out is South and West by default"," Les sorties de la " +
            " croix sont Sud et Ouest par défaut",
            false, null,
            new Map ([
                [Cardinal.SOUTH, "../../assets/img/machines/Cross/MS_CROSS_BELT_BOT_LEFT.png"],
                [Cardinal.WEST, "../../assets/img/machines/Cross/MS_CROSS_BELT_TOP_LEFT.png"],
                [Cardinal.NORTH, "../../assets/img/machines/Cross/MS_CROSS_BELT_TOP_RIGHT.png"],
                [Cardinal.EAST, "../../assets/img/machines/Cross/MS_CROSS_BELT_BOT_RIGHT.png"]
            ])
        ),
        new MachineInfo("Recycling center","Centre de recyclage", MachineStuff.MS_RECYCLING_CENTER, "R",
            500, 40,  1500, 100, 100, 500,
            "The recycling center has 3 entrances and one exit. The center can store up to 100 garbage." +
            " 10 garbage produce 1 resource by default. Storage of Recycling center increases by 10 per level.",
            "Le centre de recyclage a 3 entrées et une sortie. Le centre peut stocker jusqu'à 100 déchets. " +
            "10 déchets produisent 1 ressource par défaut. Le stockage du centre de recyclage augmente de 10 par niveau.",
            "+10 storage / level","+10 capacité / niveau",
            100, "Recycling Center Out is South by default","La sortie du centre" +
            " de recyclage est le Sud par défaut",
            true, function (level: number) : number {
                return 10 * (level-1); // we add ten by level (aside lvl1 since that's the default)
            },
            new Map ([
                [Cardinal.SOUTH, "../../assets/img/machines/Recycling_center/MS_RECYCLING_CENTER_BOT.png"],
                [Cardinal.WEST, "../../assets/img/machines/Recycling_center/MS_RECYCLING_CENTER_LEFT.png"],
                [Cardinal.NORTH, "../../assets/img/machines/Recycling_center/MS_RECYCLING_CENTER_TOP.png"],
                [Cardinal.EAST, "../../assets/img/machines/Recycling_center/MS_RECYCLING_CENTER_RIGHT.png"]
            ])
        ),
        new MachineInfo("Junkyard","Déchetterie", MachineStuff.MS_JUNKYARD, "J",
            100, 100, 200,  600, 100, 200,
            "The junkyard  has 4 entrances and no exit. It can store up to 50 garbage." +
            "Storage of Junkyard increases by 20 per level.",
            "La déchetterie a 4 entrées et aucune sortie. Il peut stocker jusqu'à 50 déchets. " +
            "Le stockage de la déchetterie augmente de 20 par niveau.","+20 storage / level",
            "+20 capacité / niveau",
            50, "Junkyard doesn't have any Out","La déchetterie ne possède pas" +
            " de sorties par défaut",
            true, function (level: number) : number {
                return 20 * (level-1); // when level = 2, return 20 since we add 20 to the 50
            },
            new Map ([
                [Cardinal.SOUTH, "../../assets/img/machines/MS_JUNKYARD.png"],
                [Cardinal.WEST, "../../assets/img/machines/MS_JUNKYARD.png"],
                [Cardinal.NORTH, "../../assets/img/machines/MS_JUNKYARD.png"],
                [Cardinal.WEST, "../../assets/img/machines/MS_JUNKYARD.png"]
            ])
        ),
    ]

    /**
     * A function to verify if the id given in argument correspond to a machineInfo
     * @param id a machine stuff, or expected to be one
     * @return If id exist, return the tab index, If not -1
     */
    static isMachineStuffValid(id: number) : number {
        for (const machine of Config.machines) {
            if (machine.type == id) return id;
        }
        return -1;
    }

    /**
     * A function to return all the information about a machineInfo according to the id
     * @param id an id
     * @return machineInfo a machine info
     */
    static getMachineStuff(id: number | MachineStuff) : MachineInfo | null {
        for (const machine of Config.machines) {
            if (machine.type == id) return machine;
        }
        return null;
    }

}