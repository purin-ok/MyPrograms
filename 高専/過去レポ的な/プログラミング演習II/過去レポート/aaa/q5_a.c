double x, y, theta, cos_theta;

glColor3d(1.0, 0.0, 0.0);
glBegin(GL_LINE_STRIP);
//グラフ描画
for (theta = 0; theta <= 2 * M_PI; theta += 0.05) {
    cos_theta = cos(theta);
    x = cos_theta * (1 + cos_theta);
    y = sin(theta) * (1 + cos_theta);
    glVertex2d(x, y);
}
glEnd();