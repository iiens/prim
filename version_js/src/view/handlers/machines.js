// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.
let machines = document.getElementById("machines-list");

// all machines
for (const machine of config.machines) {
    let div = document.createElement("div");
    div.classList.add("border", "border-dark" ,"mt-3", "p-3")

    // upgrade message
    let up = "", capacity;
    if (machine.canUpgrade) up = `Price (upgrade): 
    <span class="text-success">${machine.costUpgradeE}</span> E and 
    <span class="text-success">${machine.costUpgradeDD}</span> DD <br>`;
    // unlimited capacity
    if (machine.capacity === Number.MAX_VALUE) capacity = '';
    else capacity = `Capacity (default): <span class="text-success">${machine.capacity}</span><br>`;

    div.innerHTML = `<div class="">
                <span class="fw-bold">${machine.name}</span>
                <i class="text-success">(id=${machine.type}, tag=${machine.tag})</i>
            </div>
            <p>${machine.description}</p>
            <span>
                Price:
                <span class="text-success">${machine.costE}</span> E and 
                <span class="text-success">${machine.costDD}</span> DD <br>
                ${up}
                Price (destroy): 
                <span class="text-success">${machine.costDestroyE}</span> E and 
                <span class="text-success">${machine.costDestroyDD}</span> DD <br>
                Orientation (default): <span class="text-success">${machine.defaultOrientation}</span> <br>
                ${capacity}
            </span>`
    machines.append(div)
}