#include "CubeVertexArray.h"
#include <GL/glew.h>

CubeVertexArray::CubeVertexArray() :
	Cube(),
	_vertex_data({ 
        a,b,c,c,d,a,
        h,g,f,f,e,h,
        e,a,d,d,h,e,
        b,f,g,g,c,b,
        d,c,g,g,h,d,
        b,a,e,e,f,b
    }),
    _color_data({
        red,red,red,red,red,red,
        green,green,green,green,green,green,
        blue,blue,blue,blue,blue,blue,
        yellow,yellow,yellow,yellow,yellow,yellow,
        white,white,white,white,white,white,
        black,black,black,black,black,black
    })
{
}

void CubeVertexArray::draw() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_VERTEX_ARRAY, 0);
    glVertexPointer(3, GL_DOUBLE, 0, _vertex_data.data());
    glColorPointer(3, GL_DOUBLE, 0, _color_data.data());
    glDrawArrays(GL_TRIANGLES, 0, NUM_VERTEXS);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
