function imageOn(){ 
}
function imageOff(){ 
}
function borderBlue(){ 
}
function borderYellow(){ 
}
function borderRed(){ 
}
function imageBig(){ 
}
function imageNormal(){ 
}
function imageSmall(){ 
}

function imageLeft(){ 
}

window.onload=function(){
  document.getElementById('on').onclick = imageOn;
  document.getElementById('off').onclick = imageOff;

  document.getElementById('blue').onmouseover = borderBlue;
  document.getElementById('yellow').onmouseover = borderYellow;
  document.getElementById('red').onmouseover = borderRed;

  document.getElementById('big').onchange = imageBig;
  document.getElementById('normal').onchange = imageNormal;
  document.getElementById('small').onchange = imageSmall;

  document.getElementById('left').onchange = imageLeft;
}

