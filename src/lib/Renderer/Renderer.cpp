#include "../../lib/Renderer/Renderer.h"
#include <unordered_set>
#include <thread>

#include "../Game/DateTime.h"



/// Initializuje shadery i tekstury
Renderer::Renderer() {
    // const std::string ASSETS_PATH = "/Users/piotr/Development/C++/minecraft/src/assets";
    const std::string ASSETS_PATH = "/home/piotr/Development/C++/minecraft/src/assets";

    shader = new Shader((ASSETS_PATH + "/shaders/example/vertex.vs").c_str(),
                        (ASSETS_PATH + "/shaders/example/fragment.fs").c_str());
    instancedShader = new Shader((ASSETS_PATH + "/shaders/example/instanced.vs").c_str(),
                                 (ASSETS_PATH + "/shaders/example/instanced.fs").c_str());
    uiShader = new Shader((ASSETS_PATH + "/shaders/example/ui_vertex.vs").c_str(),
                          (ASSETS_PATH + "/shaders/example/ui_fragment.fs").c_str());
    texturePack = new Texture((ASSETS_PATH + "/textures/texturepack.png").c_str(), GL_RGBA);
    crosshair = new Crosshair();
}

/// Czyści ekran kolorem z DateTime::getSkyColor()
void Renderer::clear() {
    glm::vec3 color = DateTime::getSkyColor();
    glClearColor(color.x, color.y, color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(
    const Player &player,
    const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks
) {
    clear();


    shader->use();
    auto model = glm::mat4(1.0f);
    model = scale(model, glm::vec3(1.0, 1.0, 1.0));

    auto sunPos = DateTime::getSunPos() * 100.0f;
    auto pos = glm::vec3(sunPos.x + player.Position.x, sunPos.y + player.Position.y, sunPos.z + player.Position.z);
    float sunSize = 10.0f;
    model = translate(model, pos);
    model = scale(model, glm::vec3(sunSize, sunSize, sunSize));

    shader->setMat4("model", model);
    shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->setVec3("sunCenter", sunPos);
    shader->setFloat("sunRadius", 5.0f);
    mesh.draw();
    glClear(GL_DEPTH_BUFFER_BIT);

    updateLighting();
    updateProjection(player);

    add_chunk();
    remove_chunks();
    draw_chunks();

    uiShader->use();
    crosshair->draw();


}

void Renderer::add_chunk() {
    if (chunksToAdd.size() == 0) return;
    if (!isReadyToAdd) return;

    ChunkBuilder chunk = chunksToAdd[chunksToAdd.size() - 1];
    int x = chunk.chunk.x;
    int z = chunk.chunk.z;

    auto mesh = ChunkMesh(x, z);
    mesh.positions = chunk.positions;
    mesh.textures = chunk.textures;
    mesh.ambientOcclusions = chunk.ambientOcclusions;
    mesh.updateBuffers();
    chunkMeshes[{x, z}] = mesh;
    chunksToAdd.pop_back();
}

void Renderer::remove_chunks() {
    if (chunksToRemove.size() == 0) return;
    auto p = chunksToRemove[chunksToRemove.size() - 1];
    chunkMeshes.erase(p);
    chunksToRemove.pop_back();
}

void Renderer::draw_chunks() {
    texturePack->use(0);
    instancedShader->use();

    for (auto chunkMeshPair: chunkMeshes) {
        ChunkMesh chunkMesh = chunkMeshPair.second;
        chunkMesh.draw();
    }
}

void Renderer::updateProjection(const Player &player) {
    const glm::mat4 projection = glm::perspective(45.0f, (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 1000.0f);
    const glm::mat4 view = player.camera.GetViewMatrix();

    shader->use();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);

    instancedShader->use();
    instancedShader->setMat4("projection", projection);
    instancedShader->setMat4("view", view);
    instancedShader->setVec3("viewPos", player.camera.Position);

    const glm::mat4 orthoProjection = glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f, -1.0f, 1.0f);
    uiShader->use();
    uiShader->setMat4("projection", orthoProjection);
}

void Renderer::updateLighting() const {
    instancedShader->use();
    instancedShader->setInt("material.diffuse", 0);
    instancedShader->setInt("material.specular", 1);
    instancedShader->setFloat("material.shininess", 32.0f);



    int hour = fmod(glfwGetTime(), DAY_CYCLE);
    // float ambient = hour < 6 ? 0.1f : 0.5f;
    float ambient = 0.3;

    auto lightPos = DateTime::getSunPos();

    instancedShader->setVec3("light.direction", -lightPos);
    instancedShader->setVec3("light.ambient", ambient, ambient, ambient);
    instancedShader->setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
    instancedShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    glm::vec2 uvScale(1.0f / 8, 1.0f / 8);
    instancedShader->setVec2("uvScale", uvScale);
}
