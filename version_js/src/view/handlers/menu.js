const btn_eng = document.getElementById('button_eng');
const btn_fr = document.getElementById('button_fr');

btn_eng.addEventListener('click', changeLang)
btn_fr.addEventListener('click', changeLang)

//todo: doc
function changeLang(event){
    console.log(event.target.getAttribute("value"));
    localStorage.setItem("lang", event.target.getAttribute("value"));
}

//todo: set value
btn_fr.setAttribute("value", lang.FR);
btn_eng.setAttribute("value", lang.EN);

//todo: :(
let current = lang.current;
if (current === lang.FR){
    btn_fr.setAttribute("checked","")
} else if (current === lang.EN){
    btn_eng.setAttribute("checked","")
}