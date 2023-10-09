#include "CubeImmediateMode.h"
#include <GL/glew.h>

static void drawQuadFaceTriangles(vec3 a, vec3 b, vec3 c, vec3 d) {
    glVertex3dv(&a.x);
    glVertex3dv(&b.x);
    glVertex3dv(&c.x);

    glVertex3dv(&c.x);
    glVertex3dv(&d.x);
    glVertex3dv(&a.x);
}

void CubeImmediateMode::draw() {
    glBegin(GL_TRIANGLES);
    //front
    glColor3dv(&red.x);
    drawQuadFaceTriangles(a, b, c, d);
    //back
    glColor3dv(&green.x);
    drawQuadFaceTriangles(h, g, f, e);
    //left
    glColor3dv(&blue.x);
    drawQuadFaceTriangles(e, a, d, h);
    //right
    glColor3dv(&yellow.x);
    drawQuadFaceTriangles(b, f, g, c);
    //top
    glColor3dv(&white.x);
    drawQuadFaceTriangles(d, c, g, h);
    //bottom
    glColor3dv(&black.x);
    drawQuadFaceTriangles(b, a, e, f);
    glEnd();
}
