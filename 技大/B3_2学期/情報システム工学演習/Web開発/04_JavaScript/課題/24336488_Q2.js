changeNumber = function () {
  document.getElementById("number-ans").innerHTML = this.value;
}

window.onload = function() {
  document.getElementById("student-number").onkeyup = changeNumber
  
  // チェックボックスの処理
  const checkboxes = document.getElementsByName("know");
  checkboxes.forEach((checkbox) => {
    checkbox.addEventListener("change", updateCheckboxValues);
  });
  
  // ドロップダウンリストの処理1
  const dropdown_1 = document.getElementById("country-id");
  dropdown_1.addEventListener("change", updateDropdown1Value);

  // ドロップダウンリストの処理2
  const dropdown_2 = document.getElementById("problem-select");
  dropdown_2.addEventListener("change",updateDropdown2Value)
}