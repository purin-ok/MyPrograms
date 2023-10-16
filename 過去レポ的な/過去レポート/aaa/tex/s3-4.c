GLdouble vP[4][3] = {{1.000, 0.0000, 0.000},
                     {-0.333, 0.943, 0.000},
                     {-0.333, -0.471, 0.816},
                     {-0.333, -0.471, -0.816}};
GLdouble nV[4][3];
GLdouble vert_n[4][3];
int tP[4][3] = {{0, 1, 2}, {0, 3, 1}, {0, 2, 3}, {1, 3, 2}};
int reversTP[4][3] = {{0, 1, 2}, {0, 1, 3}, {0, 2, 3}, {1, 2, 3}};

void display(void) {
    int i, j;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            //各頂点に法線ベクトルを設定
            glNormal3dv(vert_n[tP[i][j]]);
            glVertex3dv(vP[tP[i][j]]);
        }
    }
    glEnd();
    glutSwapBuffers();
}

void init(void) {
    int i, j;
    GLdouble v1[3], v2[3], tmp[3];
    GLdouble n;
    /*中略*/
    //各面の法線ベクトルを求める
    for (i = 0; i < 4; i++) {
        vect_sub(vP[tP[i][0]], vP[tP[i][1]], v1);
        vect_sub(vP[tP[i][1]], vP[tP[i][2]], v2);
        cross(v1, v2, tmp);
        n = vect_norm(tmp);
        vect_scale(1.0 / n, tmp, nV[i]);
    }
    //頂点の法線ベクトルを求める
    for (i = 0; i < 4; i++) {
        vect_sum(nV[reversTP[i][0]], nV[reversTP[i][1]], tmp);
        vect_sum(tmp, nV[reversTP[i][2]], tmp);
        n = vect_norm(tmp);
        vect_scale(1.0 / n, tmp, vert_n[i]);
    }
}