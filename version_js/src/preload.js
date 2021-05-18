// All of the Node.js APIs are available in the preload process.
// It has the same sandbox as a Chrome extension.
const {handleWindowControls, addHeader, addPopup} = require('./frameless');
const {Translation, TrKeys, Language} = require('./utils/translation');
const {Game} = require('./game');
const {Action} = require('./utils/mappings');
const {Config} = require('./utils/config');

// When document has loaded, initialise
document.onreadystatechange = (event) => {
    if (document.readyState === "complete") {
        const jquery = require('jquery')

        // frameless window
        addHeader();
        handleWindowControls();

        // load music
        (async () => {
            // random choice of music
            // todo: let path = Math.random() > 0.5 ? "narrative.mp3" : "truth.mp3";
            let path = Game.getMusic();
            // use javascript standard class
            let audio = new Audio(__dirname+"/../assets/music/"+path);
            audio.volume = Game.getAudio();
            audio.loop = true;
            window.audio = audio;
            await audio.play();
        })();

        // get the page name (index, game, rules)
        let path = window.location.pathname;
        if (path.endsWith("/")) path = path.substring(0, path.length-1)
        let page = path.substring(path.lastIndexOf('/') + 1);
        page = page.replaceAll(".html", "");

        //We initialize the language of the game, here is French
        Translation.setLanguage(Game.getTranslationLanguage());

        // load the page javascript
        switch(page) {
            case 'index' : {

                Game.clearGame(); // clear previous game just in case
                // load config
                window.config = Config;
                // load translations
                window.translation = {
                    "tr-header": Translation.get(TrKeys.INTRO_HEADER),
                    "tr-desc": Translation.get(TrKeys.INTRO_DESC),
                    "tr-requested-by": Translation.get(TrKeys.INTRO_REQUESTED_BY),
                    "tr-version": Translation.get(TrKeys.INTRO_VERSION),
                    "tr-created-by": Translation.get(TrKeys.INTRO_CREATE_BY),

                    "tr-easy": Translation.get(TrKeys.MENU_EASY),
                    "tr-medium": Translation.get(TrKeys.MENU_MEDIUM),
                    "tr-hard": Translation.get(TrKeys.MENU_HARD),
                    "tr-rules": Translation.get(TrKeys.MENU_RULES),
                    "tr-menu": Translation.get(TrKeys.MENU_SETTINGS),
                    "tr-exit": Translation.get(TrKeys.MENU_EXIT),
                }
                translate();
                require("./view/handlers/index");
                break;
            }
            case 'game': {
                // // load JQuery terminal
                // window.$ = window.jquery = jquery;
                // const JQueryTerminal = require('jquery.terminal');
                // // noinspection JSValidateTypes
                // JQueryTerminal($);
                addPopup(); // add popup for errors

                let level = findGetParameter("lvl");
                if (level) // coming to start a game
                {
                    Game.initGame(Number(level))
                } else {
                    Game.loadSave()
                }
                window.game = Game;
                window.game.actions = Action;
                // game
                // load config
                window.config = Config;
                window.translation = {
                    "tr-game-name" : Translation.get(TrKeys.GAME_NAME),
                    "tr-game-turn": Translation.get(TrKeys.GAME_TURN),
                    "tr-game-e" : Translation.get(TrKeys.GAME_E),
                    "tr-game-dd" : Translation.get(TrKeys.GAME_DD),
                    "tr-game-fise" : Translation.get(TrKeys.GAME_FISE),
                    "tr-game-fisa" : Translation.get(TrKeys.GAME_FISA),
                    "tr-game-fisamode" : Translation.get(TrKeys.GAME_FISA_MODE),
                    "tr-game-score" : Translation.get(TrKeys.GAME_SCORE),
                    "tr-game-garbage" : Translation.get(TrKeys.GAME_GARBAGE),
                    "tr-game-legend" : Translation.get(TrKeys.LEGEND),
                    "tr-game-source" : Translation.get(TrKeys.GAME_SOURCE),
                    "tr-game-gate" : Translation.get(TrKeys.GAME_GATE),
                    "tr-game-conveyor-belt" : Translation.get(TrKeys.GAME_CONVEYOR_BELT),
                    "tr-game-cross" : Translation.get(TrKeys.GAME_CROSS),
                    "tr-game-recycling-center" : Translation.get(TrKeys.GAME_RECYCLING_CENTER),
                    "tr-game-junkyard" : Translation.get(TrKeys.GAME_JUNKYARD),
                    "tr-game-collector" : Translation.get(TrKeys.GAME_COLLECTOR),
                    "tr-game-case-selected" : Translation.get(TrKeys.GAME_CASE_SELECTED),
                    "manage-staff" : Translation.get(TrKeys.GAME_MANAGE_STAFF),
                    "tr-count1" : Translation.get(TrKeys.GAME_COUNT_1),
                    "tr-count2" : Translation.get(TrKeys.GAME_COUNT_2),
                    "tr-units" : Translation.get(TrKeys.GAME_UNITS),
                    "tr-game-exit" : Translation.get(TrKeys.GAME_EXIT),
                    "tr-game-end-turn" : Translation.get(TrKeys.GAME_END_TURN),
                    "tr-machine" : Translation.get(TrKeys.GAME_MACHINE),
                    "tr-rotation" : Translation.get(TrKeys.GAME_ROTATION),
                    "tr-buy" : Translation.get(TrKeys.GAME_BUY),
                    "tr-case-content" : Translation.get(TrKeys.GAME_CASE_CONTENT),
                    "tr-machine-level" : Translation.get(TrKeys.GAME_MACHINE_LEVEL),
                    "tr-rotation-none" : Translation.get(TrKeys.GAME_ROTATION_NONE),
                    "tr-gate" : Translation.get(TrKeys.GAME_GATE_NAME),
                    "tr-gate-desc" : Translation.get(TrKeys.GAME_GATE_DESC),
                    "tr-source" : Translation.get(TrKeys.GAME_SOURCE_NAME),
                    "tr-source-desc" : Translation.get(TrKeys.GAME_SOURCE_DESC),
                }
                translate();
                require("./view/handlers/popup");
                require("./view/handlers/game");
                break;
            }
            case 'rules': {
                // load config
                window.config = Config;
                window.translation = {
                    "tr-rules-door-title": Translation.get(TrKeys.RULES_DOOR_TITLE),
                    "tr-rules-door": Translation.get(TrKeys.RULES_DOOR),
                    "tr-rules-explain-title": Translation.get(TrKeys.RULES_EXPLAIN_TITLE),
                    "tr-rules-explain": Translation.get(TrKeys.RULES_EXPLAIN),
                    "tr-rules-play-title": Translation.get(TrKeys.RULES_PLAY_TITLE),
                    "tr-rules-play": Translation.get(TrKeys.RULES_PLAY),
                    "tr-rules": Translation.get(TrKeys.MENU_RULES),
                    "tr-back": Translation.get(TrKeys.GO_BACK_B),
                }
                translate();
                // rules
                require("./view/handlers/rules");
                // go back
                require("./view/handlers/go_back");
                break;
            }
            case 'menu': {
                // load config
                window.config = Config;
                window.audio = audio;
                window.lang = Language;
                window.lang.current = Translation.getLanguage();
                window.translation = {
                    "tr-back": Translation.get(TrKeys.GO_BACK_B),
                    "tr-menu-title": Translation.get(TrKeys.MENU_TITLE),
                    "tr-menu-en": Translation.get(TrKeys.MENU_LANGUAGE_EN),
                    "tr-menu-fr": Translation.get(TrKeys.MENU_LANGUAGE_FR),
                    "tr-volume-title" : Translation.get(TrKeys.VOLUME_TITLE),
                    "tr-music-title" : Translation.get(TrKeys.MUSIC_TITLE),
                }
                translate();
                audio.volume=Game.getAudio();
                // rules
                require("./view/handlers/menu");
                // go back
                require("./view/handlers/go_back");
                break;
            }
            case 'staffs': {
                loadGame('staffs');
                window.config = Config;
                window.translation = {
                    "tr-back": Translation.get(TrKeys.GO_BACK_B),
                }
                translate();
                break;
            }
            case 'machines': {
                loadGame('machines');
                window.config = Config;
                window.translation = {
                    "tr-back": Translation.get(TrKeys.GO_BACK_B),
                }
                translate();
                break;
            }
            case 'mappings':{
                loadGame('mappings');
                window.config = Config;
                window.translation = {
                    "tr-back": Translation.get(TrKeys.GO_BACK_B),
                }
                translate();
                break;
            }

            case 'end': {
                loadGame('end');
                window.config = Config;
                window.translation = {
                    "tr-back": Translation.get(TrKeys.GO_BACK_B),
                    "tr-end-message": Translation.get(TrKeys.END_MESSAGE),
                }
                translate();
                break;
            }
        }
    }
};

// stack overflow, get parameter value by name (or null if not found)
function findGetParameter(parameterName) {
    let result = null, tmp = [];
    let items = location.search.substr(1).split("&");
    for (let index = 0; index < items.length; index++) {
        tmp = items[index].split("=");
        if (tmp[0] === parameterName) result = decodeURIComponent(tmp[1]);
    }
    return result;
}

// translate using translation array if set. keys are html id, values are the translation.
function translate() {
    if (translation === undefined) return;
    // translate all
    for (const prop in translation) {
        if (Object.prototype.hasOwnProperty.call(translation, prop)) {
            // do stuff
            win.replaceText(prop, translation[prop])
        }
    }
}

// load game, go back and also a page handler with "file" the name without extension of handlers/ folder
function loadGame(file) {
    const {Game} = require('./game');
    Game.loadSave(); // fetch map again
    window.game = Game;
    window.game.actions = Action;
    window.config = Game.config;
    // popup
    addPopup(); // add popup for errors
    require("./view/handlers/popup");
    // end
    require("./view/handlers/"+file);
    // go back
    require("./view/handlers/go_back");
}