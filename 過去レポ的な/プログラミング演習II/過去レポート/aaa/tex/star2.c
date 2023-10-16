  glBegin(GL_LINE_STRIP);
  for (i = 0; i < N_VERTEX-1; i++) {
    theta = rot + dt*i;
    for (delta = i+1; delta < N_VERTEX; delta++) {
      x = cos(theta);
      y = sin(theta);
      glVertex2d(x, y);
      x = cos(theta-delta*dt);
      y = sin(theta-delta*dt);
      glVertex2d(x, y);
    }
  }