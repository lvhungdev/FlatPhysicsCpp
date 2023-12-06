#pragma once

#include <SDL_rect.h>
#include "Physics/Core/FlatVector.h"

class Converter
{
public:
    static FlatVector convert(const SDL_Point& point);

    static SDL_Point convert(const FlatVector& vector);
};
