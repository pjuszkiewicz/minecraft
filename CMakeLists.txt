cmake_minimum_required(VERSION 3.5.0)
project(minecraft VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(
        minecraft
        vendor/glad/glad.c
        src/main.cpp
        src/engine/window/window.cpp
        src/engine/renderer/texture.cpp
        src/engine/renderer/shader.cpp
        src/engine/renderer/renderer.cpp
        src/engine/player/player.cpp
        src/engine/renderer/mesh.cpp
        src/engine/game/game.cpp
        src/engine/player/camera.cpp
        src/engine/constants.h
        src/engine/renderer/geometry/cube_geometry.h
        src/engine/utils/assets_manager.cpp
        src/engine/utils/assets_manager.h
        src/engine/renderer/geometry/sphere_geometry.h
        src/engine/renderer/geometry/pyramid_geometry.h
        src/engine/renderer/materials/basic_material.h
        src/engine/game/game_objects/plane_object.cpp
        src/engine/game/game_objects/plane_object.h
)

target_link_libraries(minecraft glfw)