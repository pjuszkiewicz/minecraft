#ifndef RENDERER_H
#define RENDERER_H

#include "../../engine/renderer/texture.h"
#include "../../engine/renderer/shader.h"
#include "../../engine/player/player.h"
#include <unordered_map>

#include <vector>

#include "mesh.h"
#include "../constants.h"
#include "../../../vendor/glad/glad.h"

#include <glm/glm.hpp> // Używając GLM dla vec3
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "geometry/cube_geometry.h"
#include "geometry/plane_geometry.h"
#include "../utils/assets_manager.h"
#include "materials/basic_material.h"

class Renderer {
public:
    Renderer();

    Mesh *mesh;
    BasicMaterial *material;

    void clear();

    void draw(const Player &player);

    void updateProjection(const Player &player) const;
};

#endif //RENDERER_H
