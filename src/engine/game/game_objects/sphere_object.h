//
// Created by piotr on 16.02.25.
//

#ifndef SPHERE_OBJECT_H
#define SPHERE_OBJECT_H

#include "i_game_object.h"
#include "../../renderer/geometry/sphere_geometry.h"
#include "../../renderer/materials/basic_material.h"

class SphereObject : public IGameObject {
    public:
    SphereObject() {
        mesh = new Mesh(&SPHERE_GEOMETRY);

        glm::vec3 ambient = glm::vec3(0.25f, 0.25f, 0.25f);
        glm::vec3 diffuse = glm::vec3(0.4, 0.4, 0.4);
        glm::vec3 specular = glm::vec3(0.774597f, 0.774597f, 0.774597f);
        float shininess = 0.6f;
        material = new BasicMaterial(ambient, diffuse, specular, shininess);
    }

};

#endif //SPHERE_OBJECT_H