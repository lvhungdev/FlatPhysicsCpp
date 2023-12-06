#include <SDL.h>
#include "Renderer/Settings.h"
#include "Renderer/Renderer.h"
#include "Physics/PhysicWorld.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Flat Physics!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* sdlRenderer = SDL_CreateRenderer(window, -1, 0);

    Renderer renderer = Renderer(sdlRenderer);

    FlatBody* body = new FlatBody();
    body->position = FlatVector(2.0f, 2.0f);

    PhysicWorld world = PhysicWorld();
    world.addBody(body);

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
        }

        SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
        SDL_RenderClear(sdlRenderer);

        for (FlatBody* item : world.getBodies())
        {
            renderer.drawCircle(item->position, 0.3f);
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
