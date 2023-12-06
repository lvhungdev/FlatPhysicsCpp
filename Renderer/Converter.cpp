#include "Converter.h"
#include "Settings.h"

FlatVector Converter::convert(const SDL_Point& point)
{
    return FlatVector((float)point.x / Settings::SCALE_FACTOR,
            (float)(Settings::SCREEN_HEIGHT - point.y) / Settings::SCALE_FACTOR);
}

SDL_Point Converter::convert(const FlatVector& vector)
{
    return SDL_Point{ (int)(vector.x * Settings::SCALE_FACTOR),
            (int)(Settings::SCREEN_HEIGHT - vector.y * Settings::SCALE_FACTOR) };
}
