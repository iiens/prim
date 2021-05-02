// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.
//todo: maybe a table to summarize
//todo: maybe a direct value of the reduction or what the staff is currently doing

let staffs = document.getElementById("staff-list");

// add all staffs
for (const entry of game.map.staffList.entries()) {
    let staff = entry[0];
    let count = entry[1];
    let div = document.createElement("div");
    div.classList.add("border", "border-dark" ,"mt-3", "p-3")
    div.innerHTML = `<div class="">
                <span class="fw-bold">${staff.name}</span>
                <i class="text-success">(id=${staff.id})</i>
            </div>
            <p>${staff.desc}</p>
            <span>
                Cost (default): <span class="text-success">${staff.costE}</span> E and
                 <span class="text-success">${staff.costDD}</span> DD <br>
                Hired count: <span class="text-success">${count}</span> <br>
            </span>`
    staffs.append(div)
}