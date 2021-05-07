"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Language = exports.TrKeys = exports.Translation = void 0;
/**
 * Translation handler
 */
const code_1 = require("./code");
class Translation {
    /**
     * @brief Change the value of the language
     *
     * Function which will change the value of the language
     *
     *
     * @param lang: an enum Language
     * @return void
     */
    static setLanguage(lang) {
        this.language = lang;
    }
    /**
     * @brief Get the current language of the game
     *
     * Function which will return the current language of the game
     *
     *
     * @return Language : the current language
     */
    static getLanguage() {
        return this.language;
    }
    static getEnglish() {
        return Language.EN;
    }
    static getFrench() {
        return Language.FR;
    }
    /**
     * @brief Get the value of the key
     *
     * Get the value of the key in the Hashmap
     * of the correct language
     *
     * @param key: a key
     * @return string, correspond to the value
     */
    static get(key) {
        Translation.initTranslations();
        switch (this.language) {
            case Language.EN:
                return this.translations_EN.get(key);
            case Language.FR:
                return this.translations_FR.get(key);
        }
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
        switch (this.language) {
            case Language.EN:
                return this.errors_EN.get(key) ?? 'Some error occurred';
            case Language.FR:
                return this.errors_FR.get(key) ?? 'Some error occurred';
        }
    }
    static initTranslations() {
        if (this.isInit)
            return;
        //todo: cleanup
        this.translations_EN = new Map();
        // index.html
        this.translations_EN.set(TrKeys.INTRO_HEADER, 'Prim is a production line game. The player ' +
            'will have to moves resources from generators to a gate in order to close it.');
        this.translations_EN.set(TrKeys.INTRO_DESC, 'If you are wondering why are we doing that or want to know more about the lore of the game, or how do you play this game, please check out the rules area.');
        this.translations_EN.set(TrKeys.INTRO_REQUESTED_BY, 'Game requested by');
        this.translations_EN.set(TrKeys.INTRO_VERSION, 'Current version');
        this.translations_EN.set(TrKeys.INTRO_CREATE_BY, 'Made by');
        this.translations_EN.set(TrKeys.MENU_EASY, 'EASY');
        this.translations_EN.set(TrKeys.MENU_MEDIUM, 'MEDIUM');
        this.translations_EN.set(TrKeys.MENU_HARD, 'HARD');
        this.translations_EN.set(TrKeys.MENU_RULES, 'RULES');
        this.translations_EN.set(TrKeys.MENU_SETTINGS, 'SETTINGS');
        this.translations_EN.set(TrKeys.MENU_EXIT, 'EXIT');
        //rules.html
        this.translations_EN.set(TrKeys.RULES_DOOR_TITLE, 'In order to close the door');
        this.translations_EN.set(TrKeys.RULES_DOOR, 'While the students from the "Calcul intensif et ' +
            'données massives" cursus ' +
            'of ENSIIE were exploring the binary world, they have opened a gate between ' +
            'our world and another one looking exactly like ours.' +
            'However, their joy didn\'t last long. Having 2 ENSIIE made their ' +
            'ranking in durable development decrease because their were spending twice ' +
            'their usual consommation of energy. That\'s why ' +
            '<span class="text-success">you absolutely need to close the door !</span>');
        //this.translations_EN.set(TrKeys.RULES_EXPLAIN_TITLE, '')
        this.translations_FR = new Map();
        // index.html
        this.translations_FR.set(TrKeys.INTRO_HEADER, 'Prim est un jeu de ligne de production. Le joueur devra déplacer les ressources des générateurs vers une porte afin de la fermer.');
        this.translations_FR.set(TrKeys.INTRO_DESC, 'Si vous vous demandez pourquoi nous faisons cela ou si vous voulez en apprendre plus sur l\'histoire de ce jeu, ' +
            'ou tout simplement apprendre comment jouer, veuillez consulter le menu des Règles');
        this.translations_FR.set(TrKeys.INTRO_REQUESTED_BY, 'Jeu demandé par');
        this.translations_FR.set(TrKeys.INTRO_VERSION, 'Version actuelle');
        this.translations_FR.set(TrKeys.INTRO_CREATE_BY, 'Fait par');
        this.translations_FR.set(TrKeys.MENU_EASY, 'FACILE');
        this.translations_FR.set(TrKeys.MENU_MEDIUM, 'NORMAL');
        this.translations_FR.set(TrKeys.MENU_HARD, 'DIFFICILE');
        this.translations_FR.set(TrKeys.MENU_RULES, 'REGLES');
        this.translations_FR.set(TrKeys.MENU_SETTINGS, 'PARAMETRES');
        this.translations_FR.set(TrKeys.MENU_EXIT, 'QUITTER');
        // rules.html
        this.translations_FR.set(TrKeys.RULES_DOOR_TITLE, 'REGLES');
        this.translations_FR.set(TrKeys.RULES_DOOR, 'REGLES');
        this.errors_EN = new Map();
        this.errors_EN.set(code_1.ErrorCode.ERROR, 'Some error occurred');
        this.errors_EN.set(code_1.ErrorCode.ERROR_CASE_MACHINE, 'This case is a machine. Please try again.');
        this.errors_EN.set(code_1.ErrorCode.ERROR_CASE_SOURCE, "This case is a source. Please try again.");
        this.errors_EN.set(code_1.ErrorCode.ERROR_CASE_GATE, "This case is a gate. Please ry again.");
        this.errors_EN.set(code_1.ErrorCode.ERROR_CASE_NOT_FOUND, "Case not found");
        this.errors_EN.set(code_1.ErrorCode.ERROR_CASE_NOT_EMPTY, "Case not empty");
        this.errors_EN.set(code_1.ErrorCode.ERROR_CASE_CANT_BE_UPGRADED, "Case can't be upgraded.");
        this.errors_EN.set(code_1.ErrorCode.ERROR_CASE_CANT_BE_DESTROYED, "Case can't be destroyed.");
        this.errors_EN.set(code_1.ErrorCode.ERROR_NOT_ENOUGH_E, "Not enough E.");
        this.errors_EN.set(code_1.ErrorCode.ERROR_NOT_ENOUGH_DD, "Not enough DD.");
        this.errors_EN.set(code_1.ErrorCode.ERROR_NEGATIVE_RESULT, "A value decreased instead of increasing. Invalid internal state.");
        this.errors_EN.set(code_1.ErrorCode.ERROR_INVALID_ACTION_SEQUENCE, "Wrong actionWindow sequence!");
        this.errors_EN.set(code_1.ErrorCode.ERROR_CASE_EMPTY, "No machine here. Please try again.");
        this.errors_EN.set(code_1.ErrorCode.ERROR_INVALID_STAFF_NUMBER, "Invalid staff ID.");
        this.errors_EN.set(code_1.ErrorCode.ERROR_INVALID_MACHINE_NUMBER, "Invalid machine ID.");
        this.errors_EN.set(code_1.ErrorCode.ERROR_INVALID_ORIENTATION_NUMBER, "This is not a valid rotation number.");
        this.errors_FR = new Map();
        this.errors_FR.set(code_1.ErrorCode.ERROR, "Une erreur est survenue");
        this.errors_FR.set(code_1.ErrorCode.ERROR_CASE_MACHINE, "Cette case est une machine. Veuillez réessayer.");
        this.errors_FR.set(code_1.ErrorCode.ERROR_CASE_SOURCE, "Cette case est une source. Veuillez réessayer.");
        this.errors_FR.set(code_1.ErrorCode.ERROR_CASE_GATE, "Cette case est une porte. Veuillez réessayer.");
        this.errors_FR.set(code_1.ErrorCode.ERROR_CASE_NOT_FOUND, "Case non trouvée");
        this.errors_FR.set(code_1.ErrorCode.ERROR_CASE_NOT_EMPTY, "Case non vide");
        this.errors_FR.set(code_1.ErrorCode.ERROR_CASE_CANT_BE_UPGRADED, "La case ne peut pas être améliorée");
        this.errors_FR.set(code_1.ErrorCode.ERROR_CASE_CANT_BE_DESTROYED, "La case ne peut pas être détruite");
        this.errors_FR.set(code_1.ErrorCode.ERROR_NOT_ENOUGH_E, "Solde de E insuffisant.");
        this.errors_FR.set(code_1.ErrorCode.ERROR_NOT_ENOUGH_DD, "Solde de DD insufissant.");
        this.errors_FR.set(code_1.ErrorCode.ERROR_NEGATIVE_RESULT, "Une valeur a diminué au lieu d'augmenter. État interne non valide.");
        this.errors_FR.set(code_1.ErrorCode.ERROR_INVALID_ACTION_SEQUENCE, "Mauvaise séquence d'action de la fenêtre !");
        this.errors_FR.set(code_1.ErrorCode.ERROR_CASE_EMPTY, "Pas de machine à cet emplacement. Veuillez réessayer.");
        this.errors_FR.set(code_1.ErrorCode.ERROR_INVALID_STAFF_NUMBER, "ID de personnel invalide.");
        this.errors_FR.set(code_1.ErrorCode.ERROR_INVALID_MACHINE_NUMBER, "ID de machine invalide.");
        this.errors_FR.set(code_1.ErrorCode.ERROR_INVALID_ORIENTATION_NUMBER, "Ceci n'est pas un nombre de rotation valide.");
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
    TrKeys[TrKeys["MENU_SETTINGS"] = 9] = "MENU_SETTINGS";
    TrKeys[TrKeys["MENU_EXIT"] = 10] = "MENU_EXIT";
    TrKeys[TrKeys["CHOICE_DIFF"] = 11] = "CHOICE_DIFF";
    TrKeys[TrKeys["SCREEN_TOO_SMALL"] = 12] = "SCREEN_TOO_SMALL";
    TrKeys[TrKeys["GAME_NAME"] = 13] = "GAME_NAME";
    TrKeys[TrKeys["GAME_TURN"] = 14] = "GAME_TURN";
    TrKeys[TrKeys["GAME_E"] = 15] = "GAME_E";
    TrKeys[TrKeys["GAME_DD"] = 16] = "GAME_DD";
    TrKeys[TrKeys["GAME_FISE"] = 17] = "GAME_FISE";
    TrKeys[TrKeys["GAME_FISA"] = 18] = "GAME_FISA";
    TrKeys[TrKeys["GAME_FISA_MODE"] = 19] = "GAME_FISA_MODE";
    TrKeys[TrKeys["GAME_SCORE"] = 20] = "GAME_SCORE";
    TrKeys[TrKeys["GAME_GARBAGE"] = 21] = "GAME_GARBAGE";
    TrKeys[TrKeys["ACTION_LABEL"] = 22] = "ACTION_LABEL";
    TrKeys[TrKeys["GO_BACK_B"] = 23] = "GO_BACK_B";
    TrKeys[TrKeys["MACHINE_LIST_TITLE"] = 24] = "MACHINE_LIST_TITLE";
    TrKeys[TrKeys["ML_COST_TAG"] = 25] = "ML_COST_TAG";
    TrKeys[TrKeys["ML_COST_UP_TAG"] = 26] = "ML_COST_UP_TAG";
    TrKeys[TrKeys["ML_COST_DESTROY_TAG"] = 27] = "ML_COST_DESTROY_TAG";
    TrKeys[TrKeys["STAFF_LIST_TITLE"] = 28] = "STAFF_LIST_TITLE";
    TrKeys[TrKeys["STAFF_TAG"] = 29] = "STAFF_TAG";
    TrKeys[TrKeys["TO_TAG"] = 30] = "TO_TAG";
    TrKeys[TrKeys["ON_TAG"] = 31] = "ON_TAG";
    TrKeys[TrKeys["ID_TAG"] = 32] = "ID_TAG";
    TrKeys[TrKeys["OWNED_TAG"] = 33] = "OWNED_TAG";
    TrKeys[TrKeys["TRANSLATION_LIST_STAFF_INDEX"] = 34] = "TRANSLATION_LIST_STAFF_INDEX";
    TrKeys[TrKeys["TRANSLATION_PRESS_ARROW_CHANGE_PAGE"] = 35] = "TRANSLATION_PRESS_ARROW_CHANGE_PAGE";
    TrKeys[TrKeys["ACTION_LIST_TITLE"] = 36] = "ACTION_LIST_TITLE";
    // actions
    TrKeys[TrKeys["INPUT_MACHINE_LOCATION"] = 37] = "INPUT_MACHINE_LOCATION";
    TrKeys[TrKeys["INPUT_STAFF"] = 38] = "INPUT_STAFF";
    TrKeys[TrKeys["INPUT_MACHINE"] = 39] = "INPUT_MACHINE";
    TrKeys[TrKeys["INPUT_ACTION"] = 40] = "INPUT_ACTION";
    TrKeys[TrKeys["INPUT_ORIENTATION"] = 41] = "INPUT_ORIENTATION";
    // legend and view components
    TrKeys[TrKeys["LEGEND"] = 42] = "LEGEND";
    TrKeys[TrKeys["WIN"] = 43] = "WIN";
    TrKeys[TrKeys["LOST"] = 44] = "LOST";
    TrKeys[TrKeys["RULES_DOOR_TITLE"] = 45] = "RULES_DOOR_TITLE";
    TrKeys[TrKeys["RULES_DOOR"] = 46] = "RULES_DOOR";
    TrKeys[TrKeys["RULES_EXPLAIN_TITLE"] = 46] = "RULES_EXPLAIN_TITLE";
    TrKeys[TrKeys["RULES_EXPLAIN"] = 47] = "RULES_EXPLAIN";
    TrKeys[TrKeys["RULES_PLAY_TITLE"] = 48] = "RULES_PLAY_TITLE";
    TrKeys[TrKeys["RULES_PLAY"] = 49] = "RULES_PLAY";
})(TrKeys = exports.TrKeys || (exports.TrKeys = {}));
var Language;
(function (Language) {
    Language["FR"] = "fr";
    Language["EN"] = "en";
})(Language = exports.Language || (exports.Language = {}));
