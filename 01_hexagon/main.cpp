#include <stdio.h>
#include <cstring>
#include <cmath>
#include <GL/glut.h>
#define M_PI           3.14159265358979323846  /* pi */

typedef GLfloat point2[2];

void rotate_vec(point2 *vec, float angle) {
    (*vec)[0] = cos(angle);
    (*vec)[1] = sin(angle);
}

// El hexagono se construye de forma "vectorial", es decir, desde
// un punto inicial se le va sumando un vector que se va rotando.
void display_hexagon(point2 *starting_point, float s_angle) {
    point2 *p = (point2 *)malloc(sizeof(GLfloat)*2);
    point2 adding_vec = {0, 0};

    float angle = s_angle;
    int i;
    memcpy(p, starting_point, sizeof(GLfloat)*2);
    printf("%f %f\n", (*p)[0], (*p)[1]);
    fflush(stdin);

    glBegin(GL_POLYGON);
    for (i = 0; i < 7; i++) {
        glVertex2fv(*p);
        (*p)[0] += adding_vec[0];
        (*p)[1] += adding_vec[1];
        rotate_vec(&adding_vec, angle);
        angle += M_PI/3;
    }
    free(p);
    glEnd();
}

void display() {
    point2 starting_point = {-.5, -1};
    glClear(GL_COLOR_BUFFER_BIT);
    display_hexagon(&starting_point, 0);
    glFlush();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1, 1, 1, 1);
    glColor3f(1, 0, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("The Amazing Red Hexagon");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}
