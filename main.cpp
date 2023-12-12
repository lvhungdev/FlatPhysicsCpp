#include <SDL.h>
#include "Renderer/Settings.h"
#include "Renderer/Renderer.h"
#include "Renderer/Converter.h"
#include "Physics/PhysicWorld.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Flat Physics!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* sdlRenderer = SDL_CreateRenderer(window, -1, 0);

    Renderer renderer = Renderer(sdlRenderer);

    FlatBody* obstacle = new FlatBody();
    obstacle->position = FlatVector(4.0f, 4.0f);
    obstacle->flatShape.type = FlatShapeType::Circle;
    obstacle->flatShape.radius = 0.6f;
    obstacle->inverseMass = 0.0f;
    obstacle->inverseInertia = 0.0f;

    PhysicWorld world = PhysicWorld();
    world.gravity = FlatVector(0.0f, -9.8f);
    world.addBody(obstacle);

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

                FlatBody* body = new FlatBody();
                body->position = FlatVector(pos.x, pos.y);
                body->flatShape.type = FlatShapeType::Circle;
                body->flatShape.radius = 0.2f;

                world.addBody(body);
            }
        }

        SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
        SDL_RenderClear(sdlRenderer);

        for (FlatBody* item : world.bodies)
        {
            renderer.drawCircle(item->position, item->flatShape.radius, item->rotation);
        }

        SDL_RenderPresent(sdlRenderer);

        ticks = SDL_GetTicks() - frameStart;

        if (ticks < TICKS_PER_FRAME)
        {
            SDL_Delay(TICKS_PER_FRAME - ticks);
            ticks = TICKS_PER_FRAME;
        }

        world.integrate(delta);

        for (FlatBody* item : world.bodies)
        {
            if (item->position.y < 0.2f)
            {
                item->position.y = 0.2f;
                item->linearVelocity.y *= -1;
            }

            if (item->position.x < 0.2f)
            {
                item->position.x = 0.2f;
                item->linearVelocity.x *= -1;
            }

            if (item->position.x > (float)Settings::SCREEN_WIDTH / Settings::SCALE_FACTOR - 0.2f)
            {
                item->position.x = (float)Settings::SCREEN_WIDTH / Settings::SCALE_FACTOR - 0.2f;
                item->linearVelocity.x *= -1;
            }
        }
    }

    return 0;
}
