void display(void) {
	int i, j;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 3; j++) {
			glNormal3dv(vert_n[tP[i][j]]);
			glVertex3dv(vP[tP[i][j]]);
		}
	}
	glEnd();
	glutSwapBuffers();
}