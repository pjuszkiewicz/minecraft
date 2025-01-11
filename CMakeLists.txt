cmake_minimum_required(VERSION 3.5.0)
project(minecraft VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(
        minecraft
        src/lib/glad/glad.c
        src/main.cpp
        src/lib/Window/Window.cpp
        src/lib/Texture/Texture.cpp
        src/lib/Shader/Shader.cpp
        src/lib/Renderer/Renderer.cpp
        src/lib/Player/Player.cpp
        src/lib/Mesh/Mesh.cpp
        src/lib/Mesh/ChunkMesh.cpp
        src/lib/Game/Game.cpp
        src/lib/Camera/Camera.cpp
        src/lib/Chunk/Chunk.cpp
        src/lib/Buffers/VBO.cpp
        src/lib/Buffers/VAO.cpp
        src/lib/World/World.cpp
        src/lib/World/World.h
        src/lib/Texture/TexturePack.cpp
        src/lib/Texture/TexturePack.h
        src/lib/Material/Material.cpp
        src/lib/Material/Material.h
        src/lib/Constants.h
)

target_link_libraries(minecraft glfw)
# target_link_libraries(minecraft include/glad/glad.h)
# target_link_libraries(minecraft src/lib/KHR/khrplatform.h)
