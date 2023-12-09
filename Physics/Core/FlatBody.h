#pragma once

#include "FlatVector.h"

class FlatBody
{
public:
    FlatVector position;
    FlatVector linearVelocity;
    FlatVector linearAcceleration;
    float inverseMass = 1.0f;

    float restitution = 0.9f;

    void integrate(float delta);

    void applyImpulse(const FlatVector& impulse);
};
