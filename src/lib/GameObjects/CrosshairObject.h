//
// Created by Piotr Juszkiewicz on 28/01/2025.
//

#ifndef CROSSHAIROBJECT_H
#define CROSSHAIROBJECT_H

#include "../Game/GameObject.h"
#include "../Meshes/CrosshairMesh.h"


class CrosshairObject : public GameObject {
public:
    CrosshairMesh *crosshair;
    CrosshairObject();
    void Draw() override;
};



#endif //CROSSHAIROBJECT_H
