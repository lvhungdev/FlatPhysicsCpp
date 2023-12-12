#include <SDL.h>
#include "Renderer/Settings.h"
#include "Renderer/Renderer.h"
#include "Renderer/Converter.h"
#include "Physics/PhysicWorld.h"
#include "Physics/Factory.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Flat Physics!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* sdlRenderer = SDL_CreateRenderer(window, -1, 0);

    Renderer renderer = Renderer(sdlRenderer);

    FlatBody* obstacle1 = Factory::createStaticBoxBody({ 6.0f, 4.0f }, 3.0f, 0.2f);
    obstacle1->rotation = 0.6f;

    FlatBody* obstacle2 = Factory::createStaticBoxBody({ 2.0f, 4.0f }, 3.0f, 0.2f);
    obstacle2->rotation = -1.0f;

    FlatBody* ground = Factory::createStaticBoxBody({ 4.0f, 0.0f }, 8.0f, 0.2f);
    FlatBody* leftWall = Factory::createStaticBoxBody({ 0.0f, 0.0f }, 0.2f, 12.0f);
    FlatBody* rightWall = Factory::createStaticBoxBody({ 8.0f, 0.0f }, 0.2f, 12.0f);

    PhysicWorld world = PhysicWorld();
    world.gravity = FlatVector(0.0f, -9.8f);
    world.addBody(obstacle1);
    world.addBody(obstacle2);
    world.addBody(leftWall);
    world.addBody(rightWall);
    world.addBody(ground);

    const int FPS = 60;
    const int TICKS_PER_FRAME = 1000 / FPS;

    Uint32 frameStart;
    Uint32 ticks = 0;
    float delta;

    while (true)
    {
        frameStart = SDL_GetTicks();
        delta = (float)ticks / 1000;

        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
            {
                break;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX;
                int mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                FlatVector pos = Converter::convert(SDL_Point{ mouseX, mouseY });

                FlatBody* body = Factory::createBoxBody(pos, 0.4f, 0.4f);
                world.addBody(body);
            }
        }

        SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
        SDL_RenderClear(sdlRenderer);

        for (FlatBody* item : world.bodies)
        {
            if (item->shape.type == FlatShapeType::Circle)
            {
                renderer.drawCircle(item->position, item->shape.radius, item->rotation);
            } else if (item->shape.type == FlatShapeType::Polygon)
            {
                renderer.drawPolygon(item->vertices, item->vertexCount);
            }
        }

        SDL_RenderPresent(sdlRenderer);

        ticks = SDL_GetTicks() - frameStart;

        if (ticks < TICKS_PER_FRAME)
        {
            SDL_Delay(TICKS_PER_FRAME - ticks);
            ticks = TICKS_PER_FRAME;
        }

        world.integrate(delta);
    }

    return 0;
}
