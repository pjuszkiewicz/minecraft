//
// Created by Piotr Juszkiewicz on 17/01/2025.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <glm/vec3.hpp>

#include "../Renderer/Material.h"
#include "../Meshes/Mesh.h"

class GameObject {
public:
    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;

    Material *material;
    Mesh mesh;

    virtual void Draw() = 0;
};



#endif //GAMEOBJECT_H
