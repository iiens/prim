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
    /**
     * @brief Init the Hashmap which contains the translations
     *
     * It inits the Hashmap which contains the translations in English and in French
     *
     */
    static initTranslations() {
        if (this.isInit)
            return;
        //English Translation
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
        this.translations_EN.set(TrKeys.RULES_EXPLAIN_TITLE, 'What are the rules ?');
        this.translations_EN.set(TrKeys.RULES_EXPLAIN, ' You will have to spend <span class="text-success">energy (E)</span> ' +
            'to buy machines while preventing your ' +
            '<span class="text-success">durable development (DD)</span> ' +
            'from reaching <span class="text-danger">0</span> (meaning the destruction ' +
            'of your world). ' +
            '<br>' +
            'Your goal will be to produce ' +
            'and send to the gate <span class="text-success" id="game-goal"></span> ' +
            'resources in order to close it. Beware ! Each resource send will produce ' +
            'a garbage that you will have to handle otherwise your DD will decrease by ' +
            '<span class="text-success" id="game-dd-malus"></span>.');
        this.translations_EN.set(TrKeys.RULES_PLAY_TITLE, 'How should I play ?');
        this.translations_EN.set(TrKeys.RULES_PLAY, 'At the start, you will have <span class="text-success"> ' +
            '            <span id="game-nb-sources">2</span> sources</span> ' +
            '            that produces <span class="text-success"> ' +
            '            <span id="game-production">3</span> ' +
            '            resources/<span id="game-turns-prod">10</span> turns</span>. ' +
            '            You will have to buy a machine called a <span class="text-success">collector</span> ' +
            '            to mine resources from a source (or garbage from the door) then send them ' +
            '            using either a <span class="text-success">conveyor belt</span> ' +
            '            or a <span class="text-success">cross belt</span>. ' +
            '            <br> ' +
            '            You can send garbage to a <span class="text-success">recycling center</span> ' +
            '            or in a <span class="text-success">junkyard</span> according to your strategy. ' +
            '            <i class="text-muted small">You ' +
            '            will have a guide in-game to see more information about each machine.</i> ' +
            '            <br> ' +
            '            <br> ' +
            '            But in order to buy a machine, you will need <span class="text-success">E</span> ' +
            '            and <span class="text-success">DD</span> ! These are produced by the student of ' +
            '            the ENSIIE, called FISE (initial training course, <span class="text-success"> ' +
            '            <span id="game-fise-e">1</span>E+<span id="game-fise-dd">1</span>DD ' +
            '            </span> ' +
            '            per turn) or FISA (part-time training course, <span class="text-success"> ' +
            '            <span id="game-fisa-e">4</span>E</span> or <span class="text-success"> ' +
            '            <span id="game-fisa-dd">4</span> ' +
            '            DD</span> per ' +
            '            <span class="text-success" id="game-fisa-turn">2</span> ' +
            '            turns). ' +
            '            <br> ' +
            '            <br> ' +
            '            If you have enough <span class="text-success">E</span> ' +
            '            and <span class="text-success">DD</span>, you can hire a Staff that can reduce ' +
            '            the cost of a machine, hire a lot of students, ... ' +
            '            <i class="text-muted small">Be sure to check out all of them in-game !</i> ');
        //game.html
        this.translations_EN.set(TrKeys.GAME_NAME, 'Game');
        this.translations_EN.set(TrKeys.GAME_TURN, 'Turn:');
        this.translations_EN.set(TrKeys.GAME_E, 'E:');
        this.translations_EN.set(TrKeys.GAME_DD, 'DD:');
        this.translations_EN.set(TrKeys.GAME_FISE, 'FISE:');
        this.translations_EN.set(TrKeys.GAME_FISA, 'FISA:');
        this.translations_EN.set(TrKeys.GAME_FISA_MODE, 'FISA MODE:');
        this.translations_EN.set(TrKeys.GAME_SCORE, 'Score:');
        this.translations_EN.set(TrKeys.GAME_GARBAGE, 'Garbage:');
        this.translations_EN.set(TrKeys.LEGEND, 'Legend');
        this.translations_EN.set(TrKeys.GAME_SOURCE, ': Source');
        this.translations_EN.set(TrKeys.GAME_GATE, ': Gate');
        this.translations_EN.set(TrKeys.GAME_CONVEYOR_BELT, ': Conveyor Belt');
        this.translations_EN.set(TrKeys.GAME_CROSS, ': Cross');
        this.translations_EN.set(TrKeys.GAME_RECYCLING_CENTER, ': Recycling center');
        this.translations_EN.set(TrKeys.GAME_JUNKYARD, ': Junkyard');
        this.translations_EN.set(TrKeys.GAME_COLLECTOR, ': Collector');
        this.translations_EN.set(TrKeys.GAME_CASE_SELECTED, 'No case selected.');
        this.translations_EN.set(TrKeys.GAME_MANAGE_STAFF, 'Manage your staff');
        this.translations_EN.set(TrKeys.GAME_COUNT_1, 'Number');
        this.translations_EN.set(TrKeys.GAME_COUNT_2, 'Number');
        this.translations_EN.set(TrKeys.GAME_UNITS, 'Units');
        this.translations_EN.set(TrKeys.GAME_EXIT, 'QUIT');
        this.translations_EN.set(TrKeys.GAME_END_TURN, 'NEXT_TURN');
        this.translations_EN.set(TrKeys.GAME_MACHINE, 'Machine');
        this.translations_EN.set(TrKeys.GAME_ROTATION, 'Orientation');
        this.translations_EN.set(TrKeys.GAME_BUY, 'Buy');
        this.translations_EN.set(TrKeys.GAME_CASE_CONTENT, 'Content');
        this.translations_EN.set(TrKeys.GAME_MACHINE_LEVEL, 'Level');
        this.translations_EN.set(TrKeys.GAME_ROTATION_NONE, 'None.');
        this.translations_EN.set(TrKeys.GAME_GATE_NAME, 'GATE');
        this.translations_EN.set(TrKeys.GAME_GATE_DESC, 'Bring resources to the door to close it. Be careful, it ' +
            'generates garbage that will lower your DD.');
        this.translations_EN.set(TrKeys.GAME_SOURCE_NAME, 'SOURCE');
        this.translations_EN.set(TrKeys.GAME_SOURCE_DESC, 'Generates resources, ' +
            '<span id="source-gen" class="text-my-yellow">1</span> every' +
            ' <span id="source-gen-turn" class="text-my-yellow">10</span> turns by default, ' +
            'harvestable with a COLLECTOR. ');
        this.translations_EN.set(TrKeys.GAME_COST, 'Cost');
        //staffs.html, menu.html, mapping.html, end.html,rules.html
        this.translations_EN.set(TrKeys.GO_BACK_B, 'Back');
        //menu.html
        this.translations_EN.set(TrKeys.MENU_TITLE, "LANGUAGE");
        this.translations_EN.set(TrKeys.MENU_LANGUAGE_EN, 'English');
        this.translations_EN.set(TrKeys.MENU_LANGUAGE_FR, 'French');
        this.translations_EN.set(TrKeys.VOLUME_TITLE, 'VOLUME');
        this.translations_EN.set(TrKeys.MUSIC_TITLE, 'MUSIC');
        this.translations_EN.set(TrKeys.MENU_GLOBAL, 'Global Settings');
        this.translations_EN.set(TrKeys.MENU_GLOBAL_SUB, 'Customize your game experience.');
        //end.html
        this.translations_EN.set(TrKeys.END_MESSAGE, 'We hope you had fun ! If you got an idea about a game that you wants to play\n' +
            '                    or an application, get in touch with us !');
        //machines.ts
        this.translations_EN.set(TrKeys.MACHINE_PRICE, 'Price:');
        this.translations_EN.set(TrKeys.MACHINE_PRICE_DESTROY, 'Price (destroy):');
        this.translations_EN.set(TrKeys.AND_WORD, 'and');
        this.translations_EN.set(TrKeys.MACHINE_ORIENTATION, 'Orientation (default):');
        this.translations_EN.set(TrKeys.MACHINE_PRICE_UPDATE, 'Price (upgrade):');
        this.translations_EN.set(TrKeys.MACHINE_CAPACITY, 'Capacity (default):');
        //staffs.ts
        this.translations_EN.set(TrKeys.STAFF_COST, 'Upgrading cost :');
        this.translations_EN.set(TrKeys.STAFF_LEVEL, 'LEVEL');
        this.translations_EN.set(TrKeys.STAFF_LEVEL_MAX, 'Level max :');
        this.translations_EN.set(TrKeys.STAFF_EFFECT, 'Current reduction is');
        //end.ts
        this.translations_EN.set(TrKeys.END_WIN, 'Victory');
        this.translations_EN.set(TrKeys.END_LOST, 'Defeat');
        //interface.ts
        this.translations_EN.set(TrKeys.TERMINAL_HELP, 'Use help to get the list of available actions');
        //French Translation
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
        this.translations_FR.set(TrKeys.RULES_DOOR_TITLE, 'Afin de fermer la porte');
        this.translations_FR.set(TrKeys.RULES_DOOR, 'Pendant que les étudiants du cursus "Calcul intensif et ' + 'données massives" ' +
            'étaient entrain d\'explorer le monde binaire, ils ont ouvert une porte entre ' +
            'notre monde et un autre monde qui ressemble trait pour trait au notre. ' +
            'Cependant, leur joie n\'a pas duré longtemps. Avoir 2 ENSIIE a fait baisser leur ' +
            'classement en développement durable car ils dépensaient deux fois ' +
            'leur consommation d\'énergie habituelle. C\'est pourquoi ' +
            '<span class="text-success">vous devez absolument fermer la porte !</span>');
        this.translations_FR.set(TrKeys.RULES_EXPLAIN_TITLE, 'Quelles sont les règles ?');
        this.translations_FR.set(TrKeys.RULES_EXPLAIN, ' Vous devrez dépenser de l\'<span class="text-success">énergie (E)</span> ' +
            'pour acheter des machines tout en empêchant votre ' +
            '<span class="text-success">développement durable(DD)</span> ' +
            'd\'atteindre <span class="text-danger">0</span> (signifiant la destruction ' +
            'de votre monde). ' +
            '<br>' +
            'Votre but sera de produire ' +
            'et envoyer à la porte <span class="text-success" id="game-goal"></span> ' +
            'ressources afin de la fermer. Faites attention ! Chaque envoi de ressource produira ' +
            'un déchet que vous devrez manipuler sinon votre DD diminuera de ' +
            '<span class="text-success" id="game-dd-malus"></span>.');
        this.translations_FR.set(TrKeys.RULES_PLAY_TITLE, 'Comment jouer ?');
        this.translations_FR.set(TrKeys.RULES_PLAY, 'Au début de la partie vous aurez <span class="text-success"> ' +
            '            <span id="game-nb-sources">2</span> sources</span> ' +
            '            qui vont produire <span class="text-success"> ' +
            '            <span id="game-production">3</span> ' +
            '            ressources/<span id="game-turns-prod">10</span> tours</span>. ' +
            '            Vous devrez acheter une machine appelée un <span class="text-success">collecteur</span> ' +
            '            pour extraire des ressources d\'une source (ou des déchets de la porte) puis les envoyer ' +
            '            en utilisant soit un <span class="text-success">tapis roulant </span> ' +
            '            soit une <span class="text-success">croix</span>. ' +
            '            <br> ' +
            '            Vous pouvez envoyer des déchets à un <span class="text-success">centre de recyclage</span> ' +
            '            ou dans une <span class="text-success">déchetterie</span> selon votre stratégie. ' +
            '            <i class="text-muted small">Vous ' +
            '            aurez un guide dans le jeu pour voir plus d\'informations sur chaque machine.</i> ' +
            '            <br> ' +
            '            <br> ' +
            '            Mais pour acheter une machine, vous aurez besoin de <span class="text-success">E</span> ' +
            '            et de <span class="text-success">DD</span> ! Ils sont produits par les étudiants ' +
            '            de l\'ENSIIE, appelés FISE (cours de formation initiale, <span class="text-success"> ' +
            '            <span id="game-fise-e">1</span>E+<span id="game-fise-dd">1</span>DD ' +
            '            </span> ' +
            '            par tour) ou FISA (cours de formation à temps partiel, <span class="text-success"> ' +
            '            <span id="game-fisa-e">4</span>E</span> ou <span class="text-success"> ' +
            '            <span id="game-fisa-dd">4</span> ' +
            '            DD</span> tout les ' +
            '            <span class="text-success" id="game-fisa-turn">2</span> ' +
            '            tours). ' +
            '            <br> ' +
            '            <br> ' +
            '            Si vous avez assez de <span class="text-success">E</span> ' +
            '            et de <span class="text-success">DD</span>, vous pouvez embaucher un personnel qui peut réduire ' +
            '            le coût d\'une machine, embaucher beaucoup d\'étudiants, ... ' +
            '            <i class="text-muted small">Assurez-vous d\'y jeter un coup d\'oeil !</i> ');
        //game.html
        this.translations_FR.set(TrKeys.GAME_NAME, 'Jeu');
        this.translations_FR.set(TrKeys.GAME_TURN, 'Tour:');
        this.translations_FR.set(TrKeys.GAME_E, 'E:');
        this.translations_FR.set(TrKeys.GAME_DD, 'DD:');
        this.translations_FR.set(TrKeys.GAME_FISE, 'FISE:');
        this.translations_FR.set(TrKeys.GAME_FISA, 'FISA:');
        this.translations_FR.set(TrKeys.GAME_FISA_MODE, 'MODE FISA:');
        this.translations_FR.set(TrKeys.GAME_SCORE, 'Score:');
        this.translations_FR.set(TrKeys.GAME_GARBAGE, 'Déchets:');
        this.translations_FR.set(TrKeys.LEGEND, 'Légende');
        this.translations_FR.set(TrKeys.GAME_SOURCE, ': Source');
        this.translations_FR.set(TrKeys.GAME_GATE, ': Porte');
        this.translations_FR.set(TrKeys.GAME_CONVEYOR_BELT, ': Tapis roulant');
        this.translations_FR.set(TrKeys.GAME_CROSS, ': Croix');
        this.translations_FR.set(TrKeys.GAME_RECYCLING_CENTER, ': Centre de recyclage');
        this.translations_FR.set(TrKeys.GAME_JUNKYARD, ': Déchetterie');
        this.translations_FR.set(TrKeys.GAME_COLLECTOR, ': Collecteur');
        this.translations_FR.set(TrKeys.GAME_CASE_SELECTED, 'Aucune case sélectionnée.');
        this.translations_FR.set(TrKeys.GAME_MANAGE_STAFF, 'Gérer votre Personnel');
        this.translations_FR.set(TrKeys.GAME_COUNT_1, 'Nombre');
        this.translations_FR.set(TrKeys.GAME_COUNT_2, 'Nombre');
        this.translations_FR.set(TrKeys.GAME_UNITS, 'Unités');
        this.translations_FR.set(TrKeys.GAME_EXIT, 'QUITTER');
        this.translations_FR.set(TrKeys.GAME_END_TURN, 'TOUR_SUIVANT');
        this.translations_FR.set(TrKeys.GAME_MACHINE, 'Machine');
        this.translations_FR.set(TrKeys.GAME_ROTATION, 'Orientation');
        this.translations_FR.set(TrKeys.GAME_BUY, 'Acheter');
        this.translations_FR.set(TrKeys.GAME_CASE_CONTENT, 'Contenu');
        this.translations_FR.set(TrKeys.GAME_MACHINE_LEVEL, 'NIVEAU');
        this.translations_FR.set(TrKeys.GAME_ROTATION_NONE, 'Aucune rotation.');
        this.translations_FR.set(TrKeys.GAME_GATE_NAME, 'PORTAIL');
        this.translations_FR.set(TrKeys.GAME_GATE_DESC, 'Amenez des ressources à la porte pour la fermer. Attention, elle' +
            ' génère des déchets qui vont baisser vos DD.');
        this.translations_FR.set(TrKeys.GAME_SOURCE_NAME, 'GÉNÉRATEUR');
        this.translations_FR.set(TrKeys.GAME_SOURCE_DESC, 'Génère des ressources, ' +
            '<span id="source-gen" class="text-my-yellow">1</span> tous les' +
            ' <span id="source-gen-turn" class="text-my-yellow">10</span> tours par défaut, ' +
            'récoltables avec un COLLECTEUR. ');
        this.translations_FR.set(TrKeys.GAME_COST, 'Coût');
        //staffs.html, menu.html, mapping.html, end.html,rules.html
        this.translations_FR.set(TrKeys.GO_BACK_B, 'Retour');
        //menu.html
        this.translations_FR.set(TrKeys.MENU_TITLE, 'LANGUE');
        this.translations_FR.set(TrKeys.MENU_LANGUAGE_EN, 'Anglais');
        this.translations_FR.set(TrKeys.MENU_LANGUAGE_FR, 'Français');
        this.translations_FR.set(TrKeys.VOLUME_TITLE, 'VOLUME');
        this.translations_FR.set(TrKeys.MUSIC_TITLE, 'MUSIQUE');
        this.translations_FR.set(TrKeys.MENU_GLOBAL, 'Paramètres généraux');
        this.translations_FR.set(TrKeys.MENU_GLOBAL_SUB, 'Personnalisez votre expérience de jeu.');
        //end.html
        this.translations_FR.set(TrKeys.END_MESSAGE, 'Nous espérons que vous vous êtes bien amusé! Si vous avez une idée d\'un jeu' +
            ' auquel vous voulez jouer ou une application, contactez-nous !');
        //machines.ts
        this.translations_FR.set(TrKeys.MACHINE_PRICE, 'Prix:');
        this.translations_FR.set(TrKeys.MACHINE_PRICE_DESTROY, 'Prix (destruction):');
        this.translations_FR.set(TrKeys.AND_WORD, 'et');
        this.translations_FR.set(TrKeys.MACHINE_ORIENTATION, 'Orientation (par défaut):');
        this.translations_FR.set(TrKeys.MACHINE_PRICE_UPDATE, 'Prix (amélioration):');
        this.translations_FR.set(TrKeys.MACHINE_CAPACITY, 'Capacité (par défaut):');
        //staffs.ts
        this.translations_FR.set(TrKeys.STAFF_COST, 'Coût d\'amélioration');
        this.translations_FR.set(TrKeys.STAFF_LEVEL, 'NIVEAU');
        this.translations_FR.set(TrKeys.STAFF_LEVEL_MAX, 'Niveau max :');
        this.translations_FR.set(TrKeys.STAFF_EFFECT, 'Réduction actuelle de');
        //end.ts
        this.translations_FR.set(TrKeys.END_WIN, 'Victoire');
        this.translations_FR.set(TrKeys.END_LOST, 'Défaite');
        //interface.ts
        this.translations_FR.set(TrKeys.TERMINAL_HELP, 'Utilisez help pour obtenir la liste des actions disponibles');
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
    TrKeys[TrKeys["GAME_NAME"] = 11] = "GAME_NAME";
    TrKeys[TrKeys["GAME_TURN"] = 12] = "GAME_TURN";
    TrKeys[TrKeys["GAME_E"] = 13] = "GAME_E";
    TrKeys[TrKeys["GAME_DD"] = 14] = "GAME_DD";
    TrKeys[TrKeys["GAME_FISE"] = 15] = "GAME_FISE";
    TrKeys[TrKeys["GAME_FISA"] = 16] = "GAME_FISA";
    TrKeys[TrKeys["GAME_FISA_MODE"] = 17] = "GAME_FISA_MODE";
    TrKeys[TrKeys["GAME_SCORE"] = 18] = "GAME_SCORE";
    TrKeys[TrKeys["GAME_GARBAGE"] = 19] = "GAME_GARBAGE";
    TrKeys[TrKeys["GAME_SOURCE"] = 20] = "GAME_SOURCE";
    TrKeys[TrKeys["GAME_GATE"] = 21] = "GAME_GATE";
    TrKeys[TrKeys["GAME_CONVEYOR_BELT"] = 22] = "GAME_CONVEYOR_BELT";
    TrKeys[TrKeys["GAME_CROSS"] = 23] = "GAME_CROSS";
    TrKeys[TrKeys["GAME_RECYCLING_CENTER"] = 24] = "GAME_RECYCLING_CENTER";
    TrKeys[TrKeys["GAME_JUNKYARD"] = 25] = "GAME_JUNKYARD";
    TrKeys[TrKeys["GAME_COLLECTOR"] = 26] = "GAME_COLLECTOR";
    TrKeys[TrKeys["GO_BACK_B"] = 27] = "GO_BACK_B";
    // legend and view components
    TrKeys[TrKeys["LEGEND"] = 28] = "LEGEND";
    TrKeys[TrKeys["END_WIN"] = 29] = "END_WIN";
    TrKeys[TrKeys["END_LOST"] = 30] = "END_LOST";
    TrKeys[TrKeys["RULES_DOOR_TITLE"] = 31] = "RULES_DOOR_TITLE";
    TrKeys[TrKeys["RULES_DOOR"] = 32] = "RULES_DOOR";
    TrKeys[TrKeys["RULES_EXPLAIN_TITLE"] = 33] = "RULES_EXPLAIN_TITLE";
    TrKeys[TrKeys["RULES_EXPLAIN"] = 34] = "RULES_EXPLAIN";
    TrKeys[TrKeys["RULES_PLAY_TITLE"] = 35] = "RULES_PLAY_TITLE";
    TrKeys[TrKeys["RULES_PLAY"] = 36] = "RULES_PLAY";
    TrKeys[TrKeys["END_MESSAGE"] = 37] = "END_MESSAGE";
    TrKeys[TrKeys["GAME_CASE_SELECTED"] = 38] = "GAME_CASE_SELECTED";
    TrKeys[TrKeys["GAME_MANAGE_STAFF"] = 39] = "GAME_MANAGE_STAFF";
    TrKeys[TrKeys["GAME_COUNT_1"] = 40] = "GAME_COUNT_1";
    TrKeys[TrKeys["GAME_COUNT_2"] = 41] = "GAME_COUNT_2";
    TrKeys[TrKeys["GAME_UNITS"] = 42] = "GAME_UNITS";
    TrKeys[TrKeys["GAME_EXIT"] = 43] = "GAME_EXIT";
    TrKeys[TrKeys["GAME_END_TURN"] = 44] = "GAME_END_TURN";
    TrKeys[TrKeys["GAME_MACHINE"] = 45] = "GAME_MACHINE";
    TrKeys[TrKeys["GAME_ROTATION"] = 46] = "GAME_ROTATION";
    TrKeys[TrKeys["GAME_BUY"] = 47] = "GAME_BUY";
    TrKeys[TrKeys["GAME_CASE_CONTENT"] = 48] = "GAME_CASE_CONTENT";
    TrKeys[TrKeys["GAME_MACHINE_LEVEL"] = 49] = "GAME_MACHINE_LEVEL";
    TrKeys[TrKeys["GAME_ROTATION_NONE"] = 50] = "GAME_ROTATION_NONE";
    TrKeys[TrKeys["GAME_GATE_NAME"] = 51] = "GAME_GATE_NAME";
    TrKeys[TrKeys["GAME_GATE_DESC"] = 52] = "GAME_GATE_DESC";
    TrKeys[TrKeys["GAME_SOURCE_NAME"] = 53] = "GAME_SOURCE_NAME";
    TrKeys[TrKeys["GAME_SOURCE_DESC"] = 54] = "GAME_SOURCE_DESC";
    TrKeys[TrKeys["GAME_COST"] = 55] = "GAME_COST";
    TrKeys[TrKeys["MENU_TITLE"] = 56] = "MENU_TITLE";
    TrKeys[TrKeys["MENU_LANGUAGE_EN"] = 57] = "MENU_LANGUAGE_EN";
    TrKeys[TrKeys["MENU_LANGUAGE_FR"] = 58] = "MENU_LANGUAGE_FR";
    TrKeys[TrKeys["MACHINE_PRICE"] = 59] = "MACHINE_PRICE";
    TrKeys[TrKeys["MACHINE_PRICE_DESTROY"] = 60] = "MACHINE_PRICE_DESTROY";
    TrKeys[TrKeys["MACHINE_ORIENTATION"] = 61] = "MACHINE_ORIENTATION";
    TrKeys[TrKeys["AND_WORD"] = 62] = "AND_WORD";
    TrKeys[TrKeys["MACHINE_PRICE_UPDATE"] = 63] = "MACHINE_PRICE_UPDATE";
    TrKeys[TrKeys["MACHINE_CAPACITY"] = 64] = "MACHINE_CAPACITY";
    TrKeys[TrKeys["STAFF_COST"] = 65] = "STAFF_COST";
    TrKeys[TrKeys["STAFF_LEVEL"] = 66] = "STAFF_LEVEL";
    TrKeys[TrKeys["STAFF_LEVEL_MAX"] = 67] = "STAFF_LEVEL_MAX";
    TrKeys[TrKeys["STAFF_EFFECT"] = 68] = "STAFF_EFFECT";
    TrKeys[TrKeys["TERMINAL_HELP"] = 69] = "TERMINAL_HELP";
    TrKeys[TrKeys["VOLUME_TITLE"] = 70] = "VOLUME_TITLE";
    TrKeys[TrKeys["MUSIC_TITLE"] = 71] = "MUSIC_TITLE";
    TrKeys[TrKeys["MENU_GLOBAL"] = 72] = "MENU_GLOBAL";
    TrKeys[TrKeys["MENU_GLOBAL_SUB"] = 73] = "MENU_GLOBAL_SUB";
})(TrKeys = exports.TrKeys || (exports.TrKeys = {}));
var Language;
(function (Language) {
    Language["FR"] = "fr";
    Language["EN"] = "en";
})(Language = exports.Language || (exports.Language = {}));
