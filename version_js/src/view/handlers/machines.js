// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.

const {EventType} = require("../../utils/events");
const {MachineStuff} = require("../../model/machine");
const {TrKeys,Translation} = require("../../utils/translation");
const {Cardinal} = require("../../model/machine");
let machines = document.getElementById("machines-list");

// load translations
let tr_cost = Translation.get(TrKeys.MACHINE_PRICE);
let tr_cost_upgrade = Translation.get(TrKeys.MACHINE_PRICE_UPDATE);
let tr_cost_destroy = Translation.get(TrKeys.MACHINE_PRICE_DESTROY);

// all machines
for (const machine of config.machines) {
    let machine_icon = machine.imageFile.get(Cardinal.SOUTH);
    let info = config.getMachineStuff(machine.type);

    // only if upgradable
    let up_content = "";
    if (machine.canUpgrade){
        let me = game.map.getCostUpgrade(info, EventType.UPGRADE_MACHINE);
        up_content = `
        <div>
        ${tr_cost_upgrade} <span class="text-my-yellow">${me.costE} E</span>
        <span class="text-my-yellow">${me.costDD} DD</span>
        </div>
        `;
    } else {
        // should show not upgradable ?
    }

    // not an unlimited capacity
    let capacity_content = "";
    if (machine.capacity !== Number.MAX_VALUE) {
        // ...
    }

    let me = game.map.getCostUpgrade(info, EventType.BUY_MACHINE);
    let me_destroy = game.map.getCostUpgrade(info, EventType.DESTROY_MACHINE);

    // final machine view
    let div = document.createElement("div");
    div.classList.add("mt-3");
    div.innerHTML = `
          <div class="fz22">
            <div class="settings-background ps-2 py-1 text-white">
                <img src="${machine_icon}" alt="">
                <span>${machine.name(game.getTranslationLanguage())}</span>
            </div>
            <div class="content-background p-3">
                <div>
                    ${machine.description(game.getTranslationLanguage())}
                </div>
                <div class="mt-3">
                    ${tr_cost} <span class="text-my-yellow">${me.costE} E</span>
                    <span class="text-my-yellow">${me.costDD} DD</span>
                </div>
                ${up_content}
                <div>
                    ${tr_cost_destroy} <span class="text-my-yellow">${me_destroy.costE} E</span>
                    <span class="text-my-yellow">${me_destroy.costDD} DD</span>
                </div>
                <div class="mt-2 text-my-blue">
                 ${machine.canUpgrade ? machine.upgrade(Translation.getLanguage()) : ""}
                </div>
            </div>
        </div>    
    `;
    machines.append(div)
}