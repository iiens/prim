// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.
//todo: maybe a table to summarize
//todo: maybe a direct value of the reduction or what the staff is currently doing
const {TrKeys,Translation} = require("../../utils/translation");
let staffs = document.getElementById("staff-list");

// add all staffs
for (const entry of game.map.staffList.entries()) {
    let staff = entry[0];
    let count = entry[1];
    let cost_title = Translation.get(TrKeys.STAFF_COST);
    let hired_count_title = Translation.get(TrKeys.STAFF_HIRED_COUNT);
    let div = document.createElement("div");
    let and_word =Translation.get(TrKeys.AND_WORD);
    div.classList.add("border", "border-dark" ,"mt-3", "p-3")
    div.innerHTML = `<div class="">
                <span class="fw-bold">${staff.name}</span>
                <i class="text-success">(id=${staff.id})</i>
            </div>
            <p>${staff.desc}</p>
            <span>
                ${cost_title} <span class="text-success">${staff.costE}</span> E ${and_word}
                 <span class="text-success">${staff.costDD}</span> DD <br>
                ${hired_count_title} <span class="text-success">${count}</span> <br>
            </span>`
    staffs.append(div)
}