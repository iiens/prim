// This is a file that
// allow the user to go back
//
// @pre composant id 'go-back', to add go-back event
// @pre composant id 'config-back-key', to set go-back key
//

let moveBack = () => {
    win.cleanListeners(inputListener)
    location.href = document.getElementById('go-back')
        .getAttribute("data-to")
}

// create input listener
let inputListener = (event, input) => {
    if (input.type === "keyDown") {
        if (input.key === config.keys.back) {
            moveBack();
        }
        if (input.key === config.keys.exit) {
            win.close()
        }
    }
};

// allow mouse
document.getElementById('go-back').onclick = () => moveBack();
// set key according to config
let key_span = document.getElementsByClassName("config-back-key");
if (key_span[0]) key_span[0].innerHTML = config.keys.back;

// add listener
win.onInput(inputListener)