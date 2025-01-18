//
// Created by Piotr Juszkiewicz on 11/01/2025.
//

#ifndef CROSSHAIR_H
#define CROSSHAIR_H
#include "../../../vendor/glad/glad.h"


class CrosshairMesh {

public:
    unsigned int VAO, VBO;

    CrosshairMesh();

    void draw() const;
};


#endif //CROSSHAIR_H
