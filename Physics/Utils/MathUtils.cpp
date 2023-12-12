#include "MathUtils.h"
#include <cmath>

bool MathUtils::nearlyEqual(float numA, float numB)
{
	return abs(numA - numB) < 0.00001f;
}
