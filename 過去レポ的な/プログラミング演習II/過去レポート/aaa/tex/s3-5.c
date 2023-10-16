GLfloat lP1[] = {0.0,1.0,2.0,1.0};
GLfloat lC1[] = {1.0,1.0,1.0,1.0};

void init(void) {
    /*中略*/
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT1, GL_POSITION, lP1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lC1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lC1);
    glEnable(GL_LIGHT1);
    glEnable(GL_CULL_FACE);
    /*中略*/
}
