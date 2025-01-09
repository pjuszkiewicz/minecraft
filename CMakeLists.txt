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
        src/lib/Shader/shader.cpp
        src/lib/Renderer/renderer.cpp
        src/lib/player/player.cpp
        src/lib/Mesh/mesh.cpp
        src/lib/Mesh/chunkMesh.cpp
        src/lib/Game/game.cpp
        src/lib/Camera/camera.cpp
        src/lib/Chunk/chunk.cpp
        src/lib/Buffers/vbo.cpp
        src/lib/Buffers/vao.cpp
        src/lib/World/world.cpp
        src/lib/World/world.h
        src/lib/texture/TexturePack.cpp
        src/lib/texture/TexturePack.h
        src/lib/Material/Material.cpp
        src/lib/Material/Material.h
        src/lib/Constants.h
)

target_link_libraries(minecraft glfw)
# target_link_libraries(minecraft include/glad/glad.h)
# target_link_libraries(minecraft src/lib/KHR/khrplatform.h)
