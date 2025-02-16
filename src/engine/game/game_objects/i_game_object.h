//
// Created by piotr on 16.02.25.
//

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../../renderer/mesh.h"
#include "../../renderer/materials/i_material.h"


class IGameObject {
    public:
        glm::vec3 position = glm::vec3(0, 100, 0);
        Mesh *mesh;
        IMaterial *material;

    virtual void draw() {
        material->use();
        mesh->draw();
    };
};



#endif //GAME_OBJECT_H
