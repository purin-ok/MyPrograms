function changeColor() {
  document.getElementById('message').style.color = 'red';
  document.getElementById('message').style.fontSize = '48px';
}



window.onload=function(){
  document.getElementById('change').onclick = changeColor;
}

