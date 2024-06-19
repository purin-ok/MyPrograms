#include<GL/glut.h>

void display(){


}

void init(){


}

int main(int argc, char** argv){

glutInit(&argc,argv);
glutCreateWindow(argv[0]);
glutDisplayFunc(display);
init();
glutMainLoop();
return 0;

}
