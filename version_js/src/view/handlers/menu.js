const {Game} = require('../../game');
const btn_eng = document.getElementById('button_eng');
const btn_fr = document.getElementById('button_fr');

btn_eng.addEventListener('click', changeLang)
btn_fr.addEventListener('click', changeLang)

/**
* Change the lang of the game and store it in the localStorage
* @private
*/
function changeLang(event){
    console.log(event.target.getAttribute("value"));
    localStorage.setItem("lang", event.target.getAttribute("value"));
}

//todo: set value
btn_fr.setAttribute("value", lang.FR);
btn_eng.setAttribute("value", lang.EN);

//todo: :(
let current = lang.current;
if (current === lang.FR){
    btn_fr.setAttribute("checked","")
} else if (current === lang.EN){
    btn_eng.setAttribute("checked","")
}

// show slider
let rangeSlider = document.getElementById("rs-range-line");
let rangeBullet = document.getElementById("rs-bullet");
rangeSlider.value = Game.getAudio() * 100;
rangeSlider.addEventListener("input", showSliderValue, false);
function showSliderValue() {
    console.log(window.audio);

    rangeBullet.innerHTML = rangeSlider.value;
    window.audio.volume = (rangeSlider.value/rangeSlider.max);
    Game.setAudio(window.audio.volume);
    console.log(window.audio.volume);
    rangeSlider.value = Game.getAudio() * 100;
    let bulletPosition = (rangeSlider.value /rangeSlider.max);
    rangeBullet.style.left = Math.max((bulletPosition * 572), 12) + "px";
}
showSliderValue();