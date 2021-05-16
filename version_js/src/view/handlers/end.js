// This file is required by the game.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.
const {TrKeys,Translation,Language} = require("../../utils/translation");
let score = 0;

if (game.map.getPlayerScore > game.config.constants.NUMBER_RESOURCE_WIN){
    // he win, then we will calculate the score
    score = game.map.getPlayerScore - game.map.numberPollution;
    if (score > 0){ // he didn't know create as many garbage as resources
        // adding some points if not a lot of turns
        score += score * (1 / Math.log(game.map.getNumberTurn))
        // adding some points if a lot of DD
        score += Math.sqrt(game.map.getNumberDD)
        // how much staff bough ?
        let count = 0;
        for (const entry of game.map.staffList.entries()) {
            // we should also "check" if the staff is 14 15 16? 21 23 24
            // as these staffs provide as of now two much help
            count += entry[1];
        }
        // here we add a little gift if not a lot of staffs
        score += score * (1 / Math.log(count))
    }
    // a school must have students, one can't save the world but not his/her school :(
    let students = game.map.numberFISE + game.map.numberFISA;
    let studentsBase = game.config.constants.NUMBER_FISE + game.config.constants.NUMBER_FISA;
    if (students < studentsBase){
        score /= 2;
    }
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