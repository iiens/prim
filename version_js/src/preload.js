// All of the Node.js APIs are available in the preload process.
// It has the same sandbox as a Chrome extension.

const {handleWindowControls, addHeader} = require('./frameless')

// When document has loaded, initialise
document.onreadystatechange = (event) => {
    if (document.readyState === "complete") {
        const jquery = require('jquery')

        // frameless window
        addHeader();
        handleWindowControls()

        // get the page name (index, game, rules)
        let path = window.location.pathname;
        if (path.endsWith("/")) path = path.substring(0, path.length-1)
        let page = path.substring(path.lastIndexOf('/') + 1);
        page = page.replaceAll(".html", "");

        // load the page javascript
        switch(page) {
            case 'index' : {
                const {Config} = require('./utils/config');
                const {Game} = require('./game');
                const {Translation, TrKeys} = require('./utils/translation');
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
                    "tr-exit": Translation.get(TrKeys.MENU_EXIT),
                }
                translate();
                require("./view/handlers/index");
                break;
            }
            case 'game': {
                const {Game} = require('./game');
                // load JQuery terminal
                window.$ = window.jquery = jquery;
                const JQueryTerminal = require('jquery.terminal');
                // noinspection JSValidateTypes
                JQueryTerminal($);

                let level = findGetParameter("lvl");
                if (level) // coming to start a game
                {
                    Game.initGame(Number(level))
                } else {
                    Game.loadSave()
                }
                window.game = Game;
                // game
                require("./view/handlers/game");
                break;
            }
            case 'rules': {
                const {Config} = require('./utils/config');
                // load config
                window.config = Config;
                // rules
                require("./view/handlers/rules");
                // go back
                require("./view/handlers/go_back");
                break;
            }
            case 'staffs': loadGame('staffs'); break;
            case 'machines': loadGame('machines'); break;
            case 'mappings': loadGame('mappings'); break;
            case 'end': loadGame('end'); break;
        }

        // load music
        (async () => {
            // random choice of music
            let path = Math.random() > 0.5 ? "narrative.mp3" : "truth.mp3";
            // use javascript standard class
            let audio = new Audio(__dirname+"/../assets/music/"+path);
            audio.volume = 0.02;
            audio.loop = true;
            await audio.play();
        })();
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
    window.config = Game.config;
    // end
    require("./view/handlers/"+file);
    // go back
    require("./view/handlers/go_back");
}