#pragma once

#include "FlatVector.h"
#include "FlatShape.h"

class FlatBody
{
public:
    FlatBody(const FlatShape& shape, const FlatVector& position);

    ~FlatBody();

    FlatVector position;
    FlatVector linearVelocity;
    FlatVector linearAcceleration;
    float inverseMass = 0.6f;

    float rotation = 0.0f;
    float angularVelocity = 0.0f;
    float inverseInertia = 1.0f;

    FlatShape shape;
    FlatVector* vertices = nullptr;
    int vertexCount = 0;

    float restitution = 0.9f;

    void integrate(float delta);

    void applyImpulse(const FlatVector& impulse);

    void applyImpulse(const FlatVector& impulse, const FlatVector& contactPoint);

private:
    void updateVertices() const;
};
