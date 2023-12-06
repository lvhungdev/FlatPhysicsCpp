#pragma once

#include <vector>
#include "Physics/Core/FlatBody.h"

class PhysicWorld
{
public:
    ~PhysicWorld();

    int integrationSteps = 2;

    void integrate(float delta);

    void addBody(FlatBody* body);

    std::vector<FlatBody*> getBodies() const;

private:
    std::vector<FlatBody*> bodies;
};
