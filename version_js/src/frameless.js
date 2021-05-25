//
// Script mainly took for official examples
// of a frameless window
//
//todo: we should use electron@remote but I can't solve
// the warning "catch()" missing for a promise (I couldn't even find which one)
// https://github.com/electron/remote
const {remote} = require('electron')
const win = remote.getCurrentWindow();  // Module to create native browser window.

window.onbeforeunload = () => {
    /* If window is reloaded, remove win event listeners
    (DOM element listeners get auto garbage collected but not
    Electron win listeners as the win is not dereferenced unless closed) */
    win.removeAllListeners();
}

function handleWindowControls() {
    // Make minimise/maximise/restore/close buttons work when they are clicked
    document.getElementById('min-button').addEventListener("click", event => {
        win.minimize();
    });

    document.getElementById('max-button').addEventListener("click", event => {
        win.maximize();
    });

    document.getElementById('restore-button').addEventListener("click", event => {
        win.unmaximize();
    });

    document.getElementById('close-button').addEventListener("click", event => {
        win.close();
    });

    // Toggle maximise/restore buttons when maximisation/unmaximisation occurs
    toggleMaxRestoreButtons();
    win.on('maximize', toggleMaxRestoreButtons);
    win.on('unmaximize', toggleMaxRestoreButtons);

    function toggleMaxRestoreButtons() {
        if (win.isMaximized()) {
            document.body.classList.add('maximized');
        } else {
            document.body.classList.remove('maximized');
        }
    }
}

module.exports = {
    addHeader,
    addPopup,
    handleWindowControls,
}

// expose a part of the windows
window.win = {
    /** close the window **/
    close: () => win.close(),
    /** remove window listener on input event, f **/
    cleanListeners: (f) => win.webContents.removeListener("before-input-event", f),
    /** set input listener */
    onInput: (inputListener) => win.webContents.on("before-input-event", inputListener),
    /** replace element text (selector is an id and text is the text to set for this selected element) **/
    replaceText: (selector, text) => {
        const element = document.getElementById(selector)
        if (element) element.innerHTML = text+""
    }
};

/**
 * Add the header
 */
function addHeader() {
    let bar = document.getElementById('titlebar');
    if (bar){
        bar.innerHTML = `<div id="drag-region">
        <div id="window-title">
            <span>Prim - Environment Line</span>
        </div>
        <div id="window-controls">
            <div class="button" id="min-button">
                <img class="icon" srcset="../../assets/icons/min-w-10.png 1x,
                   ../../assets/icons/min-w-12.png 1.25x, ../../assets/icons/min-w-15.png 1.5x,
                    ../../assets/icons/min-w-15.png 1.75x, ../../assets/icons/min-w-20.png 2x,
                     ../../assets/icons/min-w-20.png 2.25x, ../../assets/icons/min-w-24.png 2.5x,
                      ../../assets/icons/min-w-30.png 3x, ../../assets/icons/min-w-30.png 3.5x" draggable="false" />
            </div>
            <div class="button" id="max-button">
                <img class="icon" srcset="../../assets/icons/max-w-10.png 1x, ../../assets/icons/max-w-12.png 1.25x,
                   ../../assets/icons/max-w-15.png 1.5x, ../../assets/icons/max-w-15.png 1.75x, ../../assets/icons/max-w-20.png 2x,
                    ../../assets/icons/max-w-20.png 2.25x, ../../assets/icons/max-w-24.png 2.5x, ../../assets/icons/max-w-30.png 3x,
                     ../../assets/icons/max-w-30.png 3.5x" draggable="false" />
            </div>
            <div class="button" id="restore-button">
                <img class="icon" srcset="../../assets/icons/restore-w-10.png 1x, ../../assets/icons/restore-w-12.png 1.25x,
                   ../../assets/icons/restore-w-15.png 1.5x, ../../assets/icons/restore-w-15.png 1.75x, ../../assets/icons/restore-w-20.png 2x,
                    ../../assets/icons/restore-w-20.png 2.25x, ../../assets/icons/restore-w-24.png 2.5x, ../../assets/icons/restore-w-30.png 3x,
                    ../../assets/icons/restore-w-30.png 3.5x" draggable="false" />
            </div>
            <div class="button" id="close-button">
                <img class="icon" srcset="../../assets/icons/close-w-10.png 1x, ../../assets/icons/close-w-12.png 1.25x,
                   ../../assets/icons/close-w-15.png 1.5x, ../../assets/icons/close-w-15.png 1.75x, ../../assets/icons/close-w-20.png 2x,
                   ../../assets/icons/close-w-20.png 2.25x, ../../assets/icons/close-w-24.png 2.5x, ../../assets/icons/close-w-30.png 3x,
                    ../../assets/icons/close-w-30.png 3.5x" draggable="false" />
            </div>

        </div>
    </div>`
    }
}

function addPopup() {
    let popup = document.getElementById('popup-div');
    if(popup){
        popup.classList.add('position-absolute', 'game-popup')
        popup.innerHTML = `
        <!-- close -->
        <span class="position-absolute py-2 text-dark
            pointer game-popup-close" id="game-popup-close">
            X
        </span>
        <!-- content -->
        <div>
            <div class="bg-my-blue text-white py-2 ps-2"
            id="popup-title">
                TITLE
            </div>
            <div class="settings-background text-white p-3" id="popup-content">
                Blah blah blah Blah blah blah Blah blah blah
                Blah blah blah Blah blah blah Blah blah blah
            </div>
        </div>`
    }
}