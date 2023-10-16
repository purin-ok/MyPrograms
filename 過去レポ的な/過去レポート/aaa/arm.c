//stat 0:í‚é~Å@1;âÒì]Å@-1:ãtâÒì]Å@
GLfloat rotAng[3];
int b_stat = 0, l_stat = 0, u_stat = 0, pause = 0;

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 1, 1.5, 0, 0, 0, 0, 1, 0);
	glRotated(rotAng[0], 0, 1, 0);

	glRotated(rotAng[0], 0, 1, 0);
	glCallList(ID_B);

	//ë‰ç¿
	if (pause == 0) {
		if (b_stat == 1) rotAng[0] += 3.0;
		if (b_stat == -1) rotAng[0] -= 3.0;
	}

	//â∫òr
	glTranslated(0, HEIGHT_B, 0);
	glRotated(rotAng[1], 0, 0, 1);
	glCallList(ID_L);

	if (pause == 0) {
		if (l_stat == 1) rotAng[1] += 3.0;
		if (l_stat == -1) rotAng[1] -= 3.0;
	}

	//è„òr
	glTranslated(0, HEIGHT_L, 0);
	glRotated(rotAng[2], 0, 0, 1);
	glCallList(ID_U);

	if (pause == 0) {
		if (u_stat == 1) rotAng[2] += 3.0;
		if (u_stat == -1) rotAng[2] -= 3.0;
	}

	glutSwapBuffers();

}

void keyin(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	case 'Q':exit(0); break;
	case 'w':b_stat = 1;; break;
	case 'e':b_stat = -1; break;
	case 'r':b_stat = 0; break;
	case 's':l_stat = 1; break;
	case 'd':l_stat = -1; break;
	case 'f':l_stat = 0; break;
	case 'x':u_stat = 1; break;
	case 'c':u_stat = -1; break;
	case 'v':u_stat = 0; break;
	case 'z': {dance = !dance; b_stat = 0;
		l_stat = 0; u_stat = 0; break;
	}
	case 'p':pause = !pause; break;
	}
}