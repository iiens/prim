// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.

const {TrKeys,Translation} = require("../../utils/translation");

//todo: fix ??? in staff pane
// and also add E/DD values in this menu
win.replaceText('manage-staff', 'Gérer votre Personnel')

let staffs = document.getElementById("staff-list");

// add all staffs
for (const entry of game.map.staffList.entries()) {
    let staff = entry[0];
    let count = entry[1];
    let div = document.createElement("div");
    div.classList.add("mt-3");
    div.innerHTML = `
        <div class="fz22">
            <div class="settings-background ps-2 py-1 text-white">
                <img src="../../assets/img/game/fisaH.png" alt="">
                <span>${staff.name}</span>
            </div>
            <div class="content-background p-3">
                <div>
                    ${staff.desc}
                </div>
                <div class="mt-3">
                    Niveau max : <span class="text-my-yellow">???</span>.
                </div>
                <div>
                    Cout d'amélioration : <span class="text-my-yellow">${staff.costE} E</span>
                    <span class="text-my-yellow">${staff.costDD} DD</span>
                </div>
                <div>
                <!--                    Le coût de construction des collecteurs est réduit de-->
<!--                    <span class="text-my-yellow">11 E</span>-->
<!--                    et <span class="text-my-yellow">25 DD</span>-->
<!--                    par niveau.-->
                    Réduction actuelle de <span class="text-my-yellow"> ??? E et ??? DD</span>
                </div>
                <div class="text-end mt-3">
                    <div>
                        <span class="bg-white text-dark fz22 pe-3 ps-2 py-1 game-level-button">LEVEL 
                        <span id="level${staff.id}">${count}</span>
                        </span>
                        <span class="bg-warning text-dark fz22 py-1 px-2 buy-staff-button pointer"
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
            let remaining = Number(game.mappings.getMapping(game.actions.BUY_STAFF).code(id));
            let levelIDDIV = document.getElementById('level'+id)
            // 1 is because we buy one staff so remaining becomes 0 if bought
            levelIDDIV.innerText = (Number(levelIDDIV.innerText) + 1 - remaining)+"";
        };
    }
)