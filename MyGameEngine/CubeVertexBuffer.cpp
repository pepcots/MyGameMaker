#include "CubeVertexBuffer.h"
#include <GL/glew.h>
#include <array>

using namespace std;

CubeVertexBuffer::CubeVertexBuffer() :
	Cube() {

    array<vec3, NUM_VERTEXS> vertex_data = {
        a,b,c,c,d,a,
        h,g,f,f,e,h,
        e,a,d,d,h,e,
        b,f,g,g,c,b,
        d,c,g,g,h,d,
        b,a,e,e,f,b
    };

    glGenBuffers(1, &_vertex_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * vertex_data.size(), vertex_data.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    array<vec3,NUM_VERTEXS> color_data = {
        red,red,red,red,red,red,
        green,green,green,green,green,green,
        blue,blue,blue,blue,blue,blue,
        yellow,yellow,yellow,yellow,yellow,yellow,
        white,white,white,white,white,white,
        black,black,black,black,black,black,
    };

    glGenBuffers(1, &_color_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _color_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * color_data.size(), color_data.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CubeVertexBuffer::draw() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
    glVertexPointer(3, GL_DOUBLE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, _color_buffer_id);
    glColorPointer(3, GL_DOUBLE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 3 * 2 * 6);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
