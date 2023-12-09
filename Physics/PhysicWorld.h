#pragma once

#include <vector>
#include "Physics/Core/FlatBody.h"

class PhysicWorld
{
public:
    ~PhysicWorld();

    FlatVector gravity;
    int integrationSteps = 2;
    std::vector<FlatBody*> bodies;

    void integrate(float delta);

    void addBody(FlatBody* body);
};
