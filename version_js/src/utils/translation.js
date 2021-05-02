"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.TrKeys = exports.Translation = void 0;
/**
 * Translation handler
 */
const code_1 = require("./code");
class Translation {
    static get(key) {
        Translation.initTranslations();
        return this.translations.get(key);
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
    static error(key) {
        Translation.initTranslations();
        return this.errors.get(key) ?? 'Some error occurred';
    }
    static initTranslations() {
        if (this.isInit)
            return;
        this.translations = new Map();
        // index.html
        this.translations.set(TrKeys.INTRO_HEADER, 'Prim is a production line game. The player will have to moves resources from generators to a gate in order to close it.');
        this.translations.set(TrKeys.INTRO_DESC, 'If you are wondering why are we doing that or want to know more about the lore of the game, or how do you play this game, please check out the rules area.');
        this.translations.set(TrKeys.INTRO_REQUESTED_BY, 'Game requested by');
        this.translations.set(TrKeys.INTRO_VERSION, 'Current version');
        this.translations.set(TrKeys.INTRO_CREATE_BY, 'Made by');
        this.translations.set(TrKeys.MENU_EASY, 'EASY');
        this.translations.set(TrKeys.MENU_MEDIUM, 'MEDIUM');
        this.translations.set(TrKeys.MENU_HARD, 'HARD');
        this.translations.set(TrKeys.MENU_RULES, 'RULES');
        this.translations.set(TrKeys.MENU_EXIT, 'EXIT');
        this.errors = new Map();
        this.errors.set(code_1.ErrorCode.ERROR, 'Some error occurred');
        this.errors.set(code_1.ErrorCode.ERROR_CASE_MACHINE, 'This case is a machine. Please try again.');
        this.errors.set(code_1.ErrorCode.ERROR_CASE_SOURCE, "This case is a source. Please try again.");
        this.errors.set(code_1.ErrorCode.ERROR_CASE_GATE, "This case is a gate. Please ry again.");
        this.errors.set(code_1.ErrorCode.ERROR_CASE_NOT_FOUND, "Case not found");
        this.errors.set(code_1.ErrorCode.ERROR_CASE_NOT_EMPTY, "Case not empty");
        this.errors.set(code_1.ErrorCode.ERROR_CASE_CANT_BE_UPGRADED, "Case can't be upgraded.");
        this.errors.set(code_1.ErrorCode.ERROR_CASE_CANT_BE_DESTROYED, "Case can't be destroyed.");
        this.errors.set(code_1.ErrorCode.ERROR_NOT_ENOUGH_E, "Not enough E.");
        this.errors.set(code_1.ErrorCode.ERROR_NOT_ENOUGH_DD, "Not enough DD.");
        this.errors.set(code_1.ErrorCode.ERROR_NEGATIVE_RESULT, "A value decreased instead of increasing. Invalid internal state.");
        this.errors.set(code_1.ErrorCode.ERROR_INVALID_ACTION_SEQUENCE, "Wrong actionWindow sequence!");
        this.errors.set(code_1.ErrorCode.ERROR_CASE_EMPTY, "No machine here. Please try again.");
        this.errors.set(code_1.ErrorCode.ERROR_INVALID_STAFF_NUMBER, "Invalid staff ID.");
        this.errors.set(code_1.ErrorCode.ERROR_INVALID_MACHINE_NUMBER, "Invalid machine ID.");
        this.errors.set(code_1.ErrorCode.ERROR_INVALID_ORIENTATION_NUMBER, "This is not a valid rotation number.");
        this.isInit = true;
    }
}
exports.Translation = Translation;
/** true if init called **/
Translation.isInit = false;
/**
 * All translations constants
 */
var TrKeys;
(function (TrKeys) {
    TrKeys[TrKeys["INTRO_HEADER"] = 0] = "INTRO_HEADER";
    TrKeys[TrKeys["INTRO_DESC"] = 1] = "INTRO_DESC";
    TrKeys[TrKeys["INTRO_REQUESTED_BY"] = 2] = "INTRO_REQUESTED_BY";
    TrKeys[TrKeys["INTRO_VERSION"] = 3] = "INTRO_VERSION";
    TrKeys[TrKeys["INTRO_CREATE_BY"] = 4] = "INTRO_CREATE_BY";
    TrKeys[TrKeys["MENU_EASY"] = 5] = "MENU_EASY";
    TrKeys[TrKeys["MENU_MEDIUM"] = 6] = "MENU_MEDIUM";
    TrKeys[TrKeys["MENU_HARD"] = 7] = "MENU_HARD";
    TrKeys[TrKeys["MENU_RULES"] = 8] = "MENU_RULES";
    TrKeys[TrKeys["MENU_EXIT"] = 9] = "MENU_EXIT";
    TrKeys[TrKeys["CHOICE_DIFF"] = 10] = "CHOICE_DIFF";
    TrKeys[TrKeys["SCREEN_TOO_SMALL"] = 11] = "SCREEN_TOO_SMALL";
    TrKeys[TrKeys["GAME_NAME"] = 12] = "GAME_NAME";
    TrKeys[TrKeys["GAME_TURN"] = 13] = "GAME_TURN";
    TrKeys[TrKeys["GAME_E"] = 14] = "GAME_E";
    TrKeys[TrKeys["GAME_DD"] = 15] = "GAME_DD";
    TrKeys[TrKeys["GAME_FISE"] = 16] = "GAME_FISE";
    TrKeys[TrKeys["GAME_FISA"] = 17] = "GAME_FISA";
    TrKeys[TrKeys["GAME_FISA_MODE"] = 18] = "GAME_FISA_MODE";
    TrKeys[TrKeys["GAME_SCORE"] = 19] = "GAME_SCORE";
    TrKeys[TrKeys["GAME_GARBAGE"] = 20] = "GAME_GARBAGE";
    TrKeys[TrKeys["ACTION_LABEL"] = 21] = "ACTION_LABEL";
    TrKeys[TrKeys["GO_BACK_B"] = 22] = "GO_BACK_B";
    TrKeys[TrKeys["MACHINE_LIST_TITLE"] = 23] = "MACHINE_LIST_TITLE";
    TrKeys[TrKeys["ML_COST_TAG"] = 24] = "ML_COST_TAG";
    TrKeys[TrKeys["ML_COST_UP_TAG"] = 25] = "ML_COST_UP_TAG";
    TrKeys[TrKeys["ML_COST_DESTROY_TAG"] = 26] = "ML_COST_DESTROY_TAG";
    TrKeys[TrKeys["STAFF_LIST_TITLE"] = 27] = "STAFF_LIST_TITLE";
    TrKeys[TrKeys["STAFF_TAG"] = 28] = "STAFF_TAG";
    TrKeys[TrKeys["TO_TAG"] = 29] = "TO_TAG";
    TrKeys[TrKeys["ON_TAG"] = 30] = "ON_TAG";
    TrKeys[TrKeys["ID_TAG"] = 31] = "ID_TAG";
    TrKeys[TrKeys["OWNED_TAG"] = 32] = "OWNED_TAG";
    TrKeys[TrKeys["TRANSLATION_LIST_STAFF_INDEX"] = 33] = "TRANSLATION_LIST_STAFF_INDEX";
    TrKeys[TrKeys["TRANSLATION_PRESS_ARROW_CHANGE_PAGE"] = 34] = "TRANSLATION_PRESS_ARROW_CHANGE_PAGE";
    TrKeys[TrKeys["ACTION_LIST_TITLE"] = 35] = "ACTION_LIST_TITLE";
    // actions
    TrKeys[TrKeys["INPUT_MACHINE_LOCATION"] = 36] = "INPUT_MACHINE_LOCATION";
    TrKeys[TrKeys["INPUT_STAFF"] = 37] = "INPUT_STAFF";
    TrKeys[TrKeys["INPUT_MACHINE"] = 38] = "INPUT_MACHINE";
    TrKeys[TrKeys["INPUT_ACTION"] = 39] = "INPUT_ACTION";
    TrKeys[TrKeys["INPUT_ORIENTATION"] = 40] = "INPUT_ORIENTATION";
    // legend and view components
    TrKeys[TrKeys["LEGEND"] = 41] = "LEGEND";
    TrKeys[TrKeys["WIN"] = 42] = "WIN";
    TrKeys[TrKeys["LOST"] = 43] = "LOST";
})(TrKeys = exports.TrKeys || (exports.TrKeys = {}));
