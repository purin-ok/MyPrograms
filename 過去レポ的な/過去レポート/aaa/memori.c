
char cMinus, cAbs;
glColor3d(0.0, 0.0, 0.0);
// X軸の目盛り文字
for (x = 1; x <= 2.0; x += 1.0) {
    glRasterPos2d(x - 0.05, -0.2);
    //文字をセット
    cMinus = x < 0 ? '-' : ' ';
    cAbs = '0' + abs(x);
    //文字を描画
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cMinus);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cAbs);
}
// Y軸の目盛り文字
for (y = -1; y <= 1; y += 2) {
    glRasterPos2d(-0.275, y - 0.05);
    //文字をセット
    cMinus = y < 0 ? '-' : ' ';
    cAbs = '0' + abs(y);
    //文字を描画
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cMinus);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cAbs);
}