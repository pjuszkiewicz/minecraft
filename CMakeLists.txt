cmake_minimum_required(VERSION 3.5.0)
project(minecraft VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(
        minecraft
        vendor/glad/glad.c
        src/main.cpp
        src/engine/window/Window.cpp
        src/engine/renderer/Texture.cpp
        src/engine/renderer/Shader.cpp
        src/engine/renderer/Renderer.cpp
        src/engine/player/player.cpp
        src/engine/renderer/mesh.cpp
        src/engine/game/Game.cpp
        src/engine/player/Camera.cpp
        src/engine/Constants.h
        src/engine/renderer/geometry/cube_geometry.h
        src/engine/utils/assets_manager.cpp
        src/engine/utils/assets_manager.h
        src/engine/renderer/geometry/sphere_geometry.h
        src/engine/renderer/geometry/pyramid_geometry.h
        src/engine/renderer/materials/basic_material.cpp
        src/engine/renderer/materials/basic_material.h
)

target_link_libraries(minecraft glfw)