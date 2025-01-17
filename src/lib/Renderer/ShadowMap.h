//
// Created by Piotr Juszkiewicz on 15/01/2025.
//

#ifndef SHADOWMAP_H
#define SHADOWMAP_H


#include <GLFW/glfw3.h>

class ShadowMap {
public:
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMapFBO;
    unsigned int depthMap;

    ShadowMap();
    void use(int textureUnit) const;
};


#endif //SHADOWMAP_H
