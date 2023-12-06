#pragma once

#include "FlatVector.h"

class FlatBody
{
public:
    FlatVector position;
    FlatVector linearVelocity;
    FlatVector linearAcceleration;
    float inverseMass = 1.0f;

    void integrate(float delta);
};
