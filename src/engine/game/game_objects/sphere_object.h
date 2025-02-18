//
// Created by piotr on 16.02.25.
//

#ifndef SPHERE_OBJECT_H
#define SPHERE_OBJECT_H

#include "i_game_object.h"
#include "../../renderer/geometry/sphere_geometry.h"
#include "../../renderer/materials/basic_material.h"
#include "../../renderer/materials/pbr_material.h"

class SphereObject : public IGameObject {
    public:
    SphereObject() {
        mesh = new Mesh(&SPHERE_GEOMETRY);

        // glm::vec3 ambient = glm::vec3(0.1, 0.8, 2.5);
        // glm::vec3 diffuse = glm::vec3(0.1, 0.8, 2.5);
        // glm::vec3 specular = glm::vec3();
        // float shininess = 0.6f;
        // material = new BasicMaterial(ambient, diffuse, specular, shininess);


        // glm::vec3 albedo = glm::vec3(0.1, 0.8, 2.5);
        //
        // float metallic = 2.0;
        // float roughness = -0.5;
        // float ao = 5.0f;
        // material = new PBRMaterial(albedo, metallic, roughness, ao);

        material = new PBRTextureMaterial();;
    }
};

#endif //SPHERE_OBJECT_H