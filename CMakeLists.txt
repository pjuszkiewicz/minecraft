cmake_minimum_required(VERSION 3.5.0)
project(minecraft VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(
        minecraft
        src/lib/glad/glad.c
        src/main.cpp
        src/lib/window/window.cpp
        src/lib/texture/texture.cpp
        src/lib/shader/shader.cpp
        src/lib/renderer/renderer.cpp
        src/lib/player/player.cpp
        src/lib/mesh/mesh.cpp
        src/lib/game/game.cpp
        src/lib/camera/camera.cpp
        src/lib/chunk/chunk.cpp
)

target_link_libraries(minecraft glfw)
# target_link_libraries(minecraft include/glad/glad.h)
# target_link_libraries(minecraft src/lib/KHR/khrplatform.h)
