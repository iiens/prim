"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Level = exports.Difficulty = void 0;
const logger_1 = require("./logger");
/**
 * \author Antoine Man
 * \version 0.1
 * \date 04/03/2021
 *
 * Contains all the difficulty that the player can play.
 *
 */
class Difficulty {
    constructor(level) {
        this.level = level;
    }
    /**
     * A function to get difficulty according to the id
     * @param id see Level enum
     * @return Difficulty a difficulty
     */
    static getDifficultyByID(id) {
        let logger = logger_1.Logger.Instance;
        logger.debug(" Get Difficulty according to this id " + id);
        id = Number(id);
        if (id === 2)
            return new Difficulty(Level.MEDIUM);
        if (id === 3)
            return new Difficulty(Level.HARD);
        return new Difficulty(Level.EASY);
    }
    /**
     * This function get this size of the map
     * in order to create the map type
     *
     * @return number : map size
     * @see Difficulty enum
     */
    getMapSizeByDifficulty() {
        let logger = logger_1.Logger.Instance;
        logger.debug(" Get Size map according to this level " + this.level);
        switch (this.level) { // NOLINT(hicpp-multiway-paths-covered)
            case Level.EASY:
                return 10;
            case Level.MEDIUM:
                return 20;
            case Level.HARD:
                return 30;
        }
        return -1;
    }
}
exports.Difficulty = Difficulty;
/**
 * Contains all difficulties that the play can play.
 * Difficulties change width and height of the map.
 *
 * EASY level : 10 x 10
 * MEDIUM level : 20 x 20
 * HARD level : 30 x 30
 */
var Level;
(function (Level) {
    Level[Level["EASY"] = 1] = "EASY";
    Level[Level["MEDIUM"] = 2] = "MEDIUM";
    Level[Level["HARD"] = 3] = "HARD";
})(Level = exports.Level || (exports.Level = {})); //!< Difficulty type
