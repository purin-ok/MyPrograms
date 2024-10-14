// チェックボックスの選択された値を表示する関数
function updateCheckboxValues() {
  const checkboxes = document.getElementsByName("know");
  const selectedValues = Array.from(checkboxes)
      .filter(checkbox => checkbox.checked) // チェックされている項目だけを取得
      .map(checkbox => checkbox.value);     // チェックされた値を取得
  
  // 選択された値がある場合のみ表示
  document.getElementById("checkbox-ans").innerHTML = selectedValues.join("<br>");
}