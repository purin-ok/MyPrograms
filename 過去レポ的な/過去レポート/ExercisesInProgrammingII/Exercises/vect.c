/* 3D vector */
#include <math.h>
#include <GL/glut.h>

/* w = v1 + v2 */
void vect_add(GLdouble v1[], GLdouble v2[], GLdouble w[])
{
	int i;
	for (i = 0; i < 3; i++)
	{
		w[i] = v1[i] + v2[i];
	}
}

/* w = v1 - v2 */
void vect_sub(GLdouble v1[], GLdouble v2[], GLdouble w[])
{
	int i;
	for (i = 0; i < 3; i++)
	{
		w[i] = v1[i] - v2[i];
	}
}

/* w = s * v */
void vect_scale(GLdouble s, GLdouble v[], GLdouble w[])
{
	int i;
	for (i = 0; i < 3; i++)
	{
		w[i] = s * v[i];
	}
}
/* |v| */
GLdouble vect_norm(GLdouble v[])
{
	int i;
	GLdouble norm = 0.0;
	for (i = 0; i < 3; i++)
	{
		norm += v[i] * v[i];
	}
	norm = sqrt(norm);
	return norm;
}
/* v1 dot v2 */
//GLdouble vect_innerproduct(GLdouble v1[], GLdouble v2[]);
/* v1 cross v2 */
void vect_outerproduct(GLdouble v1[], GLdouble v2[], GLdouble w[])
{
	int i;
	for (i = 0; i < 3; i++)
	{
		w[i] = (v1[(i+1)%3] * v2[(i+2)%3]) - (v1[(i+2)%3] * v2[(i+1)%3]);
	}
}

