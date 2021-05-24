// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.

const {TrKeys,Translation} = require("../../utils/translation");

let tr_cost = Translation.get(TrKeys.STAFF_COST);
let tr_level = Translation.get(TrKeys.STAFF_LEVEL);
let tr_level_max = Translation.get(TrKeys.STAFF_LEVEL_MAX);
let tr_effect = Translation.get(TrKeys.STAFF_EFFECT);
let tr_and = Translation.get(TrKeys.AND_WORD);

//todo: fix ??? in staff pane
// and also add E/DD values in this menu
win.replaceText('manage-staff', 'Gérer votre Personnel')

let staffs = document.getElementById("staff-list");

// add all staffs
for (const entry of game.map.staffList.entries()) {
    let staff = entry[0];
    let count = entry[1];
    let can = staff.levelMax - count > 0;
    let div = document.createElement("div");
    div.classList.add("mt-3");
    div.innerHTML = `
        <div class="fz22">
            <div class="settings-background ps-2 py-1 text-white">
                <img src="${staff.icon}" alt="">
                <span>${staff.name}</span>
            </div>
            <div class="content-background p-3">
                <div>
                    ${staff.desc}
                </div>
                <div class="mt-3">
                    ${tr_level_max} <span class="text-my-yellow"
                    id="max${staff.id}">${staff.levelMax}</span>.
                </div>
                <div>
                    ${tr_cost} <span class="text-my-yellow">${staff.costE} E</span>
                    <span class="text-my-yellow">${staff.costDD} DD</span>
                </div>
                <!-- <div> -->
                <!--                    Le coût de construction des collecteurs est réduit de-->
<!--                    <span class="text-my-yellow">11 E</span>-->
<!--                    et <span class="text-my-yellow">25 DD</span>-->
<!--                    par niveau.-->
                <!--    tr_effect  <span class="text-my-yellow"> ??? E tr_and ??? DD</span>  -->
               <!-- </div>  -->
                <div class="text-end mt-3">
                    <div>
                        <span class="bg-white text-dark fz22 pe-3 ps-2 py-1 game-level-button">${tr_level} 
                        <span id="level${staff.id}">${count}</span>
                        </span>
                        <span class="${ can ? 'bg-warning' : 'bg-secondary' } text-dark fz22 py-1 px-2 buy-staff-button pointer"
                        data-id="${staff.id}">+</span>
                    </div>
                </div>
            </div>
        </div>
    `;
    staffs.append(div);
}

document.querySelectorAll('.buy-staff-button').forEach(
    (b) => {
        // buy staff on click
        b.onclick = () => {
            let id = Number(b.getAttribute('data-id'))
            let levelMax = Number(document.getElementById('max'+id).innerText);
            // buy
            let bought = Number(game.mappings.getMapping(game.actions.BUY_STAFF).code(id));
            let levelIDDIV = document.getElementById('level'+id)

            // set new level
            let level = Number(levelIDDIV.innerText) + bought;
            levelIDDIV.innerText = level+"";

            // check max
            if (level === levelMax) {
                // else disable
                b.classList.remove('bg-warning');
                b.classList.add('bg-secondary');
                b.onclick = null;
            }
        };
    }
)