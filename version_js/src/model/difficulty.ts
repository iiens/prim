import {Logger} from "./logger";

/**
 * \author Antoine Man
 * \version 0.1
 * \date 04/03/2021
 *
 * Contains all the difficulty that the player can play.
 *
 */
export class Difficulty {
    readonly level : Level;

    constructor(level: Level) {
        this.level = level;
    }

    /**
     * A function to get difficulty according to the id
     * @param id see Level enum
     * @return Difficulty a difficulty
     */
    public static getDifficultyByID(id: number) : Difficulty {
        let logger = Logger.Instance;
        logger.debug(" Get Difficulty according to this id " + id);
        id = Number(id);
        if (id === 2) return new Difficulty(Level.MEDIUM);
        if (id === 3) return new Difficulty(Level.HARD);
        return new Difficulty(Level.EASY);
    }

    /**
     * This function get this size of the map
     * in order to create the map type
     *
     * @return number : map size
     * @see Difficulty enum
     */
    getMapSizeByDifficulty() : number {
        let logger = Logger.Instance;
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

/**
 * Contains all difficulties that the play can play.
 * Difficulties change width and height of the map.
 *
 * EASY level : 10 x 10
 * MEDIUM level : 20 x 20
 * HARD level : 30 x 30
 */
export enum Level {
    EASY = 1, //!< EASY level : 10 x 10
    MEDIUM, //!< MEDIUM level : 20 x 20
    HARD, //!< HARD level : 30 x 30
} //!< Difficulty type