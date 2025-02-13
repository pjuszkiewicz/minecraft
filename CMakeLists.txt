cmake_minimum_required(VERSION 3.5.0)
project(minecraft VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(
        minecraft
        vendor/glad/glad.c
        src/main.cpp
        src/engine/Window/Window.cpp
        src/engine/Renderer/Texture.cpp
        src/engine/Renderer/Shader.cpp
        src/engine/Renderer/Renderer.cpp
        src/engine/Player/Player.cpp
        src/engine/Meshes/Mesh.cpp
        src/engine/Meshes/ChunkMesh.cpp
        src/engine/Game/Game.cpp
        src/engine/Player/Camera.cpp
        src/engine/World/Chunk.cpp
        src/engine/World/World.cpp
        src/engine/World/World.h
        src/engine/Constants.h
        src/engine/Meshes/ChunkBuilder.cpp
        src/engine/Meshes/ChunkBuilder.h
        src/engine/Meshes/CrosshairMesh.cpp
        src/engine/Meshes/CrosshairMesh.h
        src/engine/Objects/Cube.h
        src/engine/Game/DateTime.cpp
        src/engine/Game/DateTime.h
        src/engine/Renderer/Material.cpp
        src/engine/Renderer/Material.h
        src/game/Materials/SunAndMoonMaterial.h
        src/engine/Utils/AssetsManager.cpp
        src/engine/Utils/AssetsManager.h
        src/game/Materials/WorldMaterial.h
        src/game/Materials/CrosshairMaterial.h
        src/engine/Game/IGameObject.cpp
        src/engine/Game/IGameObject.h
        src/game/GameObjects/SunAndMoon.cpp
        src/game/GameObjects/SunAndMoon.h
        src/game/GameObjects/WorldObject.cpp
        src/game/GameObjects/WorldObject.h
        src/game/GameObjects/CrosshairObject.cpp
        src/game/GameObjects/CrosshairObject.h
)

target_link_libraries(minecraft glfw)