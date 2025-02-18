//
// Created by Piotr Juszkiewicz on 16/02/2025.
//

#ifndef PLANE_OBJECT_H
#define PLANE_OBJECT_H
#include "i_game_object.h"
#include "../../renderer/materials/basic_material.h"
#include "../../renderer/geometry/plane_geometry.h"

class PlaneObject : public IGameObject {
    public:
    PlaneObject() {
        mesh = new Mesh(&PLANE_GEOMETRY);

        glm::vec3 ambient = glm::vec3(0.25f, 0.25f, 0.25f);
        glm::vec3 diffuse = glm::vec3(0.4, 0.4, 0.4);
        glm::vec3 specular = glm::vec3(0.774597f, 0.774597f, 0.774597f);
        float shininess = 0.6f;
        material = new BasicMaterial(ambient, diffuse, specular, shininess);
    }
};



#endif //PLANE_OBJECT_H
