#pragma once

#include "FlatVector.h"
#include "FlatShape.h"

class FlatBody
{
public:
    FlatVector position;
    FlatVector linearVelocity;
    FlatVector linearAcceleration;
    float inverseMass = 1.0f;

    float rotation = 0.0f;
    float angularVelocity = 0.0f;
    float inverseInertia = 1.0f;

    FlatShape flatShape;

    float restitution = 0.9f;

    void integrate(float delta);

    void applyImpulse(const FlatVector& impulse);

    void applyImpulse(const FlatVector& impulse, const FlatVector& contactPoint);
};
