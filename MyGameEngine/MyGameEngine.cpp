#include "MyGameEngine.h"
#include <GL\glew.h>
#include <glm/ext/matrix_transform.hpp>
#include <vector>
#include <IL/il.h>

#include "CubeImmediateMode.h"
#include "CubeVertexArray.h"
#include "CubeVertexBuffer.h"
#include "CubeInterleavedVBO.h"
#include "CubeWireframeIVBO.h"

#include "Mesh.h"

#include "GameObject.h"
#include "Shader.h"
#include "default.vsh.h"
#include "default.fsh.h"
#include "flat.sh.h"
#include "phong.sh.h"

using namespace std;

Shader s_flat;
Shader s_phong;

MyGameEngine::MyGameEngine() {

    ilInit();

    auto glew_init_error = glewInit();
    if (glew_init_error != GLEW_OK) throw exception((char*)glewGetErrorString(glew_init_error));
    if (!GLEW_VERSION_3_1) throw exception("OpenGL 3.1 Not Supported!");

    auto shader_ptr = make_shared<Shader>();
    shader_ptr->compile( default_vsh, default_fsh);

    s_flat.compile(flat_vsh, flat_fsh);
    s_phong.compile(phong_vsh, phong_fsh);

#pragma region Configure scene
    auto mesh_ptrs = Mesh::loadFromFile("Assets/BakerHouse.fbx");
    auto& mesh1_ref = scene.addChild(mesh_ptrs.front());
    scene.addChild();
    auto& mesh2_ref = scene.addChild(mesh_ptrs.back());

    mesh1_ref.setEventHandler("EventHandler1");
    mesh2_ref.setEventHandler("EventHandler2");

    mesh2_ref.shaderPtr() = shader_ptr;

    scene.removeChild(++scene.children().begin());

#pragma endregion

}

void MyGameEngine::step(std::chrono::duration<double> dt) {
    scene.step(dt.count());
}

static void drawAxis() {
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glColor3ub(255, 0, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0.8, 0, 0);
    glColor3ub(0, 255, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0.8, 0);
    glColor3ub(0, 0, 1);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0, 0.8);
    glEnd();
}

static void drawGrid(int grid_size, int grid_step) {
    glLineWidth(1.0);
    glColor3ub(128, 128, 128);

    glBegin(GL_LINES);
    for (int i = -grid_size; i <= grid_size; i += grid_step) {
        //XY plane
        glVertex2i(i, -grid_size);
        glVertex2i(i,  grid_size);
        glVertex2i(-grid_size, i);
        glVertex2i( grid_size, i);

        //XZ plane
        glVertex3i(i, 0, -grid_size);
        glVertex3i(i, 0, grid_size);
        glVertex3i(-grid_size, 0, i);
        glVertex3i( grid_size, 0, i);
    }
    glEnd();
}

static void drawPlane(int inc) {
    glColor3ub(128, 0, 0);
    glNormal3d(0, 1, 0);
    glBegin(GL_QUADS);

    for (int x = -100; x < 100; x+=inc) {
        for (int z = -100; z < 100; z+=inc) {
            glVertex3i(x, 0, z+inc);
            glVertex3i(x+inc, 0, z+inc);
            glVertex3i(x+inc, 0, z);
            glVertex3i(x, 0, z);
        }
    }

    glEnd();
}

void MyGameEngine::render() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(camera.fov, camera.aspect, camera.zNear, camera.zFar);

    glMatrixMode(GL_MODELVIEW);

    const mat4 viewMat = glm::lookAt(camera.eye, camera.center, camera.up);
    glLoadMatrixd(&viewMat[0][0]);
    
    drawGrid(100, 1);
    drawAxis();

    //scene.paint();

    //plane
    static double a = 0;
    a += 0.025;
    const vec3 lightPos(sin(a)*2, 1.5+sin(a*0.5), cos(a)*2);
    const vec3 lightViewPos = viewMat * vec4(lightPos, 1.0);
    
    glColor3ub(255, 255, 0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex3dv(&lightPos.x);
    glEnd();

    static int frame = 0;

    auto& shader_ref = ( ((++frame) % 600)<300) ? s_flat : s_phong;

    shader_ref.bind();
    shader_ref.setUniform("uLightViewPos", lightViewPos);
    drawPlane(2);

    static CubeImmediateMode cube;
    cube.draw();

    glPushMatrix();
    glTranslated(-2, 0.5, 0);
    cube.draw();
    glPopMatrix();

    glUseProgram(0);


    assert(glGetError() ==GL_NONE);
}
