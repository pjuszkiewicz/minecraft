//
// Created by Piotr Juszkiewicz on 28/01/2025.
//

#ifndef CROSSHAIROBJECT_H
#define CROSSHAIROBJECT_H

#include "../Game/GameObject.h"
#include "../Meshes/CrosshairMesh.h"

/// GameObject celownika
class CrosshairObject : public GameObject {
public:
    CrosshairMesh *crosshair; /// Mesh celownika

    /// Initializuje pozycje mesh i materiał
    CrosshairObject();

    ~CrosshairObject() override {
        delete crosshair;
    }

    /// Rysuje objekt
    void Draw() override;

    void Update() override {};
};



#endif //CROSSHAIROBJECT_H
