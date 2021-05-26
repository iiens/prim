const {Game} = require('../../game');

// ids
const LANG_ON = "lang";
const VOLUME_ON = "volume";
const MUSIC_ON = "music";
// divs
let LANG_FIELD = document.getElementById('lang-field');
let VOLUME_FIELD = document.getElementById('volume-field');
let MUSIC_FIELD = document.getElementById('music-field');

/////////////////////// LANGUAGE
// all languages
let ALL_LANGUAGES = [ lang.EN, lang.FR ]
// current langage index
let currentLanguage = ALL_LANGUAGES.findIndex((l) => lang.current === l)
// set
move(0, LANG_ON);

/////////////////////// VOLUME
move(Math.round(Game.getAudio() * 100), VOLUME_ON);

/////////////////////// MUSIC
// all musics
let ALL_MUSICS = [ "Truth (Dead Seed)", "Narrative" ]
let ALL_MUSICS_FILES = [ "truth.mp3", "narrative.mp3" ]
// current music index
let current_music = ALL_MUSICS_FILES.findIndex((l) => Game.getMusic() === l)
move(0, MUSIC_ON)

function move(value, on) {
    let text;
    let div;
    switch (on) {
        case LANG_ON:
            div = LANG_FIELD;
            currentLanguage += value;
            if (currentLanguage < 0) currentLanguage = ALL_LANGUAGES.length - 1; // go back to last
            if (currentLanguage >= ALL_LANGUAGES.length) currentLanguage = 0; // go back to first
            text = ALL_LANGUAGES[currentLanguage] === lang.EN ? translation['tr-menu-en'] : translation['tr-menu-fr'];
            if (value !== 0){
                localStorage.setItem("lang", ALL_LANGUAGES[currentLanguage]);
                location.reload();
            }
            break;
        case VOLUME_ON:
            div = VOLUME_FIELD
            let volume = Number(VOLUME_FIELD.innerText) + value;
            if (volume < 0) volume = 0;
            if (volume > 100) volume = 100;
            text = volume;
            // and change value
            audio.volume = volume / 100;
            Game.setAudio(window.audio.volume);
            break;
        case MUSIC_ON:
            div = MUSIC_FIELD;
            current_music += value;
            if (current_music < 0) current_music = ALL_MUSICS.length - 1; // go back to last
            if (current_music >= ALL_MUSICS.length) current_music = 0; // go back to first
            text = ALL_MUSICS[current_music];
            if (value !== 0){
                Game.setMusic(ALL_MUSICS_FILES[current_music]);
                location.reload();
            }
            break;
    }
    div.innerText = text;
}

// add listener
document.getElementById('move-left-lang').onclick = (e) => move(-1, LANG_ON);
document.getElementById('move-right-lang').onclick = (e) => move(1, LANG_ON);

// add listener
let left_volume = document.getElementById('move-left-volume');
let right_volume = document.getElementById('move-right-volume');
let rightVolume = -1;
let leftVolume = -1;
let initHandlerVolume = (id, h) => {
    if( id === -1 ) {
        // shutdown all
        leftVolume = shutDownHandlerVolume(left_volume);
        rightVolume = shutDownHandlerVolume(rightVolume);
        // start one
        return setInterval(h , 100)
    }
    return id;
};
let shutDownHandlerVolume = (id) => { if (id !== -1) { clearInterval(id); return -1; } return id; };

left_volume.onclick = () => move(-1, VOLUME_ON);
left_volume.onmousedown = () => leftVolume = initHandlerVolume(leftVolume, () => move(-1, VOLUME_ON))
left_volume.onmouseup = () => leftVolume = shutDownHandlerVolume(leftVolume);
left_volume.onmouseover = () => leftVolume = shutDownHandlerVolume(leftVolume);
right_volume.onclick = () => move(1, VOLUME_ON);
right_volume.onmousedown = () => rightVolume = initHandlerVolume(rightVolume, () => move(1, VOLUME_ON))
right_volume.onmouseup = () => rightVolume = shutDownHandlerVolume(rightVolume);
right_volume.onmouseover = () => rightVolume = shutDownHandlerVolume(rightVolume);

// add listener
document.getElementById('move-left-music').onclick = (e) => move(-1, MUSIC_ON);
document.getElementById('move-right-music').onclick = (e) => move(1, MUSIC_ON);