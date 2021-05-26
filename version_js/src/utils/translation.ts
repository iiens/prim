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

    /**
     * @brief Init the Hashmap which contains the translations
     *
     * It inits the Hashmap which contains the translations in English and in French
     *
     */
    private static initTranslations() {
        if (this.isInit) return;

        // ////////////////////// //
        // English Translation
        // ////////////////////// //
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

        // rules.html
        this.translations_EN.set(TrKeys.RULES_DOOR_TITLE, 'In order to close the door');
        this.translations_EN.set(TrKeys.RULES_DOOR, 'While the students from the "Calcul intensif et ' +
            'données massives" cursus ' +
            'of ENSIIE were exploring the binary world, they have opened a gate between ' +
            'our world and another one looking exactly like ours.' +
            'However, their joy didn\'t last long. Having 2 ENSIIE made their ' +
            'ranking in durable development decrease because their were spending twice ' +
            'their usual consommation of energy. That\'s why ' +
            '<span class="text-my-yellow">you absolutely need to close the door !</span>');
        this.translations_EN.set(TrKeys.RULES_EXPLAIN_TITLE, 'What are the rules ?');
        this.translations_EN.set(TrKeys.RULES_EXPLAIN, ' You will have to spend <span class="text-my-yellow">energy (E)</span> ' +
            'to buy machines while preventing your ' +
            '<span class="text-my-yellow">durable development (DD)</span> ' +
            'from reaching <span class="text-danger">0</span> (meaning the destruction ' +
            'of your world). ' +
            '<br>' +
            'Your goal will be to produce ' +
            'and send to the gate <span class="text-my-yellow" id="game-goal"></span> ' +
            'resources in order to close it. Beware ! Each resource send will produce ' +
            'a garbage that you will have to handle otherwise your DD will decrease by ' +
            '<span class="text-my-yellow" id="game-dd-malus"></span>.');
        this.translations_EN.set(TrKeys.RULES_PLAY_TITLE, 'How should I play ?');
        this.translations_EN.set(TrKeys.RULES_PLAY, `                                   
            At the start, you will have <span class="text-my-yellow">  
            <span id="game-nb-sources">2</span> sources</span>  
            <img src="../../assets/img/legend/Resource.png" width="24" height="24" alt=" ">
            that produces <span class="text-my-yellow">  
            <span id="game-production">3</span>  
            resources
            <img src="../../assets/img/game/portal.png" width="24" height="24" alt=" ">
            per <span id="game-turns-prod">10</span> turns</span>.  
            
            
           You will have to buy a machine called a <span class="text-my-yellow">collector</span>  
           <img src="../../assets/img/legend/MS_COLLECTOR_BOT.png" width="24" height="24" alt=" ">
           to mine resources from a source (or garbage from the door) then send them  
           using either a <span class="text-my-yellow">conveyor belt</span>  
           <img src="../../assets/img/legend/MS_CONVEYOR_BELT_RIGHT.png" width="24" height="24" alt=" ">            
           or a <span class="text-my-yellow">cross belt</span>
           <img src="../../assets/img/legend/MS_CROSS_BELT_TOP_RIGHT.png" width="24" height="24" alt=" ">
           .  
           <br>         
          
          You can send garbage 
          <img src="../../assets/img/game/garbage.png" width="24" height="24" alt=" ">
          to a <span class="text-my-yellow">recycling center</span>  
          <img src="../../assets/img/legend/MS_RECYCLING_CENTER_BOT.png" width="24" height="24" alt=" ">
          or in a <span class="text-my-yellow">junkyard</span>
          <img src="../../assets/img/legend/MS_JUNKYARD.png" width="24" height="24" alt=" ">
          according to your strategy.  
          
          <i class="text-muted small">You will have a guide in-game to see more information about each machine.</i>  
          
          <br><br> 
          
          But in order to buy a machine, you will need <span class="text-my-yellow">E</span>  
          and <span class="text-my-yellow">DD</span> ! These are produced by the student of  
          the ENSIIE, called FISE (initial training course, <span class="text-my-yellow">  
          <span id="game-fise-e">1</span>E+<span id="game-fise-dd">1</span>DD  
          </span>  
          per turn) or FISA (part-time training course, <span class="text-my-yellow">  
          <span id="game-fisa-e">4</span>E</span> or <span class="text-my-yellow">  
          <span id="game-fisa-dd">4</span>  
          DD</span> per <span class="text-my-yellow" id="game-fisa-turn">2</span>  
          turns).  
                    
          <br><br>  
          
          If you have enough <span class="text-my-yellow">E</span>  
          and <span class="text-my-yellow">DD</span>, you can hire a Staff that can reduce  
          the cost of a machine, hire a lot of students, ...  
          <i class="text-muted small">Be sure to check out all of them in-game !</i>
          
          `);

        // game.html
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
        this.translations_EN.set(TrKeys.GAME_SOURCE,': Source');
        this.translations_EN.set(TrKeys.GAME_GATE,': Gate');
        this.translations_EN.set(TrKeys.GAME_CONVEYOR_BELT,': Conveyor Belt');
        this.translations_EN.set(TrKeys.GAME_CROSS,': Cross');
        this.translations_EN.set(TrKeys.GAME_RECYCLING_CENTER,': Recycling center');
        this.translations_EN.set(TrKeys.GAME_JUNKYARD,': Junkyard');
        this.translations_EN.set(TrKeys.GAME_COLLECTOR,': Collector');
        this.translations_EN.set(TrKeys.GAME_CASE_SELECTED,'No case selected.');
        this.translations_EN.set(TrKeys.GAME_MANAGE_STAFF,'Manage your staff');
        this.translations_EN.set(TrKeys.GAME_COUNT_1,'Number');
        this.translations_EN.set(TrKeys.GAME_COUNT_2,'Number');
        this.translations_EN.set(TrKeys.GAME_UNITS,'Units');
        this.translations_EN.set(TrKeys.GAME_EXIT,'QUIT');
        this.translations_EN.set(TrKeys.GAME_END_TURN,'NEXT_TURN');
        this.translations_EN.set(TrKeys.GAME_MACHINE,'Machine');
        this.translations_EN.set(TrKeys.GAME_ROTATION,'Orientation');
        this.translations_EN.set(TrKeys.GAME_BUY,'Buy');
        this.translations_EN.set(TrKeys.GAME_CASE_CONTENT,'Content');
        this.translations_EN.set(TrKeys.GAME_MACHINE_LEVEL,'Level');
        this.translations_EN.set(TrKeys.GAME_ROTATION_NONE,'None.');
        this.translations_EN.set(TrKeys.GAME_GATE_NAME,'GATE');
        this.translations_EN.set(TrKeys.GAME_GATE_DESC,'Bring resources to the door to close it. Be careful, it ' +
            'generates garbage that will lower your DD.');
        this.translations_EN.set(TrKeys.GAME_SOURCE_NAME,'SOURCE');
        this.translations_EN.set(TrKeys.GAME_SOURCE_DESC,'Generates resources, ' +
            '<span id="source-gen" class="text-my-yellow">1</span> every' +
            ' <span id="source-gen-turn" class="text-my-yellow">10</span> turns by default, ' +
            'harvestable with a COLLECTOR. ');
        this.translations_EN.set(TrKeys.GAME_COST,'Cost');
        this.translations_EN.set(TrKeys.GAME_COST_IS,'Cost is');

        // staffs.html, settings.html, mapping.html, end.html,rules.html
        this.translations_EN.set(TrKeys.GO_BACK_B,'Back');
        this.translations_EN.set(TrKeys.GO_BACK_LONG,'Go back to a previous screen.');

        // settings.html
        this.translations_EN.set(TrKeys.MENU_TITLE,"LANGUAGE");
        this.translations_EN.set(TrKeys.MENU_LANGUAGE_EN,'English');
        this.translations_EN.set(TrKeys.MENU_LANGUAGE_FR,'French');
        this.translations_EN.set(TrKeys.VOLUME_TITLE,'VOLUME');
        this.translations_EN.set(TrKeys.MUSIC_TITLE,'MUSIC');
        this.translations_EN.set(TrKeys.MENU_GLOBAL,'Global Settings');
        this.translations_EN.set(TrKeys.MENU_GLOBAL_SUB,'Customize your game experience.');
        this.translations_EN.set(TrKeys.MENU_SHORTCUTS,'Shortcuts');
        this.translations_EN.set(TrKeys.MENU_RIGHT_CLICK,'Right click');
        this.translations_EN.set(TrKeys.MENU_RIGHT_CLICK_DESC,
            'On hire FISE/FISA or end turn, open a menu to do ' +
            'the action more than one in one go.');

        // end.html
        this.translations_EN.set(TrKeys.END_MESSAGE,'We hope you had fun ! If you got an idea about a game that you wants to play\n' +
            '                    or an application, get in touch with us !');

        // machines.ts
        this.translations_EN.set(TrKeys.MACHINE_PRICE,'Price:');
        this.translations_EN.set(TrKeys.MACHINE_PRICE_DESTROY,'Price (destroy):');
        this.translations_EN.set(TrKeys.AND_WORD,'and');
        this.translations_EN.set(TrKeys.MACHINE_ORIENTATION,'Orientation (default):');
        this.translations_EN.set(TrKeys.MACHINE_PRICE_UPDATE,'Price (upgrade):');
        this.translations_EN.set(TrKeys.MACHINE_CAPACITY,'Capacity (default):');

        // staffs.ts
        this.translations_EN.set(TrKeys.STAFF_COST,'Upgrading cost :');
        this.translations_EN.set(TrKeys.STAFF_LEVEL,'LEVEL');
        this.translations_EN.set(TrKeys.STAFF_LEVEL_MAX,'Level max :');
        this.translations_EN.set(TrKeys.STAFF_EFFECT,'Current reduction is');

        // end.ts
        this.translations_EN.set(TrKeys.END_WIN,'Victory');
        this.translations_EN.set(TrKeys.END_LOST,'Defeat');

        // interface.ts
        this.translations_EN.set(TrKeys.TERMINAL_HELP,'Use help to get the list of available actions');

        // ////////////////////// //
        // French Translation
        // ////////////////////// //
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
        this.translations_FR.set(TrKeys.RULES_DOOR_TITLE, 'Afin de fermer la porte');
        this.translations_FR.set(TrKeys.RULES_DOOR, 'Pendant que les étudiants du cursus "Calcul intensif et ' + 'données massives" ' +
            'étaient entrain d\'explorer le monde binaire, ils ont ouvert une porte entre ' +
            'notre monde et un autre monde qui ressemble trait pour trait au notre. ' +
            'Cependant, leur joie n\'est pas duré longtemps. Avoir 2 ENSIIE a fait baisser leur ' +
            'classement en développement durable car ils dépensaient deux fois ' +
            'leur consommation d\'énergie habituelle. C\'est pourquoi ' +
            '<span class="text-my-yellow">vous devez absolument fermer la porte !</span>');
        this.translations_FR.set(TrKeys.RULES_EXPLAIN_TITLE, 'Quelles sont les règles ?');
        this.translations_FR.set(TrKeys.RULES_EXPLAIN,
            ' Vous devrez dépenser de l\'<span class="text-my-yellow">énergie (E)</span> ' +
            'pour acheter des machines tout en empêchant votre ' +
            '<span class="text-my-yellow">développement durable(DD)</span> ' +
            'd\'atteindre <span class="text-danger">0</span> (signifiant la destruction ' +
            'de votre monde). ' +
            '<br>' +
            'Votre but sera de produire ' +
            'et envoyer à la porte <span class="text-my-yellow" id="game-goal"></span> ' +
            'ressources afin de la fermer. Faites attention ! Chaque envoi de ressource produira ' +
            'un déchet que vous devrez manipuler sinon votre DD diminuera de ' +
            '<span class="text-success" id="game-dd-malus">1</span>. ' +
            'La porte génère également des déchets tant quelle ne sera pas fermée.' +
            '' +
            '');
        this.translations_FR.set(TrKeys.RULES_PLAY_TITLE, 'Comment jouer ?');
        this.translations_FR.set(TrKeys.RULES_PLAY, `
            Au début de la partie vous aurez <span class="text-my-yellow">
            <span id="game-nb-sources">2</span> sources</span>
            <img src="../../assets/img/legend/Resource.png" width="24" height="24" alt=" ">
            qui vont produire <span class="text-my-yellow">
            <span id="game-production">3</span> ressources
             <img src="../../assets/img/game/portal.png" width="24" height="24" alt=" ">
             tous 
            les <span id="game-turns-prod">10</span> tours</span> (par défaut).
            
            Vous devrez acheter une machine appelée un <span class="text-my-yellow">collecteur</span>
            <img src="../../assets/img/legend/MS_COLLECTOR_BOT.png" width="24" height="24" alt=" ">
            pour extraire des ressources d'une source
            (ou des déchets de la porte) puis les envoyer
            en utilisant soit un <span class="text-my-yellow">tapis roulant </span>
            <img src="../../assets/img/legend/MS_CONVEYOR_BELT_RIGHT.png" width="24" height="24" alt=" ">
            soit une <span class="text-my-yellow">croix</span>
            <img src="../../assets/img/legend/MS_CROSS_BELT_TOP_RIGHT.png" width="24" height="24" alt=" ">
            .
           
            Vous pouvez envoyer des déchets
             <img src="../../assets/img/game/garbage.png" width="24" height="24" alt=" ">
             à un <span class="text-my-yellow">centre de recyclage</span>
             <img src="../../assets/img/legend/MS_RECYCLING_CENTER_BOT.png" width="24" height="24" alt=" ">
            ou dans une <span class="text-my-yellow">déchetterie</span>
            <img src="../../assets/img/legend/MS_JUNKYARD.png" width="24" height="24" alt=" ">
            selon votre stratégie.
            
             <i class="text-muted small">Vous 
             aurez un guide dans le jeu pour voir plus d\'informations sur chaque machine.</i>
             
             <br><br>
            
            Mais pour acheter une machine, vous aurez besoin de <span class="text-my-yellow">E</span>
            et de <span class="text-my-yellow">DD</span> ! Ils sont produits par les étudiants
            de l\'ENSIIE, appelés FISE (cours de formation initiale, <span class="text-my-yellow">
            <span id="game-fise-e">1</span>E+<span id="game-fise-dd">1</span>DD</span>
            par tour) ou FISA (cours de formation à temps partiel, <span class="text-my-yellow">
            <span id="game-fisa-e">4</span>E</span> ou <span class="text-my-yellow">
            <span id="game-fisa-dd">4</span>
            DD</span> tout les <span class="text-my-yellow" id="game-fisa-turn">2</span> tours).
            
            <br><br>
            
            Si vous avez assez de <span class="text-my-yellow">E</span>
            et de <span class="text-my-yellow">DD</span>, vous pouvez embaucher un personnel qui peut réduire
            le coût d'une machine, embaucher beaucoup d'étudiants, ...
            <i class="text-muted small">Assurez-vous d'y jeter un coup d'oeil !</i>
            `);

        // game.html
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
        this.translations_FR.set(TrKeys.GAME_SOURCE,': Source');
        this.translations_FR.set(TrKeys.GAME_GATE,': Porte');
        this.translations_FR.set(TrKeys.GAME_CONVEYOR_BELT,': Tapis roulant');
        this.translations_FR.set(TrKeys.GAME_CROSS,': Croix');
        this.translations_FR.set(TrKeys.GAME_RECYCLING_CENTER,': Centre de recyclage');
        this.translations_FR.set(TrKeys.GAME_JUNKYARD,': Déchetterie');
        this.translations_FR.set(TrKeys.GAME_COLLECTOR,': Collecteur');
        this.translations_FR.set(TrKeys.GAME_CASE_SELECTED,'Aucune case sélectionnée.');
        this.translations_FR.set(TrKeys.GAME_MANAGE_STAFF,'Gérer votre Personnel');
        this.translations_FR.set(TrKeys.GAME_COUNT_1,'Nombre');
        this.translations_FR.set(TrKeys.GAME_COUNT_2,'Nombre');
        this.translations_FR.set(TrKeys.GAME_UNITS,'Unités');
        this.translations_FR.set(TrKeys.GAME_EXIT,'QUITTER');
        this.translations_FR.set(TrKeys.GAME_END_TURN,'TOUR_SUIVANT');
        this.translations_FR.set(TrKeys.GAME_MACHINE,'Machine');
        this.translations_FR.set(TrKeys.GAME_ROTATION,'Orientation');
        this.translations_FR.set(TrKeys.GAME_BUY,'Acheter');
        this.translations_FR.set(TrKeys.GAME_CASE_CONTENT,'Contenu');
        this.translations_FR.set(TrKeys.GAME_MACHINE_LEVEL,'NIVEAU');
        this.translations_FR.set(TrKeys.GAME_ROTATION_NONE,'Aucune rotation.');
        this.translations_FR.set(TrKeys.GAME_GATE_NAME,'PORTAIL');
        this.translations_FR.set(TrKeys.GAME_GATE_DESC,'Amenez des ressources à la porte pour la fermer. Attention, elle' +
            ' génère des déchets qui vont baisser vos DD.');
        this.translations_FR.set(TrKeys.GAME_SOURCE_NAME,'GÉNÉRATEUR');
        this.translations_FR.set(TrKeys.GAME_SOURCE_DESC,'Génère des ressources, ' +
            '<span id="source-gen" class="text-my-yellow">1</span> tous les' +
            ' <span id="source-gen-turn" class="text-my-yellow">10</span> tours par défaut, ' +
            'récoltables avec un COLLECTEUR. ');
        this.translations_FR.set(TrKeys.GAME_COST,'Coût');
        this.translations_FR.set(TrKeys.GAME_COST_IS,'Le coût est de');

        // staffs.html, settings.html, mapping.html, end.html,rules.html
        this.translations_FR.set(TrKeys.GO_BACK_B,'Retour');
        this.translations_FR.set(TrKeys.GO_BACK_LONG,'Retourner sur l\'écran précédent.');

        // settings.html
        this.translations_FR.set(TrKeys.MENU_TITLE,'LANGUE');
        this.translations_FR.set(TrKeys.MENU_LANGUAGE_EN,'Anglais');
        this.translations_FR.set(TrKeys.MENU_LANGUAGE_FR,'Français');
        this.translations_FR.set(TrKeys.VOLUME_TITLE,'VOLUME');
        this.translations_FR.set(TrKeys.MUSIC_TITLE,'MUSIQUE');
        this.translations_FR.set(TrKeys.MENU_GLOBAL,'Paramètres généraux');
        this.translations_FR.set(TrKeys.MENU_GLOBAL_SUB,'Personnalisez votre expérience de jeu.');
        this.translations_FR.set(TrKeys.MENU_SHORTCUTS,'Raccourcis');
        this.translations_FR.set(TrKeys.MENU_RIGHT_CLICK,'Clic droit');
        this.translations_FR.set(TrKeys.MENU_RIGHT_CLICK_DESC,'Sur recruter FISE/FISA ou TOUR_SUIVANT, ' +
            'permet d\'effectuer l\'action plusieurs fois.');

        // end.html
        this.translations_FR.set(TrKeys.END_MESSAGE,'Nous espérons que vous vous êtes bien amusé! Si vous avez une idée d\'un jeu' +
            ' auquel vous voulez jouer ou une application, contactez-nous !');

        // machines.ts
        this.translations_FR.set(TrKeys.MACHINE_PRICE,'Prix:');
        this.translations_FR.set(TrKeys.MACHINE_PRICE_DESTROY,'Prix (destruction):');
        this.translations_FR.set(TrKeys.AND_WORD,'et');
        this.translations_FR.set(TrKeys.MACHINE_ORIENTATION,'Orientation (par défaut):');
        this.translations_FR.set(TrKeys.MACHINE_PRICE_UPDATE,'Prix (amélioration):');
        this.translations_FR.set(TrKeys.MACHINE_CAPACITY,'Capacité (par défaut):');

        // staffs.ts
        this.translations_FR.set(TrKeys.STAFF_COST,'Coût d\'amélioration');
        this.translations_FR.set(TrKeys.STAFF_LEVEL,'NIVEAU');
        this.translations_FR.set(TrKeys.STAFF_LEVEL_MAX,'Niveau max :');
        this.translations_FR.set(TrKeys.STAFF_EFFECT,'Réduction actuelle de');

        // end.ts
        this.translations_FR.set(TrKeys.END_WIN,'Victoire');
        this.translations_FR.set(TrKeys.END_LOST,'Défaite');

        // interface.ts
        this.translations_FR.set(TrKeys.TERMINAL_HELP,'Utilisez help pour obtenir la liste des actions disponibles');

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

    GAME_NAME, //!< name:
    GAME_TURN, //!< turn:
    GAME_E, //!< E:
    GAME_DD, //!< DD:
    GAME_FISE, //!< FISE:
    GAME_FISA, //!< FISA:
    GAME_FISA_MODE, //!< FISA MODE:
    GAME_SCORE, //!< Score:
    GAME_GARBAGE, //!< Garbage:
    GAME_SOURCE, //!< Source:
    GAME_GATE, //!< Gate:
    GAME_CONVEYOR_BELT, //!< Conveyor belt:
    GAME_CROSS, //!< Cross:
    GAME_RECYCLING_CENTER, //!< Recycling Center:
    GAME_JUNKYARD, //!< Junkyard:
    GAME_COLLECTOR, //!< Collector:

    GO_BACK_B, //!< go back message
    GO_BACK_LONG, //!< go back message

    // legend and view components
    LEGEND, //!< Legend:

    END_WIN, //!< win
    END_LOST, //!< loose

    RULES_DOOR_TITLE, //!< Title
    RULES_DOOR, //!< In order to close the door.
    RULES_EXPLAIN_TITLE, //!< Title
    RULES_EXPLAIN, //!< What are the rules ?
    RULES_PLAY_TITLE, //!< Title
    RULES_PLAY, //!< How should I play ?
    END_MESSAGE,

    GAME_CASE_SELECTED,
    GAME_MANAGE_STAFF,
    GAME_COUNT_1,
    GAME_COUNT_2,
    GAME_UNITS,
    GAME_EXIT,
    GAME_END_TURN,
    GAME_MACHINE,
    GAME_ROTATION,
    GAME_BUY,
    GAME_CASE_CONTENT,
    GAME_MACHINE_LEVEL,
    GAME_ROTATION_NONE,
    GAME_GATE_NAME,
    GAME_GATE_DESC,
    GAME_SOURCE_NAME,
    GAME_SOURCE_DESC,
    GAME_COST,
    GAME_COST_IS,

    MENU_TITLE,
    MENU_LANGUAGE_EN,
    MENU_LANGUAGE_FR,

    MACHINE_PRICE,
    MACHINE_PRICE_DESTROY,
    MACHINE_ORIENTATION,
    AND_WORD,
    MACHINE_PRICE_UPDATE,
    MACHINE_CAPACITY,

    STAFF_COST,
    STAFF_LEVEL,
    STAFF_LEVEL_MAX,
    STAFF_EFFECT,

    TERMINAL_HELP,

    VOLUME_TITLE,
    MUSIC_TITLE,
    MENU_GLOBAL,
    MENU_GLOBAL_SUB,
    MENU_SHORTCUTS,
    MENU_RIGHT_CLICK,
    MENU_RIGHT_CLICK_DESC,
}

export enum Language {
    FR = "fr",
    EN = "en",
}