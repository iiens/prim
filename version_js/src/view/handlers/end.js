// This file is required by the game.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.
const { TrKeys, Translation } = require("../../utils/translation");
let score = 0;

if (game.map.getPlayerScore > game.config.constants.NUMBER_RESOURCE_WIN){
    // parameters
    let s = game.map.getPlayerScore, g = game.map.numberPollution;
    let t = game.map.getNumberTurn;
    let dd = game.map.getNumberDD;
    let ns = 0;
    for (const staff of game.map.staffList.entries()){ ns += staff[1];}
    let fe = game.map.getNumberFISE, fa = game.map.getNumberFISA;

    // he win, then we will calculate the score
    score = s - g;
    if (score > 0) { // he didn't know create as many garbage as resources
        score += s > game.config.constants.NUMBER_RESOURCE_WIN * 2 ? Math.sqrt(s) : s;
        console.log(score)
        // malus for turns
        score += score / Math.log(t);
        console.log(score)
        // bonus for dd
        score += score / Math.sqrt( Math.round(dd / t));
        console.log(score)
        // malus for number of staffs
        score += score / Math.log( ns );
        console.log(score)
        // malus for number of garbages
        if( g > 1 ) score -= score / Math.log2(g ** 2)
    }
    // apply malus is school is empty
    let base = game.config.constants.NUMBER_FISE + game.config.constants.NUMBER_FISA;
    if(fe + fa < base) score = score / 2
    console.log(score)
    // round
    score = Math.round(score);
}

// score
win.replaceText('score', score)

// status
let haveWin = game.map.getPlayerScore > game.config.constants.NUMBER_RESOURCE_WIN;
let status = document.getElementById('status')
let winText = Translation.get(TrKeys.END_WIN);
let lostText = Translation.get(TrKeys.END_LOST);
status.innerText = haveWin ? winText : lostText;
status.classList.add( haveWin ? "text-success" : "text-danger");