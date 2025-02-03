//
// Created by Piotr Juszkiewicz on 28/01/2025.
//

#include "CrosshairObject.h"

#include "../Materials/CrosshairMaterial.h"

CrosshairObject::CrosshairObject() {
    Position = glm::vec3(0, 0, 0);
    Rotation = glm::vec3(0, 0, 0);
    Scale = glm::vec3(1, 1, 1);
    material = new CrosshairMaterial();
    crosshair = new CrosshairMesh();
}

void CrosshairObject::Draw() {
    material->Use(0);
    crosshair->draw();
}