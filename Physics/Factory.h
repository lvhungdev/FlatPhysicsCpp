#pragma once

#include "Core/FlatBody.h"

class Factory
{
public:
    static FlatBody* createCircleBody(const FlatVector& position, float radius);

    static FlatBody* createBoxBody(const FlatVector& position, float width, float height);
    static FlatBody* createStaticBoxBody(const FlatVector& position, float width, float height);
};
