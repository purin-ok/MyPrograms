function changeColor(){ 
  const elements = document.getElementsByClassName('message');
  for( const element of elements){
    element.style.color = 'red';
  }
  for( var i=0; elements.length; i++ ){
    elements[i].style.fontSize = '48px';
  }
}

window.onload=function(){
  document.getElementById('change').onclick = changeColor;
}

