// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.
let mappings = document.getElementById("mappings-list");

// all mappings, one per line
for (const mapping of game.mappings.getMappings()) {
    let div = document.createElement("div");
    div.classList.add("border", "border-dark" ,"mt-3", "p-3")
    div.innerHTML = `<div class="">
                <span class="fw-bold">${mapping.key}</span> : 
                ${mapping.desc}
            </div>`
    mappings.append(div)
}
