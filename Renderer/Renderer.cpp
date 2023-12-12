#include "Renderer.h"
#include "Converter.h"
#include "Settings.h"

Renderer::Renderer(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

void Renderer::drawCircle(const FlatVector& position, float radius, float rotation, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_Point centre = Converter::convert(position);
    int centreX = centre.x;
    int centreY = centre.y;

    const int convertedRadius = (int)(radius * Settings::SCALE_FACTOR);
    const int diameter = (int)(convertedRadius * 2);

    int x = (int)(convertedRadius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y)
    {
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }

    FlatVector rotatedLine = FlatVector(1, 0).getRotated(rotation);
    SDL_Point rotatedPoint = Converter::convert(position + rotatedLine * radius);

    SDL_RenderDrawLine(renderer, centreX, centreY, rotatedPoint.x, rotatedPoint.y);
}

void Renderer::drawPolygon(FlatVector* vertices, int vertexCount, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_Point points[4];

    for (int i = 0; i < vertexCount; i++)
    {
        points[i] = Converter::convert(vertices[i]);
    }

    SDL_RenderDrawLines(renderer, points, vertexCount);
    SDL_RenderDrawLine(renderer, points[0].x, points[0].y, points[vertexCount - 1].x, points[vertexCount - 1].y);
}
