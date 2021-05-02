import {Config} from "./utils/config";
import {Mappings} from "./utils/mappings";
import {Difficulty} from "./model/difficulty";
import {Map} from "./model/map";
import {Interface} from "./utils/interface";
import {StaffDictionary} from "./model/staffs";
import {Box, Machine} from "./model/machine";

/**
 * Game controller
 */
export class Game {

    /** game configuration **/
    public static config = Config;
    /** user mappings **/
    public static mappings = Mappings;
    /** game map **/
    public static map: Map;
    /** interface **/
    public static interface = Interface;

    /**
     * Clear any save
     */
    static clearGame(){
        // no more save
        localStorage.clear();
    }

    /**
     * @brief This function is used to initialize a game.
     * It therefore calls the necessary functions to start the interface and to create a map.
     *
     * set The starting map for a game
     *
     * @param level difficulty chosen
     */
    static initGame(level: number) {
        // create map
        this.map = new Map(Difficulty.getDifficultyByID(level));
        // save
        Game.save();
    }

    /**
     * Load the save of the map
     */
    static loadSave() {
        let save = localStorage.getItem("save");
        if (save == null) {
            console.error("no save");
            this.initGame(1); // reset
            return;
        }
        // load from save
        this.map = Map.revive(JSON.parse(save, function reviver(key, value) {
            if(typeof value === 'object' && value !== null) {
                if (value.dataType === 'StaffDictionary') {
                    return StaffDictionary.revive(value);
                }
                if (value.dataType === 'Machine') {
                    return Machine.revive(value.value);
                }
                if (value.dataType === 'Box') {
                    return Box.revive(value.value);
                }
            }
            return value;
        }));
    }

    /**
     * Save the map
     * @private
     */
    static save() {
        localStorage.setItem("save", JSON.stringify(this.map, function replacer(key, value) {
            if(value instanceof StaffDictionary) {
                return {
                    dataType: 'StaffDictionary',
                    value: Array.from(value.entries()),
                };
            } else if (value instanceof Machine) {
                return {
                    dataType: 'Machine',
                    value: value.serialize(),
                };
            } else if (value instanceof Box) {
                    return {
                        dataType: 'Box',
                        value: value.serialize(),
                    };
            } else {
                return value;
            }
        }))
    }
}