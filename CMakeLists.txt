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
        src/lib/Meshes/Mesh.cpp
        src/lib/Meshes/ChunkMesh.cpp
        src/lib/Game/Game.cpp
        src/lib/Player/Camera.cpp
        src/lib/World/Chunk.cpp
        src/lib/World/World.cpp
        src/lib/World/World.h
        src/lib/Constants.h
        src/lib/Meshes/ChunkBuilder.cpp
        src/lib/Meshes/ChunkBuilder.h
        src/lib/Meshes/CrosshairMesh.cpp
        src/lib/Meshes/CrosshairMesh.h
        src/lib/Objects/Cube.h
        src/lib/Game/DateTime.cpp
        src/lib/Game/DateTime.h
        src/lib/Renderer/ShadowMap.cpp
        src/lib/Renderer/ShadowMap.h
        src/lib/Renderer/Material.cpp
        src/lib/Renderer/Material.h
        src/lib/Materials/SunAndMoonMaterial.h
        src/lib/Utils/AssetsManager.cpp
        src/lib/Utils/AssetsManager.h
        src/lib/Materials/WorldMaterial.h
        src/lib/Materials/CrosshairMaterial.h
        src/lib/Materials/ShadowMappingMaterial.h
        src/lib/Game/GameObject.cpp
        src/lib/Game/GameObject.h
        src/lib/GameObjects/SunAndMoon.cpp
        src/lib/GameObjects/SunAndMoon.h
)

target_link_libraries(minecraft glfw)