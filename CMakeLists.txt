cmake_minimum_required(VERSION 3.5.0)
project(minecraft VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(
        minecraft
        vendor/glad/glad.c
        src/main.cpp
        src/lib/Window/Window.cpp
        src/lib/Renderer/Texture.cpp
        src/lib/Renderer/Shader.cpp
        src/lib/Renderer/Renderer.cpp
        src/lib/Player/Player.cpp
        src/lib/Renderer/Mesh.cpp
        src/lib/Renderer/ChunkMesh.cpp
        src/lib/Game/Game.cpp
        src/lib/Player/Camera.cpp
        src/lib/World/Chunk.cpp
        src/lib/World/World.cpp
        src/lib/World/World.h
        src/lib/Constants.h
        src/lib/Renderer/ChunkBuilder.cpp
        src/lib/Renderer/ChunkBuilder.h
        src/lib/Renderer/Crosshair.cpp
        src/lib/Renderer/Crosshair.h
)

target_link_libraries(minecraft glfw)