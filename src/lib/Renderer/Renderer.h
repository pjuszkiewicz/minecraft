#ifndef RENDERER_H
#define RENDERER_H

#include "../../lib/Renderer/Texture.h"
#include "../../lib/Map/PairHash.h"
#include "../../lib/Renderer/Shader.h"
#include "../../lib/Player/Player.h"
#include "../../lib/World/Chunk.h"
#include <unordered_map>

#include <vector>

#include "../Meshes/ChunkBuilder.h"
#include "../Meshes/CrosshairMesh.h"
#include "../Meshes/ChunkMesh.h"
#include "../Meshes/Mesh.h"
#include "../Constants.h"
#include "../../../vendor/glad/glad.h"

#include <glm/glm.hpp> // Używając GLM dla vec3
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Materials/SunAndMoonMaterial.h"

#include "ShadowMap.h"
#include "../GameObjects/CrosshairObject.h"
#include "../GameObjects/SunAndMoon.h"
#include "../GameObjects/WorldObject.h"
#include "../Materials/CrosshairMaterial.h"
#include "../Materials/ShadowMappingMaterial.h"
#include "../Materials/WorldMaterial.h"
#include "../Materials/DepthTestMaterial.h"

class Renderer {
public:
    SunAndMoon sunAndMoon;
    WorldObject worldObject;
    CrosshairObject crosshairObject;

    Renderer();

    void Clear();

    void Draw(const Player &player);

    void UpdateProjection(const Player &player) const;
};

#endif //RENDERER_H
