#pragma once

#include "FlatVector.h"

enum FlatShapeType
{
    Circle,
    Polygon,
};

class FlatShape
{
public:
    FlatShapeType type = FlatShapeType::Circle;

    float radius = 0.0f;

    FlatVector* vertices = nullptr;
    int vertexCount = 0;
};
