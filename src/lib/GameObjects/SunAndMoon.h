//
// Created by Piotr Juszkiewicz on 17/01/2025.
//

#ifndef SUNANDMOON_H
#define SUNANDMOON_H
#include "../Game/GameObject.h"
#include "../Materials/SunAndMoonMaterial.h"


class SunAndMoon : public GameObject {
public:
    SunAndMoon();
    void Draw() override;
};


#endif //SUNANDMOON_H
