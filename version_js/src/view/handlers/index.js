// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.
let current = 1; // current menu
const NUMBER_OF_MENUS = 5; // number of menus
const EXIT_INDEX = 5; // exit index, the only one were we are not making a redirect

// create input listener
let inputListener = (event, input) => {
    if (input.type === "keyDown"){
        let menu = document.getElementById("menu"+current)
        // choose menu
        if (input.key === "Enter") {
            win.cleanListeners(inputListener)
            if (current === EXIT_INDEX){
                win.close()
                return;
            } else {
                location.href=menu.getAttribute('data-to')
            }
        }

        // exit
        if (input.key === config.keys.exit) {
            win.close();
            return;
        }

        // menu: up
        if (input.key === "ArrowUp"){
            if (current > 1){
                current--
            }
        }
        // menu: down
        if (input.key === "ArrowDown"){
            if (current < 5){
                current++
            }
        }

        // clear old one
        menu.classList.remove("selected-menu")
        // new one selected
        menu = document.getElementById("menu"+current)
        menu.classList.add("selected-menu")
    }
};

// first is selected
let menu = document.getElementById("menu1")
menu.classList.add("selected-menu")
win.onInput(inputListener)

// allow mouse
for (let i = 1; i <= NUMBER_OF_MENUS; i++) {
    let e = document.getElementById(`menu${i}`)
    if ( i === EXIT_INDEX ) {
        e.onclick = () => win.close();
    } else {
        e.onclick = (event) => {
            win.cleanListeners(inputListener);
            let dest = event.target.getAttribute('data-to');
            if (dest == null){ // check parent
                dest = event.target.parentNode.getAttribute('data-to');
            }
            location.href=dest;
        }
    }
}

// version
win.replaceText("prim-version", config.GAME_VERSION)