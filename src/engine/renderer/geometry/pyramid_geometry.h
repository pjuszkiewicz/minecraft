//
// Created by Piotr Juszkiewicz on 16/02/2025.
//

#ifndef PYRAMID_GEOMETRY_H
#define PYRAMID_GEOMETRY_H

#include <vector>

inline std::vector<float> PYRAMID_GEOMETRY = {
    -0.5f, 0.0f, -0.5f,   0.0f, -1.0f,
     0.5f, 0.0f, -0.5f,   0.0f, -1.0f,
     0.5f, 0.0f,  0.5f,   0.0f, -1.0f,

     0.5f, 0.0f,  0.5f,   0.0f, -1.0f,
    -0.5f, 0.0f,  0.5f,   0.0f, -1.0f,
    -0.5f, 0.0f, -0.5f,   0.0f, -1.0f,

    -0.5f, 0.0f, -0.5f,   0.0f,  0.5f,
     0.5f, 0.0f, -0.5f,   0.0f,  0.5f,
     0.0f, 0.8f,  0.0f,   0.0f,  0.5f,

     0.5f, 0.0f, -0.5f,   0.5f,  0.5f,
     0.5f, 0.0f,  0.5f,   0.5f,  0.5f,
     0.0f, 0.8f,  0.0f,   0.5f,  0.5f,

     0.5f, 0.0f,  0.5f,   0.0f,  0.5f,
    -0.5f, 0.0f,  0.5f,   0.0f,  0.5f,
     0.0f, 0.8f,  0.0f,   0.0f,  0.5f,

    -0.5f, 0.0f,  0.5f,  -0.5f,  0.5f,
    -0.5f, 0.0f, -0.5f,  -0.5f,  0.5f,
     0.0f, 0.8f,  0.0f,  -0.5f,  0.5f,
};

#endif //PYRAMID_GEOMETRY_H
