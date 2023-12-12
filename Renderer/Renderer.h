#pragma once

#include <SDL_render.h>
#include "Physics/Core/FlatVector.h"

class Renderer
{
public:
    explicit Renderer(SDL_Renderer* renderer);

    void drawCircle(const FlatVector& position, float radius, float rotation,
            SDL_Color color = SDL_Color{ 255, 255, 255, 255 });

    void drawPolygon(FlatVector* vertices, int vertexCount, SDL_Color color = SDL_Color{ 255, 255, 255, 255 });

private:
    SDL_Renderer* renderer;
};
