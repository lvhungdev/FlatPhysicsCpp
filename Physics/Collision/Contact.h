#pragma once

#include "Physics/Core/FlatVector.h"
#include "Physics/Core/FlatBody.h"

class Contact
{
public:
    ~Contact();

    FlatBody* bodyA = nullptr;
    FlatBody* bodyB = nullptr;

    FlatVector normal;
    float penetration = 0.0f;

    FlatVector* point1 = nullptr;
    FlatVector* point2 = nullptr;

    void resolve();

private:
    void resolvePenetration() const;

    void resolveVelocity() const;
};
