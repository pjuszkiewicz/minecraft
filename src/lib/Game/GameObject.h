//
// Created by Piotr Juszkiewicz on 17/01/2025.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <glm/vec3.hpp>

#include "../Renderer/Material.h"
#include "../Meshes/Mesh.h"

/// Objekt gry który ma swój mesh oraz material, można go narysować.
class GameObject {
public:
    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;

    Material *material;
    Mesh mesh;

    virtual ~GameObject() {};

    /// Rysuje objekt
    virtual void Draw() = 0;

    /// Aktualizuje dane dla objektu
    virtual void Update() = 0;
};



#endif //GAMEOBJECT_H
