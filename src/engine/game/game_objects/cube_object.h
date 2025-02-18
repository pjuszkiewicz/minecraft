//
// Created by piotr on 16.02.25.
//

#ifndef CUBE_OBJECT_H
#define CUBE_OBJECT_H

#include "i_game_object.h"
#include "../../renderer/geometry/cube_geometry.h"
#include "../../renderer/materials/basic_material.h"
#include "../../renderer/materials/pbr_material.h"
#include "../../renderer/materials/pbr_texture_material.h"

class CubeObject : public IGameObject {
    public:
    CubeObject() {
        mesh = new Mesh(&CUBE_GEOMETRY);

        // glm::vec3 ambient = glm::vec3(0.25f, 0.25f, 0.25f);
        // glm::vec3 diffuse = glm::vec3(0.4, 0.4, 0.4);
        // glm::vec3 specular = glm::vec3(0.774597f, 0.774597f, 0.774597f);
        // float shininess = 0.6f;
        // material = new BasicMaterial(ambient, diffuse, specular, shininess);

        glm::vec3 albedo = glm::vec3(0.2, 0.9, 0.2);
        float metallic = 1.0;
        float roughness = 0.1;
        float ao = 0.0f;
        material = new PBRTextureMaterial();;
    }

};



#endif //CUBE_OBJECT_H
