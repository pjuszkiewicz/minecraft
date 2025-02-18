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
        glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);;
        glm::vec3 scale = glm::vec3(1, 1, 1);

        Mesh *mesh;
        IMaterial *material;

    glm::mat4 getTransformMatrix() const {
        glm::mat4 mat = glm::translate(glm::mat4(1.0f), position);
        mat = glm::rotate(mat, rotation.x, glm::vec3(1, 0, 0));
        mat = glm::rotate(mat, rotation.y, glm::vec3(0, 1, 0));
        mat = glm::rotate(mat, rotation.z, glm::vec3(0, 0, 1));
        mat = glm::scale(mat, scale);
        return mat;
    }

    virtual void draw() {
        material->use();
        mesh->draw();
    };
};



#endif //GAME_OBJECT_H
