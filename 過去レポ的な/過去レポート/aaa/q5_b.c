for (theta = 0; theta <= 2 * M_PI; theta += 0.05) {
    x = theta - sin(theta);
    y = 1 - cos(theta);
    glVertex2d(x, y);
}