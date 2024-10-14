changeNumber = function () {
  document.getElementById("number-ans").innerHTML = this.value;
}

window.onload = function() {
  document.getElementById("student-number").onkeyup=changeNumber
}