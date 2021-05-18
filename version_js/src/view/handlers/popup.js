//
// Simple file to handle popup close
//
let close = document.getElementById('game-popup-close')
if (close){
    hidePopup(); // hide at the start
    // add listener
    close.onclick = hidePopup;
}

function hidePopup() {
    let popup = document.getElementById('popup-div');
    popup.classList.add('d-none');
}

