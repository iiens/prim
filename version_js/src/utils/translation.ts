/**
 * Translation handler
 */
import {ErrorCode} from "./code";

export class Translation {
    /** our map of english mappings **/
    private static translations_EN: Map<TrKeys, string>;
    /** our map of french mappings **/
    private static translations_FR: Map<TrKeys, string>;
    /** our map of errors **/
    private static errors: Map<ErrorCode, string>;
    /** true if init called **/
    private static isInit = false;
    /** language of the game **/
    private static language : string;
    language = "en";

    static changeLanguage(value : string) : void{
        if(value == "en" )
            this.language = "en";
        else if (value == "fr" )
            this.language = "fr";
    }

    static getLanguage() : string{
        return this.language;
    }

    static IsEnglish() : boolean{
        return Translation.getLanguage()=="en";
    }

    static IsFrench() : boolean{
        return Translation.getLanguage()=="fr";
    }

    static get(key: TrKeys) : string | undefined {
        Translation.initTranslations();
        if(this.IsEnglish())
            return this.translations_EN.get(key);
        else
            return this.translations_FR.get(key);
    }

    /**
     * @brief Get an error message
     *
     * In order to know in detail an error returned by a function
     * we need a function to describe this error
     *
     * @param key: an error code
     * @return string, a string that describe the error
     * @see ErrorCode type
     */
    static error(key: ErrorCode) : string {
        Translation.initTranslations();
        return this.errors.get(key) ?? 'Some error occurred';
    }

    private static initTranslations() {
        if (this.isInit) return;

        if(this.IsEnglish()) {
            this.translations_EN = new Map<TrKeys, string>();
            // index.html
            this.translations_EN.set(TrKeys.INTRO_HEADER, 'Prim is a production line game. The player will have to moves resources from generators to a gate in order to close it.');
            this.translations_EN.set(TrKeys.INTRO_DESC, 'If you are wondering why are we doing that or want to know more about the lore of the game, or how do you play this game, please check out the rules area.');
            this.translations_EN.set(TrKeys.INTRO_REQUESTED_BY, 'Game requested by');
            this.translations_EN.set(TrKeys.INTRO_VERSION, 'Current version');
            this.translations_EN.set(TrKeys.INTRO_CREATE_BY, 'Made by');
            this.translations_EN.set(TrKeys.MENU_EASY, 'EASY');
            this.translations_EN.set(TrKeys.MENU_MEDIUM, 'MEDIUM');
            this.translations_EN.set(TrKeys.MENU_HARD, 'HARD');
            this.translations_EN.set(TrKeys.MENU_RULES, 'RULES');
            this.translations_EN.set(TrKeys.MENU_EXIT, 'EXIT');
        }
        else if(this.IsFrench()){
            this.translations_FR = new Map<TrKeys, string>();
            // index.html
            this.translations_FR.set(TrKeys.INTRO_HEADER, 'Prim is a production line game. The player will have to moves resources from generators to a gate in order to close it.');
            this.translations_FR.set(TrKeys.INTRO_DESC, 'If you are wondering why are we doing that or want to know more about the lore of the game, or how do you play this game, please check out the rules area.');
            this.translations_FR.set(TrKeys.INTRO_REQUESTED_BY, 'Game requested by');
            this.translations_FR.set(TrKeys.INTRO_VERSION, 'Current version');
            this.translations_FR.set(TrKeys.INTRO_CREATE_BY, 'Made by');
            this.translations_FR.set(TrKeys.MENU_EASY, 'EASY');
            this.translations_FR.set(TrKeys.MENU_MEDIUM, 'MEDIUM');
            this.translations_FR.set(TrKeys.MENU_HARD, 'HARD');
            this.translations_FR.set(TrKeys.MENU_RULES, 'RULES');
            this.translations_FR.set(TrKeys.MENU_EXIT, 'EXIT');
        }

        this.errors = new Map<ErrorCode, string>();

        this.errors.set(ErrorCode.ERROR, 'Some error occurred');
        this.errors.set(ErrorCode.ERROR_CASE_MACHINE, 'This case is a machine. Please try again.');
        this.errors.set(ErrorCode.ERROR_CASE_SOURCE, "This case is a source. Please try again.");
        this.errors.set(ErrorCode.ERROR_CASE_GATE, "This case is a gate. Please ry again.");
        this.errors.set(ErrorCode.ERROR_CASE_NOT_FOUND, "Case not found");
        this.errors.set(ErrorCode.ERROR_CASE_NOT_EMPTY, "Case not empty");
        this.errors.set(ErrorCode.ERROR_CASE_CANT_BE_UPGRADED, "Case can't be upgraded.");
        this.errors.set(ErrorCode.ERROR_CASE_CANT_BE_DESTROYED, "Case can't be destroyed.");
        this.errors.set(ErrorCode.ERROR_NOT_ENOUGH_E, "Not enough E.");
        this.errors.set(ErrorCode.ERROR_NOT_ENOUGH_DD, "Not enough DD.");
        this.errors.set(ErrorCode.ERROR_NEGATIVE_RESULT, "A value decreased instead of increasing. Invalid internal state.");
        this.errors.set(ErrorCode.ERROR_INVALID_ACTION_SEQUENCE, "Wrong actionWindow sequence!");
        this.errors.set(ErrorCode.ERROR_CASE_EMPTY, "No machine here. Please try again.");
        this.errors.set(ErrorCode.ERROR_INVALID_STAFF_NUMBER, "Invalid staff ID.");
        this.errors.set(ErrorCode.ERROR_INVALID_MACHINE_NUMBER, "Invalid machine ID.");
        this.errors.set(ErrorCode.ERROR_INVALID_ORIENTATION_NUMBER, "This is not a valid rotation number.");

        this.isInit = true;
    }

}

