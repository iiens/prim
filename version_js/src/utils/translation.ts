/**
 * Translation handler
 */
import {ErrorCode} from "./code";

export class Translation {
    /** our map of english mappings **/
    private static translations_EN: Map<TrKeys, string>;
    /** our map of french mappings **/
    private static translations_FR: Map<TrKeys, string>;
    /** our map of errors_EN **/
    private static errors_EN: Map<ErrorCode, string>;
    /** our map of errors_FR **/
    private static errors_FR: Map<ErrorCode, string>;
    /** true if init called **/
    private static isInit = false;
    /** language of the game **/
    private static language : Language;

    /**
     * @brief Change the value of the language
     *
     * Function which will change the value of the language
     *
     *
     * @param lang: an enum Language
     * @return void
     */
    static setLanguage(lang : Language) : void{
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
    static getLanguage() : Language{
        return this.language;
    }

    static getEnglish() : Language{
        return Language.EN;
    }

    static getFrench() : Language{
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
    static get(key: TrKeys) : string | undefined {
        Translation.initTranslations();
        switch(this.language) {
            case Language.EN :
                return this.translations_EN.get(key);
            case Language.FR :
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
    static error(key: ErrorCode) : string {
        Translation.initTranslations();
        switch(this.language) {
            case Language.EN :
                return this.errors_EN.get(key) ?? 'Some error occurred';
            case Language.FR :
                return this.errors_FR.get(key) ?? 'Some error occurred';
        }
    }

    private static initTranslations() {
        if (this.isInit) return;

        //todo: cleanup


            this.translations_EN = new Map<TrKeys, string>();
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


            this.translations_FR = new Map<TrKeys, string>();
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


        this.errors_EN = new Map<ErrorCode, string>();

        this.errors_EN.set(ErrorCode.ERROR, 'Some error occurred');
        this.errors_EN.set(ErrorCode.ERROR_CASE_MACHINE, 'This case is a machine. Please try again.');
        this.errors_EN.set(ErrorCode.ERROR_CASE_SOURCE, "This case is a source. Please try again.");
        this.errors_EN.set(ErrorCode.ERROR_CASE_GATE, "This case is a gate. Please ry again.");
        this.errors_EN.set(ErrorCode.ERROR_CASE_NOT_FOUND, "Case not found");
        this.errors_EN.set(ErrorCode.ERROR_CASE_NOT_EMPTY, "Case not empty");
        this.errors_EN.set(ErrorCode.ERROR_CASE_CANT_BE_UPGRADED, "Case can't be upgraded.");
        this.errors_EN.set(ErrorCode.ERROR_CASE_CANT_BE_DESTROYED, "Case can't be destroyed.");
        this.errors_EN.set(ErrorCode.ERROR_NOT_ENOUGH_E, "Not enough E.");
        this.errors_EN.set(ErrorCode.ERROR_NOT_ENOUGH_DD, "Not enough DD.");
        this.errors_EN.set(ErrorCode.ERROR_NEGATIVE_RESULT, "A value decreased instead of increasing. Invalid internal state.");
        this.errors_EN.set(ErrorCode.ERROR_INVALID_ACTION_SEQUENCE, "Wrong actionWindow sequence!");
        this.errors_EN.set(ErrorCode.ERROR_CASE_EMPTY, "No machine here. Please try again.");
        this.errors_EN.set(ErrorCode.ERROR_INVALID_STAFF_NUMBER, "Invalid staff ID.");
        this.errors_EN.set(ErrorCode.ERROR_INVALID_MACHINE_NUMBER, "Invalid machine ID.");
        this.errors_EN.set(ErrorCode.ERROR_INVALID_ORIENTATION_NUMBER, "This is not a valid rotation number.");

        this.errors_FR = new Map<ErrorCode, string>();

        this.errors_FR.set(ErrorCode.ERROR, "Une erreur est survenue");
        this.errors_FR.set(ErrorCode.ERROR_CASE_MACHINE, "Cette case est une machine. Veuillez réessayer.");
        this.errors_FR.set(ErrorCode.ERROR_CASE_SOURCE, "Cette case est une source. Veuillez réessayer.");
        this.errors_FR.set(ErrorCode.ERROR_CASE_GATE, "Cette case est une porte. Veuillez réessayer.");
        this.errors_FR.set(ErrorCode.ERROR_CASE_NOT_FOUND, "Case non trouvée");
        this.errors_FR.set(ErrorCode.ERROR_CASE_NOT_EMPTY, "Case non vide");
        this.errors_FR.set(ErrorCode.ERROR_CASE_CANT_BE_UPGRADED, "La case ne peut pas être améliorée");
        this.errors_FR.set(ErrorCode.ERROR_CASE_CANT_BE_DESTROYED, "La case ne peut pas être détruite");
        this.errors_FR.set(ErrorCode.ERROR_NOT_ENOUGH_E, "Solde de E insuffisant.");
        this.errors_FR.set(ErrorCode.ERROR_NOT_ENOUGH_DD, "Solde de DD insufissant.");
        this.errors_FR.set(ErrorCode.ERROR_NEGATIVE_RESULT, "Une valeur a diminué au lieu d'augmenter. État interne non valide.");
        this.errors_FR.set(ErrorCode.ERROR_INVALID_ACTION_SEQUENCE, "Mauvaise séquence d'action de la fenêtre !");
        this.errors_FR.set(ErrorCode.ERROR_CASE_EMPTY, "Pas de machine à cet emplacement. Veuillez réessayer.");
        this.errors_FR.set(ErrorCode.ERROR_INVALID_STAFF_NUMBER, "ID de personnel invalide.");
        this.errors_FR.set(ErrorCode.ERROR_INVALID_MACHINE_NUMBER, "ID de machine invalide.");
        this.errors_FR.set(ErrorCode.ERROR_INVALID_ORIENTATION_NUMBER, "Ceci n'est pas un nombre de rotation valide.");

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
    MENU_SETTINGS,
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

    RULES_DOOR_TITLE, //!< Title
    RULES_DOOR, //!< In order to close the door.
    RULES_EXPLAIN_TITLE = 46, //!< Title
    RULES_EXPLAIN = 47, //!< What are the rules ?
    RULES_PLAY_TITLE, //!< Title
    RULES_PLAY, //!< How should I play ?

}

export enum Language {
    FR = "fr",
    EN = "en",
}