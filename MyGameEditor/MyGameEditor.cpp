#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include "../MyGameEngine/MyGameEngine.h"

using namespace std;
using namespace chrono;

static const unsigned int WINDOW_WIDTH = 576*4/3;
static const unsigned int WINDOW_HEIGHT = 576;
static const unsigned int FPS = 60;
static const auto FDT = 1.0s / FPS;

static SDL_Window* initSDLWindowWithOpenGL() {
    if(SDL_Init(SDL_INIT_VIDEO)!=0) throw exception(SDL_GetError());
    
    SDL_version compiled;
    SDL_VERSION(&compiled);
    cout << "SDL Compiled with " << to_string(compiled.major) << '.' << to_string(compiled.minor) << '.' << to_string(compiled.patch);

    SDL_version linked;
    SDL_GetVersion(&linked);
    cout << "SDL Linked with "  << to_string(linked.major) << '.' << to_string(linked.minor) << '.' << to_string(linked.patch);

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
    if(!gl_context) throw exception(SDL_GetError());
    if(SDL_GL_MakeCurrent(window,gl_context)!=0) throw exception(SDL_GetError());
    if(SDL_GL_SetSwapInterval(1)!=0) throw exception(SDL_GetError());
    return gl_context;
}

static void deinitSDL(SDL_Window* window, SDL_GLContext gl_context) {
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

static void initOpenGL() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

static void initImGui(SDL_Window* window, SDL_GLContext gl_context) {
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init();
}

static void deinitImGui() {
    ImGui_ImplSDL2_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

static void renderImGui() {
    ImGui_ImplSDL2_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    ImGui::Text("Hello world, I'm GUI!");
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

static bool processSDLEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {

        ImGui_ImplSDL2_ProcessEvent(&event);

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

int main(int argc, char* argv[])
{
    try {
        auto window = initSDLWindowWithOpenGL();
        auto gl_context = createSdlGlContext(window);
        initOpenGL();
        initImGui(window,gl_context);

        {
            MyGameEngine engine;
            engine.camera.fov = 60;
            engine.camera.aspect = static_cast<double>(WINDOW_WIDTH) / WINDOW_HEIGHT;
            engine.camera.zNear = 0.1;
            engine.camera.zFar = 100;
            engine.camera.eye = vec3(5, 1.75, 5);
            engine.camera.center = vec3(0, 1, 0);
            engine.camera.up = vec3(0, 1, 0);


            while (processSDLEvents()) {
                const auto frame_start = steady_clock::now();
                engine.step(FDT);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
                engine.render();
                renderImGui();
                SDL_GL_SwapWindow(window);
                const auto frame_end = steady_clock::now();
                const auto frame_duration = frame_end - frame_start;
                if (frame_duration < FDT) this_thread::sleep_for(FDT - frame_duration);
            }
        }

        deinitImGui();
        deinitSDL(window, gl_context);

        return EXIT_SUCCESS;
    }
    catch(const exception& ex) {
        cerr << ex.what() << endl;
        return EXIT_FAILURE;
    }
}