/**
 * All translations constants
 */
export enum TrKeys {
    INTRO_HEADER,
    INTRO_DESC,
    INTRO_REQUESTED_BY,
    INTRO_VERSION,
    INTRO_CREATE_BY,

    MENU_EASY,
    MENU_MEDIUM,
    MENU_HARD,
    MENU_RULES,
    MENU_EXIT,

    CHOICE_DIFF, //!< difficulty menu header
    SCREEN_TOO_SMALL, //!< screen too small message

    GAME_NAME, //!< name:
    GAME_TURN, //!< turn:
    GAME_E, //!< E:
    GAME_DD, //!< DD:
    GAME_FISE, //!< FISE:
    GAME_FISA, //!< FISA:
    GAME_FISA_MODE, //!< FISA MODE:
    GAME_SCORE, //!< Score:
    GAME_GARBAGE, //!< Garbage:

    ACTION_LABEL, //!< Action:
    GO_BACK_B, //!< go back message

    MACHINE_LIST_TITLE, //!< list machines header
    ML_COST_TAG, //!< cost
    ML_COST_UP_TAG, //!< cost upgrade
    ML_COST_DESTROY_TAG, //!< cost destroy

    STAFF_LIST_TITLE, //!< list staff header
    STAFF_TAG, //!< see below, part of header
    TO_TAG, //!< see below, part of header
    ON_TAG, //!< see below, part of header
    ID_TAG, //!< see below, part of header
    OWNED_TAG, //!< number of this staff
    TRANSLATION_LIST_STAFF_INDEX, //!< from when to when
    TRANSLATION_PRESS_ARROW_CHANGE_PAGE, //!< move page message

    ACTION_LIST_TITLE, //!< list actions header

    // actions
    INPUT_MACHINE_LOCATION, //!< ask Location
    INPUT_STAFF, //!< ask Staff ID
    INPUT_MACHINE, //!< ask Machine ID
    INPUT_ACTION, //!< Action help
    INPUT_ORIENTATION, //!< ask orientation

    // legend and view components
    LEGEND, //!< Legend:

    WIN, //!< win
    LOST, //!< loose
}