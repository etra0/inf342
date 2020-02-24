#include <stdio.h>
#include <cstring>
#include <cmath>
#include <GL/glut.h>
#include <array>
#include <vector>

class Light {
    private:
    GLfloat diffuse[4] = {0, 0, 0, 1};
    GLfloat ambient[4]= {0, 0, 0, 1};
    GLfloat specular[4]= {0, 0, 0, 1};
    GLfloat position[4]= {0.f, 0.f, 0.f, 1};
    GLenum light_source;
    bool enabled = false;

    public:
    Light(std::array<GLfloat, 3> color, std::array<GLfloat, 3> position, GLenum light_source);
    // Activate or deactivate the light, according to `input`
    void toggle(bool input);

    // Update the position according to a delta vector (x, y, z).
    void changePosition(GLfloat x_delta, GLfloat y_delta, GLfloat z_delta);
};


// color & position must be an array of size 3.
Light::Light(std::array<GLfloat, 3> color, std::array<GLfloat, 3> position, GLenum light_source) {
    for(int i = 0;
     i < 3;
     this->diffuse[i] = color[i], 
     this->specular[i] = color[i], 
     this->position[i] = position[i], i++);

    this->light_source = light_source;

    glLightfv(this->light_source, GL_AMBIENT, this->ambient);
    glLightfv(this->light_source, GL_DIFFUSE, this->diffuse);
    glLightfv(this->light_source, GL_SPECULAR, this->specular);
    glLightfv(this->light_source, GL_POSITION, this->position);

    toggle(true);
}

void Light::toggle(bool input) {
    this->enabled = input;
    if (this->enabled) {
        glEnable(this->light_source);
        return;
    }

    glDisable(this->light_source);
}

void Light::changePosition(GLfloat x_delta, GLfloat y_delta, GLfloat z_delta) {
    this->position[0] += x_delta;
    this->position[1] += y_delta;
    this->position[2] += z_delta;

    glLightfv(this->light_source, GL_POSITION, this->position);
}

// This vector will contain all the lights (currently two: red and green).
std::vector<Light> lights;

void draw_cylinder() {
    GLUquadric *t = gluNewQuadric();
    glPushMatrix();

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    GLfloat specular[] = {.2f, .8f, .8f, .8f};
    GLfloat emission[] = {0, 0, 0, 1};
    GLfloat color[] = {.5, .5, .5};

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);

    glColor3fv(color);

    glRotatef(90.0f, 0.0f, 0.1f, 0.0f);
    glTranslatef(0.15, 0, .0f);
    gluCylinder(t, .1, .3, .6, 1000, 1000);

    glPopMatrix();

}

void display() {
    glMatrixMode(GL_MODELVIEW);
    
    glClearColor(.3, .5, .5, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

	gluLookAt(0, 0, 2, 0.0, 0.0, 0.0, 0.0, 1.0f, 0.0);

    // Force the lights to update the position according to the matrix mode.
    for (Light v: lights) v.changePosition(0, 0, 0);

    draw_cylinder();
	glutSwapBuffers();
}

void reshape_callback(int w, int h) {	
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();
    gluPerspective(45.0, 1.0*w/h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

void keys(unsigned char key, int x, int y) {
    GLfloat speed = 0.01;
    
    switch(key) {
        case '0': lights[0].toggle(false); break;
        case '1': lights[0].toggle(true); break;

        case '2': lights[1].toggle(false); break;
        case '3': lights[1].toggle(true); break;

        case 'x': lights[0].changePosition(-speed, 0, 0); break;
        case 'X': lights[0].changePosition(speed, 0, 0); break;
        case 'y': lights[0].changePosition(0, -speed, 0); break;
        case 'Y': lights[0].changePosition(0, speed, 0); break;
        case 'z': lights[0].changePosition(0, 0, -speed); break;
        case 'Z': lights[0].changePosition(0, 0, speed); break;

        case 'a': lights[1].changePosition(-speed, 0, 0); break;
        case 'A': lights[1].changePosition(speed, 0, 0); break;
        case 'b': lights[1].changePosition(0, -speed, 0); break;
        case 'B': lights[1].changePosition(0, speed, 0); break;
        case 'c': lights[1].changePosition(0, 0, -speed); break;
        case 'C': lights[1].changePosition(0, 0, speed); break;

        default:
        break;
    }

    if (key == 27) exit(0);
    display();
}

int main(int argc, char **argv) {
    // The compiler will automatically compress this sentence in one char array. This way is more readable.
    char message[] = "Instrucciones\n"
    "0: Apagar la fuente de luz 0 (rojo)\t\t2: Apagar la fuente de luz 1 (Verde)\n"
    "1: Encender la fuente de luz 0 (rojo)\t\t3: Encender la fuente de luz 1 (verde)\n\n"
    "x: Mover luz 0 -x\t\t\t\tX: Mover luz 0 +x\n"
    "y: Mover luz 0 -y\t\t\t\tY: Mover luz 0 +y\n"
    "z: Mover luz 0 -z\t\t\t\tZ: Mover luz 0 +z\n\n"
    "a: Mover luz 1 -x\t\t\t\tA: Mover luz 1 +x\n"
    "b: Mover luz 1 -y\t\t\t\tB: Mover luz 1 +y\n"
    "c: Mover luz 1 -z\t\t\t\tC: Mover luz 1 +z\n\n";
    printf(message);

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    
	glutInitWindowSize(800, 800);
	glutCreateWindow("The Amazing Red Hexagon");

    glutReshapeFunc(reshape_callback);

    glEnable(GL_LIGHTING);
    glEnable(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);

    // red light
    lights.push_back(Light({1, 0, 0}, {0, .5, 0}, GL_LIGHT0));
    // green light
    lights.push_back(Light({0, 1, 0}, {0, -.5, 0}, GL_LIGHT1));

	glutDisplayFunc(display);
	glutKeyboardFunc(keys);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
    return 0;
}
