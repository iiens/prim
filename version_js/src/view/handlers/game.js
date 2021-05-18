// This file is required by the game.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.

game.interface.init()

// replace son constants
win.replaceText('max-score', game.config.constants.NUMBER_RESOURCE_WIN)
win.replaceText('fise-cost-e', game.config.constants.COST_FISE_E)
win.replaceText('fise-cost-dd', game.config.constants.COST_FISE_DD)
win.replaceText('fisa-cost-e', game.config.constants.COST_FISA_E)
win.replaceText('fise-cost-dd', game.config.constants.COST_FISA_DD)

// call exit
document.getElementById('exit-button-event').onclick = () => game.mappings.getMapping(game.actions.EXIT).code()
// call end turn
document.getElementById('tr-game-end-turn').onclick = () => game.mappings.getMapping(game.actions.END_TURN).code()
// change production mode
changeMode(undefined, true) // set default
document.getElementById('e-dd-change-e').onclick = changeMode;
document.getElementById('e-dd-change-dd').onclick = changeMode;
// buy machine
document.getElementById('buy-button').onclick = callBuyMachine;
document.querySelectorAll('.machine-list').forEach((e) => e.onclick = select_machine)
document.querySelectorAll('.orientations').forEach((e) => initOrientationEvents(e))
// destroy/upgrade
document.getElementById('destroy-selected').onclick = callDestroy;
document.getElementById('update-selected').onclick = callUpgrade;
// hire fise/fisa
document.getElementById('buy-fise-event').onclick = () => game.mappings.getMapping(game.actions.HIRE_FISE).code()
document.getElementById('buy-fisa-event').onclick = () => game.mappings.getMapping(game.actions.HIRE_FISA).code()
// staffs
document.getElementById('manage-staff').onclick = () => game.mappings.getMapping(game.actions.LIST_STAFF).code()

//////////////
/// helpers //
//////////////

function changeMode(event=undefined, loadOnly = false) {
    if (!loadOnly) // call end turn
        game.mappings.getMapping(game.actions.CHANGE_FISA_MODE).code();

    let mode = document.getElementById('mode').innerText;
    if (loadOnly && mode === 'E'){
        // already set to E
        return;
    }
    let imageSelected; // other image since it was selected
    let imageNotSelected; // image of new selected one

    let labelSelected; // same but for label
    let labelNotSelected;

    if (mode === 'E'){
        imageSelected = document.getElementById('e-dd-change-dd-img');
        imageNotSelected = document.getElementById('e-dd-change-e-img');

        labelSelected = document.getElementById('e-dd-change-dd-label');
        labelNotSelected = document.getElementById('e-dd-change-e-label');
    } else {
        imageSelected = document.getElementById('e-dd-change-e-img');
        imageNotSelected = document.getElementById('e-dd-change-dd-img');

        labelSelected = document.getElementById('e-dd-change-e-label');
        labelNotSelected = document.getElementById('e-dd-change-dd-label');
    }

    // switch images
    let tmp = imageSelected.src;
    imageSelected.src = imageNotSelected.src;
    imageNotSelected.src = tmp;

    if(labelNotSelected){
        labelNotSelected.classList.add('text-muted')
        labelNotSelected.classList.remove('text-dark')
    }

    if(labelSelected){
        labelSelected.classList.add('text-dark')
        labelSelected.classList.remove('text-muted')
    }
}

function callUpgrade() {
    let button = document.getElementById('update-selected');
    let x = button.getAttribute('data-x');
    let y = button.getAttribute('data-y');
    game.mappings.getMapping(game.actions.UPGRADE_MACHINE).code(x, y)
}

function callDestroy() {
    let button = document.getElementById('destroy-selected');
    let x = button.getAttribute('data-x');
    let y = button.getAttribute('data-y');
    game.mappings.getMapping(game.actions.DESTROY_MACHINE).code(x, y)
}

function callBuyMachine() {
    let button = document.getElementById('buy-button');
    let x = button.getAttribute('data-x');
    let y = button.getAttribute('data-y');
    let selectedType = document.getElementsByClassName('selected-machine-type')[0];
    let selectedOrientation = document.getElementsByClassName('orientation-selected')[0];
    let machineStuff = Number(selectedType.getAttribute('data-id'))
    let orientation = Number(selectedOrientation.getAttribute('data-rotation'))
    game.mappings.getMapping(game.actions.BUY_MACHINE).code(machineStuff, x, y, orientation)
}

function select_machine(e) {
    let selected = document.getElementsByClassName('selected-machine-type')[0];
    let id = selected.getAttribute('data-id');
    // unselect machine
    selected.classList.remove('bg-info','selected-machine-type')
    // hides orientation
    document.getElementById('orientations'+id).classList.add('d-none');
    // select machine
    e.target.classList.add('bg-info','selected-machine-type')
    // show orientation
    id = e.target.getAttribute('data-id');
    document.getElementById('orientations'+id).classList.remove('d-none');

    // unselect orientation
    document.getElementsByClassName('orientation-selected')[0].classList
        .remove('border-my-yellow', 'orientation-selected')
    // select first
    let orientations = document.getElementById('orientations'+id);
    orientations.children[0].classList.add('orientation-selected')
    if (orientations.children[0].tagName === "IMG"){
        orientations.children[0].classList.add('border-my-yellow')
    }
}

function select_orientation(e) {
    let selected = document.getElementsByClassName('orientation-selected')[0];
    selected.classList.remove('border-my-yellow', 'orientation-selected')
    e.target.classList.add('border-my-yellow', 'orientation-selected')
}

function initOrientationEvents(orientationDIV) {
    for(let e of orientationDIV.children){
        e.onclick = select_orientation;
    }
}