/* 3D vector */
#if !defined(VECT_H)
#define VECT_H

/* w = v1 + v2 */
void vect_add(GLdouble v1[], GLdouble v2[], GLdouble w[]);
/* w = v1 - v2 */
void vect_sub(GLdouble v1[], GLdouble v2[], GLdouble w[]);
/* w = s * v */
void vect_scale(GLdouble s, GLdouble v[], GLdouble w[]);
/* |v| */
GLdouble vect_norm(GLdouble v[]);
/* v1 dot v2 */
//GLdouble vect_innerproduct(GLdouble v1[], GLdouble v2[]);
/* v1 cross v2 */
void vect_outerproduct(GLdouble v1[], GLdouble v2[], GLdouble w[]);

#endif /* VECT_H */
