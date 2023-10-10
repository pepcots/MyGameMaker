#include "CubeInterleavedVBO.h"
#include <GL/glew.h>
#include <array>
#include <vector>

using namespace std;

CubeInterleavedVBO::CubeInterleavedVBO() :
    Cube() {

    array<vec3, NUM_VERTEXS> vertex_data = {
        a,b,c,c,d,a,
        h,g,f,f,e,h,
        e,a,d,d,h,e,
        b,f,g,g,c,b,
        d,c,g,g,h,d,
        b,a,e,e,f,b
    };

    array<vec3, NUM_VERTEXS> color_data = {
        red,red,red,red,red,red,
        green,green,green,green,green,green,
        blue,blue,blue,blue,blue,blue,
        yellow,yellow,yellow,yellow,yellow,yellow,
        white,white,white,white,white,white,
        black,black,black,black,black,black,
    };

    vector<vec3> interleaved_data;
    for (size_t i = 0; i < vertex_data.size(); ++i) {
        interleaved_data.push_back(vertex_data[i]);
        interleaved_data.push_back(color_data[i]);
    }

    glGenBuffers(1, &_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * interleaved_data.size(), interleaved_data.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CubeInterleavedVBO::draw() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
    glVertexPointer(3, GL_DOUBLE, sizeof(vec3)*2, nullptr);
    glColorPointer(3, GL_DOUBLE, sizeof(vec3)*2, (void*)sizeof(vec3));
    glDrawArrays(GL_TRIANGLES, 0, NUM_VERTEXS);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

CubeInterleavedVBO::~CubeInterleavedVBO() {
    glDeleteBuffers(1, &_buffer_id);
}

