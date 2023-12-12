#include "MathUtils.h"

bool MathUtils::nearlyEqual(float numA, float numB)
{
    return MathUtils::abs(numA - numB) < 0.00001f;
}

float MathUtils::abs(float number)
{
    if (number < 0.0f)
    {
        return -number;
    } else
    {
        return number;
    }
}
