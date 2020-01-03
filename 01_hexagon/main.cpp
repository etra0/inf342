#include <stdio.h>
#include <cstring>
#include<GL/glut.h>

typedef GLfloat point2[2];

void display_hexagon(point2 *starting_point, float s_angle) {
}

void display() {
    point2 starting_point = {-1, -1};
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
    glutInitWindowSize(500, 500);
    glutCreateWindow("The amazing hexagon");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}
