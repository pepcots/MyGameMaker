#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "../MyGameEngine/MyGameEngine.h"

using namespace std;
using namespace chrono;

static const int WINDOW_WIDTH = 1280;
static const int WINDOW_HEIGHT = 720;
static const int FPS = 60;

static SDL_Window* initSDLWindowWithOpenGL() {
    if (SDL_Init(SDL_INIT_VIDEO)!=0) throw exception(SDL_GetError());
    
    SDL_version compiled;
    SDL_VERSION(&compiled);
    cout << "SDL Compiled with " << std::to_string(compiled.major) << '.' << std::to_string(compiled.minor) << '.' << std::to_string(compiled.patch); 

    SDL_version linked;
    SDL_GetVersion(&linked);
    cout << "SDL Linked with "  << std::to_string(linked.major) << '.' << std::to_string(linked.minor) << '.' << std::to_string(linked.patch);

    // setup SDL window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // GL 3.1 + GLSL 130
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    auto window = SDL_CreateWindow("SDL+OpenGL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (!window) throw exception(SDL_GetError());

    return window;
}

static SDL_GLContext createSdlGlContext(SDL_Window* window) {
    auto gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) throw exception(SDL_GetError());

    if (SDL_GL_MakeCurrent(window, gl_context) != 0) throw exception(SDL_GetError());

    if (SDL_GL_SetSwapInterval(1) != 0) throw exception(SDL_GetError());

    return gl_context;
}

static void initOpenGL() {
    auto glew_init_error = glewInit();
    if (glew_init_error != GLEW_OK) throw exception((char*)glewGetErrorString(glew_init_error));
    if (!GLEW_VERSION_3_1) throw exception("OpenGL 3.1 Not Supported!");

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(1, 1, 1, 1);
}

static bool processSDLEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type) {
        case SDL_QUIT: return false;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE: return false;
            }
            break;
        }
    }
    return true;
}

static void render() {
    
    
   
}

int main(int argc, char **argv)
{
    try {
        auto window = initSDLWindowWithOpenGL();
        auto gl_context = createSdlGlContext(window);
        initOpenGL();

        auto t0 = high_resolution_clock::now();
        auto t1 = high_resolution_clock::now();
        auto dt = 1000ms / FPS;

        MyGameEngine engine;
        while (processSDLEvents()) {
            auto t0 = high_resolution_clock::now();
            engine.step(dt.count()/1000.0);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            engine.render();
            SDL_GL_SwapWindow(window);
            auto t1 = high_resolution_clock::now();
            auto frame_duration = t1 - t0;
            if(frame_duration<dt) this_thread::sleep_for(dt-frame_duration);
        }

        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    catch (const exception& ex) {
        cerr << ex.what() << endl;
    }

    return 0;
}