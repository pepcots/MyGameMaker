#include "MyGameEngine.h"
#include "GL\glew.h"

double angle = 0.0;

void MyGameEngine::step(double dt) {
	const double angle_vel = 2 * 3.1416; // 2 PI rads / sec
	angle += angle_vel * dt;
}

void MyGameEngine::render() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotated(angle, 0, 0, 1);

    glColor4ub(255, 0, 0, 255);
    glBegin(GL_TRIANGLES);
    glVertex3d(-0.25, -0.25, 0);
    glVertex3d(0.25, -0.25, 0);
    glVertex3d(0, 0.25, 0);
    glEnd();
}
