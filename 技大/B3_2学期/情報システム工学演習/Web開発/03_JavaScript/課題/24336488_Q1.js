function changeRadioIs() {
  document.getElementById("radio-ans").innerText = document.getElementById("Israel-value").innerText;
}
function changeRadioHa() {
  document.getElementById("radio-ans").innerText = document.getElementById("Hamas-value").innerText;
}

window.onload = function () {
  document.getElementById("Israel").onclick = changeRadioIs;
  document.getElementById("Hamas").onclick = changeRadioHa;
}