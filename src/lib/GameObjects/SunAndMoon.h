//
// Created by Piotr Juszkiewicz on 17/01/2025.
//

#ifndef SUNANDMOON_H
#define SUNANDMOON_H
#include "../Game/GameObject.h"
#include "../Materials/SunAndMoonMaterial.h"


/// GameObject słońca i księżyca
class SunAndMoon : public GameObject {
public:
    /// Initializuje pozycje mesh i materiał
    SunAndMoon();

    ~SunAndMoon() override {
    }

    /// Rysuje objekt
    void Draw() override;

    void Update() override {};
};


#endif //SUNANDMOON_H
