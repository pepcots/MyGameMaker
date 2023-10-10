#include "CubeWireframeIVBO.h"
#include <GL/glew.h>
#include <array>

using namespace std;

CubeWireframeIVBO::CubeWireframeIVBO() :
	Cube() {

    glGenBuffers(1, &_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * 8, &a, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    const int NUM_EDGES = 12;
    enum {A=0, B,C,D,E,F,G,H};
    array<unsigned int, NUM_EDGES * 2> lines_indexs = {
       A,B,B,C,C,D,D,A,
       E,F,F,G,G,H,H,E,
       B,F,G,C,
       A,E,H,D
    };

    glGenBuffers(1, &_index_bufer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_bufer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * lines_indexs.size(), lines_indexs.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CubeWireframeIVBO::draw() {
    glLineWidth(3);
    glColor3ub(0, 0, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
    glVertexPointer(3, GL_DOUBLE, 0, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_bufer_id);
    glDrawElements(GL_LINES, 12 * 2, GL_UNSIGNED_INT, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
}

CubeWireframeIVBO::~CubeWireframeIVBO() {
    glDeleteBuffers(1, &_buffer_id);
    glDeleteBuffers(1, &_index_bufer_id);
}
