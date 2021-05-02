// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.

// let current = 1;
//
// console.log(document.win)

// let e = document.getElementById("menu1")
// if (e != null) //menu page
// {
//     let f = (event, input) => {
//         if (input.type === "keyDown"){
//             let e = document.getElementById("menu"+current)
//             if (input.key === "Enter") {
//                 win.webContents.removeListener("before-input-event", f);
//
//                 if (current === 5){
//                     win.close()
//                     return;
//                 } else {
//                     location.href=e.getAttribute('data-to')
//                 }
//             }
//
//             if (input.key === "q") {
//                 win.close()
//                 return;
//             }
//
//             e.classList.remove("selected-menu")
//             if (input.key === "ArrowUp" || input.key === "z"
//                 || input.key === "w"){
//                 if (current > 1){
//                     current--
//                 }
//             }
//             if (input.key === "ArrowDown" || input.key === "s"){
//                 if (current < 5){
//                     current++
//                 }
//             }
//             e = document.getElementById("menu"+current)
//             e.classList.add("selected-menu")
//         }
//     };
//     e.classList.add("selected-menu")
//     for (let i = 1; i <= 5; i++) {
//         e = document.getElementById(`menu${i}`)
//         if (i===5){
//             e.onclick = (event) => {
//                 win.webContents.removeListener("before-input-event", f);
//                 win.close()
//             }
//         } else {
//             e.onclick = (event) => {
//                 win.webContents.removeListener("before-input-event", f);
//                 location.href=event.target.getAttribute('data-to')
//             }
//         }
//     }
//     win.webContents.on("before-input-event", f);
// } else {
//     let e = document.getElementById("rules")
//     if (e != null){
//         let f = (event, input) => {
//             if (input.type === "keyDown"){
//                 if (input.key === "b") {
//                     win.webContents.removeListener("before-input-event", f);
//                     location.href = "index.html"
//                 }
//                 if (input.key === "q") {
//                     win.close()
//                 }
//             }
//         };
//         document.getElementById('go-back').onclick = (e) => {
//             win.webContents.removeListener("before-input-event", f);
//             location.href = "index.html"
//         }
//         win.webContents.on("before-input-event", f);
//     }
// }