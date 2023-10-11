#include "CubeImmediateMode.h"
#include <GL/glew.h>

static void drawQuadFaceTriangles(vec3 a, vec3 b, vec3 c, vec3 d) {
    glTexCoord2d( 0, 1);
    glVertex3dv(&a.x);
    glTexCoord2d(1, 1);
    glVertex3dv(&b.x);
    glTexCoord2d(1, 0);
    glVertex3dv(&c.x);

    glTexCoord2d(1, 0);
    glVertex3dv(&c.x);
    glTexCoord2d(0, 0);
    glVertex3dv(&d.x);
    glTexCoord2d(0, 1);
    glVertex3dv(&a.x);
}

CubeImmediateMode::CubeImmediateMode() : texture("Lenna.png") {}

void CubeImmediateMode::draw() {

    glEnable(GL_TEXTURE_2D);
    texture.bind();

    glColor4ub(255, 255, 255, 255);

    glBegin(GL_TRIANGLES);
    //front
    //glColor3dv(&red.x);
    drawQuadFaceTriangles(a, b, c, d);
    //back
    //glColor3dv(&green.x);
    drawQuadFaceTriangles(h, g, f, e);
    //left
    //glColor3dv(&blue.x);
    drawQuadFaceTriangles(e, a, d, h);
    //right
    //glColor3dv(&yellow.x);
    drawQuadFaceTriangles(b, f, g, c);
    //top
    //glColor3dv(&white.x);
    drawQuadFaceTriangles(d, c, g, h);
    //bottom
    //glColor3dv(&black.x);
    drawQuadFaceTriangles(b, a, e, f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
