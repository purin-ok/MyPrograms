for (theta = 0; theta <= 2 * M_PI; theta += 0.05) {
    x = cos(theta);
    x = x * x * x;
    y = sin(theta);
    y = y * y * y;
    glVertex2d(x, y);
}