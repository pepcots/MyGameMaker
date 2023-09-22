git submodule update --recursive --remote
call ..\vcpkg\bootstrap-vcpkg.bat
..\vcpkg\vcpkg.exe install opengl glew sdl2 imgui[opengl3-binding,sdl2-binding]
