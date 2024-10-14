function updateDropdown1Value() {
  const dropdown = document.getElementById("country-id");
  const selectedValue = dropdown.value;

  document.getElementById("country-ans").innerHTML = selectedValue;
}

// ドロップダウンリストの選択された値を表示する関数
function updateDropdown2Value() {
  const dropdown = document.getElementById("problem-select");
  const selectedValue = dropdown.value;
  
  // 選択された値がある場合のみ表示
  document.getElementById("select-ans").innerHTML = selectedValue;
}