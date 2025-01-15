#include "../../lib/Renderer/Renderer.h"
#include <unordered_set>
#include <thread>

float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

glm::vec3 rotateAroundAxis(const glm::vec3& point, float angle, const glm::vec3& axis) {
    glm::vec3 normalizedAxis = glm::normalize(axis);

    // Wzór Rodrigueza
    glm::vec3 rotatedPoint =
        point * cos(angle) +
        glm::cross(normalizedAxis, point) * sin(angle) +
        normalizedAxis * glm::dot(normalizedAxis, point) * (1 - cos(angle));

    return rotatedPoint;
}

// Funkcja obliczająca punkt na okręgu w przestrzeni 3D
glm::vec3 circularOrbit(float t, float radius, float angularSpeed, const glm::vec3& center, const glm::vec3& normal) {
    // Oblicz kąt w radianach
    float angle = angularSpeed * t;

    // Punkt w bazowej płaszczyźnie XY (przy założeniu normalnej {0, 0, 1})
    glm::vec3 pointOnCircle = glm::vec3(radius * cos(angle), radius * sin(angle), 0.0f);

    // Jeśli normalna to {0, 0, 1}, nie potrzeba obrotu
    if (normal == glm::vec3(0, 0, 1)) {
        return center + pointOnCircle;
    }

    // Obróć punkt na okręgu zgodnie z normalą
    glm::vec3 rotatedPoint = rotateAroundAxis(pointOnCircle, acos(glm::dot(glm::vec3(0, 0, 1), glm::normalize(normal))),
                                              glm::cross(glm::vec3(0, 0, 1), glm::normalize(normal)));

    // Dodaj przesunięcie środka
    return center + rotatedPoint;
}

Renderer::Renderer() {
    const std::string ASSETS_PATH = "/Users/piotr/Development/C++/minecraft/src/assets";
    // const std::string ASSETS_PATH = "/home/piotr/Development/C++/minecraft/src/assets";

    shader = new Shader((ASSETS_PATH + "/shaders/example/vertex.vs").c_str(),
                        (ASSETS_PATH + "/shaders/example/fragment.fs").c_str());
    instancedShader = new Shader((ASSETS_PATH + "/shaders/example/instanced.vs").c_str(),
                                 (ASSETS_PATH + "/shaders/example/instanced.fs").c_str());
    uiShader = new Shader((ASSETS_PATH + "/shaders/example/ui_vertex.vs").c_str(),
                          (ASSETS_PATH + "/shaders/example/ui_fragment.fs").c_str());
    texturePack = new Texture((ASSETS_PATH + "/textures/texturepack.png").c_str(), GL_RGBA);
    crosshair = new Crosshair();


}

/// Czyści
void Renderer::clear() {
    glm::vec3 color = getBackgroundColor();

    glClearColor(color.x, color.y, color.z, 1.0f);
    // glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/// Oblicza kolor tła na podstawie godziny z glfwGetTime()
/// @return Zwraca wektor z zmiennymi vec3(r, g, b)
glm::vec3 Renderer::getBackgroundColor() {
    float timeOfDay = fmod(glfwGetTime(), DAY_CYCLE);
    float r, g, b;

    if (timeOfDay < 6.0f) { // Noc
        r = lerp(0.05f, 0.1f, timeOfDay / 6.0f); // Od ciemnoniebieskiego do jaśniejszego
        g = lerp(0.05f, 0.1f, timeOfDay / 6.0f);
        b = lerp(0.1f, 0.2f, timeOfDay / 6.0f);
    } else if (timeOfDay < 12.0f) { // Poranek
        float t = (timeOfDay - 6.0f) / 6.0f;
        r = lerp(0.1f, 0.5f, t); // Od jaśniejszego do jasnoniebieskiego
        g = lerp(0.1f, 0.7f, t);
        b = lerp(0.2f, 1.0f, t);
    } else if (timeOfDay < 18.0f) { // Dzień
        r = 0.5f; // Jasnoniebieskie niebo
        g = 0.7f;
        b = 1.0f;
    } else if (timeOfDay < 24.0f) { // Wieczór
        float t = (timeOfDay - 18.0f) / 6.0f;
        r = lerp(0.5f, 0.9f, t); // Przejście do pomarańczowego
        g = lerp(0.7f, 0.3f, t);
        b = lerp(1.0f, 0.1f, t);
    }

    return glm::vec3(r, g, b);
}

void Renderer::draw(
    const Player &player,
    const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks
) {
    clear();

    update_shader(player);

    add_chunk();
    remove_chunks();
    draw_chunks();

    uiShader->use();
    crosshair->draw();

    shader->use();
    auto model = glm::mat4(1.0f);
    model = scale(model, glm::vec3(3.0, 3.0, 3.0));

    float angularSpeed = glm::radians(360.0f);
    glm::vec3 lightDirection = circularOrbit(glfwGetTime() / DAY_CYCLE, 10, angularSpeed, glm::vec3(0, 0, 0), glm::vec3(0, 1, 1));
    auto offset = -lightDirection + player.Position;
    // model = translate(model, lightDirection);
    model = translate(model, offset);

    shader->setMat4("model", model);
    mesh.draw();

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

void Renderer::update_shader(const Player &player) const {
    glm::mat4 projection = glm::perspective(45.0f, (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 1000.0f);
    glm::mat4 view = player.camera.GetViewMatrix();

    shader->use();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);

    instancedShader->use();
    instancedShader->setMat4("projection", projection);
    instancedShader->setMat4("view", view);
    instancedShader->setVec3("viewPos", player.camera.Position);

    instancedShader->setInt("material.diffuse", 0);
    instancedShader->setInt("material.specular", 1);
    instancedShader->setFloat("material.shininess", 32.0f);

    float angularSpeed = glm::radians(360.0f);
    glm::vec3 lightDirection = -glm::normalize(circularOrbit(glfwGetTime() / DAY_CYCLE, 10, angularSpeed, glm::vec3(0, 0, 0), glm::vec3(0, 1, 1)));
    int hour = fmod(glfwGetTime(), DAY_CYCLE);
    // float ambient = hour < 6 ? 0.1f : 0.5f;
    float ambient = 0.3;

    instancedShader->setVec3("light.direction", lightDirection.x, lightDirection.y, lightDirection.z);
    instancedShader->setVec3("light.ambient", ambient, ambient, ambient);
    instancedShader->setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
    instancedShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    glm::vec2 uvScale(1.0f / 8, 1.0f / 8);
    instancedShader->setVec2("uvScale", uvScale);

    // UI
    glm::mat4 orthoProjection = glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f, -1.0f, 1.0f);
    uiShader->use();
    uiShader->setMat4("projection", orthoProjection);
}
