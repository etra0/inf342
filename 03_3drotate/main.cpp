#include <stdio.h>
#include <cstring>
#include <cmath>
#include <GL/glut.h>
#define M_PI           3.14159265358979323846  // pi

typedef GLfloat point3[3];

static float size = 0.8;
float depth = 1*size;

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;
static GLdouble viewer[]= {0, 0, 3};
point3 initial_point = {0,0,0};

GLfloat colors[][3] = {{0.0,0.0,1.0},{1.0,0.0,0.0},
                        {0.0,1.0,0.0},{0.5,0.5,0.0},
                        {1.0,1.0,0.0},{1.0,0.0,1.0},
                        {0.0,1.0,1.0},{0.5,0.5,0.5}};

float x_foo(int i) {
    return sin(M_PI/3*i)*size;
}
float y_foo(int i) {
    return cos(M_PI/3*i)*size;
}

void display_hexagon(point3 point) {
    for (int j = 0; j < 2; j++) {
        glBegin(GL_POLYGON);
        glColor3fv(colors[j]);
        for (int i = 0; i < 7; i++) {
            glVertex3f(x_foo(i),y_foo(i),j*size);
        }
        glEnd();
    }
    for (int j = 0; j < 6; j++) {
        glBegin(GL_POLYGON);
        glColor3fv(colors[j+2]);
        glVertex3f(x_foo(j), y_foo(j), point[2]);
        glVertex3f(x_foo(j+1), y_foo(j+1), point[2]);
        glVertex3f(x_foo(j+1), y_foo(j+1), point[2]+depth);
        glVertex3f(x_foo(j), y_foo(j), point[2]+depth);
        glVertex3f(x_foo(j), y_foo(j), point[2]);
        glEnd();
    }
}

void display() {
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    printf("viewer: %f, %f, %f\n",viewer[0],viewer[1], viewer[2]);
	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    display_hexagon(initial_point);
	glutSwapBuffers();
}

void myReshape(int w, int h) {	
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();
    gluPerspective(60.0, 1.0*w/h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

void keys(unsigned char key, int x, int y) {
    if(key == 'x') viewer[0]-= 0.1;
    if(key == 'X') viewer[0]+= 0.1;
    if(key == 'y') viewer[1]-= 0.1;
    if(key == 'Y') viewer[1]+= 0.1;
    if(key == 'z') viewer[2]+= 0.1;
    if(key == 'Z') viewer[2]-= 0.1;
    if (key == 27) exit(0);
    display();
}

int main(int argc, char **argv) {
    printf("MOVER CAMARA\n- hacia la izquierda con tecla x\n- hacia la derecha con tecla X\n- hacia abajo con tecla y\n- hacia arriba con tecla Y\n- hacia atras con tecla z\n- hacia adelante con tecla Z\n\nTERMINAR CON TECLA ESC\n");
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("The Amazing Red Hexagon");
    glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keys);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
    return 0;
}
